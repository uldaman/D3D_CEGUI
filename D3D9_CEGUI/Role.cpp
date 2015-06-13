#include "Role.h"
#include "Base.h"
#include "Martin.h"
#include "GlobalVariable.h"
#include "DataType.h"
#include "NearObject.h"

CRole* CRole::m_cInstance = NULL;
CGameHOOK CRole::m_hook;
CGameHOOK CRole::m_CatHook;
std::map<int, std::string> CRole::s_allItems;

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

std::string CRole::GetRoleMap() {
    // [[[BASE_GAME]+OFFSET_ROLE_INFO_1]+8]
    DWORD dwTemp;
    if (martin->ReadPtrData(BASE_GAME, "��ȡ [��ǰ��ͼ] -- 1", dwTemp)) {
        if (martin->ReadPtrData(dwTemp + OFFSET_ROLE_INFO_1, "��ȡ [��ǰ��ͼ] -- 2", dwTemp)) {
            if (martin->ReadPtrData(dwTemp + 0x8, "��ȡ [��ǰ��ͼ] -- 3", dwTemp)) {
                if (martin->ReadPtrData(dwTemp + 0x1C, "��ȡ [��ǰ��ͼ] -- 4", dwTemp)) {
                    return (char*)dwTemp;
                }
            }
        }
    }
    return "";
}

void CRole::CityFly(std::string strKey) {
    byte package[256];
    RtlZeroMemory(package, 256);
    *(int*)(&package[0]) = 0x00000042;
    strcpy_s((char*)(&package[0x10]), 255 - 0x10, strKey.c_str());
    SendPackage((DWORD)&package[0]);
}

int CRole::GetRoleRoom() {
    int nIndex = 0;
    int nAddr = CRole::GetRoleAddr();
    martin->ReadPtrData(nAddr + 0x2C, TEXT("��ȡ [��ǰ�����]"), nIndex);
    return nIndex;
}

std::string CRole::GetRoleZone() {
    int nTemp;
    std::string strRet = "unKnown";
    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [��ǰ��ͼӢ����] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_ROLE_INFO_1, TEXT("��ȡ [��ǰ��ͼӢ����] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + 0x8, TEXT("��ȡ [��ǰ��ͼӢ����] -- 3"), nTemp)) {
                if (martin->ReadPtrData(nTemp + 0x18, TEXT("��ȡ [��ǰ��ͼӢ����] -- 4"), nTemp)) {
                    if (martin->ReadPtrData(nTemp + 0x28, TEXT("��ȡ [��ǰ��ͼӢ����] -- 5"), nTemp)) {
                        strRet = (char*)nTemp;
                    }
                }
            }
        }
    }
    return strRet;
}

void CRole::RoleTeleport(int nKey, float fx, float fy, float fz) {
    int nRoleAddr = 0, nEbx = 0;
    if (martin->ReadPtrData(BASE_GAME, TEXT("���ܶ��� Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("���ܶ��� Key -- 2"), nEbx)) {
            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                    mov eax, [ebx];
                    mov edx, nKey; //����Key
                    push edx;
                    mov edx, [eax + 0x2C];
                    mov ecx, ebx;
                    call edx;
                    mov nRoleAddr, eax;

                    popfd;
                    popad;
                }
            } catch (...) {
                martin->Debug(TEXT("RoleTeleport -- 1 --> �쳣"));
                return;
            }

            *(float*)(nRoleAddr + 0x38) = fx;//Ŀ������X
            *(float*)(nRoleAddr + 0x38 + 0x4) = fy;//Ŀ������Y
            *(float*)(nRoleAddr + 0x38 + 0x8) = fz;//Ŀ������Z

            float EmptyStackPtr[0x10];
            RtlZeroMemory(EmptyStackPtr, sizeof(EmptyStackPtr));
            DWORD dwEmptyStackPtr = (DWORD)&EmptyStackPtr;

            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ecx, nRoleAddr;
                    lea eax, [ecx + 0x38];
                    push eax;
                    lea eax, [ecx + 0x44];
                    push eax;
                    lea eax, [ecx + 0x54];
                    push eax;
                    mov ecx, dwEmptyStackPtr;  //0x10����Ա��float���飬��Աֵȫ������Ϊ0���ɡ�
                    mov eax, CALL_TELESPORT;
                    call eax;

                    popfd;
                    popad;
                }
            } catch (...) {
                martin->Debug(TEXT("RoleTeleport -- 2 --> �쳣"));
                return;
            }
        }
    }
}

