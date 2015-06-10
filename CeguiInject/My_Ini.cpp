#include "My_Ini.h"

#define DEF_PROFILE_NUM_LEN		64 // numeric string length, could be quite long for binary format
#define DEF_PROFILE_THRESHOLD	512 // temporary string length
#define DEF_PROFILE_DELIMITER	TEXT(",") // default string delimiter
#define DEF_PROFILE_TESTSTRING	TEXT("{63788286-AE30-4D6B-95DF-3B451C1C79F9}") // Uuid for internal use

CMy_Ini::CMy_Ini(LPCTSTR lpPathName) {
    m_pszPathName = NULL;
    SetPathName(lpPathName);
}

CMy_Ini::~CMy_Ini() {
}

void CMy_Ini::SetPathName(LPCTSTR lpPathName) {
    if (lpPathName == NULL) {
        if (m_pszPathName != NULL)
            *m_pszPathName = TEXT('\0');
    } else {
        if (m_pszPathName != NULL) {
            free(m_pszPathName);	//delete [] m_pszPathName;
            m_pszPathName = NULL;
        }
        m_pszPathName = _tcsdup(lpPathName);
    }
}

BOOL CMy_Ini::WriteString(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpValue) const {
    if (lpSection == NULL || lpKey == NULL)
        return FALSE;

    return ::WritePrivateProfileString(lpSection, lpKey, lpValue == NULL ? TEXT("") : lpValue, m_pszPathName);
}

BOOL CMy_Ini::WriteArray(LPCTSTR lpSection, LPCTSTR lpKey, const std::vector<std::string>* pVector
    , LPCTSTR lpDelimiter /* = NULL*/, int nWriteCount /* = -1*/) const {
    
    if (pVector == NULL) return FALSE;
    int nVctSize = pVector->size();

    if (nWriteCount < 0) {
        nWriteCount = nVctSize;
    } else {
        nWriteCount = min(nWriteCount, nVctSize);
    }

    const std::string DELIMITER = (lpDelimiter == NULL || *lpDelimiter == TEXT('\0')) ? TEXT(",") : lpDelimiter;
    std::string sLine;
    for (int i = 0; i < nWriteCount; i++) {
        sLine += (*pVector)[i];
        if (i != nWriteCount - 1) {
            sLine += DELIMITER;
        }
    }

    return WriteString(lpSection, lpKey, sLine.c_str());
}

BOOL CMy_Ini::WriteInt(LPCTSTR lpSection, LPCTSTR lpKey, int nValue, int nBase) const {
    TCHAR szValue[DEF_PROFILE_NUM_LEN + 1] = TEXT("");
    __IntToString(nValue, szValue, nBase);
    return WriteString(lpSection, lpKey, szValue);
}

BOOL CMy_Ini::WriteBool(LPCTSTR lpSection, LPCTSTR lpKey, BOOL bValue) const {
    return WriteInt(lpSection, lpKey, bValue ? 1 : 0, BASE_DECIMAL);
}

void CMy_Ini::__IntToString(int nNumber, LPTSTR lpBuffer, int nBase) {
    switch (nBase) {
    case BASE_BINARY:
    case BASE_OCTAL:
    case BASE_HEXADECIMAL:
        __UIntToString((UINT)nNumber, lpBuffer, nBase);
        break;

    default:
        _stprintf_s(lpBuffer, DEF_PROFILE_NUM_LEN, TEXT("%d"), nNumber);
        break;
    }
}

void CMy_Ini::__UIntToString(UINT nNumber, LPTSTR lpBuffer, int nBase) {
    switch (nBase) {
    case BASE_BINARY:
        __ToBinaryString(nNumber, lpBuffer, DEF_PROFILE_NUM_LEN);
        break;

    case BASE_OCTAL:
        _stprintf_s(lpBuffer, DEF_PROFILE_NUM_LEN, TEXT("%o"), nNumber);
        break;

    case BASE_HEXADECIMAL:
        _stprintf_s(lpBuffer, DEF_PROFILE_NUM_LEN, TEXT("%X"), nNumber);
        break;

    default:
        _stprintf_s(lpBuffer, DEF_PROFILE_NUM_LEN, TEXT("%u"), nNumber);
        break;
    }
}

