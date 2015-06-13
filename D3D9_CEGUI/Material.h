#pragma once
#include <string>
#include <list>
#include <windows.h>

/*-----------------------------------------------------------------------
* 类名: CMaterial
* 说明: 材料类, 游戏里地面上可采集的物品
-----------------------------------------------------------------------*/

typedef struct MATERIAL {
    std::string strName;
    float fPointX;
    float fPointY;
    float fPointZ;
    int nID;
    int nKey;
    int nType; // 类别 1:矿（挖矿工具）,2:药草,3:昆虫（捕虫工具）,5:蘑菇,6:蜂蜜,7:地面小石头,8:粪便,0xA:怪物尸体,0xC:骨头,0x11:网
    //int nIndex; //房间号
} material, *pMaterial;

class CMaterial {
public:
    void initMaterial(); // 遍历当前房间的地面物品, 初始化 m_material_list 列表
    static std::list<material> m_material_list;
};