void CRole::ByMap(const char* szKey) {
    byte szEcx[256];
    RtlZeroMemory(szEcx, 256);
    int nLen = strlen(szKey);
    *(int*)(&szEcx[0]) = 1;
    *(int*)(&szEcx[4]) = nLen;
    *(int*)(&szEcx[8]) = nLen;
    strcpy_s((char*)(&szEcx[0xC]), 255 - 0xC, szKey);

    int nTemp = (int)&szEcx[0xC];
    int nRet = 0;
    int nAddr = CRole::GetRoleAddr();

    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, nAddr; //����ָ��
            mov eax, [ecx];
            add eax, OFFSET_GET_SWITCH_REGION_ECX;
            mov edx, [eax]; //0x178:OFFSET_GET_SWITCH_REGION_ECX
            call edx;
            mov nRet, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ͼ -- 1 --> �쳣"));
        return;
    }

    try {
        _asm {
            pushad;
            pushfd;

            push nTemp;      // �������� ���·� (�˴�������ǡ�������+0c ���� �ı���ʼ�ĵط�.)
            mov ecx, nRet;   //��ECX�� ���·�
            mov eax, CALL_SWITCH_REGION;	  //CALL_SWITCH_REGION
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ͼ -- 2 --> �쳣"));
    }
}

