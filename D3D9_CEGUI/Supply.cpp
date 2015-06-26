#include "Supply.h"
#include "Martin.h"
#include "Base.h"
#include "Role.h"

std::list<Supply> CSupply::m_supply_list;

CSupply::CSupply() {
}


CSupply::~CSupply() {
}


// 说明: 初始化商店物品列表
void CSupply::initSupply() {
    m_supply_list.clear();
    char* szNpcSaleInfo = "CNpcSaleInfo";
    int nSupplyArry = 0;
    try {
        _asm {
        	pushad;
        	pushfd;
        	
            mov ecx, 0;
            push ecx;
            mov edx, szNpcSaleInfo; //ASCII 字符串指针 "CNpcSaleInfo" 
            push edx;
            mov ecx, 0;
            push ecx;
            mov eax, CALL_GET_GLOBAL_VARIABLE; //CALL_GET_GLOBAL_VARIABLE
            call eax;
            add esp, 0xc;
            mov nSupplyArry, eax;

        	popfd;
        	popad;
        }
    } catch (...) {
    	martin->Debug("initSupply --> 异常");
        return;
    }

    if (nSupplyArry) {
        DWORD dwSupplyArryStart, dwSupplyArryEnd;
        martin->ReadPtrData(nSupplyArry + 0x14, "获取 [商品组开始]", dwSupplyArryStart);
        martin->ReadPtrData(nSupplyArry + 0x18, "获取 [商品组结束]", dwSupplyArryEnd);
        //martin->Debug("商品组开始: 0x%X -- 商品组结束: 0x%X", dwSupplyArryStart, dwSupplyArryEnd);

        // 遍历商品大组
        for (unsigned int nSupplyItemArry = dwSupplyArryStart; nSupplyItemArry < dwSupplyArryEnd; nSupplyItemArry += 0x4) {
            int nTempSupplyItemArry;
            if (martin->ReadPtrData(nSupplyItemArry, "获取 [商品组]", nTempSupplyItemArry)) {
                DWORD dwSupplyItemArryStart, dwSupplyItemArryEnd;
                Supply supply;
                int nTypeName = 0;
                martin->ReadPtrData(nTempSupplyItemArry + 0x18, "获取 [商品分类名]", nTypeName);
                if (IsBadReadPtr((CONST VOID*)nTypeName, sizeof(DWORD)) == 0) {
                    supply.strTypeName = (char*)nTypeName;
                }

                martin->ReadPtrData(nTempSupplyItemArry + 0x1C, "获取 [商品信息组开始]", dwSupplyItemArryStart);
                martin->ReadPtrData(nTempSupplyItemArry + 0x20, "获取 [商品信息组结束]", dwSupplyItemArryEnd);
                //martin->Debug("商品信息组开始: 0x%X -- 商品信息组结束: 0x%X", dwSupplyItemArryStart, dwSupplyItemArryEnd);

                // 遍历商品小组, 对比所有物品信息 ID
                for (unsigned int nSupplyItem = dwSupplyItemArryStart; nSupplyItem < dwSupplyItemArryEnd; nSupplyItem += SIZE_SALE_ITEM) {
                    int nItemID = 0; // 此 ID 为物品 ID, 为来和 所有物品信息 中的 ID 对比, 取物品名
                    if (martin->ReadPtrData(nSupplyItem + 0x28, "获取 [商品物品 ID]", nItemID)) {
                        auto it = CRole::s_allItems.find(nItemID);
                        if (it != CRole::s_allItems.end()) { // 说明匹配到ID了
                            supply.strItemName = it->second.strName;
                            martin->ReadPtrData(nSupplyItem + 0x8, "获取 [商品 ID]", supply.nSupplyID);
                            martin->ReadPtrData(nSupplyItem + 0xC, "获取 [商品分类 ID]", supply.nTypeID);
                            //martin->Debug("%s -- 商品ID: 0x%X -- 分类ID: 0x%X -- 分类名: %s", supply.strItemName.c_str(), supply.nSupplyID, supply.nTypeID, supply.strTypeName.c_str());
                            m_supply_list.push_back(supply);
                        }
                    }
                }
            }
        }
    }
}
