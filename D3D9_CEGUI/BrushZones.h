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

#pragma pack (push,1)

typedef struct CRATES_LIST {
    DWORD dwNext;   // +0x0	    下一节点
    DWORD dwRoot;  // +0x4	    上一节点
    DWORD dwBase;	// +0x8	    详情指针
} CratesList, *pCratesList;

typedef struct ID_INDEX {
    DWORD dwID;   // +0x0	    下一节点
    DWORD dwIndex;  // +0x4	    上一节点
} IdIndex, *pIdIndex;

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


    void GetItemFormCrates(std::string strItems); // 补给箱取物
    void TraverList(int nStart, int nEnd, std::multimap<std::string, IdIndex>& CratesMap);
    void allotItem(int nObject, std::multimap<std::string, IdIndex>& CratesMap);
    void GetItemPack(int nIndex, int nID);

protected:
    BOOL GetBoss(int nKey);
};

