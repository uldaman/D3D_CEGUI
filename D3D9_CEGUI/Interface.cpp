#include "Interface.h"
#include "DefMessage.h"
#include "Quest.h"
#include "NearObject.h"
#include "BrushZones.h"
#include "DataType.h"
#include "Role.h"
#include "Material.h"
#include "Martin.h"
#include "Bag.h"
#include "Base.h"
#include <algorithm>

#define COMMAND_MSG(hwnd, uMsg, wParam, lParam, fn) \
    case (uMsg): return (void)(fn)((hwnd), (wParam), (lParam))

static CQuest quest;
static CNearObject nearObj;
static CBrushZones zone;
static pPOINT_TARGET s_p_Point = nullptr;

void MesageMapping(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        COMMAND_MSG(hDlg, WM_GET_CURRENT_QUEST, wParam, lParam, On_GetCurrentQuest); // 获取当前主线
        COMMAND_MSG(hDlg, WM_GET_QUEST_TABLE, wParam, lParam, On_GetQuestTable); // 获取可接主线
        COMMAND_MSG(hDlg, WM_IS_QUEST_COMPLETE, wParam, lParam, On_IsQuestComplete); // 判断任务是否完成
        COMMAND_MSG(hDlg, WM_WHERE_ROLE, wParam, lParam, On_WhereRole); // 判断当前人物在城镇还是副本, 0: 城镇  2: FB
        COMMAND_MSG(hDlg, WM_COMPLETE_QUEST, wParam, lParam, On_CompleteQuest); // 交任务
        COMMAND_MSG(hDlg, WM_ACCEPT_QUEST, wParam, lParam, On_AcceptQuest); // 接任务
        COMMAND_MSG(hDlg, WM_INTERACTIVE_QUEST, wParam, lParam, On_InteractiveQuest); // 任务对话
        COMMAND_MSG(hDlg, WM_锻造晓风短剑, wParam, lParam, On_锻造晓风短剑); // 锻造晓风短剑
        COMMAND_MSG(hDlg, WM_CITY_FLY, wParam, lParam, On_CityFly); // 城镇传送
        COMMAND_MSG(hDlg, WM_CHOOSE_FB, wParam, lParam, On_ChooseFB); // 选择副本
        COMMAND_MSG(hDlg, WM_START_FB, wParam, lParam, On_StartFB); // 开始副本
        COMMAND_MSG(hDlg, WM_INTO_FB, wParam, lParam, On_IntoFB); // 进入副本
        COMMAND_MSG(hDlg, WM_UPDATA_BOSS, wParam, lParam, On_UpdataBoss); // 获取 BOSS 名
        COMMAND_MSG(hDlg, WM_ROLE_ROOM, wParam, lParam, On_RoleRoom); // 获取当前房间
        COMMAND_MSG(hDlg, WM_BOSS_ROOM, wParam, lParam, On_BossRoom); // 获取BOSS房间
        COMMAND_MSG(hDlg, WM_GET_ZONE, wParam, lParam, On_GetZone); // 获取当前副本
        COMMAND_MSG(hDlg, WM_GET_MAP, wParam, lParam, On_GetMap); // 获取当前地图
        COMMAND_MSG(hDlg, WM_GOTO_BOSS, wParam, lParam, On_GotoBoss); // 瞬移到BOSS
        COMMAND_MSG(hDlg, WM_BY_MAP, wParam, lParam, On_ByMap); // 副本过图
        COMMAND_MSG(hDlg, WM_TURN, wParam, lParam, On_Turn); // 转向
        COMMAND_MSG(hDlg, WM_ATTACK_PACK, wParam, lParam, On_AttackPack); // 攻击
        COMMAND_MSG(hDlg, WM_FORWARD, wParam, lParam, On_Forward); // 前进
        COMMAND_MSG(hDlg, WM_STOP, wParam, lParam, On_Stop); // 停止
        COMMAND_MSG(hDlg, WM_ATTACK, wParam, lParam, On_Attack); // 攻击
        COMMAND_MSG(hDlg, WM_HAVE_WEAPON, wParam, lParam, On_HaveWeapon); // 判断是否装备了武器
        COMMAND_MSG(hDlg, WM_WEAPON, wParam, lParam, On_Weapon); // 装备武器
        COMMAND_MSG(hDlg, WM_GET_HP_PER, wParam, lParam, On_GetHpPer); // 获取当前血比
        COMMAND_MSG(hDlg, WM_INVINCIBLE, wParam, lParam, On_Invincible); // 开启无敌
        COMMAND_MSG(hDlg, WM_UN_INVINCIBLE, wParam, lParam, On_UnInvincible); // 关闭无敌
        COMMAND_MSG(hDlg, WM_TELEPORT, wParam, lParam, On_Teleport); // 瞬移到坐标
        COMMAND_MSG(hDlg, WM_GET_POINT, wParam, lParam, On_GetPoint); // 获取当前坐标
        COMMAND_MSG(hDlg, WM_GO_LEFT, wParam, lParam, On_GoLeft); // 左移
        COMMAND_MSG(hDlg, WM_GO_RIGHT, wParam, lParam, On_GoRight); // 右移
        COMMAND_MSG(hDlg, WM_GO_BACK, wParam, lParam, On_GoBack); // 后退
        COMMAND_MSG(hDlg, WM_HAVE_MODE, wParam, lParam, On_HaveMode); // 是否在菜单模式
        COMMAND_MSG(hDlg, WM_CHANGE_MODE, wParam, lParam, On_ChangeMode); // 切换菜单模式
        COMMAND_MSG(hDlg, WM_ROLL, wParam, lParam, On_Roll); // 翻滚
        COMMAND_MSG(hDlg, WM_GET_ITEM_FORM_CRATES, wParam, lParam, On_GetItemFormCrates); // 补给箱取物
        COMMAND_MSG(hDlg, WM_GETCOLLECT, wParam, lParam, On_GetCollect); // 获取采集标志位
        COMMAND_MSG(hDlg, WM_COLLECT, wParam, lParam, On_Collect); // 采集
        COMMAND_MSG(hDlg, WM_GET_COLLECTS, wParam, lParam, On_GetCollects); // 获取采集物信息
        COMMAND_MSG(hDlg, WM_BARBECUES, wParam, lParam, On_Barbecues); // 烤肉
        COMMAND_MSG(hDlg, WM_GET_BAG_ITEM_NUM, wParam, lParam, On_GetBagItemNum); // 獲取背包物品數量
        COMMAND_MSG(hDlg, WM_EAT_MEAT, wParam, lParam, On_EatMeat); // 吃烤肉
        COMMAND_MSG(hDlg, WM_USE_ITEM, wParam, lParam, On_CommonUseItems); // 通用使用物品
    }
}

