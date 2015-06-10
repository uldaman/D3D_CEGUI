#pragma once
#include "windows.h"
#include <string>
#include <fstream>
#include <vector>

class CMartin {
public:
    // 隐藏DLL, 断链, 抹PE
    void ModuleHide(HMODULE hInjectDll);

    // 读内存
    template<typename Type>
    BOOL ReadPtrData(DWORD beginAddr, std::string strFormat, OUT Type& outPut, int count = 5, int second = 50);

    // 调试功能
    void Debug(const char* szFormat, ...);
    std::ofstream m_ofile;
    void add_log(const char *fmt, ...);

    // 获取模块路径(不含文件名)
    std::string GetModulePath(HMODULE hModule);

    // 分割字符串
    std::vector<std::string> split(std::string str, std::string pattern);

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