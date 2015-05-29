//////
/////                        -=[ ForceLibrary.dll ]=-
////                                by yoda/f2f
///                                version: 1.2
//
//     You are able to use *parts* of this source code in your own programs 
//     if you mention my name.
//     Please report any bugs/comments/suggestions to yoda_f2f@gmx.net
//     Have fun.
//

#include <windows.h>
#include <tlhelp32.h>
#include <stddef.h>
#include "th32.h"

#pragma pack(1) // very important !

// this code structs load the dll
typedef struct {
    //BYTE  Int3;    
    BYTE  PushOpc;           // 0x68     = push (dword)
    DWORD PushAddr;          // address of dll name
    BYTE  CallOpc;           // 0xE8     = call (dword)
    DWORD CallAddr;          // address of LoadLibraryAPI
    WORD  jmp_$;             // 0xEBFE   = jmp eip
    char  LibPath[MAX_PATH]; // path of the dll to load
} sLibLoadCode;

typedef struct {
    //BYTE  Int3;    
    BYTE  PushOpc;           // 0x68     = push (dword)
    DWORD PushAddr;          // address of dll name
    BYTE  CallOpc;           // 0xE8     = call (dword)
    DWORD CallAddr;          // address of LoadLibraryAPI
    BYTE  RetOpc;            // 0xC2     = ret (word)
    WORD  RetValue;          // return number
    char  LibPath[MAX_PATH]; // path of the dll to load
} sLibLoadCodeNT;

typedef struct {
    BYTE  PushOpc;      // 0x68 = push (dword)
    DWORD PushAddr;     // address of dll name
    BYTE  CallOpc;      // 0xE8 = call (dword)
    DWORD CallAddr;     // address of LoadLibraryAPI
    BYTE  Int3;         // end of code
    char  LibPath[256]; // path of the dll to load
} sLibLoadCodeDBG;

typedef struct {
    DWORD  dwImageBase;
    DWORD  dwSizeOfImage;
    DWORD  dwEntryPointVA;
} sProcessPEInfo;

typedef DWORD(WINAPI* _CodeEntry)(PVOID);

// the functions
BOOL   InitCodeStruct(sLibLoadCode *LibLoaderCode,
    sLibLoadCodeNT *LibLoaderCodeNT,
    CHAR* szTargetLib,
    DWORD dwCodeStart);
DWORD  GetProcessEntryPoint(DWORD PID);
BOOL   ForceLibrary95(const CHAR* szLibraryPath, PROCESS_INFORMATION* pProcInfo);
BOOL   ForceLibraryNT(const CHAR* szLibraryPath, PROCESS_INFORMATION* pProcInfo);

// constants
const DWORD                     LOADCODESIZEDBG = sizeof(sLibLoadCodeDBG);
const DWORD                     HEADER_SIZE = 0x2000;
const BYTE                      Int3 = 0xCC;

// global variables
sLibLoadCodeDBG           LibLoadCodeDBG;
DWORD                     dwLibBase;
DWORD                     dwCodeStart, dwCodeEnd, dwBytesWritten, dwBytesRead;
CONTEXT                   TestRegs;

VOID*                     pCodeEntry;
DWORD                     dwOldProt, dwNewProt;
CONTEXT                   Regs, InitRegs;
BYTE                      bOrgEntry;

DWORD ForceLibrary(const CHAR* szLibraryPath, PROCESS_INFORMATION* pProcInfo) {
    DWORD dwWinVer = GetVersion();

    // get the highest bit
    dwWinVer = dwWinVer >> 31;

    if (!dwWinVer)
        if (ForceLibraryNT(szLibraryPath, pProcInfo))
            return dwLibBase;
        else
            return 0;
    else
        if (ForceLibrary95(szLibraryPath, pProcInfo))
            return dwLibBase;
        else
            return 0;
}

