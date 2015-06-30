#pragma once
#include <string>
#include <list>
#include "Bag.h"
/*-----------------------------------------------------------------------
* 类名: CWarehouse
* 说明: 仓库类
-----------------------------------------------------------------------*/

class CWarehouse {
public:
    void initWarehouseInfo(); // 初始化当前仓库

    std::list<BagItem> GetWarehouseInfo() { //获取仓库详情
        return m_warehouse_list;
    }

protected:
    std::list<BagItem> m_warehouse_list;
    int nMaxCapacity; // 背包格子总数
    int nCurrentCapacity; // 当前已用格子
};

