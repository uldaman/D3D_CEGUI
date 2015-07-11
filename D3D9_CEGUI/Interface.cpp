#include "GlobalVariable.h"
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
#include "Supply.h"
#include "Equipment.h"
#include "Warehouse.h"
#include "Manor.h"
#include "My_Ini.h"
#include "Clogin.h"

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
        COMMAND_MSG(hDlg, WM_BARBECUES, wParam, lParam, On_Barbecues); // ����
        COMMAND_MSG(hDlg, WM_GET_BAG_ITEM_NUM, wParam, lParam, On_GetBagItemNum); // �@ȡ������Ʒ����
        COMMAND_MSG(hDlg, WM_EAT_MEAT, wParam, lParam, On_EatMeat); // �Կ���
        COMMAND_MSG(hDlg, WM_USE_ITEM, wParam, lParam, On_CommonUseItems); // ͨ��ʹ����Ʒ
        COMMAND_MSG(hDlg, WM_PRECISION_ACCEPT_QUEST, wParam, lParam, On_PrecisionAcceptQuest); // ��׼������, ͨ���ȶ� NPC ������
        COMMAND_MSG(hDlg, WM_MADE_HP_MEDICINE, wParam, lParam, On_MadeHpMedicine); // ����ظ�ҩ
        COMMAND_MSG(hDlg, WM_BUY_SUPPLY, wParam, lParam, On_BuySupply); // ������Ʒ
        COMMAND_MSG(hDlg, WM_KILL_MONSTER, wParam, lParam, On_KillMonster); // ��ɱ����
        COMMAND_MSG(hDlg, WM_GET_MONSTER_ROOM, wParam, lParam, On_GetMonsterRoom); // ��ȡ��ǹ��﷿��
        COMMAND_MSG(hDlg, WM_GOTO_MONSTER, wParam, lParam, On_GotoMonster); // ˲�Ƶ���ǹ�
        COMMAND_MSG(hDlg, WM_TURN_TO_MONSTER, wParam, lParam, On_TurnToMonster); // ת�򵽱�ǹ�
        COMMAND_MSG(hDlg, WM_TURN_TO_POINT, wParam, lParam, On_TurnToPoint); // ת��Ŀ���
        COMMAND_MSG(hDlg, WM_ACCEPT_OFFER_A_REWARD, wParam, lParam, On_AcceptOfferAReward); // ��������
        COMMAND_MSG(hDlg, WM_GET_CURRENT_REWARD, wParam, lParam, On_GetCurrentReward); // ��ȡ��������
        COMMAND_MSG(hDlg, WM_GET_REWARD_FB, wParam, lParam, On_GetRewardBrushZone); // ��ȡ���͸���
        COMMAND_MSG(hDlg, WM_GET_COUNT_REWARD_TODAY, wParam, lParam, On_GetCountRewardToday); // ��ȡ������������ʹ���
        COMMAND_MSG(hDlg, WM_GET_ACCEPT_REWARD, wParam, lParam, On_GetAcceptReward); // ��ȡ�ɽ�����
        COMMAND_MSG(hDlg, WM_ACCEPT_REWARD, wParam, lParam, On_AcceptReward); // ������
        COMMAND_MSG(hDlg, WM_�����������̽�, wParam, lParam, On_�����������̽�); // �����������̽�
        COMMAND_MSG(hDlg, WM_GET_EXP_LIMIT, wParam, lParam, On_GetExperienceLimit); // ��ȡ��������
        COMMAND_MSG(hDlg, WM_GET_WAREHOUSE_ITEM_NUM, wParam, lParam, On_GetWarehouseItemNum); // �ֿ���Ʒ����
        COMMAND_MSG(hDlg, WM_INTO_MY_MANOR, wParam, lParam, On_IntoMyManor); // �ֿ���Ʒ����
        COMMAND_MSG(hDlg, WM_LEAVE_MANOR, wParam, lParam, On_LeaveManor); // �뿪ׯ԰
        COMMAND_MSG(hDlg, WM_UPGRADE_MUSHROOM, wParam, lParam, On_UpgradeMushroom); // ��������ľ��
        COMMAND_MSG(hDlg, WM_MOVE_ITEM_IN_WAREHOUSE, wParam, lParam, On_MoveInventoryItem); // ���
        COMMAND_MSG(hDlg, WM_GETBAG, wParam, lParam, On_GetBag); // ��ʼ������
        COMMAND_MSG(hDlg, WM_����嶡������, wParam, lParam, On_����嶡������); // ��ʼ������
        COMMAND_MSG(hDlg, WM_EAT_MEDICINE, wParam, lParam, On_EatMedicine); // ��ʼ������
        COMMAND_MSG(hDlg, WM_PAY_ITEMS, wParam, lParam, On_PayItems); // ������Ʒ
        COMMAND_MSG(hDlg, WM_GET_GLOWING_ARTICLE, wParam, lParam, On_GetGlowingArticle); // ��ȡ������Ʒ
        COMMAND_MSG(hDlg, WM_��������è, wParam, lParam, On_��������è);
        COMMAND_MSG(hDlg, WM_װ��������, wParam, lParam, On_װ��������);
        COMMAND_MSG(hDlg, WM_TAKE_MEDICINE, wParam, lParam, On_TakeMedicine); // �ݴ�ʽ��ҩ
        COMMAND_MSG(hDlg, WM_WEAR_EQUIPMENT, wParam, lParam, On_WearEquipment); // ��װ��
        COMMAND_MSG(hDlg, WM_GET_ROLE_LEVEL, wParam, lParam, On_GetRoleLevel); // ��ȡ����ȼ�
        COMMAND_MSG(hDlg, WM_PRECISION_COMPLETE_QUEST, wParam, lParam, On_PrecisionCompleteQuest); // ��׼������, ͨ���ȶ� NPC ������
        COMMAND_MSG(hDlg, WM_FIRST_ATTACK_TRUN, wParam, lParam, On_FirstAttackTrun); // ������һ������
        COMMAND_MSG(hDlg, WM_LOGIN, wParam, lParam, On_Login); // ��¼��Ϸ
        COMMAND_MSG(hDlg, WM_NEW_ROLE, wParam, lParam, On_NewRole); // �½���ɫ
        COMMAND_MSG(hDlg, WM_COUNTS_OF_ROLES, wParam, lParam, On_CountsOfRoles); // ��ɫ����
        COMMAND_MSG(hDlg, WM_ENTER_CHANNEL, wParam, lParam, On_EnterChannel); // ȷ��Ƶ��
        COMMAND_MSG(hDlg, WM_IS_ONLINE, wParam, lParam, On_IsOnLine); // �Ƿ�����
        COMMAND_MSG(hDlg, WM_IS_LOADING, wParam, lParam, On_IsLoading); // �Ƿ��ͼ
        //COMMAND_MSG(hDlg, WM_INIT_ROLE_LIST, wParam, lParam, On_InitRoleList); // ��ʼ����ɫ�б�
        COMMAND_MSG(hDlg, WM_IS_SELECT, wParam, lParam, On_IsSelect); // �Ƿ���ѡ���ɫ
        COMMAND_MSG(hDlg, WM_��ȡ�ɳ������һ�ȯ, wParam, lParam, On_��ȡ�ɳ������һ�ȯ); // ��ȡ�ɳ������һ�ȯ
        COMMAND_MSG(hDlg, WM_�һ�����֮��, wParam, lParam, On_�һ�����֮��); // �һ�����֮��
        COMMAND_MSG(hDlg, WM_�һ�����֮��, wParam, lParam, On_�һ�����֮��); // �һ�����֮��
        COMMAND_MSG(hDlg, WM_RETURN_SELECT_ROLE, wParam, lParam, On_ReturnSelectRole); // �һ�����֮��
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
    material.initMaterial_2();
}

