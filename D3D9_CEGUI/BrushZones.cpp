#include "BrushZones.h"
#include "Martin.h"
#include "Base.h"
#include "DataType.h"
#include "Role.h"
#include "NearObject.h"
#include "GlobalVariable.h"

std::map<std::string, int> CBrushZones::s_fbMap;
std::list<Monster> CBrushZones::m_monster_list;
pMonster CBrushZones::m_monster = nullptr;

CBrushZones::CBrushZones() {
}


CBrushZones::~CBrushZones() {
}

void CBrushZones::initZonesInfo() {
    CBrushZones::s_fbMap.clear();
    int nRet = 0;
    char* szCMHLevelInfo = "CMHLevelInfo";
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, 0;
            push ecx;
            mov edx, szCMHLevelInfo; //ASCII �ַ���ָ�� "CDamageInfo" //�����ַ���"CMonsterPartInfo"�ɱ����������岿λ
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
        martin->Debug(TEXT("initZonesInfo --> �쳣"));
    }

    if (nRet) {
        //martin->Debug(TEXT("0x%X"), nRet);
        DWORD dwStart, dwEnd;
        martin->ReadPtrData(nRet + 0x14, TEXT("��ȡ [��ͼ��Ϣ����ͷ]"), dwStart);
        martin->ReadPtrData(nRet + 0x18, TEXT("��ȡ [��ͼ��Ϣ����ͷ]"), dwEnd);
        for (unsigned i = dwStart; i < dwEnd; i += 0x4) {
            DWORD dwTmep;
            if (martin->ReadPtrData(i, TEXT("��ȡ [��ͼ��Ϣ����]"), dwTmep)) {
                if (IsBadReadPtr((CONST VOID*)dwTmep, sizeof(DWORD)) == 0) {
                    DWORD dwName;
                    if (martin->ReadPtrData(dwTmep + 0x1C, TEXT("��ȡ [��ͼ��]"), dwName)) {
                        try {
                            if (dwName != 0x0) {
                                int nID;
                                std::string strNmae = (CHAR*)dwName;
                                std::string::size_type idx_1 = strNmae.find("�ؿ�");
                                std::string::size_type idx_2 = strNmae.find("����");
                                std::string::size_type idx_3 = strNmae.find("map");

                                if (idx_1 == std::string::npos          // û�ҵ� "�ؿ�"
                                    && idx_2 == std::string::npos       // û�ҵ� "����"
                                    && idx_3 == std::string::npos) {    // û�ҵ� "map"
                                    //martin->Debug(strNmae.c_str());
                                    martin->ReadPtrData(dwTmep + 0x10, TEXT("��ȡ [��ͼID]"), nID);
                                    auto it = CBrushZones::s_fbMap.find(strNmae);
                                    if (it == CBrushZones::s_fbMap.end()) {
                                        CBrushZones::s_fbMap.insert(std::map<std::string, int>::value_type(strNmae, nID));
                                    } else {
                                        it->second = nID;
                                    }
                                }
                            }
                        } catch (...) {
                            martin->Debug(TEXT("��ȡ��ͼ�� --> �쳣"));
                        }
                    }
                }
            }
        }
    }
}

void CBrushZones::ChooseFB(int nZoneId) {
    pCHOOSE_FB_PACKAGE pCfp = new CHOOSE_FB_PACKAGE;
    RtlZeroMemory(pCfp, sizeof(CHOOSE_FB_PACKAGE));
    pCfp->A_ = 0x19;
    pCfp->E_ = 0x1;
    pCfp->F_ = 0x1;
    pCfp->G_ = nZoneId;
    pCfp->H_ = 0x1;
    CRole::SendPackage((DWORD)pCfp);
    delete pCfp;
}

void CBrushZones::StartFB(int nZoneId) {
    pSTART_FB_PACKAGE pSfp = new START_FB_PACKAGE;
    RtlZeroMemory(pSfp, sizeof(START_FB_PACKAGE));
    pSfp->A_ = 0x21;
    pSfp->E_ = 0x1;
    pSfp->F_ = 0x1;
    pSfp->G_ = nZoneId;
    CRole::SendPackage((DWORD)pSfp);
    delete pSfp;
}