void CMy_Ini::__ToBinaryString(UINT nNumber, LPTSTR lpBuffer, DWORD dwBufSize) {
    if (dwBufSize == 0)
        return;

    DWORD dwIndex = 0;
    do {
        lpBuffer[dwIndex++] = (nNumber % 2) ? TEXT('1') : TEXT('0');
        nNumber /= 2;
    } while (nNumber > 0 && dwIndex < dwBufSize);

    lpBuffer[dwIndex] = TEXT('\0');
    _tcsrev(lpBuffer);
}

BOOL CMy_Ini::DeleteSection(LPCTSTR lpSection) const {
    return ::WritePrivateProfileString(lpSection, NULL, _T(""), m_pszPathName);
}

BOOL CMy_Ini::WriteDataBlock(LPCTSTR lpSection, LPCTSTR lpKey, LPCVOID lpData, DWORD dwDataSize) const {
    const BYTE* lpb = (const BYTE*)lpData;
    if (lpb == NULL) return FALSE;

    LPTSTR psz = new TCHAR[(dwDataSize + 1) * 2]; // + 1 是补 '\0' 位
    RtlZeroMemory(psz, (dwDataSize + 1) * 2);

    for (DWORD i = 0, j = 0; i < dwDataSize; i++, j += 2) {
        _stprintf_s(&psz[j], sizeof(TCHAR) * 2, TEXT("%02X"), lpb[i]);
    }

    const BOOL RES = WriteString(lpSection, lpKey, psz);
    delete[] psz;
    return TRUE;
}



LPTSTR CMy_Ini::__GetStringDynamic(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault) const {
    TCHAR* psz = NULL;
    if (lpSection == NULL || lpKey == NULL) {
        // Invalid section or key name, just return the default string
        if (lpDefault == NULL) {
            // Empty string
            psz = new TCHAR[1];
            *psz = TEXT('\0');
        } else {
            int nLen = _tcslen(lpDefault) + 1;
            psz = new TCHAR[nLen];
            _tcscpy_s(psz, nLen, lpDefault);
        }

        return psz;
    }

    DWORD dwLen = DEF_PROFILE_THRESHOLD;
    psz = new TCHAR[dwLen + 1];
    DWORD dwCopied = ::GetPrivateProfileString(lpSection, lpKey, lpDefault == NULL ? TEXT("") : lpDefault, psz, dwLen, m_pszPathName);
    while (dwCopied + 1 >= dwLen) {
        dwLen += DEF_PROFILE_THRESHOLD;
        delete[] psz;
        psz = new TCHAR[dwLen + 1];
        dwCopied = ::GetPrivateProfileString(lpSection, lpKey, lpDefault == NULL ? _T("") : lpDefault, psz, dwLen, m_pszPathName);
    }

    return psz;
}

std::string CMy_Ini::GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpDefault /*= NULL*/) const {
    LPTSTR psz = __GetStringDynamic(lpSection, lpKey, lpDefault);
    std::string str(psz);
    delete[] psz;
    return str;
}

DWORD CMy_Ini::GetString(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize, LPCTSTR lpDefault /*= NULL*/) const {
    if (lpBuffer != NULL) {
        *lpBuffer = _T('\0');
    }

    LPTSTR psz = __GetStringDynamic(lpSection, lpKey, lpDefault);
    DWORD dwLen = _tcslen(psz);

    if (lpBuffer != NULL) {
        _tcsncpy_s(lpBuffer, dwBufSize - 1, psz, dwLen);
        dwLen = min(dwLen, dwBufSize);
    }

    delete[] psz;
    return dwLen;
}

void CMy_Ini::GetArray(LPCTSTR lpSection, LPCTSTR lpKey, std::vector<std::string>* pVector
    , LPCTSTR lpDelimiter /*= NULL*/, BOOL bTrimString /*= TRUE*/) const {

    if (!pVector->empty()) {
        pVector->swap(std::vector<std::string>());
    }

    const DWORD LEN = GetArray(lpSection, lpKey, NULL, 0, lpDelimiter);
    if (LEN == 0) {
        return;
    }

    LPTSTR psz = new TCHAR[LEN + 3];
    GetArray(lpSection, lpKey, psz, LEN + 2, lpDelimiter, bTrimString);
    ParseDNTString(psz, __SubStrAdd, (LPVOID)pVector);
    delete[] psz;
}

