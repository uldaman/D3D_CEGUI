#pragma once
#include <string>
#include <windows.h>
#include "GameHOOK.h"
#include <map>
#include "DataType.h"

class map_finder_name {
public:
    map_finder_name(std::string cmp_string) : m_string(cmp_string) {}

    bool operator () (const std::map<int, NAME_OID>::value_type pair) {
        return pair.second.strName == m_string;
    }
private:
    std::string m_string;
};

class CRole {
public:
    virtual ~CRole();
    static CRole* GetInstance();
    static int GetRoleAddr();
    static int WhereIsRole(); // ��ǰ����λ��, 0: ����  2: FB
    static void SendPackage(DWORD PDATA);
    static std::string GetRoleMap(); // ��ȡ��ǰ��ͼ
    static std::string GetRoleZone(); // ��ȡ��ǰ����
    static void CityFly(std::string strKey); // ������
    static int GetRoleRoom(); // ��ȡ��ǰ����
    static void TeleportToPoint(float fx, float fy, float fz);
    static void RoleTeleport(int nKey, float fx, float fy, float fz);
    static void GetPoint(float& fx, float& fy, float& fz);
    static void ByMap(const char* szKey); // ������ͼ
    static void Turn(); // ת��
    static BOOL TurntoBoss(int nKey);
    static void Attack_Pack(int nPart); // �������
    static void GoForward();
    static void GoLeft();
    static void GoRight();
    static void GoBack();
    static void Stop(std::string pos);
    static void Attack();
    static void Roll();
    static int HaveWeapon();
    static int HaveMode();
    static void Weapon();
    static void ChangeMode();
    static float GetHpPer(); // ��ȡѪ���ٷֱ�
    static int GetRoleLevel(); // ��ȡ����ȼ�
    static void Invincible(); // ���޵�
    static void UnInvincible(); // ���޵�
    static void CatInvincible(); // è�޵�
    static BOOL WhetherOrBusy(); // TRUE ��ʾ�ڷ�æ
    static void Collect(int nID);
    static int GetExpLimit(); // ��ȡ��������
    static void SetAccompanyingCat(); // ��è��Ϊ����
    static void װ���嶡������(); // Ϊèװ���嶡������

    static std::map<int, NAME_OID> s_allItems; // ��Ϸ��������Ʒ
    static void initAllItems();

protected:
    int         m_nRoleAddr; // ����ָ��
    static BOOL Attack_Pack_Boss(int nBossKey, int nPart);
    static void Send_Attack_Pack(int nRoleKey, int nBoosKey, float fx, float fy, float fz, int nPart);
    static int Decode(int nData); // ���ݽ���

private:
    CRole();
    static CRole*  m_cInstance;
    static CGameHOOK m_hook; // ����ʵ�������޵�
    static CGameHOOK m_CatHook; // ����ʵ��è�޵�
};