BOOL InitCodeStruct(sLibLoadCode *LibLoaderCode,
    sLibLoadCodeNT *LibLoaderCodeNT,
    const CHAR* szTargetLib,
    DWORD dwCodeStart) {
    DWORD dwLoadLibApiAddr;

    dwLoadLibApiAddr = (DWORD)GetProcAddress(
        GetModuleHandle("kernel32.dll"),
        "LoadLibraryA");
    if (!dwLoadLibApiAddr)
        return FALSE;

    if (LibLoaderCode) {
        //LibLoaderCode->Int3             = Int3;
        LibLoaderCode->PushOpc = 0x68;
        LibLoaderCode->CallOpc = 0xE8;
        LibLoaderCode->CallAddr = dwLoadLibApiAddr - dwCodeStart -
            offsetof(sLibLoadCode, jmp_$);
        strcpy(LibLoaderCode->LibPath, szTargetLib);
        LibLoaderCode->PushAddr = dwCodeStart + offsetof(sLibLoadCode, LibPath);
        LibLoaderCode->jmp_$ = 0xFEEB;
    } else {
        //LibLoaderCodeNT->Int3           = Int3;
        LibLoaderCodeNT->PushOpc = 0x68;
        LibLoaderCodeNT->CallOpc = 0xE8;
        LibLoaderCodeNT->CallAddr = dwLoadLibApiAddr - dwCodeStart -
            offsetof(sLibLoadCodeNT, RetOpc);
        strcpy(LibLoaderCodeNT->LibPath, szTargetLib);
        LibLoaderCodeNT->PushAddr = dwCodeStart + offsetof(sLibLoadCodeNT, LibPath);
        LibLoaderCodeNT->RetOpc = 0xC2;
        LibLoaderCodeNT->RetValue = 0x0004;
    }
    return TRUE;
}

// returns...
// 0 - error
DWORD GetProcessEntryPoint(DWORD PID) {
    HANDLE          hSnap;
    MODULEENTRY32   ModuleInfo;
    PROCESSENTRY32  ProcInfo;
    sProcessPEInfo  ProcPEInfo;
    CHAR            ProcPath[256];
    DWORD           dwMemSize, dwPEHeaderAddr;
    VOID*           pHeader;
    HANDLE          hProc;

    // get ToolHelp32 addresses
    if (!GetTh32())
        return FALSE;

    // I - get the process filename
    hSnap = _CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE)
        return 0;

    // init the ProcInfo struct
    ZeroMemory(&ProcInfo, sizeof(ProcInfo));
    ProcInfo.dwSize = sizeof(ProcInfo);

    // find the to the PID corresponding file path
    _Process32First(hSnap, &ProcInfo);
    ProcPath[0] = 0;
    while (_Process32Next(hSnap, &ProcInfo))
        if (ProcInfo.th32ProcessID == PID)
            strcpy((LPTSTR)&ProcPath, ProcInfo.szExeFile);
    CloseHandle(hSnap);
    if (ProcPath[0] == 0)
        return 0;

    // II - find the ImageBase/SizeOfImage
    hSnap = _CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
    if (hSnap == INVALID_HANDLE_VALUE)
        return 0;

    // init the ModuleInfo and the ProcPEInfo struct
    ZeroMemory(&ModuleInfo, sizeof(ModuleInfo));
    ModuleInfo.dwSize = sizeof(ModuleInfo);
    ZeroMemory(&ProcPEInfo, sizeof(ProcPEInfo));

    _Module32First(hSnap, &ModuleInfo);
    if (stricmp((LPCTSTR)&ModuleInfo.szExePath, (LPCTSTR)&ProcPath) == 0) {
        ProcPEInfo.dwImageBase = (DWORD)ModuleInfo.modBaseAddr;
        ProcPEInfo.dwSizeOfImage = ModuleInfo.modBaseSize;
    }
    while (_Module32Next(hSnap, &ModuleInfo)) {
        if (stricmp((LPCTSTR)&ModuleInfo.szExePath, (LPCTSTR)&ProcPath) == 0) {
            ProcPEInfo.dwImageBase = (DWORD)ModuleInfo.modBaseAddr;
            ProcPEInfo.dwSizeOfImage = ModuleInfo.modBaseSize;
        }
    }
    CloseHandle(hSnap);
    if (ProcPEInfo.dwImageBase == 0)
        return 0;

    // get the EntryPoint
    if (ProcPEInfo.dwSizeOfImage < HEADER_SIZE)
        dwMemSize = ProcPEInfo.dwSizeOfImage;
    else
        dwMemSize = HEADER_SIZE;
    if (!(hProc = OpenProcess(PROCESS_VM_READ, FALSE, PID)))
        return 0;
    if (!(pHeader = GlobalAlloc(GMEM_FIXED, dwMemSize)))
        return 0;
    if (!ReadProcessMemory(
        hProc,
        (PVOID)ProcPEInfo.dwImageBase,
        pHeader,
        dwMemSize,
        &dwBytesRead)) {
        GlobalFree(pHeader);
        return 0;
    }
    if (((PIMAGE_DOS_HEADER)pHeader)->e_magic != IMAGE_DOS_SIGNATURE) {
        GlobalFree(pHeader);
        return 0;
    }
    dwPEHeaderAddr = ((PIMAGE_DOS_HEADER)pHeader)->e_lfanew;
    if (((PIMAGE_NT_HEADERS)(dwPEHeaderAddr + (DWORD)pHeader))->Signature !=
        IMAGE_NT_SIGNATURE) {
        GlobalFree(pHeader);
        return 0;
    }
    ProcPEInfo.dwEntryPointVA = ((PIMAGE_NT_HEADERS)(dwPEHeaderAddr + (DWORD)pHeader))->OptionalHeader \
        .AddressOfEntryPoint + ProcPEInfo.dwImageBase;
    GlobalFree(pHeader);
    return ProcPEInfo.dwEntryPointVA;
}

