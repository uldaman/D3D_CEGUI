#include "cthreadinjectdll.h"
#include <windows.h>
#include <tlhelp32.h>
#include "DataType.h"
#include "CMartin.h"
#include "..\CeguiInject\forcelib\ForceLib.h"


CThreadInjectDll::CThreadInjectDll(QObject *parent)
    : QThread(parent) {

}

CThreadInjectDll::~CThreadInjectDll() {

}

bool GetProcessOf(const char exename[], PROCESSENTRY32 *process) {
    HANDLE handle;
    process->dwSize = sizeof(PROCESSENTRY32);
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(handle, process)) {
        do {
            BOOL bfind = FALSE;
            if (lstrcmp(process->szExeFile, exename) == 0) {
                for (int i = 0; i < g_processVec.length(); i++) {
                    if (g_processVec[i] == process->th32ProcessID) {
                        bfind = TRUE;
                        break;
                    }
                }
                if (bfind == FALSE) {
                    CloseHandle(handle);
                    return true;
                }
            }
        } while (Process32Next(handle, process));
    }

    CloseHandle(handle);
    return false;
}

bool GetThreadOf(DWORD ProcessID, THREADENTRY32* thread) {
    HANDLE handle;
    thread->dwSize = sizeof(THREADENTRY32);
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if (Thread32First(handle, thread)) {
        do {
            if (thread->th32OwnerProcessID == ProcessID) {
                CloseHandle(handle);
                return true;
            }
        } while (Thread32Next(handle, thread));
    }

    CloseHandle(handle);
    return false;
}

void CThreadInjectDll::run() {
    PROCESSENTRY32 pe32;
    while (!GetProcessOf("MHOClient.exe", &pe32)) {
        if (g_bInjectDll == FALSE) {
            return;
        }
        Sleep(10);
    }

    THREADENTRY32 te32;
    while (!GetThreadOf(pe32.th32ProcessID, &te32)) {
        if (g_bInjectDll == FALSE) {
            return;
        }
        Sleep(2);
    }

    PROCESS_INFORMATION PI;
    PI.dwProcessId = pe32.th32ProcessID;
    PI.dwThreadId = te32.th32ThreadID;
    PI.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);

    std::string strDll = martin->GetModulePath(NULL);
    strDll += "\\D3D9_CEGUI.dll";

    if (!ForceLibrary(strDll.c_str(), &PI)) {
        TerminateProcess(PI.hProcess, 0);
        ::MessageBox(NULL, "无法开启插件...", "Tatnium Error", MB_ICONERROR);
    }

    CloseHandle(PI.hProcess);

    while (true) {
        if (g_bInjectDll == FALSE) {
            return;
        }

        HWND hwnd = martin->GetCurrentHwnd(PI.dwProcessId, "CryENGINE");
        if (hwnd) {
            pItem->setData(Qt::UserRole + 0x100, (int)hwnd);
            emit SignalDone(pItem);
            return;
        }

        Sleep(500);
    }
}