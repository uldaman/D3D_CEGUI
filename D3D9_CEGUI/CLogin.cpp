#include "CLogin.h"
#include "Martin.h"
#include "Base.h"
#include "StrConvert.h"
#include "Role.h"
#include "NearObject.h"
#include <xutility>

std::list<ROLE_STRUCT> CLogin::m_role_list;
std::list<std::string> CLogin::m_roleName_list;

void CLogin::RoleTraverse() {
    m_role_list.swap(std::list<ROLE_STRUCT>());
    DWORD dwRoleListAddr;
    try {
    	_asm {
    		pushad;
    		pushfd;
    		
            mov eax, CALL_GET_ROLE_LIST_INFO;
            call eax;
            mov ecx, [eax + 0x4];
            mov eax, [ecx];
            mov edx, [eax + 0x28];
            call edx;
            mov dwRoleListAddr, eax;

    		popfd;
    		popad;
    	}
    } catch (...) {
    	martin->Debug("RoleTraverse --> 异常");
        return;
    }

    DWORD dwRoleListStart, dwRoleListEnd;
    if (martin->ReadPtrData(dwRoleListAddr + 0x8, "获取 [角色双向链表首节点]", dwRoleListStart)
        && martin->ReadPtrData(dwRoleListAddr + 0xC, "获取 [角色双向链表尾节点]", dwRoleListEnd)) {
        TraverList(dwRoleListStart, dwRoleListEnd);
    }
}

void CLogin::TraverList(int nObjectStart, int nObjectEnd) {
    PROLE_LIST pList;
    pList = (PROLE_LIST)nObjectStart;

    if (pList->dwNext != pList->dwRoot) {
        ROLE_STRUCT role_struct;
        role_struct.bIsSuccess = FALSE;
        role_struct.role_list = *pList;
        m_role_list.push_back(role_struct);
    }

    if (nObjectStart == nObjectEnd) {
        return;
    } else {
        TraverList(pList->dwNext, nObjectEnd);
    }
}

std::string CLogin::GetName() {
    std::string strName = "", strNextName = "";
    //乱序取名
    srand(GetTickCount());
    int iRange1 = 0xf7 - 0xb1;
    int iRange2 = 0xfe - 0xa1;
    byte iCode1, iCode2;
    for (int i = 0; i < 4; i++) {
        iCode1 = rand() % iRange1 + 0xb1;
        iCode2 = rand() % iRange2 + 0xa1;
        if (iCode1 != 0x7F && iCode2 != 0x7F) {
            char ch[3] = { iCode1, iCode2, 0 };
            strNextName = ch;
            if (strNextName != "") {
                strName = strName + ch;
            } else { i--; }
        } else { i--; }
    }
    return strName;
}

void CLogin::NewRole() {
    DWORD dwPackage[100];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x00000003;
    std::string strNewName = GetName();
    strcpy_s((char*)&dwPackage[4], strNewName.length() * 2, strNewName.c_str());
    dwPackage[12] = 0x01000100;
    dwPackage[13] = 0x00000100;
    dwPackage[14] = 0x1A000000;
    dwPackage[15] = 0x96001A1A;
    dwPackage[16] = 0x32009696;
    dwPackage[17] = 0x60000000;
    dwPackage[18] = 0x00007B71;
    dwPackage[19] = 0x00000000;
    dwPackage[20] = 0x0000FF00;
    SendPackage((DWORD)&dwPackage);
}

void CLogin::SendPackage(DWORD PDATA) {
    DWORD dwEcx;
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, CALL_GET_ROLE_LIST_INFO;
            call eax;
            mov ecx, [eax + 0x4];
            mov eax, [ecx];
            mov edx, [eax + 0x28];
            call edx;
            mov eax, [eax + 0x4];
            mov eax, [eax + 0x1C];
            mov dwEcx, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug("SendPackage -- 1 --> 异常");
        return;
    }
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, dwEcx;
            mov eax, PDATA; //包数据
            push eax;
            mov eax, CALL_SEND_PACKET; //CALL_SEND_PACKET
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("SendPackage -- 2 --> 异常"));
    }
}

int CLogin::GetCountsOfRoles() {
    RoleTraverse();
    if (m_role_list.empty()) {
        return 0;
    }
    return m_role_list.size();
}

void CLogin::LoginGame() {
    for (auto& v : m_role_list) {
        BOOL bIsSuccess = FALSE;
        for (auto& w : m_roleName_list) {
            if (w == (char*)v.role_list.dwName) { // 如果找到了, 说明此角色已经刷过了
                bIsSuccess = TRUE;
                break;
            }
        }

        if (bIsSuccess == FALSE) {
            DWORD dwPackage[100];
            RtlZeroMemory(&dwPackage, sizeof(dwPackage));
            dwPackage[0] = 0x00000007;
            dwPackage[4] = v.role_list.dwRoleSvrIndex;
            SendPackage((DWORD)&dwPackage);
            return;
        }
    }
}

void CLogin::EnterChannel() {
    DWORD dwPackage[100];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x00000051;
    dwPackage[4] = 0x00000002;
    SendPackage((DWORD)&dwPackage);
}

BOOL CLogin::IsOnline() {
    int nRoleAddr = CRole::GetRoleAddr();
    if (IsBadReadPtr((CONST VOID*)nRoleAddr, sizeof(DWORD)) != 0) {
        return FALSE;
    }

    int nOnline;
    if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, "获取 [掉线状态]", nOnline)) {
        if (martin->ReadPtrData(nOnline + OFFSET_SEND_PACKET_ECX_2, "获取 [掉线状态]", nOnline)) {
            if (martin->ReadPtrData(nOnline + OFFSET_SEND_PACKET_ECX_3, "获取 [掉线状态]", nOnline)) {
                if (martin->ReadPtrData(nOnline + 0x24, "获取 [掉线状态]", nOnline)) {
                    if (nOnline == 0) {
                        return FALSE;
                    } else {
                        int nRoleAddr = CRole::GetRoleAddr();
                        std::string strRoleName = CNearObject::GetObjectName(nRoleAddr);
                        if (std::find(m_roleName_list.begin(), m_roleName_list.end(), strRoleName) == m_roleName_list.end()) {
                            m_roleName_list.push_back(strRoleName);
                        }
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}