void On_Barbecues(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "�����") {
            DWORD dwArg_1[3];
            RtlZeroMemory(dwArg_1, sizeof(dwArg_1));
            dwArg_1[0] = (*p).nID_1;
            dwArg_1[1] = (*p).nID_2;
            dwArg_1[2] = (*p).nIndex * 0x100;

            int nRoleAddr = CRole::GetRoleAddr();
            DWORD dwArg_2;
            if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, "�@ȡ [���� Call ����2] -- 1", dwArg_2)) {
                dwArg_2 += OFFSET_SEND_PACKET_ECX_2;
                try {
                    _asm {
                        pushad;
                        pushfd;

                        mov ecx, dwArg_1; //������CALL_1����1��
                        push ecx;
                        mov edx, dwArg_2; //������CALL_1����2��
                        push edx;
                        mov eax, CALL_BAKE_1; //CALL_BAKE_1
                        call eax;

                        popfd;
                        popad;
                    }
                } catch (...) {
                    martin->Debug("������CALL_1 --> �쳣");
                }

                char sCmdName[0x20] = "BAKE_START";
                DWORD dwCmdNamePtr = (DWORD)sCmdName;
                try {
                    _asm {
                        pushad;
                        pushfd;

                        mov ecx, nRoleAddr; //����ָ��
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
                    martin->Debug("������CALL_2 --> �쳣");
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
    // ��v����ȡ��������
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "��������") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // �@ȡһЩ�؂䅢��
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);

            DWORD ʱ��� = CBrushZones::��ȡʱ���();

            // �l�ڶ�����
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = ʱ���;
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

            // �l��������
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("��������"));
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

            // �l���Ă���
            ʱ��� = CBrushZones::��ȡʱ���();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = ʱ���;
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
            DWORD pDwArg_1 = (DWORD)&dwArg_1;

            int nRoleAddr = CRole::GetRoleAddr();
            DWORD dwArg_2;
            if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, "�@ȡ [ʹ����Ʒ����2] -- 1", dwArg_2)) {
                dwArg_2 += OFFSET_SEND_PACKET_ECX_2;
                try {
                    _asm {
                        pushad;
                        pushfd;

                        mov ecx, pDwArg_1; //������CALL_1����1��
                        push ecx;
                        mov edx, dwArg_2; //������CALL_1����2��
                        push edx;
                        mov eax, CALL_BAKE_1; //CALL_BAKE_1
                        call eax;

                        popfd;
                        popad;
                    }
                } catch (...) {
                    martin->Debug("ʹ�� %s --> �쳣", (*p).strName.c_str());
                }
            }
            break;
        }
    }
}

