#pragma once
#include "initsock.h"

class CSocketClient 
    :public CInitSock {
public:
    CSocketClient(HWND hGame, BYTE minorVer = 2, BYTE majorVer = 2);
    
    ~CSocketClient() {
    };

};