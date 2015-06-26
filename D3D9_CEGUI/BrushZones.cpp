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
            mov edx, szCMHLevelInfo; //ASCII 字符串指针 "CDamageInfo" //传入字符串"CMonsterPartInfo"可遍历所有身体部位
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
        martin->Debug(TEXT("initZonesInfo --> 异常"));
    }

    if (nRet) {
        //martin->Debug(TEXT("0x%X"), nRet);
        DWORD dwStart, dwEnd;
        martin->ReadPtrData(nRet + 0x14, TEXT("获取 [地图信息数组头]"), dwStart);
        martin->ReadPtrData(nRet + 0x18, TEXT("获取 [地图信息数组头]"), dwEnd);
        for (unsigned i = dwStart; i < dwEnd; i += 0x4) {
            DWORD dwTmep;
            if (martin->ReadPtrData(i, TEXT("获取 [地图信息数组]"), dwTmep)) {
                if (IsBadReadPtr((CONST VOID*)dwTmep, sizeof(DWORD)) == 0) {
                    DWORD dwName;
                    if (martin->ReadPtrData(dwTmep + 0x1C, TEXT("获取 [地图名]"), dwName)) {
                        try {
                            if (dwName != 0x0) {
                                int nID;
                                std::string strNmae = (CHAR*)dwName;
                                std::string::size_type idx_1 = strNmae.find("关卡");
                                std::string::size_type idx_2 = strNmae.find("测试");
                                std::string::size_type idx_3 = strNmae.find("map");

                                if (idx_1 == std::string::npos          // 没找到 "关卡"
                                    && idx_2 == std::string::npos       // 没找到 "测试"
                                    && idx_3 == std::string::npos) {    // 没找到 "map"
                                    //martin->Debug(strNmae.c_str());
                                    martin->ReadPtrData(dwTmep + 0x10, TEXT("获取 [地图ID]"), nID);
                                    auto it = CBrushZones::s_fbMap.find(strNmae);
                                    if (it == CBrushZones::s_fbMap.end()) {
                                        CBrushZones::s_fbMap.insert(std::map<std::string, int>::value_type(strNmae, nID));
                                    } else {
                                        it->second = nID;
                                    }
                                }
                            }
                        } catch (...) {
                            martin->Debug(TEXT("获取地图名 --> 异常"));
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

    if (martin->ReadPtrData(BASE_GAME, TEXT("读取 [BOSS信息] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("读取 [BOSS信息] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("读取 [BOSS信息] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("读取 [BOSS信息] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    //martin->Debug(TEXT("bEmpty : %d"), bEmpty);
                    if (!bEmpty) {
                        int nTempEsi_Next = nRoot;
                        while (nTempEsi_Next != nEnd) {
                            int nTempNode = 0, nCurrentKey = 0;
                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 1"), nTempNode);
                            martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("读取 [节点Key]"), nCurrentKey);
                            //TODO:根据对象Key取出对象详情指针...参见：【根据Key取对象指针】
                            //martin->Debug(TEXT("Key: 0x%X"), nCurrentKey);
                            if (CBrushZones::GetBoss(nCurrentKey) == TRUE) { // 说明找到 BOSS 不用再遍历了
                                break;
                            }

                            if (++nNodeCount > 0x400) {//计数器，防止遍历太多
                                break;
                            }

                            if (nTempNode != 0) {
                                nTempEsi_Next = nTempNode;
                                int nTemp = 0;
                                while (true) {
                                    martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("读取 [节点8]"), nTemp);
                                    if (nTemp != 0) {
                                        nTempEsi_Next = nTemp;
                                    } else {
                                        break;
                                    }
                                }
                            } else {
                                martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("读取 [节点4] -- 1"), nTempNode);
                                int nTemp = 0;
                                martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 2"), nTemp);

                                if (nTempEsi_Next == nTemp) {
                                    do {
                                        nTempEsi_Next = nTempNode;
                                        martin->ReadPtrData(nTempNode + 0x4, TEXT("读取 [节点4] -- 2"), nTempNode);
                                        martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 3"), nTemp);
                                    } while (nTempEsi_Next == nTemp);
                                }

                                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 4"), nTemp);
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
    if (martin->ReadPtrData(BASE_GAME, TEXT("解密对象 Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("解密对象 Key -- 2"), nEbx)) {
            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                    mov eax, [ebx];
                    mov edx, nKey; //对象Key
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
                martin->Debug("GetBoss -- 1 --> 异常");
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

                mov ecx, nRet;  //对象指针(来自于 【根据Key取对象指针】的返回值)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug("GetBoss -- 2 --> 异常");
            return FALSE;
        }

        if (nRet_2) {
            // 先判断是否死亡
            int nDead = 0;
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ecx, nRet_2; //对象指针
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
                martin->Debug("GetBoss -- 3 --> 异常");
                return FALSE;
            }

            if (nDead == 1) {
                return FALSE;
            }

            int nName = 0;

            std::string strName = CNearObject::GetObjectName(nRet_2);
            //martin->Debug(strName.c_str());
            for (int i = 0; BossName[i] != ""; i++) {
                if (BossName[i] == strName) { // 找到 BOSS
                    m_strBossName = strName;
                    // 获取房间号, 显示在标题
                    // martin->Debug(TEXT("找到 BOSS -- %s"), A2W(strName.c_str()));
                    int nIndex = 0;
                    martin->ReadPtrData(nRet_2 + 0x2C, TEXT("获取 [BOSS房间号]"), nIndex);
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

    if (martin->ReadPtrData(BASE_GAME, TEXT("读取 [BOSS信息] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("读取 [BOSS信息] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("读取 [BOSS信息] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("读取 [BOSS信息] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    //martin->Debug(TEXT("bEmpty : %d"), bEmpty);
                    if (!bEmpty) {
                        int nTempEsi_Next = nRoot;
                        while (nTempEsi_Next != nEnd) {
                            int nTempNode = 0, nCurrentKey = 0;
                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 1"), nTempNode);
                            martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("读取 [节点Key]"), nCurrentKey);
                            //TODO:根据对象Key取出对象详情指针...参见：【根据Key取对象指针】
                            //martin->Debug(TEXT("Key: 0x%X"), nCurrentKey);
                            if (CBrushZones::Teleport(nCurrentKey) == TRUE) { // 说明找到 BOSS 不用再遍历了
                                break;
                            }

                            if (++nNodeCount > 0x400) {//计数器，防止遍历太多
                                break;
                            }

                            if (nTempNode != 0) {
                                nTempEsi_Next = nTempNode;
                                int nTemp = 0;
                                while (true) {
                                    martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("读取 [节点8]"), nTemp);
                                    if (nTemp != 0) {
                                        nTempEsi_Next = nTemp;
                                    } else {
                                        break;
                                    }
                                }
                            } else {
                                martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("读取 [节点4] -- 1"), nTempNode);
                                int nTemp = 0;
                                martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 2"), nTemp);

                                if (nTempEsi_Next == nTemp) {
                                    do {
                                        nTempEsi_Next = nTempNode;
                                        martin->ReadPtrData(nTempNode + 0x4, TEXT("读取 [节点4] -- 2"), nTempNode);
                                        martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 3"), nTemp);
                                    } while (nTempEsi_Next == nTemp);
                                }

                                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 4"), nTemp);
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
    if (martin->ReadPtrData(BASE_GAME, TEXT("解密对象 Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("解密对象 Key -- 2"), nEbx)) {
            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                    mov eax, [ebx];
                    mov edx, nKey; //对象Key
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
                martin->Debug("Teleport -- 1 --> 异常");
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

                mov ecx, nRet;  //对象指针(来自于 【根据Key取对象指针】的返回值)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug("Teleport -- 2 --> 异常");
            return FALSE;
        }

        if (nRet_2) {
            // 先判断是否死亡
            int nDead = 0;
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ecx, nRet_2; //对象指针
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
                martin->Debug("Teleport -- 3 --> 异常");
                return FALSE;
            }

            if (nDead == 1) {
                return FALSE;
            }

            int nName = 0;
            std::string strName = CNearObject::GetObjectName(nRet_2);
            for (int i = 0; BossName[i] != ""; i++) {
                if (BossName[i] == strName) { // 找到 BOSS
                    // 获取 BOSS 坐标
                    float fx, fy, fz;
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("获取 [BOSS 坐标]"), fx);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("获取 [BOSS 坐标]"), fy);
                    martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x8, TEXT("获取 [BOSS 坐标]"), fz);
                    // martin->Debug("BOSS 坐标: %f, %f, %f", fx, fy, fz);

                    int nRoleAddr = 0, nRoleKey = 0;
                    if (martin->ReadPtrData(BASE_GAME, TEXT("获取 [当前人物指针] -- 1"), nRoleAddr)) {
                        if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_1, TEXT("获取 [当前人物指针] -- 2"), nRoleAddr)) {
                            if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_2, TEXT("获取 [当前人物指针] -- 3"), nRoleAddr)) {
                                if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_4, TEXT("获取 [当前人物指针] -- 4"), nRoleAddr)) {
                                    if (martin->ReadPtrData(nRoleAddr + 0x8, TEXT("获取 [当前人物 KEY]"), nRoleKey)) {
                                        // 瞬移
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
        martin->Debug("GetItemFormCrates --> 异常");
        return;
    }

    if (IsBadReadPtr((CONST VOID*)dwRet, sizeof(DWORD)) == 0) {
        DWORD dwTemp;
        if (martin->ReadPtrData(dwRet + 0x8, "获取 [物品遍历链表] -- 1", dwTemp)) {
            if (martin->ReadPtrData(dwTemp, "获取 [物品遍历链表] -- 2", dwTemp)) {
                martin->ReadPtrData(dwTemp + 0x10, "获取 [物品遍历链表首]", dwStart);
                martin->ReadPtrData(dwTemp + 0x14, "获取 [物品遍历链表尾]", dwEnd);
                std::multimap<std::string, IdIndex> CratesMap;
                TraverList(dwStart, dwEnd, CratesMap);
                for (auto itMap = CratesMap.begin(); itMap != CratesMap.end(); itMap++) {
                    martin->Debug("补给箱物品: %s -- 序号: %d -- ID: 0x%X", (itMap->first).c_str(), (itMap->second).dwIndex, (itMap->second).dwID);
                }

                auto it = CratesMap.find(strItem);
                if (it != CratesMap.end()) { // 说明匹配到ID了
                    // 取物品
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
    martin->ReadPtrData(nObject, "获取 [补给箱物品序号]", nIndex);
    martin->ReadPtrData(nObject + 0x4, "获取 [补给箱物品ID]", nID);
    //martin->Debug("ID: 0x%X", nID);

    auto it = CRole::s_allItems.find(nID);
    if (it != CRole::s_allItems.end()) { // 说明匹配到ID了
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

int CBrushZones::获取时间戳() {
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
        martin->Debug("获取时间戳 --> 异常");
    }
    return nRet;
}

void CBrushZones::initMonster(std::string strMonster) {
    m_monster_list.clear();
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;

    if (martin->ReadPtrData(BASE_GAME, TEXT("读取 [BOSS信息] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("读取 [BOSS信息] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("读取 [BOSS信息] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("读取 [BOSS信息] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    //martin->Debug(TEXT("bEmpty : %d"), bEmpty);
                    if (!bEmpty) {
                        int nTempEsi_Next = nRoot;
                        while (nTempEsi_Next != nEnd) {
                            int nTempNode = 0, nCurrentKey = 0;
                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 1"), nTempNode);
                            martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("读取 [节点Key]"), nCurrentKey);
                            //TODO:根据对象Key取出对象详情指针...参见：【根据Key取对象指针】
                            //martin->Debug(TEXT("Key: 0x%X"), nCurrentKey);
                            CBrushZones::GetMonster(nCurrentKey, strMonster);

                            if (++nNodeCount > 0x400) {//计数器，防止遍历太多
                                break;
                            }

                            if (nTempNode != 0) {
                                nTempEsi_Next = nTempNode;
                                int nTemp = 0;
                                while (true) {
                                    martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("读取 [节点8]"), nTemp);
                                    if (nTemp != 0) {
                                        nTempEsi_Next = nTemp;
                                    } else {
                                        break;
                                    }
                                }
                            } else {
                                martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("读取 [节点4] -- 1"), nTempNode);
                                int nTemp = 0;
                                martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 2"), nTemp);

                                if (nTempEsi_Next == nTemp) {
                                    do {
                                        nTempEsi_Next = nTempNode;
                                        martin->ReadPtrData(nTempNode + 0x4, TEXT("读取 [节点4] -- 2"), nTempNode);
                                        martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 3"), nTemp);
                                    } while (nTempEsi_Next == nTemp);
                                }

                                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 4"), nTemp);
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
    if (martin->ReadPtrData(BASE_GAME, TEXT("解密对象 Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("解密对象 Key -- 2"), nEbx)) {
            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
            try {
                _asm {
                    pushad;
                    pushfd;

                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                    mov eax, [ebx];
                    mov edx, nKey; //对象Key
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
                martin->Debug("GetMonster -- 1 --> 异常");
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

                mov ecx, nRet;  //对象指针(来自于 【根据Key取对象指针】的返回值)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug("GetMonster -- 2 --> 异常");
            return;
        }

        if (nRet_2) {
            std::string strName = CNearObject::GetObjectName(nRet_2);
            //martin->Debug(strName.c_str());
            if (strMonster == strName) { // 找到 怪物
                Monster monster;
                monster.strMonsterName = strName;
                int nIndex = 0;
                martin->ReadPtrData(nRet_2 + 0x2C, TEXT("获取 [怪物 房间号]"), nIndex);

                martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("获取 [BOSS 坐标]"), monster.fMonsterPointX);
                martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("获取 [BOSS 坐标]"), monster.fMonsterPointY);
                martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x8, TEXT("获取 [BOSS 坐标]"), monster.fMonsterPointZ);

                monster.nMonsterRoom = nIndex;

                // 判断是否死亡
                int nDead = 0;
                try {
                    _asm {
                        pushad;
                        pushfd;

                        mov ecx, nRet_2; //对象指针
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
                    martin->Debug("GetMonster -- 3 --> 异常");
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