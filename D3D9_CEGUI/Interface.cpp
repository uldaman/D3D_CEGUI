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
        COMMAND_MSG(hDlg, WM_GET_CURRENT_QUEST, wParam, lParam, On_GetCurrentQuest); // ��ȡ��ǰ����
        COMMAND_MSG(hDlg, WM_GET_QUEST_TABLE, wParam, lParam, On_GetQuestTable); // ��ȡ�ɽ�����
        COMMAND_MSG(hDlg, WM_IS_QUEST_COMPLETE, wParam, lParam, On_IsQuestComplete); // �ж������Ƿ����
        COMMAND_MSG(hDlg, WM_WHERE_ROLE, wParam, lParam, On_WhereRole); // �жϵ�ǰ�����ڳ����Ǹ���, 0: ����  2: FB
        COMMAND_MSG(hDlg, WM_COMPLETE_QUEST, wParam, lParam, On_CompleteQuest); // ������
        COMMAND_MSG(hDlg, WM_ACCEPT_QUEST, wParam, lParam, On_AcceptQuest); // ������
        COMMAND_MSG(hDlg, WM_INTERACTIVE_QUEST, wParam, lParam, On_InteractiveQuest); // ����Ի�
        COMMAND_MSG(hDlg, WM_��������̽�, wParam, lParam, On_��������̽�); // ��������̽�
        COMMAND_MSG(hDlg, WM_CITY_FLY, wParam, lParam, On_CityFly); // ������
        COMMAND_MSG(hDlg, WM_CHOOSE_FB, wParam, lParam, On_ChooseFB); // ѡ�񸱱�
        COMMAND_MSG(hDlg, WM_START_FB, wParam, lParam, On_StartFB); // ��ʼ����
        COMMAND_MSG(hDlg, WM_INTO_FB, wParam, lParam, On_IntoFB); // ���븱��
        COMMAND_MSG(hDlg, WM_UPDATA_BOSS, wParam, lParam, On_UpdataBoss); // ��ȡ BOSS ��
        COMMAND_MSG(hDlg, WM_ROLE_ROOM, wParam, lParam, On_RoleRoom); // ��ȡ��ǰ����
        COMMAND_MSG(hDlg, WM_BOSS_ROOM, wParam, lParam, On_BossRoom); // ��ȡBOSS����
        COMMAND_MSG(hDlg, WM_GET_ZONE, wParam, lParam, On_GetZone); // ��ȡ��ǰ����
        COMMAND_MSG(hDlg, WM_GET_MAP, wParam, lParam, On_GetMap); // ��ȡ��ǰ��ͼ
        COMMAND_MSG(hDlg, WM_GOTO_BOSS, wParam, lParam, On_GotoBoss); // ˲�Ƶ�BOSS
        COMMAND_MSG(hDlg, WM_BY_MAP, wParam, lParam, On_ByMap); // ������ͼ
        COMMAND_MSG(hDlg, WM_TURN, wParam, lParam, On_Turn); // ת��
        COMMAND_MSG(hDlg, WM_ATTACK_PACK, wParam, lParam, On_AttackPack); // ����
        COMMAND_MSG(hDlg, WM_FORWARD, wParam, lParam, On_Forward); // ǰ��
        COMMAND_MSG(hDlg, WM_STOP, wParam, lParam, On_Stop); // ֹͣ
        COMMAND_MSG(hDlg, WM_ATTACK, wParam, lParam, On_Attack); // ����
        COMMAND_MSG(hDlg, WM_HAVE_WEAPON, wParam, lParam, On_HaveWeapon); // �ж��Ƿ�װ��������
        COMMAND_MSG(hDlg, WM_WEAPON, wParam, lParam, On_Weapon); // װ������
        COMMAND_MSG(hDlg, WM_GET_HP_PER, wParam, lParam, On_GetHpPer); // ��ȡ��ǰѪ��
        COMMAND_MSG(hDlg, WM_INVINCIBLE, wParam, lParam, On_Invincible); // �����޵�
        COMMAND_MSG(hDlg, WM_UN_INVINCIBLE, wParam, lParam, On_UnInvincible); // �ر��޵�
        COMMAND_MSG(hDlg, WM_TELEPORT, wParam, lParam, On_Teleport); // ˲�Ƶ�����
        COMMAND_MSG(hDlg, WM_GET_POINT, wParam, lParam, On_GetPoint); // ��ȡ��ǰ����
        COMMAND_MSG(hDlg, WM_GO_LEFT, wParam, lParam, On_GoLeft); // ����
        COMMAND_MSG(hDlg, WM_GO_RIGHT, wParam, lParam, On_GoRight); // ����
        COMMAND_MSG(hDlg, WM_GO_BACK, wParam, lParam, On_GoBack); // ����
        COMMAND_MSG(hDlg, WM_HAVE_MODE, wParam, lParam, On_HaveMode); // �Ƿ��ڲ˵�ģʽ
        COMMAND_MSG(hDlg, WM_CHANGE_MODE, wParam, lParam, On_ChangeMode); // �л��˵�ģʽ
        COMMAND_MSG(hDlg, WM_ROLL, wParam, lParam, On_Roll); // ����
        COMMAND_MSG(hDlg, WM_GET_ITEM_FORM_CRATES, wParam, lParam, On_GetItemFormCrates); // ������ȡ��
        COMMAND_MSG(hDlg, WM_GETCOLLECT, wParam, lParam, On_GetCollect); // ��ȡ�ɼ���־λ
        COMMAND_MSG(hDlg, WM_COLLECT, wParam, lParam, On_Collect); // �ɼ�
        COMMAND_MSG(hDlg, WM_GET_COLLECTS, wParam, lParam, On_GetCollects); // ��ȡ�ɼ�����Ϣ
    }
}

void On_GetCurrentQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initUnCompleteQuest();
    for (auto& v : quest.m_unComplete_quest) {
        if (v.strQuestType == "����") {
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
        if (v.strQuestType == "����" && *(std::string*)wParam == v.strQuestName) {
            if (v.strQuestStatus == "���") {
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
        if (v.strQuestType == "����" && *(std::string*)wParam == v.strQuestName) {
            if (v.strQuestStatus == "���") {
                // ������
                // 1. �� NPC
                nearObj.initNear();
                for (auto& w : nearObj.m_near_object) {
                    if (w.strNpcName == *(std::string*)lParam) { // �ҵ� NPC
                        nearObj.Interactive(w.nNpcID);
                        Sleep(50);
                        break;
                    }
                }
                // 2. ������
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
            // ������
            // 1. �� NPC
            nearObj.initNear();
            for (auto& w : nearObj.m_near_object) {
                if (w.strNpcName == *(std::string*)lParam) { // �ҵ� NPC
                    nearObj.Interactive(w.nNpcID);
                    Sleep(50);
                    break;
                }
            }
            // 2. ������
            quest.AcceptQuest(v.nQuestID);
            break;
        }
    }
}

void On_InteractiveQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initUnCompleteQuest();
    for (auto& v : quest.m_unComplete_quest) {
        if (v.strQuestType == "����" && *(std::string*)wParam == v.strQuestName) {
            // ����Ի�
            // 1. �� NPC
            nearObj.initNear();
            for (auto& w : nearObj.m_near_object) {
                if (w.strNpcName == *(std::string*)lParam) { // �ҵ� NPC
                    nearObj.Interactive(w.nNpcID);
                    Sleep(50);
                    break;
                }
            }
            // 2. ����Ի�
            quest.InteractiveQuest(v.nQuestID);
            break;
        }
    }
}

void On_��������̽�(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.��������̽�();
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
    CRole::GoForward(); // ǰ����
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
