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

    if (martin->ReadPtrData(BASE_GAME, TEXT("��ȡ [��Χ����] -- 1"), nTemp)) {
        if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT, TEXT("��ȡ [��Χ����] -- 2"), nTemp)) {
            if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x8, TEXT("��ȡ [��Χ����] -- 3"), nRoot)) {
                if (martin->ReadPtrData(nTemp + OFFSET_NEARBY_OBJECT_ROOT + 0x18, TEXT("��ȡ [��Χ����] -- 4"), bEmpty)) {
                    nEnd = nTemp + OFFSET_NEARBY_OBJECT_ROOT;
                    int nNodeCount = 0;
                    if (!bEmpty) {
                        int nTempEsi_Next = nRoot;
                        while (nTempEsi_Next != nEnd) {
                            int nTempNode = 0, nCurrentKey = 0;
                            martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 1"), nTempNode);
                            martin->ReadPtrData(nTempEsi_Next + 0x10, TEXT("��ȡ [�ڵ�Key]"), nCurrentKey);
                            
                            allotObject(nCurrentKey);

                            if (++nNodeCount > 0x400) {//����������ֹ����̫��
                                break;
                            }

                            if (nTempNode != 0) {
                                nTempEsi_Next = nTempNode;
                                int nTemp = 0;
                                while (true) {
                                    martin->ReadPtrData(nTempEsi_Next + 0x8, TEXT("��ȡ [�ڵ�8]"), nTemp);
                                    if (nTemp != 0) {
                                        nTempEsi_Next = nTemp;
                                    } else {
                                        break;
                                    }
                                }
                            } else {
                                martin->ReadPtrData(nTempEsi_Next + 0x4, TEXT("��ȡ [�ڵ�4] -- 1"), nTempNode);
                                int nTemp = 0;
                                martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 2"), nTemp);

                                if (nTempEsi_Next == nTemp) {
                                    do {
                                        nTempEsi_Next = nTempNode;
                                        martin->ReadPtrData(nTempNode + 0x4, TEXT("��ȡ [�ڵ�4] -- 2"), nTempNode);
                                        martin->ReadPtrData(nTempNode + 0xc, TEXT("��ȡ [�ڵ�C] -- 3"), nTemp);
                                    } while (nTempEsi_Next == nTemp);
                                }

                                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("��ȡ [�ڵ�C] -- 4"), nTemp);
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
    if (martin->ReadPtrData(BASE_GAME, TEXT("���ܶ��� Key -- 1"), nEbx)) {
        if (martin->ReadPtrData(nEbx + OFFSET_NEARBY_OBJECT, TEXT("���ܶ��� Key -- 2"), nEbx)) {
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

                    popfd;
                    popad;
                }
            } catch (...) {
                martin->Debug("allotObject -- 1 --> �쳣");
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

                mov ecx, nRet;  //����ָ��(������ ������Keyȡ����ָ�롿�ķ���ֵ)
                mov eax, [ecx];
                add eax, OFFSET_GET_OBJECT_DETAIL;
                mov edx, [eax];
                call edx;
                mov nRet_2, eax;

                popfd;
                popad;
            }
        } catch (...) {
            martin->Debug(TEXT("allotObject -- 2 --> �쳣"));
            return;
        }

        if (nRet_2) {
            int nID;
            if (martin->ReadPtrData(nRet_2 + 0x4, TEXT("��ȡ [����ID]"), nID)) {
                std::string strName = GetObjectName(nRet_2);
                NearObject nearObj;
                nearObj.nNpcID = nID;
                nearObj.strNpcName = strName;
                martin->ReadPtrData(nRet_2 + OFFSET_COOR, TEXT("��ȡ [BOSS ����]"), nearObj.fNpcPointX);
                martin->ReadPtrData(nRet_2 + OFFSET_COOR + 0x4, TEXT("��ȡ [BOSS ����]"), nearObj.fNpcPointY);
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

            mov ecx, nAddr;  //48664A30:��ǰ����
            mov edx, [ecx];
            mov eax, OFFSET_GET_ROLE_NAME;
            mov eax, [edx + eax];     //0xB0:OFFSET_GET_ROLE_NAME
            call eax;
            mov nName, eax;

            popfd;
            popad;
        }
    } catch (...) {
        martin->Debug(TEXT("GetObjectName --> �쳣"));
    }
    martin->ReadPtrData(nName, "��ȡ [������]", nName);
    //martin->Debug((char*)nName);
    return (char*)nName;
}

// �Ի� NPC
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