#pragma once
#include <windows.h>
#include "CLua.h"
#include <string>

extern cLua*                    g_pClua;            // 全局 Lua Context
extern std::string              BossName[];         // 所有 BOSS
extern HANDLE                   g_hLuaThread;       // 全局 Lua Thread
extern BOOL                     g_isWork;           // 用来控制脚本工作
extern std::string              g_strEventHandle;   // 用来注册 Lua 事件