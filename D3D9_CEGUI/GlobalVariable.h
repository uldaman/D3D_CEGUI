#pragma once
#include <windows.h>
#include "CLua.h"
#include <string>

extern cLua*                    g_pClua;            // ȫ�� Lua Context
extern std::string              BossName[];         // ���� BOSS
extern HANDLE                   g_hLuaThread;       // ȫ�� Lua Thread
extern BOOL                     g_isWork;           // �������ƽű�����
extern std::string              g_strEventHandle;   // ����ע�� Lua �¼