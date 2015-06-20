#pragma once
#include <windows.h>

#define Naked   __declspec( naked )
#define CODE_LEN 1000

class CGameHOOK {
public:
    CGameHOOK(void);
    ~CGameHOOK(void);
public:
    BOOL  IsHook;
    DWORD dwCodeAdress;
    DWORD dwCodeLen;
    DWORD  bSaveCode;
    DWORD  bSwitch;
public:
    void StartHook(DWORD dwAdress, DWORD dwFun);
    void UnHook();
    void StartHookByByte(DWORD dwAdress, DWORD dwFun, byte Numberbytes);
    void UnHookByByte();

    // ������� HOOK ��ר��Ϊ��ʵ�֟o��������
    byte bOriginal[6];
    void StartInvincible(DWORD dwAdress);
    void UnInvincible(DWORD dwAdress);
};

