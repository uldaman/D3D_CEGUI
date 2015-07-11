#pragma once
#include <windows.h>
/////////////////////////////////////////////////////////////////////////
// �ļ���:   Interface.h
// ˵��:     ��������HOOK��Ϸ���ڹ��̺���Զ�����Ϣ
// ����ʱ��: 2015/06/10 20:36
//
// ������־: 
/////////////////////////////////////////////////////////////////////////

void MesageMapping(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void On_GetCurrentQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰ����
void On_GetQuestTable(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ�ɽ�����
void On_IsQuestComplete(HWND hDlg, WPARAM wParam, LPARAM lParam); // �ж������Ƿ����
void On_WhereRole(HWND hDlg, WPARAM wParam, LPARAM lParam); // �жϵ�ǰ�����ڳ����Ǹ���, 0: ����  2: FB
void On_CompleteQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������
void On_AcceptQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������
void On_InteractiveQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����Ի�
void On_��������̽�(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��������̽�
void On_MadeHpMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����ظ�ҩ
void On_CityFly(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������
void On_ChooseFB(HWND hDlg, WPARAM wParam, LPARAM lParam); // ѡ�񸱱�
void On_StartFB(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ʼ����
void On_IntoFB(HWND hDlg, WPARAM wParam, LPARAM lParam); // ���븱��
void On_UpdataBoss(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ BOSS ��
void On_RoleRoom(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰ����
void On_BossRoom(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡBOSS����
void On_GetZone(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰ����
void On_GetMap(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰ��ͼ
void On_GotoBoss(HWND hDlg, WPARAM wParam, LPARAM lParam); // ˲�Ƶ�BOSS
void On_ByMap(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������ͼ
void On_Turn(HWND hDlg, WPARAM wParam, LPARAM lParam); // ת��
void On_AttackPack(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_Forward(HWND hDlg, WPARAM wParam, LPARAM lParam); // ǰ��
void On_Stop(HWND hDlg, WPARAM wParam, LPARAM lParam); // ǰ��
void On_Attack(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_HaveWeapon(HWND hDlg, WPARAM wParam, LPARAM lParam); // �ж��Ƿ�װ��������
void On_Weapon(HWND hDlg, WPARAM wParam, LPARAM lParam); // װ������
void On_GetHpPer(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰѪ��
void On_Invincible(HWND hDlg, WPARAM wParam, LPARAM lParam); // �����޵�
void On_UnInvincible(HWND hDlg, WPARAM wParam, LPARAM lParam); // �ر��޵�
void On_Teleport(HWND hDlg, WPARAM wParam, LPARAM lParam); // ˲�Ƶ�����
void On_GetPoint(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰ����
void On_GoLeft(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_GoRight(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_GoBack(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_HaveMode(HWND hDlg, WPARAM wParam, LPARAM lParam); // �Ƿ��ڲ˵�ģʽ
void On_ChangeMode(HWND hDlg, WPARAM wParam, LPARAM lParam); // �л��˵�ģʽ
void On_Roll(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_GetItemFormCrates(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������ȡ��
void On_GetCollect(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ�ɼ���־λ
void On_Collect(HWND hDlg, WPARAM wParam, LPARAM lParam); // �ɼ�
void On_GetCollects(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ�ɼ�����Ϣ
void On_Barbecues(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_GetBagItemNum(HWND hDlg, WPARAM wParam, LPARAM lParam); // �@ȡ������Ʒ����
void On_EatMeat(HWND hDlg, WPARAM wParam, LPARAM lParam); // �Կ���
void On_CommonUseItems(HWND hDlg, WPARAM wParam, LPARAM lParam); // ͨ��ʹ����Ʒ
void On_PrecisionAcceptQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��׼������, ͨ���ȶ� NPC ������
void On_BuySupply(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������Ʒ
void On_KillMonster(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ɱ��Ʒ
void On_GetMonsterRoom(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ɱ��Ʒ
void On_GotoMonster(HWND hDlg, WPARAM wParam, LPARAM lParam); // ˲�Ƶ���ǹ�
void On_TurnToMonster(HWND hDlg, WPARAM wParam, LPARAM lParam); // ת�򵽱�ǹ�
void On_TurnToPoint(HWND hDlg, WPARAM wParam, LPARAM lParam); // ת�򵽱�ǹ�
void On_AcceptOfferAReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������������
void On_GetCurrentReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰ��������
void On_GetRewardBrushZone(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ���͸���
void On_GetCountRewardToday(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ������������ʹ���
void On_GetAcceptReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ�ɽ�����
void On_AcceptReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������
void On_�����������̽�(HWND hDlg, WPARAM wParam, LPARAM lParam); // �����������̽�
void On_GetExperienceLimit(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��������
void On_GetWarehouseItemNum(HWND hDlg, WPARAM wParam, LPARAM lParam); // �@ȡ�ֿ���Ʒ����
void On_IntoMyManor(HWND hDlg, WPARAM wParam, LPARAM lParam); // �����ҵ�ׯ԰
void On_LeaveManor(HWND hDlg, WPARAM wParam, LPARAM lParam); // �뿪ׯ԰
void On_UpgradeMushroom(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��������ľ��
void On_MoveInventoryItem(HWND hDlg, WPARAM wParam, LPARAM lParam); // ���
void On_GetBag(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����
void On_����嶡������(HWND hDlg, WPARAM wParam, LPARAM lParam); // ����嶡������
void On_EatMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam); // �Իظ�ҩ
void On_PayItems(HWND hDlg, WPARAM wParam, LPARAM lParam); // ������Ʒ
void On_GetGlowingArticle(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ������Ʒ
void On_��������è(HWND hDlg, WPARAM wParam, LPARAM lParam);
void On_װ��������(HWND hDlg, WPARAM wParam, LPARAM lParam);
void On_TakeMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam);  // �ݴ�ʽ��ҩ
void On_WearEquipment(HWND hDlg, WPARAM wParam, LPARAM lParam);  // ��װ��
void On_GetRoleLevel(HWND hDlg, WPARAM wParam, LPARAM lParam);  // ��ȡ����ȼ�
void On_PrecisionCompleteQuest(HWND hDlg, WPARAM wParam, LPARAM lParam);  // ��׼������, ͨ���ȶ� NPC ������
void On_FirstAttackTrun(HWND hDlg, WPARAM wParam, LPARAM lParam);  // ������һ������
void On_Login(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ʼ��Ϸ(�ǽ�����Ϸ, ��ʼ��Ϸ��Ҫѡ��Ƶ��)
void On_NewRole(HWND hDlg, WPARAM wParam, LPARAM lParam); // �½���ɫ
void On_CountsOfRoles(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ��ǰ��ɫ����
void On_EnterChannel(HWND hDlg, WPARAM wParam, LPARAM lParam); // ȷ��Ƶ��, ȷ�Ϻ�ͽ�����Ϸ��
void On_IsOnLine(HWND hDlg, WPARAM wParam, LPARAM lParam); // �Ƿ�����
void On_IsLoading(HWND hDlg, WPARAM wParam, LPARAM lParam); // �Ƿ��ͼ
//void On_InitRoleList(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ʼ���б�
void On_IsSelect(HWND hDlg, WPARAM wParam, LPARAM lParam); // �Ƿ���ѡ���ɫ
void On_��ȡ�ɳ������һ�ȯ(HWND hDlg, WPARAM wParam, LPARAM lParam); // ��ȡ�ɳ������һ�ȯ
void On_�һ�����֮��(HWND hDlg, WPARAM wParam, LPARAM lParam); // �һ�����֮��
void On_�һ�����֮��(HWND hDlg, WPARAM wParam, LPARAM lParam); // �һ�����֮��
void On_ReturnSelectRole(HWND hDlg, WPARAM wParam, LPARAM lParam); // ���ؽ�ɫѡ��