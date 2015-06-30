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
    int nQuestStatus;
    std::string strQuestType;   // ���� || ����
    int nQuestID;
    int nTheTaskMinimumLevel; // ���΄���С�ȼ�
    int nTheTaskMaximumLevel; // ���΄����ȼ�
    int nTargetBrushZonesID;  // ������Ҫ�����FB
    bool operator()(GAME_QUEST& p) { // ��ʹ�� std::find_if ����
        return (strQuestName == p.strQuestName);
    }
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
    void initOfferARewardQuest(); // ��ʼ�����p�΄��б�
    

    std::list<GameQuest> m_unComplete_quest;    // δ�������
    std::list<GameQuest> m_complete_quest;      // ���������
    std::list<GameQuest> m_questTable_quest;    // �������������б�
    std::list<GameQuest> m_offerAReward_quest;  // �����Б��p�����б�
    int m_nCountOfTodayOfferAReward = 0; // ���Ց��p�΄���ɔ���

    void CompleteQuest(int nQuestID); // ������
    void AcceptQuest(int nQuestID); // ������
    std::string GetQuestTable(); // ��ȡ��ǰ�ɽ�����
    void InteractiveQuest(int nQuestID); // ����Ի�
    void ��������̽�();
    void ����嶡������();
    void MadeHpMedicine(); // �����ظ�ҩ

protected:
    void allotQuest(int nQuestInfo, std::list<GameQuest>& QuestList); // ���ݴ�����������Ϣָ��������� List
    void TraverTree(int iObject);
    std::string TransformName(std::string strName); // ת������
    void StringReplace(std::string &strBase, std::string strSrc, std::string strDes);
};