BOOL ForceLibrary95(const char* szLibraryPath, PROCESS_INFORMATION* pProcInfo) {
    DWORD            dwEntryPoint, dwEWRProt;
    sLibLoadCode     LibLoadCode;

    InitRegs.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;
    if (!GetThreadContext(pProcInfo->hThread, &InitRegs))
        return FALSE;
    if (!(dwEntryPoint = GetProcessEntryPoint(pProcInfo->dwProcessId)))
        return FALSE;

    // init the LibLoadCode struct
    if (!InitCodeStruct(&LibLoadCode, NULL, szLibraryPath, dwEntryPoint))
        return FALSE;

    // save the code at the EntryPoint
    pCodeEntry = GlobalAlloc(GMEM_FIXED, sizeof(LibLoadCode));
    if (!pCodeEntry)
        return FALSE;
    VirtualProtectEx(
        pProcInfo->hProcess,
        (VOID*)dwEntryPoint,
        sizeof(LibLoadCode),
        PAGE_EXECUTE_READWRITE,
        &dwOldProt);
    if (!ReadProcessMemory(
        pProcInfo->hProcess,
        (VOID*)dwEntryPoint,
        pCodeEntry,
        sizeof(LibLoadCode),
        &dwBytesRead)) {
        GlobalFree(pCodeEntry);
        return FALSE;
    }

    // write the loader code to the EntryPoint
    if (!WriteProcessMemory(
        pProcInfo->hProcess,
        (VOID*)dwEntryPoint,
        &LibLoadCode,
        sizeof(LibLoadCode),
        &dwBytesWritten)) {
        GlobalFree(pCodeEntry);
        return FALSE;
    }

    // execute the copied code
    Regs = InitRegs;
    Regs.Eip = dwEntryPoint;
    ResumeThread(pProcInfo->hThread);

    // wait until the thread finishes
    dwCodeEnd = dwEntryPoint + offsetof(sLibLoadCode, jmp_$);
    TestRegs.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;
    do {
        Sleep(50);
        GetThreadContext(pProcInfo->hThread, &TestRegs);
    } while (TestRegs.Eip != dwCodeEnd);
    dwLibBase = TestRegs.Eax;

    // suspend the thread and restore all !
    SuspendThread(pProcInfo->hThread);
    if (!WriteProcessMemory(
        pProcInfo->hProcess,
        (VOID*)dwEntryPoint,
        pCodeEntry,
        sizeof(LibLoadCode),
        &dwBytesWritten)) {
        GlobalFree(pCodeEntry);
        return FALSE;
    }
    GlobalFree(pCodeEntry);
    VirtualProtectEx(
        pProcInfo->hProcess,
        (VOID*)dwCodeStart,
        sizeof(LibLoadCode),
        dwOldProt,
        &dwEWRProt);
    InitRegs.Eip = dwEntryPoint;
    if (!SetThreadContext(pProcInfo->hThread, &InitRegs))
        return FALSE;
    return TRUE;
}