void CRole::Turn() {
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;

    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [ת����Ϣ] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [ת����Ϣ] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("��ȡ [ת����Ϣ] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("��ȡ [ת����Ϣ] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    //martin->Debug(TEXT("bEmpty : %d"), bEmpty);
                    if (!bEmpty) {
                        int nTempEsi_Next = nRoot;
                        while (nTempEsi_Next != nEnd) {
                            int nTempNode = 0, nCurrentKey = 0;
                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 1"), nTempNode);
                            martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("��ȡ [�ڵ�Key]"), nCurrentKey);
                            //TODO:���ݶ���Keyȡ����������ָ��...�μ���������Keyȡ����ָ�롿
                            //martin->Debug(TEXT("Key: 0x%X"), nCurrentKey);
                            if (TurntoBoss(nCurrentKey) == TRUE) { // ˵���ҵ� BOSS �����ٱ�����
                                break;
                            }

                            if (++nNodeCount > 0x400) {//����������ֹ����̫��
                                break;
                            }

                            if (nTempNode != 0) {
                                nTempEsi_Next = nTempNode;
                                int nTemp = 0;
                                while (true) {
                                    martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("��ȡ [�ڵ�8]"), nTemp);
                                    if (nTemp != 0) {
                                        nTempEsi_Next = nTemp;
                                    } else {
                                        break;
                                    }
                                }
                            } else {
                                martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("��ȡ [�ڵ�4] -- 1"), nTempNode);
                                int nTemp = 0;
                                martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 2"), nTemp);

                                if (nTempEsi_Next == nTemp) {
                                    do {
                                        nTempEsi_Next = nTempNode;
                                        martin->ReadPtrData(nTempNode + 0x4, TEXT("��ȡ [�ڵ�4] -- 2"), nTempNode);
                                        martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 3"), nTemp);
                                    } while (nTempEsi_Next == nTemp);
                                }

                                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 4"), nTemp);
                                if (nTemp != nTempNode) {
                                    nTempEsi_Next = nTempNode;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

BOOL CRole::TurntoBoss(int nKey) {
    int nEbx = 0, nRet = 0;
    if (martin->ReadPtrData(BASE_GAME, TEXT("���ܶ��� Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("���ܶ��� Key -- 2"), nEbx)) {
            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                    mov eax, [ebx];
                    mov edx, nKey; //����Key
                    push edx;
                    mov edx, [eax + 0x2C];
                    mov ecx, ebx;
                    call edx;
                    //mov ecx, OFFSET_OBJECT_DETAIL;
                    //mov eax, [eax + ecx];
                    mov nRet, eax;

                    popfd;
                    popad;
                }
            } catch (...) {
                martin->Debug(TEXT("TurntoBoss -- 1 --> �쳣"));
                return FALSE;
            }
        }
    }

    if (nRet) {
        int nRet_2 = 0;
        try {
            _asm {
                pushad;
                pushfd;

                mov ecx, nRet;  //����ָ��(������ ������Keyȡ����ָ�롿�ķ���ֵ)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug(TEXT("TurntoBoss -- 2 --> �쳣"));
            return FALSE;
        }

        if (nRet_2) {
            int nName = 0;
            std::string strName = CNearObject::GetObjectName(nRet_2);
            for (int i = 0; BossName[i] != ""; i++) {
                if (BossName[i] == strName) { // �ҵ� BOSS
                    // ��ȡ BOSS ����
                    float fx, fy, fz;
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("��ȡ [BOSS x ����]"), fx);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("��ȡ [BOSS y ����]"), fy);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x8, TEXT("��ȡ [BOSS z ����]"), fz);
                    martin->Debug(TEXT("BOSS ����: %f, %f, %f"), fx, fy, fz);

                    // ת��
                    float role_fx = 0.0f;
                    float role_fy = 0.0f;
                    int nRoleAddr = GetRoleAddr();
                    martin->ReadPtrData(nRoleAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
                    martin->ReadPtrData(nRoleAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);

                    float fTurn = static_cast<float>(atan2(fy - role_fy, fx - role_fx));
#define PI 3.1415926535898
                    if (fTurn >= PI / 2) {
                        fTurn = fTurn - static_cast<float>(PI / 2);
                    } else {
                        fTurn = static_cast<float>(PI * 1.5) + fTurn;
                    }

                    int nTmep;
                    if (martin->ReadPtrData(BASE_CAMERA, TEXT("��ȡ��ǰ�������� -- 1"), nTmep)) {
                        if (martin->ReadPtrData(nTmep + OFFSET_CAREMA_1, TEXT("��ȡ��ǰ�������� -- 2"), nTmep)) {
                            if (martin->ReadPtrData(nTmep + OFFSET_CAREMA_2, TEXT("��ȡ��ǰ�������� -- 3"), nTmep)) {
                                *(float*)(nTmep + OFFSET_CAREMA_ANGLE) = fTurn;
                                return TRUE;
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}

void CRole::Attack_Pack(int nPart) {
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;

    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [�������] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [�������] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("��ȡ [�������] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("��ȡ [�������] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    //martin->Debug(TEXT("bEmpty : %d"), bEmpty);
                    if (!bEmpty) {
                        int nTempEsi_Next = nRoot;
                        while (nTempEsi_Next != nEnd) {
                            int nTempNode = 0, nCurrentKey = 0;
                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 1"), nTempNode);
                            martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("��ȡ [�ڵ�Key]"), nCurrentKey);
                            //TODO:���ݶ���Keyȡ����������ָ��...�μ���������Keyȡ����ָ�롿
                            //martin->Debug(TEXT("Key: 0x%X"), nCurrentKey);
                            if (CRole::Attack_Pack_Boss(nCurrentKey, nPart) == TRUE) { // ˵���ҵ� BOSS �����ٱ�����
                                break;
                            }

                            if (++nNodeCount > 0x400) {//����������ֹ����̫��
                                break;
                            }

                            if (nTempNode != 0) {
                                nTempEsi_Next = nTempNode;
                                int nTemp = 0;
                                while (true) {
                                    martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("��ȡ [�ڵ�8]"), nTemp);
                                    if (nTemp != 0) {
                                        nTempEsi_Next = nTemp;
                                    } else {
                                        break;
                                    }
                                }
                            } else {
                                martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("��ȡ [�ڵ�4] -- 1"), nTempNode);
                                int nTemp = 0;
                                martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 2"), nTemp);

                                if (nTempEsi_Next == nTemp) {
                                    do {
                                        nTempEsi_Next = nTempNode;
                                        martin->ReadPtrData(nTempNode + 0x4, TEXT("��ȡ [�ڵ�4] -- 2"), nTempNode);
                                        martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 3"), nTemp);
                                    } while (nTempEsi_Next == nTemp);
                                }

                                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 4"), nTemp);
                                if (nTemp != nTempNode) {
                                    nTempEsi_Next = nTempNode;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

BOOL CRole::Attack_Pack_Boss(int nBossKey, int nPart) {
    int nEbx = 0, nRet = 0;
    if (martin->ReadPtrData(BASE_GAME, TEXT("���ܶ��� Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("���ܶ��� Key -- 2"), nEbx)) {
            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                    mov eax, [ebx];
                    mov edx, nBossKey; //����Key
                    push edx;
                    mov edx, [eax + 0x2C];
                    mov ecx, ebx;
                    call edx;
                    //mov ecx, OFFSET_OBJECT_DETAIL;
                    //mov eax, [eax + ecx];
                    mov nRet, eax;

                    popfd;
                    popad;
                }
            } catch (...) {
                martin->Debug(TEXT("Attack_Pack_Boss_1 --> �쳣"));
                return FALSE;
            }
        }
    }

    if (nRet) {
        int nRet_2 = 0;
        try {
            _asm {
                pushad;
                pushfd;

                mov ecx, nRet;  //����ָ��(������ ������Keyȡ����ָ�롿�ķ���ֵ)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug(TEXT("Attack_Pack_Boss_2 --> �쳣"));
            return FALSE;
        }

        if (nRet_2) {
            // ���ж��Ƿ�����
            int nDead = 0;
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ecx, nRet_2; //����ָ��
                    mov eax, [ecx];
                    add eax, OFFSET_GET_SWITCH_REGION_ECX;
                    mov edx, [eax]; //0x178:OFFSET_GET_SWITCH_REGION_ECX
                    call edx;
                    mov ebx, eax;
                    mov edx, [ebx];
                    add edx, OFFSET_IS_DEAD;
                    mov eax, [edx]; //OFFSET_IS_DEAD
                    mov ecx, ebx;
                    call eax;
                    movzx ecx, al;
                    mov nDead, ecx;

                    popfd;
                    popad;
                }
            } catch (...) {
                martin->Debug(TEXT("WhetherOrBusy --> �쳣"));
                return TRUE;
            }

            if (nDead == 1) {
                return FALSE;
            }

            int nName = 0;
            std::string strName = CNearObject::GetObjectName(nRet_2);
            for (int i = 0; BossName[i] != ""; i++) {
                if (BossName[i] == strName) { // �ҵ� BOSS
                    // ��ȡ BOSS ����
                    float fx, fy, fz;
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("��ȡ BOSS ����"), fx);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("��ȡ BOSS ����"), fy);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x8, TEXT("��ȡ BOSS ����"), fz);
                    martin->Debug(TEXT("BOSS ����: %f, %f, %f"), fx, fy, fz);

                    int nRoleAddr = 0, nRoleKey = 0;
                    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ��ǰ����ָ�� -- 1"), nRoleAddr)) {
                        if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_1, TEXT("��ȡ��ǰ����ָ�� -- 2"), nRoleAddr)) {
                            if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_2, TEXT("��ȡ��ǰ����ָ�� -- 3"), nRoleAddr)) {
                                if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_4, TEXT("��ȡ��ǰ����ָ�� -- 4"), nRoleAddr)) {
                                    if (martin->ReadPtrData(nRoleAddr + 0x8, TEXT("��ȡ��ǰ���� KEY"), nRoleKey)) {
                                        Send_Attack_Pack(nRoleKey, nBossKey, fx, fy, fz, nPart);
                                    }
                                }
                            }
                        }
                    }
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

void CRole::Send_Attack_Pack(int nRoleKey, int nBoosKey, float fx, float fy, float fz, int nPart) {
    pATTACK_PACKAGE p_attack_package = new ATTACK_PACKAGE;
    RtlZeroMemory(p_attack_package, sizeof(ATTACK_PACKAGE));
    p_attack_package->A_RoleKey = nRoleKey;
    p_attack_package->B_MonsterKey = nBoosKey;
    p_attack_package->D_Action = 1;
    int nAddr = CRole::GetRoleAddr();
    martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), p_attack_package->H_RoleOffset74);
    martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), p_attack_package->I_RoleOffset78);

    float role_fx = 0.0f;
    float role_fy = 0.0f;
    float role_fz = 0.0f;
    martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
    martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
    martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);
    *(float*)&p_attack_package->J_RoleOffset60 = role_fx;
    *(float*)&p_attack_package->K_RoleOffset64 = role_fy;
    *(float*)&p_attack_package->L_RoleOffset68 = role_fz;

    p_attack_package->N_AttackPart = nPart;
    martin->Debug(TEXT("������λ: 0x%X"), nPart);

    *(float*)&p_attack_package->P_MonsterCoorX = fx;
    *(float*)&p_attack_package->Q_MonsterCoorY = fy;
    *(float*)&p_attack_package->R_MonsterCoorZ = fz;
    p_attack_package->T_Key2 = 0x35B5B245;

    int nRet = 0;
    char* szCDamageInfo = "CDamageInfo";
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, 0;
            push ecx;
            mov edx, szCDamageInfo; //ASCII �ַ���ָ�� "CDamageInfo" //�����ַ���"CMonsterPartInfo"�ɱ����������岿λ
            push edx;
            mov ecx, 0;
            push ecx;
            mov eax, CALL_GET_GLOBAL_VARIABLE; //CALL_GET_GLOBAL_VARIABLE
            call eax;
            add esp, 0xc;
            mov nRet, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("Send_Attack_Pack -- 1 --> �쳣"));
    }

    if (nRet) {
        int nTemp;
        if (martin->ReadPtrData(nRet + 0x14, TEXT("��ȡ [�������Key] -- 1"), nTemp)) {
            if (martin->ReadPtrData(nTemp + 0x184 * 0x4, TEXT("��ȡ [�������Key] -- 2"), nTemp)) {
                if (martin->ReadPtrData(nTemp + 0x2C, TEXT("��ȡ [�������Key] -- 3"), nRet)) {
                    if (nRet == 0) {
                        nRet = 0xB1714D13;
                    }
                    p_attack_package->F_Key1[0] = nRet;
                    p_attack_package->F_Key1[1] = nRet;
                    for (int i = 0; i < 20; i++) {
                        try {
                            _asm {
                                pushad;
                                pushfd;

                                mov ecx, BASE_CAMERA;
                                mov ecx, [ecx];
                                push p_attack_package;
                                mov eax, CALL_INJURE;
                                call eax;

                                popfd;
                                popad;
                            }
                        } catch (...) {
                            martin->Debug(TEXT("Send_Attack_Pack -- 2 --> �쳣"));
                        }
                    }
                }
            }
        }
    }
    delete p_attack_package;
}

