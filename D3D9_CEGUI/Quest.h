#pragma once
#include <string>
#include <list>
#include <windows.h>

#pragma pack (push,1)

typedef struct GAME_QUEST {
    std::string strChapter;     // 任务所属大章
    std::string strSection;     // 任务所属小节
    std::string strQuestName;   // 任务名
    std::string strQuestStatus; // 进行中 || 失败 || 完成
    std::string strQuestType;   // 主线 || 悬赏
    int nQuestID;
    bool operator()(GAME_QUEST& p) {
        return (strQuestName == p.strQuestName);
    }
} GameQuest, *pGameQuest;

typedef struct QUEST_TREE {
    DWORD dwHash;   // +0x0	    无用数据
    DWORD dwSBase;  // +0x4	    上一层树的地址
    DWORD dwLBase;	// +0x8	    左树
    DWORD dwRBase;	// +0xC	    右树
    DWORD dwID;		// +0x10	无用数据
    DWORD dwPBase;	// +0x14    任务信息指针
} QuestTree, *pQuestTree;

#pragma pack(pop)

class CQuest {
public:
    CQuest();
    ~CQuest();

    void initUnCompleteQuest(); // 未完成任务初始化
    void initCompleteQuest();   // 已完成任务
    void initQuestTable();      // 初始化所有主线任务列表
    

    std::list<GameQuest> m_unComplete_quest;  // 未完成任务
    std::list<GameQuest> m_complete_quest;    // 已完成任务
    std::list<GameQuest> m_questTable_quest;  // 所有主线任务列表

    void CompleteQuest(int nQuestID); // 交任务
    void AcceptQuest(int nQuestID); // 接任务
    std::string GetQuestTable(); // 获取当前可接主线
    void InteractiveQuest(int nQuestID); // 任务对话
    void 锻造晓风短剑();

protected:
    void allotQuest(int nQuestInfo, std::list<GameQuest>& QuestList); // 根据传进的任务信息指针分配任务 List
    void TraverTree(int iObject);
    std::string TransformName(std::string strName); // 转换名字
    void StringReplace(std::string &strBase, std::string strSrc, std::string strDes);
};