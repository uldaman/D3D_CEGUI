#include "NearObject.h"
#include "Martin.h"
#include "Base.h"
#include "DataType.h"
#include "Role.h"


CNearObject::CNearObject() {
}


CNearObject::~CNearObject() {
}

void CNearObject::initNear() {
    m_near_object.clear();
    int nTemp = 0, nRoot = 0, nEnd = 0;
    BYTE bEmpty = 0;

    if (martin->ReadPtrData(BASE_GAME, TEXT("读取 [周围对象] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("读取 [周围对象] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("读取 [周围对象] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("读取 [周围对象] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    if (!bEmpty) {
                        int nTempEsi_Next = nRoot;
                        while (nTempEsi_Next != nEnd) {
                            int nTempNode = 0, nCurrentKey = 0;
                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 1"), nTempNode);
                            martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("读取 [节点Key]"), nCurrentKey);
                            
                            allotObject(nCurrentKey);

                            if (++nNodeCount > 0x400) {//计数器，防止遍历太多
                                break;
                            }

                            if (nTempNode != 0) {
                                nTempEsi_Next = nTempNode;
                                int nTemp = 0;
                                while (true) {
                                    martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("读取 [节点8]"), nTemp);
                                    if (nTemp != 0) {
                                        nTempEsi_Next = nTemp;
                                    } else {
                                        break;
                                    }
                                }
                            } else {
                                martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("读取 [节点4] -- 1"), nTempNode);
                                int nTemp = 0;
                                martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 2"), nTemp);

                                if (nTempEsi_Next == nTemp) {
                                    do {
                                        nTempEsi_Next = nTempNode;
                                        martin->ReadPtrData(nTempNode + 0x4, TEXT("读取 [节点4] -- 2"), nTempNode);
                                        martin->ReadPtrData(nTempNode + 0xc, TEXT("读取 [节点C] -- 3"), nTemp);
                                    } while (nTempEsi_Next == nTemp);
                                }

                                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 4"), nTemp);
                                if (nTemp != nTempNode) {
                                    nTempEsi_Next = nTempNode;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CNearObject::allotObject(int nKey) {
    int nEbx = 0, nRet = 0;
    if (martin->ReadPtrData(BASE_GAME, TEXT("解密对象 Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("解密对象 Key -- 2"), nEbx)) {
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
                martin->Debug("allotObject -- 1 --> 异常");
                return;
            }
        }
    }

    if (nRet) {
        int nRet_2 = 0;
        try {
            _asm {
                pushad;
                pushfd;

                mov ecx, nRet;  //对象指针(来自于 【根据Key取对象指针】的返回值)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug(TEXT("allotObject -- 2 --> 异常"));
            return;
        }

        if (nRet_2) {
            int nID;
            if (martin->ReadPtrData(nRet_2 + 0x4, TEXT("获取 [对象ID]"), nID)) {
                std::string strName = GetObjectName(nRet_2);
                NearObject nearObj;
                nearObj.nNpcID = nID;
                nearObj.strNpcName = strName;
                martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("获取 [BOSS 坐标]"), nearObj.fNpcPointX);
                martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("获取 [BOSS 坐标]"), nearObj.fNpcPointY);
                m_near_object.push_back(nearObj);
            }
        }
    }
}

std::string CNearObject::GetObjectName(int nAddr) {
    int nName;
    try {
        _asm {
            pushad;
            pushfd;

            mov ecx, nAddr;  //48664A30:当前人物
            mov edx, [ecx];
            mov eax, OFFSET_GET_ROLE_NAME;
            mov eax, [edx + eax];     //0xB0:OFFSET_GET_ROLE_NAME
            call eax;
            mov nName, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("GetObjectName --> 异常"));
    }
    martin->ReadPtrData(nName, "获取 [对象名]", nName);
    //martin->Debug((char*)nName);
    return (char*)nName;
}

// 对话 NPC
void CNearObject::Interactive(int nID) {
    pInteractivePackage pPackage = new InteractivePackage;
    RtlZeroMemory(pPackage, sizeof(InteractivePackage));
    pPackage->A_Head = 0x00001401;
    pPackage->E_Fixation = 0x00000102;
    *(int*)((byte*)(&(pPackage->F_NPC_ID)) + 1) = nID;
    *((byte*)(&(pPackage->G_NPC_ID)) + 1) = 0x2;
    CRole::SendPackage((DWORD)pPackage);
    delete pPackage;
}