#pragma once
#include <windows.h>
#include <list>

/*-----------------------------------------------------------------------
 * 类名: CLogin
 * 说明: 登录功能
 -----------------------------------------------------------------------*/
typedef struct ROLE_LIST {
    DWORD dwNext;               // +0x0	        下一节点
    DWORD dwRoot;               // +0x4	        上一节点
    DWORD dwUnKnown_1;	        // +0x8	    
    DWORD dwUnKnown_2;	        // +0xC	    
    DWORD dwRoleSvrIndex;	    // +0x10	    角色服务器编号
    byte  bUnKnown_1[0x14];     // +0x14
    DWORD dwName;               // +0x28        角色名
    DWORD dwSex;	            // +0x2c	    性别
    byte  bUnKnown_2[0x8];      // +0x30
    DWORD dwLevel;              // +0x38        等级
}*PROLE_LIST;

typedef struct ROLE_STRUCT {
    ROLE_LIST role_list;
    BOOL bIsSuccess; // 是否已经刷过的号, 此功能作废, 改用登录进游戏就取一次人物名, 加入已经刷列表
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