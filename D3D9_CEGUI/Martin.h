#pragma once
#include <tchar.h>
#include "windows.h"
#include <string>
#include <vector>

class CMartin {
public:
    void ModuleHide(HMODULE hInjectDll);    //Òþ²ØDLL

    ///////////////////////////////////////////////////////////////
public:
    static CMartin* GetInstance();

protected:
    virtual ~CMartin() {
        if (m_cInstance != NULL) {
            delete m_cInstance;
        }
    };

private:
    BOOL BreakLdrModuleLink(DWORD dwBaseAddr);
    static CMartin* m_cInstance;
    CMartin() {};
};
extern CMartin* martin;
///////////////////////////////////////////////////////////////

typedef struct _LSA_UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_MODULE {
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID BaseAddress;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;
    LIST_ENTRY HashTableEntry;
    ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE, *PLML;

#include "Martin.inl"