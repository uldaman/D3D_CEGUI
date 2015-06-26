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
#include <list>

#pragma pack (push,1)

typedef struct CRATES_LIST {
    DWORD dwNext;   // +0x0	    ��һ�ڵ�
    DWORD dwRoot;  // +0x4	    ��һ�ڵ�
    DWORD dwBase;	// +0x8	    ����ָ��
} CratesList, *pCratesList;

typedef struct ID_INDEX {
    DWORD dwID;   
    DWORD dwIndex;
} IdIndex, *pIdIndex;

typedef struct t_monster {
    float fMonsterPointX;
    float fMonsterPointY;
    float fMonsterPointZ;
    std::string strMonsterName;
    int nMonsterAddr; // �����ַ, ����ʵʱ��ȡ����״̬
    BOOL bIsDead; // ����״̬
    int nMonsterRoom; // ���﷿��
    float fDistance;
} Monster, *pMonster;

#pragma pack(pop)

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

    static std::list<Monster> m_monster_list;  // ������ָ�������б�
    static pMonster m_monster;
    void initMonster(std::string strMonster); // ��ʼ��������ָ������


    void GetItemFormCrates(std::string strItems); // ������ȡ��
    void TraverList(int nStart, int nEnd, std::multimap<std::string, IdIndex>& CratesMap);
    void allotItem(int nObject, std::multimap<std::string, IdIndex>& CratesMap);
    void GetItemPack(int nIndex, int nID);
    static int ��ȡʱ���();

protected:
    BOOL GetBoss(int nKey);
    void GetMonster(int nKey, std::string strMonster);
};

