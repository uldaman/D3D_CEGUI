#pragma once
#include "windows.h"
#include <string>
#include <fstream>

class CMartin {
public:
    void ModuleHide(HMODULE hInjectDll);    //Òþ²ØDLL
    template<typename Type>
    BOOL ReadPtrData(DWORD beginAddr, std::string strFormat, OUT Type& outPut, int count = 5, int second = 50);
    void Debug(const char* szFormat, ...);
    std::ofstream m_ofile;
    void add_log(const char *fmt, ...);

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