#include "Role.h"
#include "Base.h"
#include "Martin.h"
#include "GlobalVariable.h"
#include "DataType.h"

CRole* CRole::m_cInstance = NULL;

CRole* CRole::GetInstance() {
    if (m_cInstance == NULL) {
        m_cInstance = new CRole;
    }

    return m_cInstance;
}

CRole::CRole() {
}


CRole::~CRole() {
    if (m_cInstance == NULL) {
        delete m_cInstance;
        m_cInstance = NULL;
    }
}

int CRole::GetRoleAddr() {
    int nTemp = 0, nRet = 0;
    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ��ǰ����ָ�� -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_ROLE_INFO_1, TEXT("��ȡ��ǰ����ָ�� -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_ROLE_INFO_2, TEXT("��ȡ��ǰ����ָ�� -- 3"), nTemp)) {
                martin->ReadPtrData(nTemp + OFFSET_ROLE_INFO_4, TEXT("��ȡ��ǰ����ָ�� -- 4"), nRet);
            }
        }
    }

    return nRet;
}

int CRole::WhereIsRole() {
    int nAddr = CRole::GetRoleAddr();
    int nRet = -1, nTemp;
    if (martin->ReadPtrData(nAddr + OFFSET_CITY_FLAG_1, TEXT("��ȡ��ǰ����λ�� -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_CITY_FLAG_2, TEXT("��ȡ��ǰ����λ�� -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_CITY_FLAG_3, TEXT("��ȡ��ǰ����λ�� -- 3"), nTemp)) {
                if (martin->ReadPtrData(nTemp + OFFSET_CITY_FLAG_4, TEXT("��ȡ��ǰ����λ�� -- 4"), nTemp)) {
                    martin->ReadPtrData(nTemp + OFFSET_CITY_FLAG_5, TEXT("��ȡ��ǰ����λ�� -- 5"), nRet);
                }
            }
        }
    }
    return nRet;
}

void CRole::SendPackage(DWORD PDATA) {
    int nAddr = CRole::GetRoleAddr();
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, nAddr;
            add ecx, OFFSET_SEND_PACKET_ECX_1;
            mov ecx, [ecx];
            add ecx, OFFSET_SEND_PACKET_ECX_2;
            mov ecx, [ecx];
            add ecx, OFFSET_SEND_PACKET_ECX_3;
            mov ecx, [ecx];
            mov eax, PDATA; //������
            push eax;
            mov eax, CALL_SEND_PACKET; //CALL_SEND_PACKET
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("SendPackage --> �쳣"));
    }
}
