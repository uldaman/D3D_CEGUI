#pragma once
#include <string>
#include <list>


/*-----------------------------------------------------------------------
* ����: CBag
* ˵��: ������, ��ű�����Ʒ
-----------------------------------------------------------------------*/

typedef struct BAG_ITEM {
    std::string strName;
    int nNum;
    int nIndex;
    int nID_1;
    int nID_2;
    void initBagItem(int nAddr, int _nIndex);
    void MoveInventoryItem(); // ����
} BagItem, *pBagItem;

class CBag {
public:
    void initBagInfo(); // ��ʼ����ǰ������ʹ�����

    std::list<BagItem> GetBagInfo() { //��ȡ��������
        return m_bagItem_list;
    }

protected:
    std::list<BagItem> m_bagItem_list;
    int nMaxCapacity; // ������������
    int nCurrentCapacity; // ��ǰ���ø���
};

