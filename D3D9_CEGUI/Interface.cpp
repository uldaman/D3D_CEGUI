#include "Interface.h"
#include "DefMessage.h"
#include "Quest.h"
#include "NearObject.h"
#include "BrushZones.h"
#include "DataType.h"
#include "Role.h"
#include "Material.h"
#include "Martin.h"

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
    material.initMaterial();
}
