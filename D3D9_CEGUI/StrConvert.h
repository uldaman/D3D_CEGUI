#pragma once
#include <windows.h>
#include <string>

class StrConvert {
public:
    StrConvert(void);
    ~StrConvert(void);
public:
    //UFT8 ASii ��ת
    static std::string UFTtoAsii(char * str);
    static std::string AsiitoUFT(char * str);
    //Uncode  Asii ��ת
    static std::string UncodetoAsii(WCHAR * str);
    static std::wstring AsiitoUncode(char * str);
    //UFT8 Uncode ��ת
    static std::string UncodetoUFT(WCHAR * str);
    static std::wstring UFTtoUncode(char * str);
};