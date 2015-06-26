#include "Supply.h"
#include "Martin.h"
#include "Base.h"
#include "Role.h"

std::list<Supply> CSupply::m_supply_list;

CSupply::CSupply() {
}


CSupply::~CSupply() {
}


// ˵��: ��ʼ���̵���Ʒ�б�
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
            mov edx, szNpcSaleInfo; //ASCII �ַ���ָ�� "CNpcSaleInfo" 
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
    	martin->Debug("initSupply --> �쳣");
        return;
    }

    if (nSupplyArry) {
        DWORD dwSupplyArryStart, dwSupplyArryEnd;
        martin->ReadPtrData(nSupplyArry + 0x14, "��ȡ [��Ʒ�鿪ʼ]", dwSupplyArryStart);
        martin->ReadPtrData(nSupplyArry + 0x18, "��ȡ [��Ʒ�����]", dwSupplyArryEnd);
        //martin->Debug("��Ʒ�鿪ʼ: 0x%X -- ��Ʒ�����: 0x%X", dwSupplyArryStart, dwSupplyArryEnd);

        // ������Ʒ����
        for (unsigned int nSupplyItemArry = dwSupplyArryStart; nSupplyItemArry < dwSupplyArryEnd; nSupplyItemArry += 0x4) {
            int nTempSupplyItemArry;
            if (martin->ReadPtrData(nSupplyItemArry, "��ȡ [��Ʒ��]", nTempSupplyItemArry)) {
                DWORD dwSupplyItemArryStart, dwSupplyItemArryEnd;
                Supply supply;
                int nTypeName = 0;
                martin->ReadPtrData(nTempSupplyItemArry + 0x18, "��ȡ [��Ʒ������]", nTypeName);
                if (IsBadReadPtr((CONST VOID*)nTypeName, sizeof(DWORD)) == 0) {
                    supply.strTypeName = (char*)nTypeName;
                }

                martin->ReadPtrData(nTempSupplyItemArry + 0x1C, "��ȡ [��Ʒ��Ϣ�鿪ʼ]", dwSupplyItemArryStart);
                martin->ReadPtrData(nTempSupplyItemArry + 0x20, "��ȡ [��Ʒ��Ϣ�����]", dwSupplyItemArryEnd);
                //martin->Debug("��Ʒ��Ϣ�鿪ʼ: 0x%X -- ��Ʒ��Ϣ�����: 0x%X", dwSupplyItemArryStart, dwSupplyItemArryEnd);

                // ������ƷС��, �Ա�������Ʒ��Ϣ ID
                for (unsigned int nSupplyItem = dwSupplyItemArryStart; nSupplyItem < dwSupplyItemArryEnd; nSupplyItem += SIZE_SALE_ITEM) {
                    int nItemID = 0; // �� ID Ϊ��Ʒ ID, Ϊ���� ������Ʒ��Ϣ �е� ID �Ա�, ȡ��Ʒ��
                    if (martin->ReadPtrData(nSupplyItem + 0x28, "��ȡ [��Ʒ��Ʒ ID]", nItemID)) {
                        auto it = CRole::s_allItems.find(nItemID);
                        if (it != CRole::s_allItems.end()) { // ˵��ƥ�䵽ID��
                            supply.strItemName = it->second.strName;
                            martin->ReadPtrData(nSupplyItem + 0x8, "��ȡ [��Ʒ ID]", supply.nSupplyID);
                            martin->ReadPtrData(nSupplyItem + 0xC, "��ȡ [��Ʒ���� ID]", supply.nTypeID);
                            //martin->Debug("%s -- ��ƷID: 0x%X -- ����ID: 0x%X -- ������: %s", supply.strItemName.c_str(), supply.nSupplyID, supply.nTypeID, supply.strTypeName.c_str());
                            m_supply_list.push_back(supply);
                        }
                    }
                }
            }
        }
    }
}
