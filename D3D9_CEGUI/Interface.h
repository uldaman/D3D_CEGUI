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