DWORD CMy_Ini::GetArray(LPCTSTR lpSection, LPCTSTR lpKey, LPTSTR lpBuffer, DWORD dwBufSize
    , LPCTSTR lpDelimiter /*= NULL*/, BOOL bTrimString /*= TRUE*/) const {
    if (lpBuffer != NULL) {
        *lpBuffer = TEXT('\0');
    }

    if (lpSection == NULL || lpKey == NULL) {
        return 0;
    }

    LPTSTR psz = __GetStringDynamic(lpSection, lpKey);

    DWORD dwCopied = 0;

    if (*psz != TEXT('\0')) {
        if (lpBuffer == NULL) {
            // just calculate the required buffer size
            const DWORD MAX_LEN = _tcslen(psz) + 2;
            LPTSTR p = new TCHAR[MAX_LEN + 1];
            dwCopied = __StringSplit(psz, p, MAX_LEN, lpDelimiter, bTrimString);
            delete[] p;
        } else {
            dwCopied = __StringSplit(psz, lpBuffer, dwBufSize, lpDelimiter, bTrimString);
        }
    }

    delete[] psz;
    return dwCopied;
}

DWORD CMy_Ini::__StringSplit(LPCTSTR lpString, LPTSTR lpBuffer, DWORD dwBufSize
    , LPCTSTR lpDelimiter /*= NULL*/, BOOL bTrimString /*= TRUE*/) {
    if (lpString == NULL || lpBuffer == NULL || dwBufSize == 0) {
        return 0;
    }

    DWORD dwCopied = 0;
    *lpBuffer = TEXT('\0');
    if (*lpString == TEXT('\0')) {
        return 0;
    }

    // If lpDelimiter is NULL, use the default delimiter ",", if delimiter length
    // is 0, then return whole string
    if (lpDelimiter != NULL && *lpDelimiter == TEXT('\0')) {
        _tcsncpy_s(lpBuffer, dwBufSize - 1, lpString, _TRUNCATE);
        return _tcslen(lpBuffer);
    }

    LPTSTR pszDel = (lpDelimiter == NULL) ? _tcsdup(DEF_PROFILE_DELIMITER) : _tcsdup(lpDelimiter);
    const DWORD DEL_LEN = _tcslen(pszDel);
    LPTSTR lpTarget = lpBuffer;

    // Search through lpString for delimiter matches, and extract sub strings out
    LPCTSTR lpPos = lpString;
    LPCTSTR lpEnd = _tcsstr(lpPos, pszDel);

    while (lpEnd != NULL) {
        LPTSTR pszSeg = __StrDupEx(lpPos, lpEnd);
        if (bTrimString) {
            __TrimString(pszSeg);
        }

        const DWORD SEG_LEN = _tcslen(pszSeg);
        const DWORD COPY_LEN = min(SEG_LEN, dwBufSize - dwCopied);

        // Need to avoid buffer overflow
        if (COPY_LEN > 0) {
            dwCopied += COPY_LEN + 1;
            _tcsncpy_s(lpTarget, COPY_LEN + 1, pszSeg, _TRUNCATE); // 第二个参数要有足够的长度来存放'\0'
            lpTarget[COPY_LEN] = TEXT('\0');
            lpTarget = &lpTarget[SEG_LEN + 1];
        }
        delete[] pszSeg;
        lpPos = &lpEnd[DEL_LEN]; // Advance the pointer for next search		
        lpEnd = _tcsstr(lpPos, pszDel);
    }

    // The last part of string, there may not be the trailing delimiter, so we
    // need to take care of this part, too
    LPTSTR pszSeg = _tcsdup(lpPos);
    if (bTrimString) {
        __TrimString(pszSeg);
    }

    const DWORD SEG_LEN = _tcslen(pszSeg);
    const DWORD COPY_LEN = min(SEG_LEN, dwBufSize - dwCopied);

    if (COPY_LEN > 0) {
        dwCopied += COPY_LEN + 1;
        _tcsncpy_s(lpTarget, COPY_LEN + 1, pszSeg, _TRUNCATE); // 第二个参数要有足够的长度来存放'\0'
        lpTarget[COPY_LEN] = TEXT('\0');
    }

    delete[] pszSeg;
    lpBuffer[dwCopied] = TEXT('\0');
    delete[] pszDel;
    return dwCopied;
}

