#include "Material.h"
#include <windows.h>
#include "Martin.h"
#include "Base.h"
#include <algorithm>
#include "Role.h"
#include "GlobalVariable.h"
#include "DefMessage.h"
#include "DataType.h"
#include <process.h>
#include "Game.h"

std::list<material> CMaterial::m_material_list;

void CMaterial::initMaterial() {
    //USES_CONVERSION;
    CMaterial::m_material_list.swap(std::list<material>()); // 清空当前列表

    int arrTemp, arrStart, arrEnd;
    bool bSuccess = false;
    if (martin->ReadPtrData(BASE_CURRENT_MAP_OBJECTS2, TEXT("获取 [采集物品数组] -- 1"), arrTemp)) {
        if (martin->ReadPtrData(arrTemp + OFFSET_CURRENT_MAP_OBJECTS2, TEXT("获取 [采集物品数组] -- 2"), arrTemp)) {
            if (martin->ReadPtrData(arrTemp + 0x4, TEXT("获取 [采集物品数组] -- 3"), arrTemp)) {
                if (martin->ReadPtrData(arrTemp + 0x4 + 0x8, TEXT("获取 [采集物品数组头]"), arrStart)
                    && martin->ReadPtrData(arrTemp + 0x4 + 0xC, TEXT("获取 [采集物品数组尾]"), arrEnd)) {
                    bSuccess = true;
                }
            }
        }
    }

    if (bSuccess) {
        bSuccess = false;
        int nAddr;
        std::vector<DWORD> vct;

        for (int i = arrStart; i < arrEnd; i += 0x4) {
            if (martin->ReadPtrData(i, TEXT("遍历 [采集物品数组] -- 1"), nAddr)) {
                vct.push_back(nAddr);
            }
        }

        sort(vct.begin(), vct.end());  //排序
        vct.erase(unique(vct.begin(), vct.end()), vct.end()); //去重

        for (auto& v : vct) {
            //martin->Debug("====================== 0x%X ===================", v);

            if (IsBadReadPtr((CONST VOID*)nAddr, sizeof(DWORD)) == 0) {
                if (martin->ReadPtrData(v + 0x8, TEXT("遍历 [采集物品数组] --2"), nAddr)) {
                    material item;
                    if (martin->ReadPtrData(nAddr + 0x4, TEXT("遍历 [采集物品数组] --3"), item.nID)
                        && martin->ReadPtrData(nAddr + 0x8, TEXT("遍历[采集物品数组] --4"), item.nKey)
                        && martin->ReadPtrData(nAddr + 0x60, TEXT("遍历 [采集物品数组] --5"), item.fPointX)
                        && martin->ReadPtrData(nAddr + 0x64, TEXT("遍历采 [集物品数组] --6"), item.fPointY)
                        && martin->ReadPtrData(nAddr + 0x68, TEXT("遍历 [采集物品数组] --7"), item.fPointZ)) {
                        int nEbx = 0, nRet = 0, nKey = 0;
                        if (martin->ReadPtrData(BASE_GAME, TEXT("获取 [对象指针] -- 1"), nEbx)) {
                            if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("获取 [取对象指针] -- 2"), nEbx)) {
                                //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
                                nKey = item.nKey;
                                //int nTmep;
                                try {
                                    _asm {
                                        pushad;
                                        pushfd;

                                        mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                                        mov eax, [ebx];
                                        mov edx, nKey; //对象Key
                                        push edx;
                                        mov edx, [eax + 0x2C];
                                        mov ecx, ebx;
                                        call edx;
                                        mov nRet, eax;
                                        //mov ecx, 0x110;
                                        //mov eax, [eax + ecx];
                                        //mov nTmep, eax;

                                        popfd;
                                        popad;
                                    }
                                } catch (...) {
                                    martin->Debug(TEXT("获取 [对象指针] --> 异常"));
                                    continue;
                                }

                                if (nRet) {
                                    try {
                                        _asm {
                                            pushad;
                                            pushfd;

                                            mov ecx, nRet;
                                            mov eax, [ecx];
                                            mov edx, [eax + 0x34];
                                            call edx;
                                            mov nRet, eax;

                                            popfd;
                                            popad;
                                        }
                                    } catch (...) {
                                        martin->Debug(TEXT("获取 [对象英文名] --> 异常"));
                                        continue;
                                    }

                                    item.strName = (char*)nRet;
                                    //
                                    //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- 类别: 0x%X -- %f : %f : %f", \
                                                                                                        //   item.strName.c_str(), item.nID, item.nKey, item.nType, item.fPointX, item.fPointY, item.fPointZ);

                                    std::string::size_type idx = item.strName.find("CGameCollectPoint");
                                    if (idx != std::string::npos) { // 找到名称
                                        int nType = 0;
                                        try {
                                            _asm {
                                                pushad;
                                                pushfd;

                                                mov ecx, nAddr; //对象详情指针
                                                mov eax, [ecx];
                                                add eax, OFFSET_GET_COLLECT_ITEM_TYPE;
                                                mov edx, [eax];
                                                call edx;
                                                mov nType, eax;

                                                popfd;
                                                popad;
                                            }
                                        } catch (...) {
                                            martin->Debug("获取 [对象类别] --> 异常");
                                        }
                                        item.strType = "Unknown";
                                        // 类别 1:矿（挖矿工具）,2:药草,3:昆虫（捕虫工具）,5:蘑菇,6:蜂蜜,7:地面小石头,8:粪便,0xA:怪物尸体,0xC:骨头,0x11:网
                                        switch (nType) {
                                        case 1:
                                            item.strType = "矿";
                                            break;
                                        case 2:
                                            item.strType = "药草";
                                            break;
                                        case 3:
                                            item.strType = "昆虫";
                                            break;
                                        case 5:
                                            item.strType = "蘑菇";
                                            break;
                                        case 6:
                                            item.strType = "蜂蜜";
                                            break;
                                        case 7:
                                            item.strType = "小石头";
                                            break;
                                        case 8:
                                            item.strType = "粪便";
                                            break;
                                        case 0xA:
                                            item.strType = "尸体";
                                            break;
                                        case 0xC:
                                            item.strType = "骨头";
                                            break;
                                        case 0x11:
                                            item.strType = "网";
                                            break;
                                        case 0x12:
                                            item.strType = "可疑的香草";
                                            break;
                                        }

                                        CMaterial::m_material_list.push_back(item);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CMaterial::initMaterial_2() {
    CMaterial::m_material_list.swap(std::list<material>()); // 清空当前列表

    int arrTemp, arrStart, arrEnd;
    bool bSuccess = false;
    if (martin->ReadPtrData(BASE_CURRENT_MAP_OBJECTS, TEXT("获取 [采集物品数组]"), arrTemp)) {
        if (martin->ReadPtrData(arrTemp + OFFSET_CURRENT_MAP_ENTITY_COUNT + 0x4, TEXT("获取 [采集物品数组头]"), arrStart)
            && martin->ReadPtrData(arrTemp + OFFSET_CURRENT_MAP_ENTITY_COUNT + 0x8, TEXT("获取 [采集物品数组尾]"), arrEnd)) {
            bSuccess = true;
        }
    }

    if (bSuccess) {
        int nKey;
        std::vector<DWORD> vctKey;

        for (int i = arrStart; i < arrEnd; i += 0x4) {
            if (martin->ReadPtrData(i, TEXT("遍历 [采集物品数组] -- 1"), nKey)) {
                vctKey.push_back(nKey);
            }
        }

        sort(vctKey.begin(), vctKey.end());  //排序
        vctKey.erase(unique(vctKey.begin(), vctKey.end()), vctKey.end()); //去重

        for (auto& v : vctKey) {
            material item;
            item.nKey = v;

            int nEbx = 0, nRet = 0, nKey = 0;
            if (martin->ReadPtrData(BASE_GAME, TEXT("获取 [对象指针] -- 1"), nEbx)) {
                if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("获取 [取对象指针] -- 2"), nEbx)) {
                    nKey = v;
                    try {
                        _asm {
                            pushad;
                            pushfd;

                            mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                            mov eax, [ebx];
                            mov edx, nKey; //对象Key
                            push edx;
                            mov edx, [eax + 0x2C];
                            mov ecx, ebx;
                            call edx;
                            mov nRet, eax;

                            popfd;
                            popad;
                        }
                    } catch (...) {
                        martin->Debug(TEXT("获取 [对象指针] --> 异常"));
                        continue;
                    }

                    if (nRet) {
                        int nName;
                        try {
                            _asm {
                                pushad;
                                pushfd;

                                mov ecx, nRet;
                                mov eax, [ecx];
                                mov edx, [eax + 0x34];
                                call edx;
                                mov nName, eax;

                                popfd;
                                popad;
                            }
                        } catch (...) {
                            martin->Debug(TEXT("获取 [对象英文名] --> 异常"));
                            continue;
                        }

                        item.strName = (char*)nName;

                        std::string::size_type idx = item.strName.find("CGameCollectPoint");
                        if (idx != std::string::npos) { // 找到名称
                            try {
                                _asm {
                                    pushad;
                                    pushfd;

                                    mov ecx, nRet;  //对象指针(来自于 【根据Key取对象指针】的返回值)
                                    mov eax, [ecx];
                                    add eax, OFFSET_GET_OBJECT_DETAIL;
                                    mov edx, [eax];
                                    call edx;
                                    mov nRet, eax;

                                    popfd;
                                    popad;
                                }
                            } catch (...) {
                                martin->Debug("获取 [对象详情] --> 异常");
                                continue;
                            }

                            int nType = 0;
                            try {
                                _asm {
                                    pushad;
                                    pushfd;

                                    mov ecx, nRet; //对象详情指针
                                    mov eax, [ecx];
                                    add eax, OFFSET_GET_COLLECT_ITEM_TYPE;
                                    mov edx, [eax];
                                    call edx;
                                    mov nType, eax;

                                    popfd;
                                    popad;
                                }
                            } catch (...) {
                                martin->Debug("获取 [对象类别] --> 异常");
                            }
                            item.strType = "Unknown";
                            // 类别 1:矿（挖矿工具）,2:药草,3:昆虫（捕虫工具）,5:蘑菇,6:蜂蜜,7:地面小石头,8:粪便,0xA:怪物尸体,0xC:骨头,0x11:网
                            switch (nType) {
                            case 1:
                                item.strType = "矿";
                                break;
                            case 2:
                                item.strType = "药草";
                                break;
                            case 3:
                                item.strType = "昆虫";
                                break;
                            case 5:
                                item.strType = "蘑菇";
                                break;
                            case 6:
                                item.strType = "蜂蜜";
                                break;
                            case 7:
                                item.strType = "小石头";
                                break;
                            case 8:
                                item.strType = "粪便";
                                break;
                            case 0xA:
                                item.strType = "尸体";
                                break;
                            case 0xC:
                                item.strType = "骨头";
                                break;
                            case 0x11:
                                item.strType = "网";
                                break;
                            case 0x12:
                                item.strType = "可疑的香草";
                                break;
                            }

                            if (martin->ReadPtrData(nRet + 0x4, TEXT("遍历 [采集物品数组] --3"), item.nID)
                                && martin->ReadPtrData(nRet + 0x60, TEXT("遍历 [采集物品数组] --5"), item.fPointX)
                                && martin->ReadPtrData(nRet + 0x64, TEXT("遍历采 [集物品数组] --6"), item.fPointY)
                                && martin->ReadPtrData(nRet + 0x68, TEXT("遍历 [采集物品数组] --7"), item.fPointZ)) {
                                // martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- 类别: %s -- %f : %f : %f", \
                                     //item.strName.c_str(), item.nID, item.nKey, item.strType.c_str(), item.fPointX, item.fPointY, item.fPointZ);
                                    CMaterial::m_material_list.push_back(item);
                            }
                        }
                    }
                }
            }
        }
    }
}
