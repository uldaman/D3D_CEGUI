/////////////////////////////////////////////////////////////////////////
// �ļ���:   BrushZones.h
// ˵��:     ������
// ����ʱ��: 2015/06/04 20:38
//
// ������־: 
/////////////////////////////////////////////////////////////////////////
#pragma once
#include <map>
#include <windows.h>

class CBrushZones {
public:
    CBrushZones();
    ~CBrushZones();

    void initZonesInfo(); // ��ʼ����Ϸ�����и���
    static std::map<std::string, int> s_fbMap;

    void ChooseFB(int nZoneId);
    void StartFB(int nZoneId);
    void IntoFB();

    void initBoss();
    void GotoBoss();
    BOOL Teleport(int nKey);
    int m_nBossRoom; // BOSS����
    std::string m_strBossName; // BOSS ��

protected:
    BOOL GetBoss(int nKey);
};

