#include "Quest.h"
#include "Martin.h"
#include "Base.h"
#include "DataType.h"
#include "Role.h"
#include <algorithm>
#include "NearObject.h"


CQuest::CQuest() {
}


CQuest::~CQuest() {
}

void CQuest::initUnCompleteQuest() {
    m_unComplete_quest.clear();

    DWORD dwTemp, dwRoot, dwEnd;
    if (martin->ReadPtrData(BASE_TASK, TEXT("读取 [任务信息] -- 1"), dwTemp)) {
        if (martin->ReadPtrData(dwTemp + 0x18, TEXT("读取 [任务信息] -- 2"), dwRoot)) {
            dwEnd = dwTemp + 0x10;
            int nNodeCount = 0;
            int nTempEsi_Next = dwRoot;

            while (nTempEsi_Next != dwEnd) {
                int nTempNode = 0, nQuestInfo = 0;
                martin->ReadPtrData(nTempEsi_Next + 0xc, TEXT("读取 [节点C] -- 1"), nTempNode);

                if (martin->ReadPtrData(nTempEsi_Next + 0x14, TEXT("读取 [节点信息]"), nQuestInfo)) {
                    allotQuest(nQuestInfo, m_unComplete_quest);
                }

                if (++nNodeCount > 0x400) { // 计数器，防止遍历太多
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

void CQuest::allotQuest(int nQuestInfo, std::list<GameQuest>& QuestList) {
    int nTemp;
    if (martin->ReadPtrData(nQuestInfo + 0x8, TEXT("读取 [任务详情]"), nTemp)) {
        // 先判断类别
        int nType;
        if (martin->ReadPtrData(nTemp + 0x10, TEXT("读取 [任务类别]"), nType)) {
            if (nType == 1 || nType == 0x400) {
                GameQuest quest;

                if (nType == 1) {
                    quest.strQuestType = "主线";
                } else if (nType == 0x400) {
                    quest.strQuestType = "悬赏";
                }

                int nName;
                if (martin->ReadPtrData(nTemp + 0x8, TEXT("读取 [任务名]"), nName)) {
                    quest.strQuestName = TransformName((char*)nName);
                }

                int nID;
                if (martin->ReadPtrData(nTemp + 0x4, TEXT("读取 [任务ID]"), nID)) {
                    quest.nQuestID = nID;
                }

                int nStatus;
                quest.strQuestStatus = "完成";
                if (martin->ReadPtrData(nQuestInfo + 0x14, TEXT("读取 [任务状态]"), nStatus)) {
                    if (nStatus == 1) {
                        quest.strQuestStatus = "进行中";
                    } else if (nStatus == 2) {
                        quest.strQuestStatus = "失败";
                    } else if (nStatus == 4) {
                        quest.strQuestStatus = "完成";
                    }
                }
                QuestList.push_back(quest);
            }
        }
    }
}

void CQuest::initCompleteQuest() {
    m_complete_quest.clear();
    DWORD dwObject;
    if (martin->ReadPtrData(BASE_TASK, "获取 [已经完成任务二叉树] -- 1", dwObject)) {
        if (martin->ReadPtrData(dwObject + 0x28 + 0x4, "获取 [已经完成任务二叉树] -- 2", dwObject)) {
            if (IsBadReadPtr((CONST VOID*)dwObject, sizeof(DWORD)) == 0) {
                TraverTree(dwObject);
            }
        }
    }
}

void CQuest::TraverTree(int iObject) {
    pQuestTree pTree;
    pTree = (pQuestTree)iObject;
    allotQuest(pTree->dwPBase, m_complete_quest);

    if (pTree->dwLBase) {
        TraverTree(pTree->dwLBase);
    }

    if (pTree->dwRBase) {
        TraverTree(pTree->dwRBase);
    }
}

void CQuest::initQuestTable() {
    m_questTable_quest.clear();
    char* CTaskChapterInfo = "CTaskChapterInfo";
    int npChapter = 0xFFFFFFFF;

    try {
    	_asm {
    		pushad;
    		pushfd;
    		
            mov ecx, 0;
            push ecx;
            mov edx, CTaskChapterInfo; //ASCII 字符串指针 "CTaskChapterInfo" 
            push edx;
            mov ecx, 0;
            push ecx;
            mov eax, CALL_GET_GLOBAL_VARIABLE; //CALL_GET_GLOBAL_VARIABLE
            call eax;
            add esp, 0xc;
            mov npChapter, eax;

    		popfd;
    		popad;
    	}
    } catch (...) {
    	martin->Debug(TEXT("initQuestTable --> 异常"));
        return;
    }

    if (npChapter != 0xFFFFFFFF) {
        DWORD dwStart, dwEnd;
        martin->ReadPtrData(npChapter + 0x14, TEXT("获取 [大章信息] 数组头"), dwStart);
        martin->ReadPtrData(npChapter + 0x18, TEXT("获取 [大章信息] 数组尾"), dwEnd);
        for (unsigned i = dwStart; i < dwEnd; i += 0x4) {
            DWORD dwTemp_1;
            if (martin->ReadPtrData(i, TEXT("获取 [大章详情指针] -- 1"), dwTemp_1)) {
                if (IsBadReadPtr((CONST VOID*)dwTemp_1, sizeof(DWORD)) == 0) {
                    DWORD ChapterInfo;
                    if (martin->ReadPtrData(dwTemp_1 + 0x18, TEXT("获取 [大章详情指针] -- 2"), ChapterInfo)) {
                        GameQuest quest;
                        int nChapterName;
                        if (martin->ReadPtrData(ChapterInfo + 0x8, TEXT("获取 [大章名]"), nChapterName)) {
                            //martin->Debug((char*)nChapterName);
                            quest.strChapter = (char*)nChapterName;
                        }
                        
                        DWORD dwSectionStart, dwSectionEnd;
                        martin->ReadPtrData(dwTemp_1 + 0x1C, TEXT("获取 [小节] 数组头"), dwSectionStart);
                        martin->ReadPtrData(dwTemp_1 + 0x20, TEXT("获取 [小节] 数组尾"), dwSectionEnd);
                        for (unsigned j = dwSectionStart; j < dwSectionEnd; j += 0x4) {
                            DWORD dwTemp_2;
                            if (martin->ReadPtrData(j, TEXT("获取 [小节详情指针] -- 1"), dwTemp_2)) {
                                if (IsBadReadPtr((CONST VOID*)dwTemp_2, sizeof(DWORD)) == 0) {
                                    DWORD SectionInfo;
                                    if (martin->ReadPtrData(dwTemp_2 + 0x18, TEXT("获取 [小节详情指针] -- 2"), SectionInfo)) {
                                        int nSectionName;
                                        if (martin->ReadPtrData(SectionInfo + 0x8, TEXT("获取 [小节名]"), nSectionName)) {
                                            //martin->Debug((char*)nSectionName);
                                            quest.strSection = (char*)nSectionName;
                                        }

                                        DWORD dwQuestStart, dwQuestEnd;
                                        martin->ReadPtrData(dwTemp_2 + 0x1C, TEXT("获取 [任务] 数组头"), dwQuestStart);
                                        martin->ReadPtrData(dwTemp_2 + 0x20, TEXT("获取 [任务] 数组尾"), dwQuestEnd);
                                        for (unsigned k = dwQuestStart; k < dwQuestEnd; k += 0x4) {
                                            DWORD dwTemp_3;
                                            if (martin->ReadPtrData(k, TEXT("获取 [任务详情指针] -- 1"), dwTemp_3)) {
                                                if (IsBadReadPtr((CONST VOID*)dwTemp_3, sizeof(DWORD)) == 0) {
                                                    DWORD QuestInfo;
                                                    if (martin->ReadPtrData(dwTemp_3 + 0x18, TEXT("获取 [任务详情指针] -- 2"), QuestInfo)) {
                                                        int nQuestName;
                                                        if (martin->ReadPtrData(QuestInfo + 0x8, TEXT("获取 [任务名]"), nQuestName)) {
                                                            //martin->Debug((char*)nQuestName);
                                                            quest.strQuestName = TransformName((char*)nQuestName);
                                                        }

                                                        int nID;
                                                        if (martin->ReadPtrData(QuestInfo + 0x4, TEXT("获取 [任务ID]"), nID)) {
                                                            quest.nQuestID = nID;
                                                        }
                                                        m_questTable_quest.push_back(quest);
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
            }
        }
    }
}

std::string CQuest::TransformName(std::string strName) {
    StringReplace(strName, "“", "");
    StringReplace(strName, "”", "");
    StringReplace(strName, "!", "");
    StringReplace(strName, "！", "");
    StringReplace(strName, "？", "");
    StringReplace(strName, "?", "");
    StringReplace(strName, "-", "");
    std::string::size_type idx = strName.find_first_of("]");
    if (idx == std::string::npos) {
        return strName;
    } else {
        return strName.substr(idx + 1);
    }
}

void CQuest::CompleteQuest(int nQuestID) {
    pQuestPackage pPackage = new QuestPackage;
    RtlZeroMemory(pPackage, sizeof(QuestPackage));
    pPackage->A_Head = 0x00000E04;
    pPackage->E_FID = nQuestID;
    CRole::SendPackage((DWORD)pPackage);
    delete pPackage;
}

std::string CQuest::GetQuestTable() {
    initQuestTable(); // 先初始化一次所有主线
    initCompleteQuest(); // 再初始化一次已完成主线
    for (auto& v : m_questTable_quest) {
        std::list<GameQuest>::iterator it = std::find_if(m_complete_quest.begin(), m_complete_quest.end(), v);
        if (it == m_complete_quest.end()) {
            return v.strQuestName;
        } else {
            martin->Debug(it->strQuestName.c_str());
        }
    }
    return "";
}

void CQuest::AcceptQuest(int nQuestID) {
    pQuestPackage pPackage = new QuestPackage;
    RtlZeroMemory(pPackage, sizeof(QuestPackage));
    pPackage->A_Head = 0x00000E01;
    pPackage->E_FID = nQuestID;
    CRole::SendPackage((DWORD)pPackage);
    delete pPackage;
}

void CQuest::InteractiveQuest(int nQuestID) {
    pQuestInteractivePackage pPackage = new QuestInteractivePackage;
    RtlZeroMemory(pPackage, sizeof(QuestInteractivePackage));
    pPackage->A_Head = 0x00002402;
    pPackage->E_Fixation = 0x00000002;
    pPackage->F_FID = nQuestID;
    CRole::SendPackage((DWORD)pPackage);
    delete pPackage;
}

void CQuest::StringReplace(std::string &strBase, std::string strSrc, std::string strDes) {
    std::string::size_type pos = 0;
    std::string::size_type srcLen = strSrc.size();
    std::string::size_type desLen = strDes.size();
    pos = strBase.find(strSrc, pos);
    while ((pos != std::string::npos)) {
        strBase.replace(pos, srcLen, strDes);
        pos = strBase.find(strSrc, (pos + desLen));
    }
}

void CQuest::锻造晓风短剑() {
    pPackage锻造晓风短剑 pPackage = new Package锻造晓风短剑;
    RtlZeroMemory(pPackage, sizeof(Package锻造晓风短剑));
    pPackage->A_Head = 0x00000903;
    pPackage->E_Fixation = 0x00000544;
    CRole::SendPackage((DWORD)pPackage);
    delete pPackage;
}
