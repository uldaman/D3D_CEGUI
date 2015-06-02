#pragma once
#include <string>
#include <windows.h>

class CRole {
public:
    virtual ~CRole();
    static CRole*  GetInstance();
    static int  GetRoleAddr();
    static int  WhereIsRole(); // ��ǰ����λ��, 0: ����  2: FB
    static void  SendPackage(DWORD PDATA);

protected:
    int         m_nRoleAddr; // ����ָ��

private:
    CRole();
    static CRole*  m_cInstance;
};