void CRole::GoForward() {
    // ��ǰ��
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 1; //����
            push eax;
            mov eax, 0x11; //��Ӧ'W' //1F��Ӧ��'S' //1E��Ӧ��'A' //20��Ӧ��'D'
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ǰ�� --> �쳣"));
    }
}

void CRole::Stop(std::string pos) {
    int nPos = 0x11;

    if (pos == "����") {
        nPos = 0x1E;
    } else if (pos == "����") {
        nPos = 0x20;
    } else if (pos == "����") {
        nPos = 0x1F;
    }

    // ֹͣ�ƶ�
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 0; //����
            push eax;
            mov eax, nPos; //��Ӧ'W' //1F��Ӧ��'S' //1E��Ӧ��'A' //20��Ӧ��'D'
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("ֹͣ�ƶ� --> �쳣"));
    }
}

void CRole::Attack() {
    int nAddr = CRole::GetRoleAddr();
    int nArg_1 = 0, nArg_2 = 0;
    //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, nAddr; //����ָ��
            mov eax, [ecx];
            add eax, OFFSET_GET_SWITCH_REGION_ECX;
            mov edx, [eax]; //0x178:OFFSET_GET_SWITCH_REGION_ECX
            call edx;

            mov ecx, OFFSET_ATTACK_PARAM1;
            mov eax, [eax + ecx]; //0x1D90:OFFSET_ATTACK_PARAM1
            mov eax, [eax + 0x10];
            mov nArg_1, eax;

            mov eax, [eax + 0x10];
            mov ecx, OFFSET_ATTACK_PARAM2_1;
            mov eax, [eax + ecx]; //0d8:OFFSET_ATTACK_PARAM2_1
            mov ecx, OFFSET_ATTACK_PARAM2_2;
            mov eax, [eax + ecx];//031c:OFFSET_ATTACK_PARAM2_2
            //lea eax, [eax + 0xA * 0x8]; // ���
            lea eax, [eax + 0x5 * 0x8]; // �Ҽ�
            mov nArg_2, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("Attack1 --> �쳣"));
    }

    if (nArg_1 && nArg_2) {
        try {
            _asm {
                pushad;
                pushfd;

                mov eax, nArg_2; //������2����[[[����1+8]+0d8]+31c]+0a*8
                push eax;
                mov eax, nArg_1; //������1����[[[[[[[258590C]+0xc8]+0x28]+214]+90] +1d90]+10]
                push eax;
                mov eax, CALL_ATTACK; //CALL_ATTACK
                call eax;
                add esp, 8;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug(TEXT("Attack2 --> �쳣"));
        }
    }
}

