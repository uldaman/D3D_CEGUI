#pragma once
#include <string>
#include <list>
#include "Bag.h"
/*-----------------------------------------------------------------------
* ����: CWarehouse
* ˵��: �ֿ���
-----------------------------------------------------------------------*/

class CWarehouse {
public:
    void initWarehouseInfo(); // ��ʼ����ǰ�ֿ�

    std::list<BagItem> GetWarehouseInfo() { //��ȡ�ֿ�����
        return m_warehouse_list;
    }

protected:
    std::list<BagItem> m_warehouse_list;
    int nMaxCapacity; // ������������
    int nCurrentCapacity; // ��ǰ���ø���
};