void On_GetCurrentQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initUnCompleteQuest();
    for (auto& v : quest.m_unComplete_quest) {
        if (v.strQuestType == "主线") {
            *(std::string*)wParam = v.strQuestName;
            break;
        }
    }
}

void On_GetQuestTable(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(std::string*)wParam = quest.GetQuestTable();
}

void On_IsQuestComplete(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initUnCompleteQuest();
    for (auto& v : quest.m_unComplete_quest) {
        if (v.strQuestType == "主线" && *(std::string*)wParam == v.strQuestName) {
            if (v.strQuestStatus == "完成") {
                *(int*)lParam = 1;
            }
            break;
        }
    }
}

void On_WhereRole(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(int*)wParam = CRole::WhereIsRole();
}

void On_CompleteQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initUnCompleteQuest();
    for (auto& v : quest.m_unComplete_quest) {
        if (v.strQuestType == "主线" && *(std::string*)wParam == v.strQuestName) {
            if (v.strQuestStatus == "完成") {
                // 交任务
                // 1. 打开 NPC
                nearObj.initNear();
                for (auto& w : nearObj.m_near_object) {
                    if (w.strNpcName == *(std::string*)lParam) { // 找到 NPC
                        nearObj.Interactive(w.nNpcID);
                        Sleep(50);
                        break;
                    }
                }
                // 2. 交任务
                quest.CompleteQuest(v.nQuestID);
            }
            break;
        }
    }
}

void On_AcceptQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initQuestTable();
    for (auto& v : quest.m_questTable_quest) {
        if (*(std::string*)wParam == v.strQuestName) {
            // 接任务
            // 1. 打开 NPC
            nearObj.initNear();
            for (auto& w : nearObj.m_near_object) {
                if (w.strNpcName == *(std::string*)lParam) { // 找到 NPC
                    nearObj.Interactive(w.nNpcID);
                    Sleep(50);
                    break;
                }
            }
            // 2. 接任务
            quest.AcceptQuest(v.nQuestID);
            break;
        }
    }
}

