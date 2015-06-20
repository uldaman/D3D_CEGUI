#pragma once
#include <string>
#include <list>


/*-----------------------------------------------------------------------
* 类名: CBag
* 说明: 背包类, 存放背包物品
-----------------------------------------------------------------------*/

typedef struct BAG_ITEM {
    std::string strName;
    int nNum;
    int nIndex;
    int nID_1;
    int nID_2;
    void initBagItem(int nAddr, int _nIndex);
    void MoveInventoryItem(); // 存物
} BagItem, *pBagItem;

class CBag {
public:
    void initBagInfo(); // 初始化当前背包的使用情况

    std::list<BagItem> GetBagInfo() { //获取背包详情
        return m_bagItem_list;
    }

protected:
    std::list<BagItem> m_bagItem_list;
    int nMaxCapacity; // 背包格子总数
    int nCurrentCapacity; // 当前已用格子
};