BOOL ForceLibraryNT(const CHAR* szLibraryPath, PROCESS_INFORMATION* pProcInfo) {
    sLibLoadCodeNT  LibLoadCode;
    DWORD           dwRemoteThreadID;
    HANDLE          hRemoteThread;
    _CodeEntry      CodeEntry;


    // import NT only stuff manually
    HMODULE kernel = GetModuleHandle("kernel32.dll");

    typedef LPVOID(WINAPI*VirtualAllocExFunc)(
        HANDLE hProcess,          // process to allocate memory
        LPVOID lpAddress,         // desired starting address 
        SIZE_T dwSize,            // size of region to allocate
        DWORD flAllocationType,   // type of allocation
        DWORD flProtect           // type of access protection
        );
    VirtualAllocExFunc VirtualAllocExPtr = (VirtualAllocExFunc)GetProcAddress(kernel, "VirtualAllocEx");

    typedef BOOL(WINAPI*VirtualFreeExFunc)(
        HANDLE hProcess,   // handle to process
        LPVOID lpAddress,  // starting address of memory region
        SIZE_T dwSize,     // size of memory region
        DWORD dwFreeType   // operation type
        );
    VirtualFreeExFunc VirtualFreeExPtr = (VirtualFreeExFunc)GetProcAddress(kernel, "VirtualFreeEx");

    if (!VirtualFreeExPtr || !VirtualAllocExPtr) {
        MessageBox(0, "couldnt import virtualallocex", 0, 0);
        ExitProcess(1);
    }



    // get some mem in the target's process memory
    dwCodeStart = (DWORD)VirtualAllocExPtr(
        pProcInfo->hProcess,
        NULL,
        sizeof(LibLoadCode),
        MEM_COMMIT,
        PAGE_EXECUTE_READWRITE);
    if (!dwCodeStart)
        return FALSE;

    // init the LibLoadCode struct
    if (!InitCodeStruct(0, &LibLoadCode, szLibraryPath, dwCodeStart)) {
        VirtualFreeExPtr(
            pProcInfo->hProcess,
            (VOID*)dwCodeStart,
            sizeof(LibLoadCode),
            MEM_DECOMMIT);
        return FALSE;
    }

    // copy the code into the allocated mem
    if (!WriteProcessMemory(
        pProcInfo->hProcess,
        (VOID*)dwCodeStart,
        &LibLoadCode,
        sizeof(LibLoadCode),
        &dwBytesWritten)) {
        VirtualFreeExPtr(
            pProcInfo->hProcess,
            (VOID*)dwCodeStart,
            sizeof(LibLoadCode),
            MEM_DECOMMIT);
        return FALSE;
    }

    // execute it
    CodeEntry = (_CodeEntry)dwCodeStart;
    if (!(hRemoteThread = CreateRemoteThread(
        pProcInfo->hProcess,
        NULL,
        0,
        CodeEntry,
        NULL,
        0,
        &dwRemoteThreadID))) {
        VirtualFreeExPtr(
            pProcInfo->hProcess,
            (VOID*)dwCodeStart,
            sizeof(LibLoadCode),
            MEM_DECOMMIT);
        return FALSE;
    }

    // wait until the thread finishes
    WaitForSingleObject(hRemoteThread, INFINITE);
    if (!GetExitCodeThread(hRemoteThread, &dwLibBase)) {
        VirtualFreeExPtr(
            pProcInfo->hProcess,
            (VOID*)dwCodeStart,
            sizeof(LibLoadCode),
            MEM_DECOMMIT);
        return FALSE;
    }

    // clean up
    VirtualFreeExPtr(
        pProcInfo->hProcess,
        (VOID*)dwCodeStart,
        sizeof(LibLoadCode),
        MEM_DECOMMIT);
    CloseHandle(hRemoteThread);

    if (dwLibBase)
        return TRUE;
    else
        return FALSE;
}