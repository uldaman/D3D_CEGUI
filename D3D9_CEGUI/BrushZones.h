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
#include <list>

#pragma pack (push,1)

typedef struct CRATES_LIST {
    DWORD dwNext;   // +0x0	    下一节点
    DWORD dwRoot;  // +0x4	    上一节点
    DWORD dwBase;	// +0x8	    详情指针
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
    int nMonsterAddr; // 怪物基址, 用来实时获取死亡状态
    BOOL bIsDead; // 死亡状态
    int nMonsterRoom; // 怪物房间
    float fDistance;
} Monster, *pMonster;

#pragma pack(pop)

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

    static std::list<Monster> m_monster_list;  // 副本内指定怪物列表
    static pMonster m_monster;
    void initMonster(std::string strMonster); // 初始化副本内指定怪物


    void GetItemFormCrates(std::string strItems); // 补给箱取物
    void TraverList(int nStart, int nEnd, std::multimap<std::string, IdIndex>& CratesMap);
    void allotItem(int nObject, std::multimap<std::string, IdIndex>& CratesMap);
    void GetItemPack(int nIndex, int nID);
    static int 获取时间戳();

protected:
    BOOL GetBoss(int nKey);
    void GetMonster(int nKey, std::string strMonster);
};