void CRole::Roll() {
    int nAddr = CRole::GetRoleAddr();
    int nArg_1 = 0, nArg_2 = 0;

    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, nAddr; //����ָ��
            mov eax, [ecx];
            add eax, OFFSET_GET_SWITCH_REGION_ECX;
            mov edx, [eax]; //0x178:OFFSET_GET_SWITCH_REGION_ECX
            call edx;

            mov ecx, OFFSET_ATTACK_PARAM1;
            mov eax, [eax + ecx]; //0x1D90:OFFSET_ATTACK_PARAM1
            mov eax, [eax + 0x10];

            mov eax, [eax + 0x8];
            mov ecx, OFFSET_ATTACK_PARAM2_1;
            mov eax, [eax + ecx]; //0d8:OFFSET_ATTACK_PARAM2_1
            mov edi, eax;

            mov ecx, OFFSET_DODGE_ACTION;
            mov edi, [edi + ecx];//0334
            mov nArg_1, edi;

            mov ecx, OFFSET_ATTACK_PARAM2_2;
            mov eax, [eax + ecx];//031c:OFFSET_ATTACK_PARAM2_2
            lea eax, [eax + 0x0 * 0x8];
            mov nArg_2, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug("Roll -- 1 --> �쳣");
        return;
    }

    try {
    	_asm {
    		pushad;
    		pushfd;
    		
            mov ecx, nArg_1;
            mov eax, nArg_2;
            push eax;
            mov eax, CALL_DO_ACTION;
            call eax;
    		
    		popfd;
    		popad;
    	}
    } catch (...) {
        martin->Debug("Roll -- 2 --> �쳣");
    }
}

int CRole::HaveWeapon() {
    int nRet = 0xFFFFFFFF;
    int nAddr = CRole::GetRoleAddr();
    if (martin->ReadPtrData(nAddr + 0x90, TEXT("��ȡ�Ƿ�װ������"), nAddr)) {
        martin->ReadPtrData(nAddr + OFFSET_WEAPON, TEXT("��ȡ�Ƿ�װ������"), nRet);
    }
    return nRet;
}

