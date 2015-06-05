/////////////////////////////////////////////////////////////////////////
// 文件名:   BrushZones.h
// 说明:     副本类
// 创建时间: 2015/06/04 20:38
//
// 更新日志: 
/////////////////////////////////////////////////////////////////////////
#pragma once
#include <map>
#include <windows.h>

class CBrushZones {
public:
    CBrushZones();
    ~CBrushZones();

    void initZonesInfo(); // 初始化游戏内所有副本
    static std::map<std::string, int> s_fbMap;

    void ChooseFB(int nZoneId);
    void StartFB(int nZoneId);
    void IntoFB();

    void initBoss();
    void GotoBoss();
    BOOL Teleport(int nKey);
    int m_nBossRoom; // BOSS房间
    std::string m_strBossName; // BOSS 名

protected:
    BOOL GetBoss(int nKey);
};

