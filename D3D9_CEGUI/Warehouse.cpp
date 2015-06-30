#include "Warehouse.h"
#include "Martin.h"
#include "Base.h"
#include "Role.h"

void CWarehouse::initWarehouseInfo() {
    m_warehouse_list.swap(std::list<BagItem>()); // ��յ�ǰ�б�

    nMaxCapacity = nCurrentCapacity = 0;

    int nRoleAddr = CRole::GetRoleAddr();
    
    int nTemp = 0, nAddr = 0;
    if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, TEXT("��ȡ [��ǰ�ֿ�] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + 2 * 4 + 0xC, TEXT("��ȡ [��ǰ�ֿ�] -- 2"), nTemp)) {
            martin->ReadPtrData(nTemp + 0x8, TEXT("��ȡ [��ǰ�ֿ�����]"), nMaxCapacity);
            martin->ReadPtrData(nTemp + 0x18, TEXT("��ȡ [��ǰ�ֿ���Ʒ����]"), nAddr);
        }
    }

    if (nAddr) {
        //martin->Debug(TEXT("0x%X"), nAddr);
        for (int j = 0, i = nAddr; j < nMaxCapacity; j++, i += 0xC) {
            int nItem;
            if (martin->ReadPtrData(i + 0x8, TEXT("��ȡ [��Ʒָ��]"), nItem)) {
                if (IsBadReadPtr((CONST VOID*)nItem, sizeof(DWORD)) == 0) {
                    BagItem bagItem;
                    bagItem.initBagItem(nItem, j);
                    m_warehouse_list.push_back(bagItem);
                    nCurrentCapacity++;
                }
            }
        }
    }
}