void On_PrecisionAcceptQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    pQuestInfo questInfo = (pQuestInfo)wParam;
    pPOINT_TARGET pointTarget = (pPOINT_TARGET)lParam;
    quest.initQuestTable();
    for (auto& v : quest.m_questTable_quest) {
        if (questInfo->strQuestName == v.strQuestName) {
            martin->Debug((*(std::string*)wParam).c_str());
            // ������
            // 1. �� NPC
            nearObj.initNear();
            for (auto& w : nearObj.m_near_object) {
                if (w.strNpcName == questInfo->strNpcName) { // �ҵ� NPC
                    // �ȶ� npc ����
                    martin->Debug((questInfo->strNpcName).c_str());
                    if (martin->Compare_Coord(pointTarget->fPontX, pointTarget->fPontY, w.fNpcPointX, w.fNpcPointY) < 5) {
                        nearObj.Interactive(w.nNpcID);
                        Sleep(50);
                        break;
                    } // ��Ŀ���������С�� 5 ���ʾ�ҵ��� npc 
                }
            }
            // 2. ������
            quest.AcceptQuest(v.nQuestID);
            break;
        }
    }
}

void On_MadeHpMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.MadeHpMedicine();
}

void On_BuySupply(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CSupply supply;
    supply.initSupply();

    pSupplyInfo supplyInfo = (pSupplyInfo)wParam; // ��Ϊ������ƷҲ��Ҫ���� string ����, ����ֱ���� t_questInfo
    int nNumOfSupply = *(PINT)lParam;

    for (auto& v : supply.m_supply_list) {
        //martin->Debug("%s -- ��ƷID: 0x%X -- ����ID: 0x%X", v.strItemName.c_str(), v.nSupplyID, v.nTypeID);
        if (supplyInfo->strSupplyName == v.strItemName
            && supplyInfo->strTypeName == v.strTypeName) {
            // 1. �� NPC
            nearObj.initNear();
            for (auto& w : nearObj.m_near_object) {
                if (w.strNpcName == supplyInfo->strNpcName) { // �ҵ� NPC
                    nearObj.Interactive(w.nNpcID);
                    Sleep(50);
                    break;
                }
            }
            // 2. ����
            DWORD Package[17];
            RtlZeroMemory(Package, sizeof(Package));
            Package[0] = 0x00000F01;
            Package[4] = v.nTypeID;
            Package[5] = v.nSupplyID;
            Package[6] = nNumOfSupply;
            Package[7] = 0xFFFFFFFF;
            Package[8] = 0xFFFFFFFF;
            CRole::SendPackage((DWORD)&Package);
            return;
        }
    }
}

void On_KillMonster(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.initMonster(*(std::string*)wParam);

    CBrushZones::m_monster = new Monster;
    CBrushZones::m_monster->fDistance = 9999999.0f;
    pMonster monsterTemp = CBrushZones::m_monster; // ��Ϊ monster ����Ҫ����ַ, �������ﱣ��һ��, �����˳�ʱ�ͷŸõ�ַ

    for (auto& v : zone.m_monster_list) {
        if (v.bIsDead == FALSE && CBrushZones::m_monster->fDistance > v.fDistance) {
            CBrushZones::m_monster = &v;
        }
    }

    //for (auto& v : zone.m_monster_list) {
    //    martin->Debug("%s -- ����: %f : %f : %f -- �Ƿ񱻹���: %d -- ����״̬: %d -- ����: %d -- ����: %f"
    //        , v.strMonsterName.c_str(), v.fMonsterPointX, v.fMonsterPointY, v.fMonsterPointZ
    //        , v.bIsDead, v.nMonsterRoom, v.fDistance);
    //}

    delete monsterTemp;
}