void CBrushZones::IntoFB() {
    pSET_OUT_FB_PACKAGE pSofp = new SET_OUT_FB_PACKAGE;
    RtlZeroMemory(pSofp, sizeof(SET_OUT_FB_PACKAGE));
    pSofp->A_ = 0x23;
    pSofp->E_ = 0x1;
    pSofp->H_ = 0x1;
    CRole::SendPackage((DWORD)pSofp);
    delete pSofp;
}

void CBrushZones::initBoss() {
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;
    m_nBossRoom = 0;
    m_strBossName = "";

    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [BOSS��Ϣ] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [BOSS��Ϣ] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("��ȡ [BOSS��Ϣ] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("��ȡ [BOSS��Ϣ] -- 4"), bEmpty)) {
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
                            if (CBrushZones::GetBoss(nCurrentKey) == TRUE) { // ˵���ҵ� BOSS �����ٱ�����
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

BOOL CBrushZones::GetBoss(int nKey) {
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
                martin->Debug("GetBoss -- 1 --> �쳣");
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
            martin->Debug("GetBoss -- 2 --> �쳣");
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
                martin->Debug("GetBoss -- 3 --> �쳣");
                return FALSE;
            }

            if (nDead == 1) {
                return FALSE;
            }

            int nName = 0;

            std::string strName = CNearObject::GetObjectName(nRet_2);
            //martin->Debug(strName.c_str());
            for (int i = 0; BossName[i] != ""; i++) {
                if (BossName[i] == strName) { // �ҵ� BOSS
                    m_strBossName = strName;
                    // ��ȡ�����, ��ʾ�ڱ���
                    // martin->Debug(TEXT("�ҵ� BOSS -- %s"), A2W(strName.c_str()));
                    int nIndex = 0;
                    martin->ReadPtrData(nRet_2 + 0x2C, TEXT("��ȡ [BOSS�����]"), nIndex);
                    m_nBossRoom = nIndex;
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

void CBrushZones::GotoBoss() {
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;

    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [BOSS��Ϣ] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [BOSS��Ϣ] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("��ȡ [BOSS��Ϣ] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("��ȡ [BOSS��Ϣ] -- 4"), bEmpty)) {
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
                            if (CBrushZones::Teleport(nCurrentKey) == TRUE) { // ˵���ҵ� BOSS �����ٱ�����
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

BOOL CBrushZones::Teleport(int nKey) {
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
                martin->Debug("Teleport -- 1 --> �쳣");
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
            martin->Debug("Teleport -- 2 --> �쳣");
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
                martin->Debug("Teleport -- 3 --> �쳣");
                return FALSE;
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
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("��ȡ [BOSS ����]"), fx);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("��ȡ [BOSS ����]"), fy);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x8, TEXT("��ȡ [BOSS ����]"), fz);
                    // martin->Debug("BOSS ����: %f, %f, %f", fx, fy, fz);

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
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

void CBrushZones::GetItemFormCrates(std::string strItem) {
    DWORD dwRet, dwStart, dwEnd;

    try {
        _asm {
            pushad;
            pushfd;

            mov eax, BASE_SUPPLY_BOX;
            mov edi, [eax];
            mov eax, [edi];
            mov edx, OFFSET_GET_SUPPLY_BOX;
            mov edx, [eax + edx]; //0x164:OFFSET_GET_SUPPLY_BOX 
            mov ecx, edi;
            call edx;
            mov dwRet, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug("GetItemFormCrates --> �쳣");
        return;
    }

    if (IsBadReadPtr((CONST VOID*)dwRet, sizeof(DWORD)) == 0) {
        DWORD dwTemp;
        if (martin->ReadPtrData(dwRet + 0x8, "��ȡ [��Ʒ��������] -- 1", dwTemp)) {
            if (martin->ReadPtrData(dwTemp, "��ȡ [��Ʒ��������] -- 2", dwTemp)) {
                martin->ReadPtrData(dwTemp + 0x10, "��ȡ [��Ʒ����������]", dwStart);
                martin->ReadPtrData(dwTemp + 0x14, "��ȡ [��Ʒ��������β]", dwEnd);
                std::multimap<std::string, IdIndex> CratesMap;
                TraverList(dwStart, dwEnd, CratesMap);
                for (auto itMap = CratesMap.begin(); itMap != CratesMap.end(); itMap++) {
                    martin->Debug("��������Ʒ: %s -- ���: %d -- ID: 0x%X", (itMap->first).c_str(), (itMap->second).dwIndex, (itMap->second).dwID);
                }

                auto it = CratesMap.find(strItem);
                if (it != CratesMap.end()) { // ˵��ƥ�䵽ID��
                    // ȡ��Ʒ
                    GetItemPack(it->second.dwIndex, it->second.dwID);
                }
            }
        }
    }
}

void CBrushZones::TraverList(int nStart, int nEnd, std::multimap<std::string, IdIndex>& CratesMap) {
    pCratesList pList;
    pList = (pCratesList)nStart;
    allotItem(pList->dwBase, CratesMap);

    if (nStart == nEnd) {
        return;
    } else {
        TraverList(pList->dwNext, nEnd, CratesMap);
    }
}

void CBrushZones::allotItem(int nObject, std::multimap<std::string, IdIndex>& CratesMap) {
    int nIndex, nID;
    std::string strName;
    martin->ReadPtrData(nObject, "��ȡ [��������Ʒ���]", nIndex);
    martin->ReadPtrData(nObject + 0x4, "��ȡ [��������ƷID]", nID);
    //martin->Debug("ID: 0x%X", nID);

    auto it = CRole::s_allItems.find(nID);
    if (it != CRole::s_allItems.end()) { // ˵��ƥ�䵽ID��
        strName = it->second.strName;
        IdIndex idindex{ nID, nIndex };
        CratesMap.insert(std::map<std::string, IdIndex>::value_type(strName, idindex));
    }
}

void CBrushZones::GetItemPack(int nIndex, int nID) {
    pGET_ITEM_PACKAGE pGip = new GET_ITEM_PACKAGE;
    RtlZeroMemory(pGip, sizeof(GET_ITEM_PACKAGE));
    pGip->A_Head = 0xD01;
    pGip->E_Index = nIndex;
    pGip->F_ID = nID;
    pGip->G_Num = 1;
    CRole::SendPackage((DWORD)pGip);
    delete pGip;
}

int CBrushZones::��ȡʱ���() {
    int nRet = 0;
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, BASE_GAME;
            mov ecx, [ecx];
            mov ecx, [ecx + 0x4];
            mov ecx, [ecx + 0xC]; //[[[BASE_GAME]+4]+0c]
            mov edx, [ecx];
            add edx, OFFSET_GET_TIMESTAMP;
            mov eax, [edx];
            call eax;
            mov nRet, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug("��ȡʱ��� --> �쳣");
    }
    return nRet;
}

void CBrushZones::initMonster(std::string strMonster) {
    m_monster_list.clear();
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;

    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [BOSS��Ϣ] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [BOSS��Ϣ] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("��ȡ [BOSS��Ϣ] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("��ȡ [BOSS��Ϣ] -- 4"), bEmpty)) {
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
                            CBrushZones::GetMonster(nCurrentKey, strMonster);

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

void CBrushZones::GetMonster(int nKey, std::string strMonster) {
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
                martin->Debug("GetMonster -- 1 --> �쳣");
                return;
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
            martin->Debug("GetMonster -- 2 --> �쳣");
            return;
        }

        if (nRet_2) {
            std::string strName = CNearObject::GetObjectName(nRet_2);
            //martin->Debug(strName.c_str());
            if (strMonster == strName) { // �ҵ� ����
                Monster monster;
                monster.strMonsterName = strName;
                int nIndex = 0;
                martin->ReadPtrData(nRet_2 + 0x2C, TEXT("��ȡ [���� �����]"), nIndex);

                martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("��ȡ [BOSS ����]"), monster.fMonsterPointX);
                martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("��ȡ [BOSS ����]"), monster.fMonsterPointY);
                martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x8, TEXT("��ȡ [BOSS ����]"), monster.fMonsterPointZ);

                monster.nMonsterRoom = nIndex;

                // �ж��Ƿ�����
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
                    martin->Debug("GetMonster -- 3 --> �쳣");
                    return;
                }

                if (nDead == 1) {
                    monster.bIsDead = TRUE;
                } else {
                    monster.bIsDead = FALSE;
                }

                monster.nMonsterAddr = nRet_2;

                float fPointX, fPointY, fPointZ;
                CRole::GetPoint(fPointX, fPointY, fPointZ);
                monster.fDistance = martin->Compare_Coord(fPointX, fPointY, monster.fMonsterPointX, monster.fMonsterPointY);

                m_monster_list.push_back(monster);

                return;
            }
        }
    }

    return;
}