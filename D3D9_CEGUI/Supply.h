#pragma once
#include <string>
#include <list>


/*-----------------------------------------------------------------------
 * 类名: CSupply
 * 说明: 补给类, 即从商店购买物品, 步骤: 对话->遍历->购买
-----------------------------------------------------------------------*/
typedef struct t_supply {
    std::string strItemName;
    std::string strTypeName;
    int nTypeID;
    int nSupplyID;
} Supply, *pSupply;

class CSupply {
public:
    CSupply();
    ~CSupply();

    void initSupply();
    static std::list<Supply> m_supply_list;
};

