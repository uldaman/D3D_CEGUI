#include "Bag.h"
#include "Martin.h"
#include "Base.h"
#include "Role.h"

void BAG_ITEM::initBagItem(int nAddr, int _nIndex) {
    nIndex = _nIndex;
    martin->ReadPtrData(nAddr + 0x3C, TEXT("获取 [物品数量]"), nNum);
    nNum = max(1, nNum);
    martin->ReadPtrData(nAddr + 0x10, TEXT("获取 [物品ID_1]"), nID_1);
    martin->ReadPtrData(nAddr + 0x14, TEXT("获取 [物品ID_2]"), nID_2);
    int nInfoAddr;
    if (martin->ReadPtrData(nAddr + 0x8, TEXT("获取 [物品详情]"), nInfoAddr)) {
        int nName;
        if (martin->ReadPtrData(nInfoAddr + 0x14, TEXT("获取 [物品名称]"), nName)) {
            strName = (char*)nName;
        }
    }
}

void BAG_ITEM::MoveInventoryItem() {

    int _nIndex = nIndex;
    int nRoleAddr = CRole::GetRoleAddr();
    if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, TEXT("获取当前背包"), nRoleAddr)) {
        try {
            _asm {
                mov eax, 00000002; //固定值
                push eax;
                mov eax, _nIndex; //物品在背包中的索引
                push eax;
                mov eax, 00000000; //固定值
                push eax;
                mov eax, nRoleAddr; //[2B391020+42f4]
                push eax;
                mov eax, CALL_MOVE_INVENTORY_ITEM;  //CALL_MOVE_INVENTORY_ITEM
                call eax;
            }
        } catch (...) {
            martin->Debug(TEXT("MoveInventoryItem --> 异常"));
        }
    }
}

void CBag::initBagInfo() {
    m_bagItem_list.swap(std::list<BagItem>()); // 清空当前列表

    nMaxCapacity = nCurrentCapacity = 0;

    int nRoleAddr = CRole::GetRoleAddr();
    
    int nTemp = 0, nAddr = 0;
    if (martin->ReadPtrData(nRoleAddr + OFFSET_SEND_PACKET_ECX_1, TEXT("获取 [当前背包] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + 0 * 4 + 0xC, TEXT("获取 [当前背包] -- 2"), nTemp)) {
            martin->ReadPtrData(nTemp + 0x8, TEXT("获取 [当前背包容量]"), nMaxCapacity);
            martin->ReadPtrData(nTemp + 0x18, TEXT("获取 [当前背包物品数组]"), nAddr);
        }
    }

    if (nAddr) {
        //martin->Debug(TEXT("0x%X"), nAddr);
        for (int j = 0, i = nAddr; j < nMaxCapacity; j++, i += 0xC) {
            int nItem;
            if (martin->ReadPtrData(i + 0x8, TEXT("获取 [物品指针]"), nItem)) {
                if (IsBadReadPtr((CONST VOID*)nItem, sizeof(DWORD)) == 0) {
                    BagItem bagItem;
                    bagItem.initBagItem(nItem, j);
                    m_bagItem_list.push_back(bagItem);
                    nCurrentCapacity++;
                }
            }
        }
    }
}