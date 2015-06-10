#pragma once
#include <windows.h>
#include <tchar.h>
#include <vector>
#include "atlstr.h"

// Number bases
#define BASE_BINARY			2
#define BASE_OCTAL			8
#define BASE_DECIMAL		10
#define BASE_HEXADECIMAL	16

typedef BOOL(CALLBACK *SUBSTRPROC)(LPCTSTR, LPVOID);

class CMy_Ini {
public:
    CMy_Ini(LPCTSTR lpPathName);
    virtual ~CMy_Ini();

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
    LPTSTR __GetStringDynamic(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault = NULL) const;

    int GetInt(LPCTSTR lpSection, LPCTSTR lpKey, int nDefault, int nBase = BASE_DECIMAL) const;
    BOOL GetBool(LPCTSTR lpSection, LPCTSTR lpKey, BOOL bDefault) const;
    DWORD GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDefault = NULL) const;
    std::string GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault = NULL) const;
    void GetArray(LPCTSTR lpSection, LPCTSTR lpKey, std::vector<std::string>* pVector, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE) const;
    DWORD GetArray(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDelimiter = NULL, BOOL bTrimString = TRUE) const;
};


