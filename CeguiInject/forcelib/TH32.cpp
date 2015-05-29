//
// TH32.c: loads dynamically the ToolHelp32 API's because they
//         aren't available on NT4 ! Much thanks goes to ELiCZ
//         for putting my attention on that fact.
//

#include "th32.h"
#pragma pack(1) // very important !

// global variables
fCreateToolhelp32Snapshot    _CreateToolhelp32Snapshot;
fProcess32First              _Process32First;
fProcess32Next               _Process32Next;
fModule32First               _Module32First;
fModule32Next                _Module32Next;

BOOL GetTh32() {
    HINSTANCE hKrnl;

    // get kernel32 base
    hKrnl = LoadLibrary("Kernel32.dll");
    if (!hKrnl)
        return FALSE;

    // get th32 addresses
    _CreateToolhelp32Snapshot = (fCreateToolhelp32Snapshot)GetProcAddress(
        hKrnl, "CreateToolhelp32Snapshot");
    _Process32First = (fProcess32First)GetProcAddress(hKrnl, "Process32First");
    _Process32Next = (fProcess32Next)GetProcAddress(hKrnl, "Process32Next");
    _Module32First = (fModule32First)GetProcAddress(hKrnl, "Module32First");
    _Module32Next = (fModule32Next)GetProcAddress(hKrnl, "Module32Next");

    if (!_CreateToolhelp32Snapshot ||
        !_Process32First ||
        !_Process32Next ||
        !_Module32First ||
        !_Module32Next)
        return FALSE;

    return TRUE;
}