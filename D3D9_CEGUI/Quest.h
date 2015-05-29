#pragma once
#include <string>
#include <list>
#include <windows.h>

#pragma pack (push,1)

typedef struct GAME_QUEST {
    std::string strChapter;     // ������������
    std::string strSection;     // ��������С��
    std::string strQuestName;   // ������
    std::string strQuestStatus; // ������ || ʧ�� || ���
    std::string strQuestType;   // ���� || ����
    int nQuestID;
} GameQuest, *pGameQuest;

typedef struct QUEST_TREE {
    DWORD dwHash;   // +0x0	    ��������
    DWORD dwSBase;  // +0x4	    ��һ�����ĵ�ַ
    DWORD dwLBase;	// +0x8	    ����
    DWORD dwRBase;	// +0xC	    ����
    DWORD dwID;		// +0x10	��������
    DWORD dwPBase;	// +0x14    ������Ϣָ��
} QuestTree, *pQuestTree;

#pragma pack(pop)

class CQuest {
public:
    CQuest();
    ~CQuest();

    void initUnCompleteQuest(); // δ��������ʼ��
    void initCompleteQuest();   // ���������
    void initQuestTable();      // ��ʼ���������������б�

    std::list<GameQuest> m_unComplete_quest;  // δ�������
    std::list<GameQuest> m_complete_quest;    // ���������
    std::list<GameQuest> m_questTable_quest;  // �������������б�

protected:
    void allotQuest(int nQuestInfo, std::list<GameQuest>& QuestList); // ���ݴ�����������Ϣָ��������� List
    void TraverTree(int iObject);
};