void On_InteractiveQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initUnCompleteQuest();
    for (auto& v : quest.m_unComplete_quest) {
        if (v.strQuestType == "主线" && *(std::string*)wParam == v.strQuestName) {
            // 任务对话
            // 1. 打开 NPC
            nearObj.initNear();
            for (auto& w : nearObj.m_near_object) {
                if (w.strNpcName == *(std::string*)lParam) { // 找到 NPC
                    nearObj.Interactive(w.nNpcID);
                    Sleep(50);
                    break;
                }
            }
            // 2. 任务对话
            quest.InteractiveQuest(v.nQuestID);
            break;
        }
    }
}

void On_锻造晓风短剑(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.锻造晓风短剑();
}

void On_CityFly(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::CityFly(*(std::string*)wParam);
}

void On_ChooseFB(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.ChooseFB((int)wParam);
}

void On_StartFB(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.StartFB((int)wParam);
}

void On_IntoFB(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.IntoFB();
}

void On_UpdataBoss(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    ((CBrushZones*)wParam)->initBoss();
}

void On_RoleRoom(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(int*)wParam = CRole::GetRoleRoom();
}

void On_BossRoom(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.initBoss();
    *(int*)wParam = zone.m_nBossRoom;
}

void On_GetZone(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(std::string*)wParam = CRole::GetRoleZone();
}

void On_GetMap(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(std::string*)wParam = CRole::GetRoleMap();
}

void On_GotoBoss(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.GotoBoss();
}

void On_ByMap(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::ByMap((char*)wParam);
}

void On_Turn(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Turn();
}

void On_AttackPack(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Attack_Pack((int)wParam);
}

void On_Forward(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::GoForward(); // 前进下
}

void On_Stop(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Stop(*(std::string*)wParam);
}

void On_Attack(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Attack();
}

void On_HaveWeapon(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(int*)wParam = CRole::HaveWeapon();
}

void On_Weapon(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Weapon();
}

void On_GetHpPer(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(float*)wParam = CRole::GetHpPer();
}

void On_Invincible(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Invincible();
}

void On_UnInvincible(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::UnInvincible();
}

void On_Teleport(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    s_p_Point = (pPOINT_TARGET)wParam;
    CRole::TeleportToPoint(s_p_Point->fPontX, s_p_Point->fPontY, s_p_Point->fPontZ);
}

void On_GetPoint(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    s_p_Point = (pPOINT_TARGET)wParam;
    CRole::GetPoint(s_p_Point->fPontX, s_p_Point->fPontY, s_p_Point->fPontZ);
}

void On_GoLeft(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::GoLeft();
}

void On_GoRight(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::GoRight();
}

void On_GoBack(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::GoBack();
}

void On_HaveMode(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(int*)wParam = CRole::HaveMode();
}

void On_ChangeMode(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::ChangeMode();
}

void On_Roll(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Roll();
}

void On_GetItemFormCrates(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.GetItemFormCrates(*(std::string*)wParam);
}

void On_GetCollect(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(BOOL*)wParam = CRole::WhetherOrBusy();
}

void On_Collect(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::Collect(*(int*)wParam);
}

void On_GetCollects(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CMaterial material;
    material.initMaterial_2();
}

void On_Barbecues(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "烤肉架") {
            DWORD dwArg_1[3];
            RtlZeroMemory(dwArg_1, sizeof(dwArg_1));
            dwArg_1[0] = (*p).nID_1;
            dwArg_1[1] = (*p).nID_2;
            dwArg_1[2] = (*p).nIndex * 0x100;

            int nRoleAddr = CRole::GetRoleAddr();
            DWORD dwArg_2;
            if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, "獲取 [烤肉 Call 參數2] -- 1", dwArg_2)) {
                dwArg_2 += OFFSET_SEND_PACKET_ECX_2;
                try {
                    _asm {
                        pushad;
                        pushfd;

                        mov ecx, dwArg_1; //见【子CALL_1参数1】
                        push ecx;
                        mov edx, dwArg_2; //见【子CALL_1参数2】
                        push edx;
                        mov eax, CALL_BAKE_1; //CALL_BAKE_1
                        call eax;

                        popfd;
                        popad;
                    }
                } catch (...) {
                    martin->Debug("烤肉子CALL_1 --> 异常");
                }

                char sCmdName[0x20] = "BAKE_START";
                DWORD dwCmdNamePtr = (DWORD)sCmdName;
                try {
                    _asm {
                        pushad;
                        pushfd;

                        mov ecx, nRoleAddr; //对象指针
                        mov eax, [ecx];
                        add eax, OFFSET_GET_SWITCH_REGION_ECX;
                        mov edx, [eax]; //0x178:OFFSET_GET_SWITCH_REGION_ECX
                        call edx;
                        add eax, OFFSET_ATTACK_PARAM1;
                        mov ecx, [eax];
                        mov eax, 0;
                        push eax;
                        mov eax, 0;
                        push eax;
                        mov eax, 0;
                        push eax;
                        mov eax, dwCmdNamePtr;
                        push eax;
                        mov eax, CALL_PLAY_ACTION; //CALL_PLAY_ACTION
                        call eax;

                        popfd;
                        popad;
                    }
                } catch (...) {
                    martin->Debug("烤肉子CALL_2 --> 异常");
                }
            }
            break;
        }
    }
}

