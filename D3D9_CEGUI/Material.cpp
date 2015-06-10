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
bool CMaterial::m_bStart = false;

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
                                item.nType = nType;
                                item.strName = (char*)nRet;
                                
                                martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- 类别: %d -- %f : %f : %f", \
                                   item.strName.c_str(), item.nID, item.nKey, item.nType, item.fPointX, item.fPointY, item.fPointZ);
                                
                                std::string::size_type idx = item.strName.find("CGameCollectPoint");
                                if (idx != std::string::npos) { // 找到名称
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

void CMaterial::Collect() {
    ::CloseHandle((HANDLE)_beginthreadex(NULL, 0, Thread_Collect, NULL, 0, NULL));
}

unsigned int __stdcall CMaterial::Thread_Collect(PVOID pM) {
    //// 记录下当前坐标, 用于采集完返回
    //POINT_TARGET Current_Point;
    //::SendMessage(theApp.m_hGWnd, WM_GETROLEPOINT, (WPARAM)&Current_Point, NULL);

    //for (auto& v : CMaterial::m_material_list) {
    //    // 先判断下是不是在FB里
    //    int nWhere;
    //    ::SendMessage(theApp.m_hGWnd, WM_WHERE, (WPARAM)&nWhere, /*(LPARAM)&nKey*/NULL);
    //    if (nWhere != 2 || CMaterial::m_bStart == false) {
    //        goto MaterialEnd; // 如果不在FB 则跳出
    //    }
    //    
    //    //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- %f : %f : %f",
    //    //    v.strName.c_str(), v.nID, v.nKey, v.fPointX, v.fPointY, v.fPointZ);

    //    POINT_TARGET _Point = { v.fPointX, v.fPointY, v.fPointZ };
    //    int nID = v.nID;
    //    int nKey = v.nKey;

    //    // 瞬移
    //    ::SendMessage(theApp.m_hGWnd, WM_FINDWAY, (WPARAM)&_Point, /*(LPARAM)&nKey*/NULL);
    //    Sleep(1000);

    //    // 采集
    //    for (int i = 0; i < 3; i++) {
    //        ::SendMessage(theApp.m_hGWnd, WM_WHERE, (WPARAM)&nWhere, /*(LPARAM)&nKey*/NULL);
    //        if (nWhere != 2 || CMaterial::m_bStart == false) {
    //            goto MaterialEnd; // 如果不在FB 则跳出
    //        }

    //        ::SendMessage(theApp.m_hGWnd, WM_COLLECT, (WPARAM)&nID, NULL);
    //        Sleep(500);

    //        // 判断是否在采集中, 是的话, 接着采集, 否则开始下一个
    //        BOOL bCollect = FALSE;
    //        ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
    //        //martin->Debug(TEXT("采集标识: %d"), bCollect);

    //        while (bCollect) { // 说明在采集中
    //            Sleep(1000);
    //            ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
    //        }

    //        Sleep(500);
    //    }

    //    Sleep(500);
    //}

    //MaterialEnd:
    //// 返回开始处
    //::SendMessage(theApp.m_hGWnd, WM_FINDWAY, (WPARAM)&Current_Point, NULL);
    //CMaterial::m_bStart = false;
    return 0;
}