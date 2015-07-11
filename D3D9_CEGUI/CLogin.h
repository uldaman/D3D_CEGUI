#pragma once
#include <windows.h>
#include <list>

/*-----------------------------------------------------------------------
 * ����: CLogin
 * ˵��: ��¼����
 -----------------------------------------------------------------------*/
typedef struct ROLE_LIST {
    DWORD dwNext;               // +0x0	        ��һ�ڵ�
    DWORD dwRoot;               // +0x4	        ��һ�ڵ�
    DWORD dwUnKnown_1;	        // +0x8	    
    DWORD dwUnKnown_2;	        // +0xC	    
    DWORD dwRoleSvrIndex;	    // +0x10	    ��ɫ���������
    byte  bUnKnown_1[0x14];     // +0x14
    DWORD dwName;               // +0x28        ��ɫ��
    DWORD dwSex;	            // +0x2c	    �Ա�
    byte  bUnKnown_2[0x8];      // +0x30
    DWORD dwLevel;              // +0x38        �ȼ�
}*PROLE_LIST;

typedef struct ROLE_STRUCT {
    ROLE_LIST role_list;
    BOOL bIsSuccess; // �Ƿ��Ѿ�ˢ���ĺ�, �˹�������, ���õ�¼����Ϸ��ȡһ��������, �����Ѿ�ˢ�б�
}*PROLE_STRUCT;

class CLogin {
public:
    void RoleTraverse();
    void NewRole();
    int GetCountsOfRoles();
    BOOL LoginGame();
    void EnterChannel();
    BOOL IsOnline();
    void ReturnSelectRole();

private:
    static std::list<ROLE_STRUCT> m_role_list;
    static std::list<std::string> m_roleName_list;
    
    void TraverList(int nObjectStart, int nObjectEnd);
    std::string GetName();
    void SendPackage(DWORD PDATA);
};