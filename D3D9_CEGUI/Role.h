#pragma once
#include <string>
#include <windows.h>

class CRole {
public:
    virtual ~CRole();
    static CRole* GetInstance();
    static int GetRoleAddr();
    static int WhereIsRole(); // 当前人物位置, 0: 城镇  2: FB
    static void SendPackage(DWORD PDATA);
    static std::string GetRoleMap(); // 获取当前地图
    static std::string GetRoleZone(); // 获取当前副本
    static void CityFly(std::string strKey); // 城镇传送
    static int GetRoleRoom(); // 获取当前房间
    static void RoleTeleport(int nKey, float fx, float fy, float fz);
    static void ByMap(const char* szKey); // 副本过图
    static void Turn(); // 转向
    static BOOL TurntoBoss(int nKey);
    static void Attack_Pack(int nPart); // 攻击封包
    static void GoForward();
    static void Stop();
    static void Attack();
    static int HaveWeapon();
    static void Weapon();

protected:
    int         m_nRoleAddr; // 人物指针
    static BOOL Attack_Pack_Boss(int nBossKey, int nPart);
    static void Send_Attack_Pack(int nRoleKey, int nBoosKey, float fx, float fy, float fz, int nPart);

private:
    CRole();
    static CRole*  m_cInstance;
};