LPTSTR CMy_Ini::__StrDupEx(LPCTSTR lpStart, LPCTSTR lpEnd) {
    const DWORD LEN = ((DWORD)lpEnd - (DWORD)lpStart) / sizeof(TCHAR);
    LPTSTR psz = new TCHAR[LEN + 1];
    _tcsncpy_s(psz, LEN + 1, lpStart, _TRUNCATE); // 第二个参数要有足够的长度来存放'\0'
    psz[LEN] = TEXT('\0');
    return psz; // !!! Requires the caller to free this memory !!!
}

BOOL CMy_Ini::__TrimString(LPTSTR lpString) {
    if (lpString == NULL) {
        return FALSE;
    }

    BOOL bTrimmed = FALSE;
    int nLen = _tcslen(lpString);

    // '\n' and '\r' are actually not possible in this case, but anyway...

    // Trim right side
    while (nLen >= 0
        && (lpString[nLen - 1] == TEXT(' ')
        || lpString[nLen - 1] == TEXT('\t')
        || lpString[nLen - 1] == TEXT('\r')
        || lpString[nLen - 1] == TEXT('\n'))) {
        lpString[--nLen] = TEXT('\0');
        bTrimmed = TRUE;
    }

    // Trim left side
    LPCTSTR p = lpString;
    while (*p == TEXT(' ')
        || *p == TEXT('\t')
        || *p == TEXT('\r')
        || *p == TEXT('\n')) {
        p = &p[1];
        bTrimmed = TRUE;
    }

    if (p != lpString) {
        LPTSTR psz = _tcsdup(p);
        _tcscpy_s(lpString, nLen, psz);
        delete[] psz;
    }

    return bTrimmed;
}

BOOL CMy_Ini::ParseDNTString(LPCTSTR lpString, SUBSTRPROC lpFnStrProc, LPVOID lpParam /*= NULL*/) {
    if (lpString == NULL || lpFnStrProc == NULL) {
        return FALSE;
    }

    LPCTSTR p = lpString;
    DWORD dwLen = _tcslen(p);

    while (dwLen > 0) {
        if (!lpFnStrProc(p, lpParam)) {
            return FALSE;
        }

        p = &p[dwLen + 1];
        dwLen = _tcslen(p);
    }
    return TRUE;
}

BOOL CALLBACK CMy_Ini::__SubStrAdd(LPCTSTR lpString, LPVOID lpParam) {
    std::vector<CString>* pArray = (std::vector<CString>*)lpParam;
    if (pArray == NULL || lpString == NULL) {
        return FALSE;
    }

    pArray->push_back(lpString);
    return TRUE;
}

int CMy_Ini::GetInt(LPCTSTR lpSection, LPCTSTR lpKey, int nDefault, int nBase /*= BASE_DECIMAL*/) const {
    TCHAR sz[DEF_PROFILE_NUM_LEN + 1] = TEXT("");
    GetString(lpSection, lpKey, sz, DEF_PROFILE_NUM_LEN);
    return *sz == TEXT('\0') ? nDefault : int(_tcstoul(sz, NULL, __ValidateBase(nBase)));
}

int CMy_Ini::__ValidateBase(int nBase) {
    switch (nBase) {
    case BASE_BINARY:
    case BASE_OCTAL:
    case BASE_HEXADECIMAL:
        break;
    default:
        nBase = BASE_DECIMAL;
    }
    return nBase;
}

BOOL CMy_Ini::GetBool(LPCTSTR lpSection, LPCTSTR lpKey, BOOL bDefault) const {
    TCHAR sz[DEF_PROFILE_NUM_LEN + 1] = TEXT("");
    GetString(lpSection, lpKey, sz, DEF_PROFILE_NUM_LEN);
    return StringToBool(sz, bDefault);
}

BOOL CMy_Ini::StringToBool(LPCTSTR lpString, BOOL bDefault /*= FALSE*/) {
    if (lpString == NULL || *lpString == TEXT('\0')) {
        return bDefault;
    }

    return (_tcsicmp(lpString, TEXT("true")) == 0
        || _tcsicmp(lpString, TEXT("yes")) == 0
        || _tcstol(lpString, NULL, BASE_DECIMAL) != 0);
}