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
    CMaterial::m_material_list.swap(std::list<material>()); // ��յ�ǰ�б�

    int arrTemp, arrStart, arrEnd;
    bool bSuccess = false;
    if (martin->ReadPtrData(BASE_CURRENT_MAP_OBJECTS2, TEXT("��ȡ [�ɼ���Ʒ����] -- 1"), arrTemp)) {
        if (martin->ReadPtrData(arrTemp + OFFSET_CURRENT_MAP_OBJECTS2, TEXT("��ȡ [�ɼ���Ʒ����] -- 2"), arrTemp)) {
            if (martin->ReadPtrData(arrTemp + 0x4, TEXT("��ȡ [�ɼ���Ʒ����] -- 3"), arrTemp)) {
                if (martin->ReadPtrData(arrTemp + 0x4 + 0x8, TEXT("��ȡ [�ɼ���Ʒ����ͷ]"), arrStart)
                    && martin->ReadPtrData(arrTemp + 0x4 + 0xC, TEXT("��ȡ [�ɼ���Ʒ����β]"), arrEnd)) {
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
            if (martin->ReadPtrData(i, TEXT("���� [�ɼ���Ʒ����] -- 1"), nAddr)) {
                vct.push_back(nAddr);
            }
        }

        sort(vct.begin(), vct.end());  //����
        vct.erase(unique(vct.begin(), vct.end()), vct.end()); //ȥ��

        for (auto& v : vct) {
            //martin->Debug("====================== 0x%X ===================", v);

            if (martin->ReadPtrData(v + 0x8, TEXT("���� [�ɼ���Ʒ����] --2"), nAddr)) {
                material item;
                if (martin->ReadPtrData(nAddr + 0x4, TEXT("���� [�ɼ���Ʒ����] --3"), item.nID)
                    && martin->ReadPtrData(nAddr + 0x8, TEXT("����[�ɼ���Ʒ����] --4"), item.nKey)
                    && martin->ReadPtrData(nAddr + 0x60, TEXT("���� [�ɼ���Ʒ����] --5"), item.fPointX)
                    && martin->ReadPtrData(nAddr + 0x64, TEXT("������ [����Ʒ����] --6"), item.fPointY)
                    && martin->ReadPtrData(nAddr + 0x68, TEXT("���� [�ɼ���Ʒ����] --7"), item.fPointZ)) {
                    int nEbx = 0, nRet = 0, nKey = 0;
                    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [����ָ��] -- 1"), nEbx)) {
                        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [ȡ����ָ��] -- 2"), nEbx)) {
                            //::MessageBox(NULL, TEXT("111"), TEXT("111"), 0);
                            nKey = item.nKey;
                            //int nTmep;
                            try {
                                _asm {
                                    pushad;
                                    pushfd;

                                    mov ebx, nEbx; //[[BASE_GAME]+OFFSET_NEARBY_OBJECT]
                                    mov eax, [ebx];
                                    mov edx, nKey; //����Key
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
                                martin->Debug(TEXT("��ȡ [����ָ��] --> �쳣"));
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
                                    martin->Debug(TEXT("��ȡ [����Ӣ����] --> �쳣"));
                                    continue;
                                }

                                item.strName = (char*)nRet;
                                //
                                //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- ���: 0x%X -- %f : %f : %f", \
                                //   item.strName.c_str(), item.nID, item.nKey, item.nType, item.fPointX, item.fPointY, item.fPointZ);

                                std::string::size_type idx = item.strName.find("CGameCollectPoint");
                                if (idx != std::string::npos) { // �ҵ�����
                                    int nType = 0;
                                    try {
                                        _asm {
                                            pushad;
                                            pushfd;

                                            mov ecx, nAddr; //��������ָ��
                                            mov eax, [ecx];
                                            add eax, OFFSET_GET_COLLECT_ITEM_TYPE;
                                            mov edx, [eax];
                                            call edx;
                                            mov nType, eax;

                                            popfd;
                                            popad;
                                        }
                                    } catch (...) {
                                        martin->Debug("��ȡ [�������] --> �쳣");
                                    }
                                    item.nType = nType;

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