void On_GetMonsterRoom(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    //martin->Debug("%s -- ����: %f : %f : %f -- �Ƿ񱻹���: %d -- ����״̬: %d -- ����: %d -- ����: %f"
    //    , CBrushZones::m_monster->strMonsterName.c_str(), CBrushZones::m_monster->fMonsterPointX, CBrushZones::m_monster->fMonsterPointY, CBrushZones::m_monster->fMonsterPointZ
    //    , CBrushZones::m_monster->bIsDead, CBrushZones::m_monster->nMonsterRoom, CBrushZones::m_monster->fDistance);

    if (IsBadReadPtr((CONST VOID*)CBrushZones::m_monster, sizeof(Monster)) == 0) {
        // �ж��Ƿ�����
        int nDead = 0;
        int nMonsterAddr = CBrushZones::m_monster->nMonsterAddr;
        try {
            _asm {
                pushad;
                pushfd;

                mov ecx, nMonsterAddr; //����ָ��
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
            CBrushZones::m_monster->bIsDead = TRUE;
            return;
        }

        martin->ReadPtrData(CBrushZones::m_monster->nMonsterAddr + 0x2C, TEXT("��ȡ [���� �����]"), CBrushZones::m_monster->nMonsterRoom);
        *(PINT)wParam = CBrushZones::m_monster->nMonsterRoom;
    }
}

void On_GotoMonster(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    //martin->Debug("%s -- ����: %f : %f : %f -- �Ƿ񱻹���: %d -- ����״̬: %d -- ����: %d -- ����: %f"
    //    , CBrushZones::m_monster->strMonsterName.c_str(), CBrushZones::m_monster->fMonsterPointX, CBrushZones::m_monster->fMonsterPointY, CBrushZones::m_monster->fMonsterPointZ
    //    , CBrushZones::m_monster->bIsDead, CBrushZones::m_monster->nMonsterRoom, CBrushZones::m_monster->fDistance);

    if (IsBadReadPtr((CONST VOID*)CBrushZones::m_monster, sizeof(Monster)) == 0) {
        int nRoleAddr = 0, nRoleKey = 0;
        if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [��ǰ����ָ��] -- 1"), nRoleAddr)) {
            if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_1, TEXT("��ȡ [��ǰ����ָ��] -- 2"), nRoleAddr)) {
                if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_2, TEXT("��ȡ [��ǰ����ָ��] -- 3"), nRoleAddr)) {
                    if (martin->ReadPtrData(nRoleAddr + OFFSET_ROLE_INFO_4, TEXT("��ȡ [��ǰ����ָ��] -- 4"), nRoleAddr)) {
                        if (martin->ReadPtrData(nRoleAddr + 0x8, TEXT("��ȡ [��ǰ���� KEY]"), nRoleKey)) {
                            // ˲��
                            martin->ReadPtrData(CBrushZones::m_monster->nMonsterAddr + OFFSET_COOR, TEXT("��ȡ [��ǹ� ����]"), CBrushZones::m_monster->fMonsterPointX);
                            martin->ReadPtrData(CBrushZones::m_monster->nMonsterAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǹ� ����]"), CBrushZones::m_monster->fMonsterPointY);
                            martin->ReadPtrData(CBrushZones::m_monster->nMonsterAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǹ� ����]"), CBrushZones::m_monster->fMonsterPointZ);
                            CRole::RoleTeleport(nRoleKey, CBrushZones::m_monster->fMonsterPointX, CBrushZones::m_monster->fMonsterPointY, CBrushZones::m_monster->fMonsterPointZ);
                        }
                    }
                }
            }
        }
    }
}

void On_TurnToMonster(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    if (IsBadReadPtr((CONST VOID*)CBrushZones::m_monster, sizeof(Monster)) == 0) {
        // ��ȡ ��ǹ� ����
        martin->ReadPtrData(CBrushZones::m_monster->nMonsterAddr + OFFSET_COOR, TEXT("��ȡ [��ǹ� x ����]"), CBrushZones::m_monster->fMonsterPointX);
        martin->ReadPtrData(CBrushZones::m_monster->nMonsterAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǹ� y ����]"), CBrushZones::m_monster->fMonsterPointY);
        martin->ReadPtrData(CBrushZones::m_monster->nMonsterAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǹ� z ����]"), CBrushZones::m_monster->fMonsterPointZ);
        // martin->Debug(TEXT("BOSS ����: %f, %f, %f"), fx, fy, fz);

        // ת��
        float role_fx = 0.0f;
        float role_fy = 0.0f;
        int nRoleAddr = CRole::GetRoleAddr();
        martin->ReadPtrData(nRoleAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
        martin->ReadPtrData(nRoleAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);

        float fTurn = static_cast<float>(atan2(CBrushZones::m_monster->fMonsterPointY - role_fy, CBrushZones::m_monster->fMonsterPointX - role_fx));
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
                    return;
                }
            }
        }
    }
}

void On_TurnToPoint(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    // ת��
    float role_fx = 0.0f;
    float role_fy = 0.0f;
    int nRoleAddr = CRole::GetRoleAddr();
    martin->ReadPtrData(nRoleAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
    martin->ReadPtrData(nRoleAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);

    float fTurn = static_cast<float>(atan2(*(PFLOAT)lParam - role_fy, *(PFLOAT)wParam - role_fx));
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
                return;
            }
        }
    }
}

void On_AcceptOfferAReward(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initOfferARewardQuest();
    int nRoleLevel = CRole::GetRoleLevel();
    for (auto& v : quest.m_offerAReward_quest) {
        if (v.nTheTaskMinimumLevel <= nRoleLevel
            && v.nTheTaskMaximumLevel >= nRoleLevel
            && v.strQuestStatus != "�ѽ�") {
            std::string::size_type idx = v.strQuestName.find(*(std::string*)wParam);
            if (idx != std::string::npos) { // �ҵ�����
                idx = v.strQuestName.find(*(std::string*)lParam);
                if (idx != std::string::npos) { // �ҵ�����
                    // 1. �� NPC
                    nearObj.initNear();
                    for (auto& w : nearObj.m_near_object) {
                        martin->Debug(w.strNpcName.c_str());
                        if (w.strNpcName == "���Ϳ���") { // �ҵ� NPC
                            nearObj.Interactive(w.nNpcID);
                            Sleep(50);
                            break;
                        }
                    }

                    // ������
                    quest.AcceptQuest(v.nQuestID);
                    return;
                }
            }
        }
    }
}