int CRole::HaveMode() {
    int nRet = 0xFFFFFFFF;
    try {
    	_asm {
    		pushad;
    		pushfd;
    		
            mov eax, CALL_GET_UI_MODE; //CALL_GET_UI_MODE
            call eax;
            mov nRet, eax;
    		
    		popfd;
    		popad;
    	}
    } catch (...) {
    }
    return nRet;
}

void CRole::Weapon() {
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 1; //����
            push eax;
            mov eax, 0x10; //��Ӧ'W' //1F��Ӧ��'S' //1E��Ӧ��'A' //20��Ӧ��'D'
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("Weapon -- 1 --> �쳣"));
    }

    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 0; //����
            push eax;
            mov eax, 0x10; //��Ӧ'W' //1F��Ӧ��'S' //1E��Ӧ��'A' //20��Ӧ��'D'
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("Weapon -- 2 --> �쳣"));
    }
}

int CRole::Decode(int nData) {
    int cad = CALL_VALUE_DECRYPT;
    int nRet = 0;

    try {
        _asm {
            pushad;
            pushfd;

            mov  ecx, nData;
            mov  eax, cad;
            call eax;
            mov  nRet, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("Decode --> �쳣"));
    }
    return nRet;
}

float CRole::GetHpPer() {
    int nRoleAddr = GetRoleAddr();
    int nowHp = Decode(nRoleAddr + OFFSET_ROLE_CURHP) - 0x64;
    int maxHp = Decode(nRoleAddr + OFFSET_ROLE_HP);
    float fNowHp = nowHp * 1.0f;
    float fMaxHp = maxHp * 1.0f;
    return fNowHp / fMaxHp;
}

_declspec(naked) void Invincible() {
    _asm {
        ret;
    }
}

void CRole::Invincible() {
    m_hook.bSwitch = FALSE;
    if (m_hook.IsHook == FALSE) {
        m_hook.StartHookByByte(HOOK_INVINCIBLE, (DWORD)Invincible, 6);
    }
}

void CRole::UnInvincible() {
    if (m_hook.IsHook == TRUE) {
        m_hook.UnHookByByte();
    }
}

BOOL GetCat(int nKey) {
    int nEbx = 0, nRet = 0;
    if (martin->ReadPtrData(BASE_GAME, TEXT("���ܶ��� Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("���ܶ��� Key -- 2"), nEbx)) {
            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                    mov eax, [ebx];
                    mov edx, nKey; //����Key
                    push edx;
                    mov edx, [eax + 0x2C];
                    mov ecx, ebx;
                    call edx;
                    mov nRet, eax;

                    popfd;
                    popad;
                }
            } catch (...) {
                martin->Debug(TEXT("GetCat -- 1 --> �쳣"));
                return FALSE;
            }
        }
    }

    if (nRet) {
        int nRet_2 = 0;
        try {
            _asm {
                pushad;
                pushfd;

                mov ecx, nRet;  //����ָ��(������ ������Keyȡ����ָ�롿�ķ���ֵ)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug(TEXT("GetCat -- 2 --> �쳣"));
            return FALSE;
        }

        if (nRet_2) {
            int nName = 0;
            std::string strName = CNearObject::GetObjectName(nRet_2);

            int nRoleAddr;
            std::string strRoleName = "δ֪������";
            if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ��ǰ����ָ�� -- 1"), nRoleAddr)) {
                if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_1, TEXT("��ȡ��ǰ����ָ�� -- 2"), nRoleAddr)) {
                    if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_2, TEXT("��ȡ��ǰ����ָ�� -- 3"), nRoleAddr)) {
                        if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_4, TEXT("��ȡ��ǰ����ָ�� -- 4"), nRoleAddr)) {
                            strRoleName = CNearObject::GetObjectName(nRoleAddr);
                        }
                    }
                }
            }
            std::string::size_type idx = strName.find(strRoleName);
            if (idx != std::string::npos && strName != strRoleName) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

