#pragma once
#include <string>

#pragma pack (push,1)

typedef struct _POINT_TARGET {
    float fPontX;
    float fPontY;
    float fPontZ;
} POINT_TARGET, *pPOINT_TARGET;

typedef struct t_QuestInfo {
    std::string strQuestName;
    std::string strNpcName;
} QuestInfo, *pQuestInfo;

typedef struct t_SupplyInfo {
    std::string strSupplyName;
    std::string strTypeName;
    std::string strNpcName;
} SupplyInfo, *pSupplyInfo;

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

//-----------------------------------------------------------
//    锻造晓风短剑
//-----------------------------------------------------------
typedef struct PACKAGE_锻造晓风短剑 {
    DWORD  A_Head;  //包头 00000903
    DWORD  B_Unknown;
    DWORD  C_Unknown;
    DWORD  D_Unknown;
    DWORD  E_Fixation; //固定值 00000544
    DWORD  F_Unknown;
    DWORD  G_Unknown;
} Package锻造晓风短剑, *pPackage锻造晓风短剑;

typedef struct _CHOOSE_FB_PACKAGE {
    DWORD A_;
    DWORD B_;
    DWORD C_;
    DWORD D_;
    DWORD E_;
    DWORD F_;
    DWORD G_;
    DWORD H_;
} CHOOSE_FB_PACKAGE, *pCHOOSE_FB_PACKAGE;

typedef struct _START_FB_PACKAGE {
    DWORD A_;
    DWORD B_;
    DWORD C_;
    DWORD D_;
    DWORD E_;
    DWORD F_;
    DWORD G_;
} START_FB_PACKAGE, *pSTART_FB_PACKAGE;

typedef struct _SET_OUT_FB_PACKAGE {
    DWORD A_;
    DWORD B_;
    DWORD C_;
    DWORD D_;
    DWORD E_;
    DWORD F_;
    DWORD G_;
    DWORD H_;
} SET_OUT_FB_PACKAGE, *pSET_OUT_FB_PACKAGE;

typedef struct _ATTACK_PACKAGE {
    DWORD A_RoleKey;        //当前人物的Key
    DWORD B_MonsterKey;     //怪物的Key
    DWORD C_Unknown1;       //0填充
    DWORD D_Action;         //1:开始，2：完毕.(调用时，可使用1，2作为参数分别调用一次)
    DWORD E_Unknown2[2];    //0填充
    DWORD F_Key1[2];        //【技能效果相关Key】 见下方
    DWORD G_Unknown3[4];    //0填充
    DWORD H_RoleOffset74;   //[当前人物+74]
    DWORD I_RoleOffset78;   //[当前人物+78] 
    DWORD J_RoleOffset60;   //[当前人物+60] 人物坐标X OFFSET_COOR
    DWORD K_RoleOffset64;   //[当前人物+60+4] 人物坐标Y OFFSET_COOR+4
    DWORD L_RoleOffset68;   //[当前人物+60+8] 人物坐标Y OFFSET_COOR+8
    DWORD M_Unknown4;       //0填充
    DWORD N_AttackPart;     //攻击部位 2:身体 恐龙头:0x11,鸟头:0x1D
    DWORD O_Unknown5;       //0填充
    DWORD P_MonsterCoorX;   //怪物坐标X
    DWORD Q_MonsterCoorY;   //怪物坐标Y
    DWORD R_MonsterCoorZ;   //怪物坐标Z	
    DWORD S_Unknown6[0x40]; //0填充
    DWORD T_Key2;           //固定值 35B5B245 
    DWORD U_Unknown8[0x100];//填充满 0
} ATTACK_PACKAGE, *pATTACK_PACKAGE;

typedef struct _GET_ITEM_PACKAGE {
    DWORD A_Head;        //包头 00000D01
    DWORD B_Unknown; 
    DWORD C_Unknown; 
    DWORD D_Unknown; 
    DWORD E_Index;          // 索引号
    DWORD F_ID;             // 对象ID
    DWORD G_Num;            // 对象数量
    DWORD H_Unknown;
} GET_ITEM_PACKAGE, *pGET_ITEM_PACKAGE;

typedef struct _NAME_OID {
    std::string strName;
    int nOID;
} NAME_OID, *pNAME_OID;

enum class SOCKET_MESSAGE { // socket 消息类型
    GetScript,
    StopScript,
    StartScript,
};

typedef struct SOCKET_INFO {
    SOCKET_MESSAGE message;
    char szAccOrScript[25];
    char szName[25];
    int nLevel;
    char szMap[25];
    int nMoney;
}*PSOCKET_INFO;

#pragma pack(pop)