#pragma once
#include <string>
#include <list>


/*-----------------------------------------------------------------------
 * ����: CSupply
 * ˵��: ������, �����̵깺����Ʒ, ����: �Ի�->����->����
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