int FindCatKey() {
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;

    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [è��Ϣ] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [è��Ϣ] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("��ȡ [è��Ϣ] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("��ȡ [è��Ϣ] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    //martin->Debug(TEXT("bEmpty : %d"), bEmpty);
                    //if (!bEmpty) {
                    int nTempEsi_Next = nRoot;
                    while (nTempEsi_Next != nEnd) {
                        int nTempNode = 0, nCurrentKey = 0;
                        martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 1"), nTempNode);
                        martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("��ȡ [�ڵ�Key]"), nCurrentKey);
                        //TODO:���ݶ���Keyȡ����������ָ��...�μ���������Keyȡ����ָ�롿
                        //martin->Debug(TEXT("Key: 0x%X"), nCurrentKey);
                        if (GetCat(nCurrentKey) == TRUE) { // ˵���ҵ� BOSS �����ٱ�����
                            return nCurrentKey;
                        }

                        if (++nNodeCount > 0x400) {//����������ֹ����̫��
                            break;
                        }

                        if (nTempNode != 0) {
                            nTempEsi_Next = nTempNode;
                            int nTemp = 0;
                            while (true) {
                                martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("��ȡ [�ڵ�8]"), nTemp);
                                if (nTemp != 0) {
                                    nTempEsi_Next = nTemp;
                                } else {
                                    break;
                                }
                            }
                        } else {
                            martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("��ȡ [�ڵ�4] --1"), nTempNode);
                            int nTemp = 0;
                            martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 2"), nTemp);

                            if (nTempEsi_Next == nTemp) {
                                do {
                                    nTempEsi_Next = nTempNode;
                                    martin->ReadPtrData(nTempNode + 0x4, TEXT("��ȡ [�ڵ�4] -- 2"), nTempNode);
                                    martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 3"), nTemp);
                                } while (nTempEsi_Next == nTemp);
                            }

                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 4"), nTemp);
                            if (nTemp != nTempNode) {
                                nTempEsi_Next = nTempNode;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0xFFFFFFFF;
}

void ReplaceKill() {
    int nAttackID = 0xFFFFFFFF, nCatKey_2 = 0xFFFFFFFF;
    int nEsi = 0xFFFFFFFF;

    _asm {
        pushad;
        pushfd;

        mov nEsi, esi;
        mov ecx, [esi];
        mov nAttackID, ecx; // ������ Key

        mov ecx, [esi + 0x4]; // �������� Key
        mov nCatKey_2, ecx;

        popfd;
        popad;
    }

    int nCatKey = FindCatKey();

    if (nCatKey == nCatKey_2) { // �����è��������, ������
        return;
    }

    //for (int i = 0; i < g_nKill; i++) {
        _asm {
            pushad;
            pushfd;

            mov ecx, BASE_CAMERA;
            mov ecx, [ecx];
            push esi;
            mov eax, CALL_INJURE;
            call eax;

            popfd;
            popad;
        }
    //}
}

_declspec(naked) void MultipleKill() {
    _asm {
        pushad;
        pushfd;
    }

    ReplaceKill();

    _asm {
        popfd;
        popad;
        ret;
    }
}

void CRole::CatInvincible() {
    m_CatHook.bSwitch = FALSE;
    if (m_CatHook.IsHook == FALSE) {
        m_CatHook.StartHookByByte(HOOK_INJURE, (DWORD)MultipleKill, 12);
    }
}

void CRole::TeleportToPoint(float fx, float fy, float fz) {
    int nRoleAddr = 0, nRoleKey = 0;
    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [��ǰ����ָ��] -- 1"), nRoleAddr)) {
        if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_1, TEXT("��ȡ [��ǰ����ָ��] -- 2"), nRoleAddr)) {
            if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_2, TEXT("��ȡ [��ǰ����ָ��] -- 3"), nRoleAddr)) {
                if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_4, TEXT("��ȡ [��ǰ����ָ��] -- 4"), nRoleAddr)) {
                    if (martin->ReadPtrData(nRoleAddr + 0x8, TEXT("��ȡ [��ǰ���� KEY]"), nRoleKey)) {
                        // ˲��
                        CRole::RoleTeleport(nRoleKey, fx, fy, fz);
                    }
                }
            }
        }
    }
}

void CRole::GetPoint(float& fx, float& fy, float& fz) {
    int nRoleAddr = GetRoleAddr();
    martin->ReadPtrData(nRoleAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), fx);
    martin->ReadPtrData(nRoleAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), fy);
    martin->ReadPtrData(nRoleAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), fz);
}

void CRole::GoLeft() {
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 1; //����
            push eax;
            mov eax, 0x1E; //��Ӧ'W' //1F��Ӧ��'S' //1E��Ӧ��'A' //20��Ӧ��'D'
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ǰ�� --> �쳣"));
    }
}

void CRole::GoRight() {
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 1; //����
            push eax;
            mov eax, 0x20; //��Ӧ'W' //1F��Ӧ��'S' //1E��Ӧ��'A' //20��Ӧ��'D'
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ǰ�� --> �쳣"));
    }
}

void CRole::GoBack() {
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 1; //����
            push eax;
            mov eax, 0x1F; //��Ӧ'W' //1F��Ӧ��'S' //1E��Ӧ��'A' //20��Ӧ��'D'
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ǰ�� --> �쳣"));
    }
}

