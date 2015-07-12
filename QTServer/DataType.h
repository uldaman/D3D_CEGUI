#pragma once
#include "QVector"
#include <windows.h>

extern QVector<DWORD> g_processVec;
extern BOOL g_bInjectDll;

#pragma pack (push,1)

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

typedef struct {
    DWORD dwRet;
    DWORD Key;
    WCHAR DatiAcc[25];
    WCHAR DatiPwd[25];
    DWORD DatiErrorCode;
    DWORD DatiType;
    DWORD cmdtype;
    WCHAR acc[25];
    WCHAR psw[25];
    WCHAR area[25];
    WCHAR server[25];
}ShareLoginInfo, *PShareLoginInfo;

enum SHARELGOININFOSTATE { //自动登录dll(新)
    SHARELGOININFOSTATE_INFO = 1, //告诉登陆器开始登陆账号
    SHARELGOININFOSTATE_SUCCEED, //成功登陆
    SHARELGOININFOSTATE_CLOSE, //告诉登陆器关闭
    SHARELGOINRET_ERROR_ACCDONGJIE, //被冻结
    SHARELGOINRET_ERROR_PSWWRONG
};

#pragma pack(pop,1)