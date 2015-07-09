#pragma once
#include "windows.h"
#include <string>
#include <fstream>
#include <vector>

#ifdef _DEBUG
#pragma comment(lib,"CMartin_Debug.lib")
#else
#pragma comment(lib,"CMartin_Release.lib")
#endif

// Number bases
#define BASE_BINARY			2
#define BASE_OCTAL			8
#define BASE_DECIMAL		10
#define BASE_HEXADECIMAL	16

typedef BOOL(CALLBACK *SUBSTRPROC)(LPCTSTR, LPVOID);

class CMartin {
public:
    // ����DLL, ����, ĨPE
    void ModuleHide(HMODULE hInjectDll);

    // ���ڴ�
    template<typename Type>
    BOOL ReadPtrData(DWORD beginAddr, std::string strFormat, OUT Type& outPut, int count = 5, int second = 50);

    // ���Թ���
    void Debug(const char* szFormat, ...);
    void add_log(const char *fmt, ...);

    // ��ȡģ��·��(�����ļ���)
    std::string GetModulePath(HMODULE hModule);

    // �ָ��ַ���
    std::vector<std::string> split(std::string str, std::string pattern);

    // ��������
    float Compare_Coord(float x1, float y1, float x2, float y2);

    // ����: char * lpApplicationName ��ִ��ģ����ַ���(·��)
    // ����: char * lpCommandLine ��ִ��ģ����ַ���(·��)
    // ����: char * lpDLLName Ҫע���DLL(·��)
    // ����: char * lpCurrentDirectory ָ���ӽ��̵Ĺ���·��
    // ˵��: ��������, ��ע��DLL
    BOOL CreatProcessInsertDLL(char* lpApplicationName, char* lpCommandLine, char* lpDLLName, char* lpCurrentDirectory);

    /////////////////////////////////////////////////////////////////////////
    //    ������ ini ̎����
    /////////////////////////////////////////////////////////////////////////
    void SetPathName(LPCTSTR lpPathName);
    LPTSTR m_pszPathName;

    BOOL WriteString(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpValue) const;
    BOOL WriteArray(LPCTSTR lpSection, LPCTSTR lpKey, const std::vector<std::string>* pVector, LPCTSTR lpDelimiter = NULL, int nWriteCount = -1) const;
    BOOL WriteInt(LPCTSTR lpSection, LPCTSTR lpKey, int nValue, int nBase = BASE_DECIMAL) const;
    BOOL WriteBool(LPCTSTR lpSection, LPCTSTR lpKey, BOOL bValue) const;
    BOOL DeleteSection(LPCTSTR lpSection) const;
    BOOL WriteDataBlock(LPCTSTR lpSection, LPCTSTR lpKey, LPCVOID lpData, DWORD dwDataSize) const;

    static int __ValidateBase(int nBase);
    static BOOL __TrimString(LPTSTR lpString);
    static LPTSTR __StrDupEx(LPCTSTR lpStart, LPCTSTR lpEnd);
    static BOOL StringToBool(LPCTSTR lpString, BOOL bDefault = FALSE);
    static void __IntToString(int nNumber, LPTSTR lpBuffer, int nBase);
    static void __UIntToString(UINT nNumber, LPTSTR lpBuffer, int nBase);
    static void __ToBinaryString(UINT nNumber, LPTSTR lpBuffer, DWORD dwBufSize);
    static DWORD __StringSplit(LPCTSTR lpString, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE);
    static BOOL ParseDNTString(LPCTSTR lpString, SUBSTRPROC lpFnStrProc, LPVOID lpParam = NULL);
    static BOOL CALLBACK __SubStrAdd(LPCTSTR lpString, LPVOID lpParam);
    static BOOL CALLBACK __KeyPairProc(LPCTSTR lpString, LPVOID lpParam);
    LPTSTR __GetStringDynamic(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault = NULL) const;

    int GetInt(LPCTSTR lpSection, LPCTSTR lpKey, int nDefault, int nBase = BASE_DECIMAL) const;
    BOOL GetBool(LPCTSTR lpSection, LPCTSTR lpKey, BOOL bDefault) const;
    DWORD GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDefault = NULL) const;
    std::string GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault = NULL) const;
    void GetArray(LPCTSTR lpSection, LPCTSTR lpKey, std::vector<std::string>* pVector, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE) const;
    DWORD GetArray(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE) const;
    DWORD GetKeyNames(LPCTSTR lpSection, LPTSTR lpBuffer, DWORD dwBufSize) const;
    void GetKeyNames(LPCTSTR lpSection, std::vector<std::string>* pVector) const;
    DWORD GetKeyLines(LPCTSTR lpSection, LPTSTR lpBuffer, DWORD dwBufSize) const;
    void GetKeyLines(LPCTSTR lpSection, std::vector<std::string>* pVector) const;
public:
    static CMartin* GetInstance();
};
extern CMartin* martin;