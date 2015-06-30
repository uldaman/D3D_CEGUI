#pragma once
#include <string>
#include <list>
#include "Bag.h"
/*-----------------------------------------------------------------------
* 类名: CEquipment
* 说明: 装备类
* 成员索引对应的装备类别：
        0:武器，1：头部，2：手腕部，3：胸部（铠甲等），4：腰部，5：脚部
-----------------------------------------------------------------------*/

class CEquipment {
public:
    void initEquipmentInfo(); // 初始化当前装备

    std::list<BagItem> GetEquipmentInfo() { //获取背包详情
        return m_equipment_list;
    }

protected:
    std::list<BagItem> m_equipment_list;
    int nMaxCapacity; // 装备格子总数
    int nCurrentCapacity; // 当前已用格子
};

