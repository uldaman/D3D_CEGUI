#include "Equipment.h"
#include "Martin.h"
#include "Base.h"
#include "Role.h"

void CEquipment::initEquipmentInfo() {
    m_equipment_list.swap(std::list<BagItem>()); // 清空当前列表

    nMaxCapacity = nCurrentCapacity = 0;

    int nRoleAddr = CRole::GetRoleAddr();
    
    int nTemp = 0, nAddr = 0;
    if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, TEXT("获取 [当前装备] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + 3 * 4 + 0xC, TEXT("获取 [当前装备] -- 2"), nTemp)) {
            martin->ReadPtrData(nTemp + 0x8, TEXT("获取 [当前装备容量]"), nMaxCapacity);
            martin->ReadPtrData(nTemp + 0x18, TEXT("获取 [当前背包物品数组]"), nAddr);
        }
    }

    if (nAddr) {
        //martin->Debug(TEXT("0x%X"), nAddr);
        for (int j = 0, i = nAddr; j < nMaxCapacity; j++, i += 0xC) {
            int nItem;
            if (martin->ReadPtrData(i + 0x8, TEXT("获取 [装备指针]"), nItem)) {
                if (IsBadReadPtr((CONST VOID*)nItem, sizeof(DWORD)) == 0) {
                    BagItem bagItem;
                    bagItem.initBagItem(nItem, j);
                    switch (j) { // 0:武器，1：头部，2：手腕，3：胸部，4：腰部，5：脚部
                    case 0:
                        bagItem.strPlace = "武器";
                        break;
                    case 1:
                        bagItem.strPlace = "头部";
                        break;
                    case 2:
                        bagItem.strPlace = "手腕";
                        break;
                    case 3:
                        bagItem.strPlace = "胸部";
                        break;
                    case 4:
                        bagItem.strPlace = "腰部";
                        break;
                    case 5:
                        bagItem.strPlace = "脚部";
                        break;
                    default:
                        bagItem.strPlace = "UnKnown";
                        break;
                    }

                    m_equipment_list.push_back(bagItem);
                    nCurrentCapacity++;
                }
            }
        }
    }
}