void On_GetCurrentReward(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initOfferARewardQuest();
    int nRoleLevel = CRole::GetRoleLevel();
    for (auto& v : quest.m_offerAReward_quest) {
        if (v.strQuestStatus == "δ���") {
            *(std::string*)wParam = v.strQuestName;
            return;
        }
    }
}

void On_GetRewardBrushZone(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initOfferARewardQuest();
    int nRoleLevel = CRole::GetRoleLevel();
    for (auto& v : quest.m_offerAReward_quest) {
        if (v.strQuestName == *(std::string*)wParam) {
            *(PINT)lParam = v.nTargetBrushZonesID;
            return;
        }
    }
}

void On_GetCountRewardToday(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initOfferARewardQuest();
    *(PINT)wParam = quest.m_nCountOfTodayOfferAReward;
}

void On_GetAcceptReward(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initOfferARewardQuest();
    int nRoleLevel = CRole::GetRoleLevel();
    for (auto& v : quest.m_offerAReward_quest) {
        if (v.strQuestStatus == "���") {
            *(std::string*)wParam = v.strQuestName;
            return;
        }
    }
}

void On_AcceptReward(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.initOfferARewardQuest();
    int nRoleLevel = CRole::GetRoleLevel();
    for (auto& v : quest.m_offerAReward_quest) {
        if (v.strQuestName == *(std::string*)wParam) {
            // 1. �� NPC
            nearObj.initNear();
            for (auto& w : nearObj.m_near_object) {
                if (w.strNpcName == "���Ϳ���") { // �ҵ� NPC
                    nearObj.Interactive(w.nNpcID);
                    Sleep(50);
                    break;
                }
            }

            // ������
            quest.CompleteQuest(v.nQuestID);
            return;
        }
    }
}

void On_�����������̽�(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    BOOL bSendPackage = FALSE;
    int nItemId;
    auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("�����̽�"));
    nItemId = (*it).first;

    int nPlace = 0xFFFFFFFF;
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    int nID_1, nID_2, nIndex;

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "����̽�") {
            nID_1 = (*p).nID_1;
            nID_2 = (*p).nID_2;
            nIndex = (*p).nIndex;
            nPlace = 0;
            bSendPackage = TRUE;
            break;
        }
    }

    // ���������Ĳ������ҵ���"����̽�", �򲻻�ִ�������
    if (bSendPackage == FALSE) {
        CEquipment equipment;
        equipment.initEquipmentInfo();
        std::list<BagItem> equipment_list = equipment.GetEquipmentInfo();

        for (auto p = equipment_list.begin(); p != equipment_list.end(); ++p) {
            if ((*p).strName == "����̽�") {
                nID_1 = (*p).nID_1;
                nID_2 = (*p).nID_2;
                nIndex = (*p).nIndex;
                nPlace = 0x3;
                bSendPackage = TRUE;
                break;
            }
        }
    }

    if (bSendPackage) {
        nearObj.initNear();
        for (auto& w : nearObj.m_near_object) {
            if (w.strNpcName == "��ŷ") { // �ҵ� NPC
                nearObj.Interactive(w.nNpcID);
                break;
            }
        }

        DWORD package_1[7 + 10];
        RtlZeroMemory(package_1, sizeof(package_1));
        package_1[0] = 0x0000310D;
        package_1[4] = nID_1;
        package_1[5] = nID_2;
        *(PBYTE)&package_1[6] = nPlace; // 03: ��ʾ��������װ����0: ��ʾ���������е�װ��
        *(PWORD)((PBYTE)&package_1[6] + 1) = nIndex;
        *(PWORD)((PBYTE)&package_1[6] + 3) = nItemId;
        CRole::SendPackage((DWORD)&package_1[0]);
    }
}

void On_GetExperienceLimit(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(PINT)wParam = CRole::GetExpLimit();
}

void On_GetWarehouseItemNum(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CWarehouse warehouse;
    warehouse.initWarehouseInfo();
    std::list<BagItem> warehouse_list = warehouse.GetWarehouseInfo();

    for (auto p = warehouse_list.begin(); p != warehouse_list.end(); ++p) {
        if ((*p).strName == *(std::string*)lParam) {
            *(int*)wParam = (*p).nNum;
            break;
        }
    }
}

void On_IntoMyManor(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CManor oManor;
    oManor.intoMyManor();
}

void On_LeaveManor(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CManor oManor;
    oManor.leaveManor();
}

void On_UpgradeMushroom(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CManor oManor;
    oManor.UpgradeMushroom();
}

void On_MoveInventoryItem(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    ((pBagItem)wParam)->MoveInventoryItem();
}

void On_GetBag(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CBag bag;
    bag.initBagInfo();
    *(std::list<BagItem>*)wParam = bag.GetBagInfo();
}

void On_����嶡������(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    quest.����嶡������();
}

