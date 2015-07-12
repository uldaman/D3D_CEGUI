#pragma once
#include "QVector"
#include <windows.h>

extern QVector<DWORD> g_processVec;
extern BOOL g_bInjectDll;

#pragma pack (push,1)

enum class SOCKET_MESSAGE { // socket ��Ϣ����
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

enum SHARELGOININFOSTATE { //�Զ���¼dll(��)
    SHARELGOININFOSTATE_INFO = 1, //���ߵ�½����ʼ��½�˺�
    SHARELGOININFOSTATE_SUCCEED, //�ɹ���½
    SHARELGOININFOSTATE_CLOSE, //���ߵ�½���ر�
    SHARELGOINRET_ERROR_ACCDONGJIE, //������
    SHARELGOINRET_ERROR_PSWWRONG
};

#pragma pack(pop,1)