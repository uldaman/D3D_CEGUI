#pragma once
#include <string>

#pragma pack (push,1)

//-----------------------------------------------------------
//    交互封包
//-----------------------------------------------------------
typedef struct INTERACTIVE_PACKAGE {
    DWORD  A_Head;  //包头 00001401
    DWORD  B_Unknown;
    DWORD  C_Unknown;
    DWORD  D_Unknown;
    DWORD  E_Fixation; //固定值 0x00000102
    DWORD  F_NPC_ID; //0000AC：NPCID_Part2   （完整的NPCID : 100000AC，来自于《D - 对象遍历.txt》->【根据对象指针获取对象详情指针】->ID）
    DWORD  G_NPC_ID; //000002:固定值 10：NPCID_Part1
    DWORD  H_Unknown;
    DWORD  I_Unknown;
} InteractivePackage, *pInteractivePackage;

//-----------------------------------------------------------
//    任务封包
//-----------------------------------------------------------
typedef struct QUEST_PACKAGE {
    DWORD  A_Head;  //包头 00001401
    DWORD  B_Unknown;
    DWORD  C_Unknown;
    DWORD  D_Unknown;
    DWORD  E_FID; //任务ID
    DWORD  F_Unknown;
} QuestPackage, *pQuestPackage;

//-----------------------------------------------------------
//    任务对话封包
//-----------------------------------------------------------
typedef struct QUEST_INTERACTIVE_PACKAGE {
    DWORD  A_Head;  //包头 00001401
    DWORD  B_Unknown;
    DWORD  C_Unknown;
    DWORD  D_Unknown;
    DWORD  E_Fixation; //固定值 00000002
    DWORD  F_FID; //任务ID
    DWORD  G_Unknown;
    DWORD  H_Unknown;
    DWORD  I_Unknown;
} QuestInteractivePackage, *pQuestInteractivePackage;

#pragma pack(pop)