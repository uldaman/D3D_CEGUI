#pragma once
#include <string>
#include <list>
#include "Bag.h"
/*-----------------------------------------------------------------------
* ����: CEquipment
* ˵��: װ����
* ��Ա������Ӧ��װ�����
        0:������1��ͷ����2�����󲿣�3���ز������׵ȣ���4��������5���Ų�
-----------------------------------------------------------------------*/

class CEquipment {
public:
    void initEquipmentInfo(); // ��ʼ����ǰװ��

    std::list<BagItem> GetEquipmentInfo() { //��ȡ��������
        return m_equipment_list;
    }

protected:
    std::list<BagItem> m_equipment_list;
    int nMaxCapacity; // װ����������
    int nCurrentCapacity; // ��ǰ���ø���
};