void On_EatMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "֧���ûظ�ҩ") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // �@ȡһЩ�؂䅢��
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);

            DWORD ʱ��� = CBrushZones::��ȡʱ���();

            // �l�ڶ�����
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = ʱ���;
            *(float*)&package_2[6] = role_fx;
            *(float*)&package_2[7] = role_fy;
            *(float*)&package_2[8] = role_fz;
            package_2[11] = dwRole_74;
            package_2[12] = dwRole_78;
            package_2[21] = 0x7A720002;
            package_2[22] = 0xA13C86D0;
            package_2[23] = 0xECB9B7E8;
            package_2[24] = 0x6D3684D8;
            package_2[25] = 0x00A26F7E;
            package_2[26] = 0x48B00000;
            package_2[27] = 0x00010BED;
            CRole::SendPackage((DWORD)&package_2[0]);

            // �l��������
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("֧���ûظ�ҩ"));
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

            // �l���Ă���
            ʱ��� = CBrushZones::��ȡʱ���();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = ʱ���;
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
            return;
        }
    }

    // ����ҵ��� "֧���ûظ�ҩ" �򲻻��������Ĳ���
    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "�ظ�ҩ") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // �@ȡһЩ�؂䅢��
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);

            DWORD ʱ��� = CBrushZones::��ȡʱ���();

            // �l�ڶ�����
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = ʱ���;
            *(float*)&package_2[6] = role_fx;
            *(float*)&package_2[7] = role_fy;
            *(float*)&package_2[8] = role_fz;
            package_2[11] = dwRole_74;
            package_2[12] = dwRole_78;
            package_2[21] = 0x7A720002;
            package_2[22] = 0xA13C86D0;
            package_2[23] = 0xECB9B7E8;
            package_2[24] = 0x6D3684D8;
            package_2[25] = 0x00A26F7E;
            package_2[26] = 0x48B00000;
            package_2[27] = 0x00010BED;
            CRole::SendPackage((DWORD)&package_2[0]);

            // �l��������
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("�ظ�ҩ"));
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

            // �l���Ă���
            ʱ��� = CBrushZones::��ȡʱ���();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = ʱ���;
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
            return;
        }
    }
}

void On_PayItems(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    zone.PayItems();
}

void On_GetGlowingArticle(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CNearObject* oNearObject = (CNearObject*)wParam;
    //s_p_Point = (pPOINT_TARGET)wParam;
    oNearObject->GetGlowingArticle(/*s_p_Point->fPontX, s_p_Point->fPontY, s_p_Point->fPontZ*/);
}

void On_��������è(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::SetAccompanyingCat();
}

void On_װ��������(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CRole::װ���嶡������();
}

void Detoxication() {
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "֧���ýⶾҩ") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // �@ȡһЩ�؂䅢��
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);

            DWORD ʱ��� = CBrushZones::��ȡʱ���();

            // �l�ڶ�����
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = ʱ���;
            *(float*)&package_2[6] = role_fx;
            *(float*)&package_2[7] = role_fy;
            *(float*)&package_2[8] = role_fz;
            package_2[11] = dwRole_74;
            package_2[12] = dwRole_78;
            package_2[21] = 0x7A720002;
            package_2[22] = 0xA13C86D0;
            package_2[23] = 0xECB9B7E8;
            package_2[24] = 0x6D3684D8;
            package_2[25] = 0x01666F7E;
            package_2[26] = 0x48AF0000;
            package_2[27] = 0x00010BED;
            CRole::SendPackage((DWORD)&package_2[0]);

            // �l��������
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("֧���ýⶾҩ"));
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

            // �l���Ă���
            ʱ��� = CBrushZones::��ȡʱ���();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = ʱ���;
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
            return;
        }
    }

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "�ⶾҩ") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // �@ȡһЩ�؂䅢��
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);

            DWORD ʱ��� = CBrushZones::��ȡʱ���();

            // �l�ڶ�����
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = ʱ���;
            *(float*)&package_2[6] = role_fx;
            *(float*)&package_2[7] = role_fy;
            *(float*)&package_2[8] = role_fz;
            package_2[11] = dwRole_74;
            package_2[12] = dwRole_78;
            package_2[21] = 0x7A720002;
            package_2[22] = 0xA13C86D0;
            package_2[23] = 0xECB9B7E8;
            package_2[24] = 0x6D3684D8;
            package_2[25] = 0x01666F7E;
            package_2[26] = 0x48AF0000;
            package_2[27] = 0x00010BED;
            CRole::SendPackage((DWORD)&package_2[0]);

            // �l��������
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("�ⶾҩ"));
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

            // �l���Ă���
            ʱ��� = CBrushZones::��ȡʱ���();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = ʱ���;
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
            return;
        }
    }
}

