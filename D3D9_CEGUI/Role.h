#pragma once
#include <string>
#include <windows.h>

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
    static void RoleTeleport(int nKey, float fx, float fy, float fz);
    static void ByMap(const char* szKey); // ������ͼ
    static void Turn(); // ת��
    static BOOL TurntoBoss(int nKey);
    static void Attack_Pack(int nPart); // �������
    static void GoForward();
    static void Stop();
    static void Attack();
    static int HaveWeapon();
    static void Weapon();

protected:
    int         m_nRoleAddr; // ����ָ��
    static BOOL Attack_Pack_Boss(int nBossKey, int nPart);
    static void Send_Attack_Pack(int nRoleKey, int nBoosKey, float fx, float fy, float fz, int nPart);

private:
    CRole();
    static CRole*  m_cInstance;
};