void On_GetBagItemNum(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == *(std::string*)lParam) {
            *(int*)wParam = (*p).nNum;
            break;
        }
    }
}

void On_EatMeat(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    // 遍歷背包取烤焦的肉
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "烤焦的肉") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // 獲取一些必備參數
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("当前人物 + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("当前人物 + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("获取 [当前人物 x 坐标]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("获取 [当前人物 y 坐标]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("获取 [当前人物 z 坐标]"), role_fz);

            DWORD 时间戳 = CBrushZones::获取时间戳();

            // 發第二個包
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = 时间戳;
            *(float*)&package_2[6] = role_fx;
            *(float*)&package_2[7] = role_fy;
            *(float*)&package_2[8] = role_fz;
            package_2[11] = dwRole_74;
            package_2[12] = dwRole_78;
            package_2[21] = 0x1D110002;
            package_2[22] = 0x4132B61B;
            package_2[23] = 0x75A80E9A;
            package_2[24] = 0xE9911DE2;
            package_2[25] = 0x00A3EE97;
            package_2[26] = 0x48AE0000;
            package_2[27] = 0x00010BED;
            CRole::SendPackage((DWORD)&package_2[0]);

            // 發第三個包
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("烤焦的肉"));
            nAllId = (*it).second.nOID;

            DWORD package_3[11 + 10];
            RtlZeroMemory(package_3, sizeof(package_3));
            package_3[0] = 0x00000B01;
            package_3[5] = nAllId;
            package_3[6] = 0x00000001;
            package_3[7] = 0x00000003;
            package_3[8] = 0x73554C50;
            package_3[9] = 0x65744965;
            package_3[10] = 0x0000006D;
            CRole::SendPackage((DWORD)&package_3[0]);

            // 發第四個包
            时间戳 = CBrushZones::获取时间戳();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = 时间戳;
            *(float*)&package_4[6] = role_fx;
            *(float*)&package_4[7] = role_fy;
            *(float*)&package_4[8] = role_fz;
            package_4[11] = dwRole_74;
            package_4[12] = dwRole_78;
            package_4[21] = 0x91A50001;
            package_4[22] = 0x7F5A4453;
            package_4[23] = 0xF1BAEC41;
            package_4[24] = 0x19BD17B5;
            package_4[25] = 0x000087E0;
            CRole::SendPackage((DWORD)&package_4[0]);

            break;
        }
    }
}

void On_CommonUseItems(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == *(std::string*)wParam) {
            DWORD dwArg_1[3];
            RtlZeroMemory(dwArg_1, sizeof(dwArg_1));
            dwArg_1[0] = (*p).nID_1;
            dwArg_1[1] = (*p).nID_2;
            dwArg_1[2] = (*p).nIndex * 0x100;

            int nRoleAddr = CRole::GetRoleAddr();
            DWORD dwArg_2;
            if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, "獲取 [使用物品參數2] -- 1", dwArg_2)) {
                dwArg_2 += OFFSET_SEND_PACKET_ECX_2;
                try {
                    _asm {
                        pushad;
                        pushfd;

                        mov ecx, dwArg_1; //见【子CALL_1参数1】
                        push ecx;
                        mov edx, dwArg_2; //见【子CALL_1参数2】
                        push edx;
                        mov eax, CALL_BAKE_1; //CALL_BAKE_1
                        call eax;

                        popfd;
                        popad;
                    }
                } catch (...) {
                    martin->Debug("使用 %s --> 异常", (*p).strName);
                }
            }
            break;
        }
    }
}