void On_TakeMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    On_EatMedicine(hDlg, wParam, lParam); // �ظ�ҩ
    Detoxication(); // �ⶾ

    // ����������
    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "֧��������") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // �@ȡһЩ�؂䅢��
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);

            DWORD ʱ��� = CBrushZones::��ȡʱ���();

            // �l�ڶ�����
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = ʱ���;
            *(float*)&package_2[6] = role_fx;
            *(float*)&package_2[7] = role_fy;
            *(float*)&package_2[8] = role_fz;
            package_2[11] = dwRole_74;
            package_2[12] = dwRole_78;
            package_2[21] = 0x7A720002;
            package_2[22] = 0xA13C86D0;
            package_2[23] = 0xECB9B7E8;
            package_2[24] = 0x6D3684D8;
            package_2[25] = 0x00A26F7E;
            package_2[26] = 0x48AA0000;
            package_2[27] = 0x00010BED;
            CRole::SendPackage((DWORD)&package_2[0]);

            // �l��������
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("֧��������"));
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

            // �l���Ă���
            ʱ��� = CBrushZones::��ȡʱ���();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = ʱ���;
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
            return;
        }
    }

    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == "����") {
            DWORD package_1[7 + 10];
            RtlZeroMemory(package_1, sizeof(package_1));
            package_1[0] = 0x0000300D;
            package_1[4] = (*p).nID_1;
            package_1[5] = (*p).nID_2;
            package_1[6] = (*p).nIndex * 0x100;
            CRole::SendPackage((DWORD)&package_1[0]);

            // �@ȡһЩ�؂䅢��
            DWORD dwRole_74, dwRole_78;
            int nAddr = CRole::GetRoleAddr();
            martin->ReadPtrData(nAddr + 0x74, TEXT("��ǰ���� + 0x74"), dwRole_74);
            martin->ReadPtrData(nAddr + 0x78, TEXT("��ǰ���� + 0x78"), dwRole_78);

            float role_fx = 0.0f;
            float role_fy = 0.0f;
            float role_fz = 0.0f;
            martin->ReadPtrData(nAddr + OFFSET_COOR, TEXT("��ȡ [��ǰ���� x ����]"), role_fx);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x4, TEXT("��ȡ [��ǰ���� y ����]"), role_fy);
            martin->ReadPtrData(nAddr + OFFSET_COOR + 0x8, TEXT("��ȡ [��ǰ���� z ����]"), role_fz);

            DWORD ʱ��� = CBrushZones::��ȡʱ���();

            // �l�ڶ�����
            DWORD package_2[28 + 10];
            RtlZeroMemory(package_2, sizeof(package_2));
            package_2[0] = 0x00000251;
            package_2[4] = ʱ���;
            *(float*)&package_2[6] = role_fx;
            *(float*)&package_2[7] = role_fy;
            *(float*)&package_2[8] = role_fz;
            package_2[11] = dwRole_74;
            package_2[12] = dwRole_78;
            package_2[21] = 0x7A720002;
            package_2[22] = 0xA13C86D0;
            package_2[23] = 0xECB9B7E8;
            package_2[24] = 0x6D3684D8;
            package_2[25] = 0x00A26F7E;
            package_2[26] = 0x48AA0000;
            package_2[27] = 0x00010BED;
            CRole::SendPackage((DWORD)&package_2[0]);

            // �l��������
            int nAllId;
            auto it = std::find_if(CRole::s_allItems.begin(), CRole::s_allItems.end(), map_finder_name("����"));
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

            // �l���Ă���
            ʱ��� = CBrushZones::��ȡʱ���();
            DWORD package_4[26];
            RtlZeroMemory(package_4, sizeof(package_4));
            package_4[0] = 0x00100251;
            package_4[1] = 0x00000074;
            package_4[4] = ʱ���;
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
            return;
        }
    }
}

void On_WearEquipment(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    std::string strEquipment = *(std::string*)wParam;
    std::string strPlace = *(std::string*)lParam;
    // 0:������1��ͷ����2������3���ز���4��������5���Ų�
    int nPlace = 0;
    if (strPlace == "����") {
        nPlace = 0;
    } else if (strPlace == "ͷ��") {
        nPlace = 1;
    } else if (strPlace == "����") {
        nPlace = 2;
    } else if (strPlace == "�ز�") {
        nPlace = 3;
    } else if (strPlace == "����") {
        nPlace = 4;
    } else if (strPlace == "�Ų�") {
        nPlace = 5;
    } else {
        martin->Debug("װ����������");
        return;
    }

    CEquipment equipment;
    equipment.initEquipmentInfo();
    std::list<BagItem> equipment_list = equipment.GetEquipmentInfo();

    BOOL bEquipment = FALSE; // ��ʾ�����Ƿ���װ��
    for (auto p = equipment_list.begin(); p != equipment_list.end(); ++p) {
        if ((*p).strPlace == strPlace) {
            bEquipment = TRUE;
            break;
        }
    }

    DWORD OSIITE = OFFSET_SWAP_INVENTORY_ITEM - 0x4;
    if (bEquipment) {
        OSIITE = OFFSET_SWAP_INVENTORY_ITEM;
    }

    CBag bag;
    bag.initBagInfo();
    std::list<BagItem> bagItem_list = bag.GetBagInfo();

    int nIndex;
    BOOL bSendPackage = FALSE;
    for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
        if ((*p).strName == strEquipment) {
            nIndex = (*p).nIndex;
            bSendPackage = TRUE;
            break;
        }
    }

    if (bSendPackage) {
        int nRoleAddr = CRole::GetRoleAddr();
        try {
            _asm {
                pushad;
                pushfd;

                mov edi, nRoleAddr;
                add edi, OFFSET_SEND_PACKET_ECX_1;
                mov ecx, [edi];
                mov edx, [ecx];
                add edx, OSIITE;
                mov edx, [edx];
                mov eax, nPlace; //װ�����0:������1��ͷ����2������3���ز���4��������5���Ų���
                push eax;
                mov eax, 0x3;  //�̶�ֵ
                push eax;
                mov eax, nIndex;
                push eax;
                mov eax, 0x0; //�̶�ֵ
                push eax;
                call edx;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug("On_WearEquipment --> �쳣");
        }
    }
}

