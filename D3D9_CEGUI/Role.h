#pragma once
#include <string>
#include <windows.h>

class CRole {
public:
    virtual ~CRole();
    static CRole*  GetInstance();
    static int  GetRoleAddr();
    static int  WhereIsRole(); // 当前人物位置, 0: 城镇  2: FB
    static void  SendPackage(DWORD PDATA);

protected:
    int         m_nRoleAddr; // 人物指针

private:
    CRole();
    static CRole*  m_cInstance;
};