void CRole::ChangeMode() {
    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 1; //����
            push eax;
            mov eax, 0x29; //11��Ӧ'W' //1E��Ӧ��'A' //1F��Ӧ��'S' //20��Ӧ��'F'//10��Ӧ'Q' //29��Ӧ'`'(����/�ر� �˵�)
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ǰ�� --> �쳣"));
    }

    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 0; //����
            push eax;
            mov eax, 0x29; //11��Ӧ'W' //1E��Ӧ��'A' //1F��Ӧ��'S' //20��Ӧ��'F'//10��Ӧ'Q' //29��Ӧ'`'(����/�ر� �˵�)
            push eax;
            mov ecx, BASE_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            add ecx, OFFSET_KEYBOARD_HANDLER;
            mov ecx, [ecx];
            mov ecx, [ecx]; //[[[BASE_KEYBOARD_HANDLER]+OFFSET_KEYBOARD_HANDLER]]
            mov eax, CALL_KEYBOARD_EVENT_HANDLE;
            call eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("��ǰ�� --> �쳣"));
    }
}

void CRole::initAllItems() {
    int nRet = 0;
    char* szItemBaseInfo = "CItemBaseInfo";
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, 0;
            push ecx;
            mov edx, szItemBaseInfo; //ASCII �ַ���ָ�� "CDamageInfo" //�����ַ���"CMonsterPartInfo"�ɱ����������岿λ
            push edx;
            mov ecx, 0;
            push ecx;
            mov eax, CALL_GET_GLOBAL_VARIABLE; //CALL_GET_GLOBAL_VARIABLE
            call eax;
            add esp, 0xc;
            mov nRet, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("initAllItems -- 1 --> �쳣"));
    }

    if (nRet) {
        DWORD dwStart, dwEnd;
        martin->ReadPtrData(nRet + 0x14, TEXT("��ȡ [��Ʒ��Ϣ����ͷ]"), dwStart);
        martin->ReadPtrData(nRet + 0x18, TEXT("��ȡ [��Ʒ��Ϣ����β]"), dwEnd);

        for (unsigned i = dwStart; i < dwEnd; i += 0x4) {
            DWORD dwTmep;
            if (martin->ReadPtrData(i, TEXT("��ȡ [��Ʒ��Ϣ����]"), dwTmep)) {
                if (IsBadReadPtr((CONST VOID*)dwTmep, sizeof(DWORD)) == 0) {
                    DWORD dwName;
                    if (martin->ReadPtrData(dwTmep + 0x14, TEXT("��ȡ [��Ʒ��]"), dwName)) {
                        try {
                            if (dwName != 0x0) {
                                int nID;
                                std::string strNmae = (CHAR*)dwName;
                                //martin->Debug("ȫ����Ʒ: %s -- ID: 0x%X", strNmae.c_str(), nID);
                                martin->ReadPtrData(dwTmep + 0x10, TEXT("��ȡ [��ƷID]"), nID);
                                CRole::s_allItems.insert(std::map<int, std::string>::value_type(nID, strNmae));
                                //auto it = CRole::s_allItems.find(strNmae);
                                //if (it == CRole::s_allItems.end()) { // û�ҵ������
                                //    CRole::s_allItems.insert(std::map<std::string, int>::value_type(strNmae, nID));
                                //} else {
                                //    // it->second = nID;
                                //}
                            }
                        } catch (...) {
                            martin->Debug(TEXT("��ȡ��Ʒ�� --> �쳣"));
                        }
                    }
                }
            }
        }
    }
}

BOOL CRole::WhetherOrBusy() {
    int nAddr = CRole::GetRoleAddr();
    int nRet = 1;
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, nAddr; //����ָ��
            mov eax, [ecx];
            mov edx, OFFSET_GET_SWITCH_REGION_ECX;
            mov edx, [eax + edx]; //0x178:
            call edx;
            mov ecx, OFFSET_ROLE_IDLE_STATE_1;
            mov eax, [eax + ecx]; //1b80:
            mov ecx, OFFSET_ROLE_IDLE_STATE_2;
            mov eax, [eax + ecx];   //24:
            mov ecx, OFFSET_ROLE_IDLE_STATE_3;
            mov eax, [eax + ecx]; //135c:
            mov eax, [eax + 8];
            mov ecx, eax;
            mov eax, CALL_GET_OBJECT_IDLE_STATE; //
            call eax;
            movzx ecx, al;
            mov nRet, ecx;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("WhetherOrBusy --> �쳣"));
        return TRUE;
    }

    if (nRet == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void CRole::Collect(int nID) {
    int nAddr = CRole::GetRoleAddr();

    try {
        _asm {
            pushad;
            pushfd;

            mov eax, 0;       //�̶�ֵ
            push eax;
            mov eax, 0;       //�̶�ֵ
            push eax;
            mov eax, 5;        //�̶�ֵ
            push eax;
            mov eax, nID; //�ɼ���ID
            push eax;
            mov ecx, nAddr;
            mov edx, OFFSET_COLLECTING_ACTION;
            mov ecx, [ecx + edx];
            mov ecx, [ecx + 0x8]; //[[����ָ��+204c]+8]  //[[����ָ��+OFFSET_COLLECTING_ACTION]+8]
            mov edx, CALL_COLLECTING2; //
            call edx;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("Collect --> �쳣"));
    }
}