void On_GetRoleLevel(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(PINT)wParam = CRole::GetRoleLevel();
}

void On_PrecisionCompleteQuest(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    pQuestInfo questInfo = (pQuestInfo)wParam;
    pPOINT_TARGET pointTarget = (pPOINT_TARGET)lParam;

    quest.initUnCompleteQuest();
    for (auto& v : quest.m_unComplete_quest) {
        if (v.strQuestType == "����" && questInfo->strQuestName == v.strQuestName) {
            if (v.strQuestStatus == "���") {
                // ������
                // 1. �� NPC
                nearObj.initNear();
                for (auto& w : nearObj.m_near_object) {
                    if (w.strNpcName == questInfo->strNpcName) { // �ҵ� NPC
                        // �ȶ� npc ����
                        if (martin->Compare_Coord(pointTarget->fPontX, pointTarget->fPontY, w.fNpcPointX, w.fNpcPointY) < 5) {
                            nearObj.Interactive(w.nNpcID);
                            Sleep(50);
                            break;
                        } // ��Ŀ���������С�� 5 ���ʾ�ҵ��� npc 
                    }
                }
                // 2. ������
                quest.CompleteQuest(v.nQuestID);
                break;
            }
        }
    }
}

void On_FirstAttackTrun(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    int nAttackAutoDir, nAttackAutoDirTemp;
    if (martin->ReadPtrData(BASE_SETTINGS, "��ȡ ����һ������-- 1", nAttackAutoDirTemp)) {
        if (martin->ReadPtrData(nAttackAutoDirTemp + OFFSET_SETTINGS_ATTACK_AUTO_DIR, "��ȡ ����һ������-- 2", nAttackAutoDir)) {
            if (nAttackAutoDir != 1) {
                *(PINT)(nAttackAutoDirTemp + OFFSET_SETTINGS_ATTACK_AUTO_DIR) = 1;
            }
        }
    }
}

void On_Login(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CLogin oLogin;
    if (oLogin.LoginGame()) {
        *(PINT)wParam = 1;
    }
}

void On_NewRole(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CLogin oLogin;
    oLogin.NewRole();
}

void On_CountsOfRoles(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CLogin oLogin;
    *(PINT)wParam = oLogin.GetCountsOfRoles();
}

void On_EnterChannel(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CLogin oLogin;
    oLogin.EnterChannel();
}

void On_IsOnLine(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CLogin oLogin;
    *(PINT)wParam = static_cast<int>(oLogin.IsOnline());
}

void On_IsLoading(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    int nRet = 0;
    martin->ReadPtrData(BASE_LOADING_FLAG, "��ȡ [��ͼ��ʶ]", nRet);
    if (nRet == 0) { // ��ͼ���
        *(PINT)wParam = 0; // ���ؼ�, ��ʾ���ڹ�ͼ
    } else {
        *(PINT)wParam = 1; // ������, ��ʾ�ڹ�ͼ
    }
}

void On_IsSelect(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    *(PINT)wParam = 0;
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
        martin->Debug("RoleTraverse --> �쳣");
        return;
    }

    int nRet;
    if (martin->ReadPtrData(dwRoleListAddr + 0x10, "��ȡ [��ɫ�б���������Ϣ]", nRet)) {
        if (nRet == 1) {
            *(PINT)wParam = 1;
        }
    }
}

void On_��ȡ�ɳ������һ�ȯ(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    DWORD dwPackage[100];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x00004807;
    dwPackage[4] = 0x00000082;
    dwPackage[5] = 0x017FE301;
    dwPackage[6] = 0x00000060;
    dwPackage[7] = 0x000000D8;
    CRole::SendPackage((DWORD)&dwPackage);
}

void On_�һ�����֮��(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    DWORD dwPackage[100];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x00000F01;
    dwPackage[4] = 0x0000002D;
    dwPackage[5] = 0x000002B6;
    dwPackage[6] = 0x00000001;
    dwPackage[7] = 0xFFFFFFFF;
    dwPackage[8] = 0xFFFFFFFF;
    CRole::SendPackage((DWORD)&dwPackage);
}

void On_�һ�����֮��(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    DWORD dwPackage[100];
    RtlZeroMemory(&dwPackage, sizeof(dwPackage));
    dwPackage[0] = 0x00000F01;
    dwPackage[4] = 0x0000002D;
    dwPackage[5] = 0x000002BD;
    dwPackage[6] = 0x00000001;
    dwPackage[7] = 0xFFFFFFFF;
    dwPackage[8] = 0xFFFFFFFF;
    CRole::SendPackage((DWORD)&dwPackage);
}

void On_ReturnSelectRole(HWND hDlg, WPARAM wParam, LPARAM lParam) {
    CLogin oLogin;
    oLogin.ReturnSelectRole();
}

//void On_InitRoleList(HWND hDlg, WPARAM wParam, LPARAM lParam) {
//    CLogin oLogin;
//    oLogin.RoleTraverse();
//}
