#include "StrConvert.h"


StrConvert::StrConvert(void) {
}


StrConvert::~StrConvert(void) {
}

std::string StrConvert::UFTtoAsii(char * str) {
    int strmub = strlen(str);
    char* szU8 = new char[strmub + 1];
    szU8[strmub] = '\0';
    memcpy(szU8, (void *)str, strmub);
    int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
    char* szAnsi = new char[ansiLen + 1];
    ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
    szAnsi[ansiLen] = '\0';
    std::string RetszU8 = szAnsi;
    delete[] szU8;
    delete[] wszString;
    delete[] szAnsi;
    wszString = NULL;
    szAnsi = NULL;
    szU8 = NULL;
    return RetszU8;
}

std::string StrConvert::AsiitoUFT(char * str) {
    int strmub = strlen(str);
    char* szAnsi = new char[strmub + 1];
    szAnsi[strmub] = '\0';
    memcpy(szAnsi, (void *)str, strmub);
    int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
    char* szU8 = new char[u8Len + 1];
    ::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szU8, u8Len, NULL, NULL);
    szU8[u8Len] = '\0';
    std::string RetszU8 = szU8;
    delete[] szU8;
    delete[] wszString;
    delete[] szAnsi;
    wszString = NULL;
    szAnsi = NULL;
    szU8 = NULL;
    return RetszU8;
}


std::string StrConvert::UncodetoAsii(WCHAR * str) {
    int strmub = wcslen(str);
    wchar_t* wszString = new wchar_t[strmub + 1];
    wszString[strmub] = '\0';
    memcpy(wszString, (void *)str, strmub);
    int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
    char* szAnsi = new char[ansiLen + 1];
    ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
    szAnsi[ansiLen] = '\0';
    std::string RetAsii = szAnsi;
    delete[] wszString;
    delete[] szAnsi;
    wszString = NULL;
    szAnsi = NULL;
    return RetAsii;
}

std::wstring StrConvert::AsiitoUncode(char * str) {
    int strmub = strlen(str);
    char* szAnsi = new char[strmub + 1];
    szAnsi[strmub] = '\0';
    memcpy(szAnsi, (void *)str, strmub);
    int wcsLen = ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    ::MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    std::wstring RetUn = wszString;
    delete[] szAnsi;
    delete[] wszString;
    wszString = NULL;
    szAnsi = NULL;
    return RetUn;
}

std::string StrConvert::UncodetoUFT(WCHAR * str) {
    int strmub = wcslen(str);
    wchar_t* wszString = new wchar_t[strmub + 1];
    wszString[strmub] = '\0';
    memcpy(wszString, (void *)str, strmub);
    int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
    char* szU8 = new char[u8Len + 1];
    ::WideCharToMultiByte(CP_UTF8, NULL, wszString, wcslen(wszString), szU8, u8Len, NULL, NULL);
    szU8[u8Len] = '\0';
    std::string RetU8 = szU8;
    delete[] szU8;
    delete[] wszString;
    wszString = NULL;
    szU8 = NULL;
    return RetU8;
}

std::wstring StrConvert::UFTtoUncode(char * str) {
    int strmub = strlen(str);
    char* szU8 = new char[strmub + 1];
    szU8[strmub] = '\0';
    memcpy(szU8, (void *)str, strmub);
    int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    std::wstring RetszU8 = wszString;
    delete[] szU8;
    delete[] wszString;
    wszString = NULL;
    szU8 = NULL;
    return RetszU8;
}