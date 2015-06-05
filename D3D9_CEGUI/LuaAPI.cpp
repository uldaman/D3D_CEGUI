#include "LuaAPI.h"
#include "Base.h"
#include "DefMessage.h"
#include "Game.h"
#include <CEGUI\widgets\FrameWindow.h>
#include <CEGUI\widgets\PushButton.h>
#include "Role.h"
#include "BrushZones.h"

//Lua调试
LuaGlue Lua_Trac(lua_State *L) {
    if (g_pClua) {
        char szBuffer[1024] = { "Debug:" };
        strcat_s(szBuffer, g_pClua->GetStringArgument(1));
        OutputDebugStringA(szBuffer);
    }
    return 0;
}

//延时
LuaGlue Lua_Sleep(lua_State *L) {
    if (g_pClua) {
        Sleep(g_pClua->GetIntArgument(1));
    }
    return 0;
}

//MH_是否工作
LuaGlue Lua_IsWork(lua_State *L) {
    g_pClua->PushInt(g_isWork);

    return 1;
}

// 注册函数
LuaGlue _RegisterEvent(lua_State* L) {
    g_strEventHandle = g_pClua->GetStringArgument(1, "");
    return 0;
}

// MH_获取当前主线
LuaGlue Lua_GetCurrentQuest(lua_State* L) {
    std::string strMap;
    ::SendMessage(theApp.m_hGWnd, WM_GET_CURRENT_QUEST, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_获取可接主线
LuaGlue Lua_GetQuestTable(lua_State* L) {
    std::string strMap;
    ::SendMessage(theApp.m_hGWnd, WM_GET_QUEST_TABLE, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_执行命令文本
LuaGlue Lua_DoScriptStr(lua_State* L) {
    std::string strScript = g_pClua->GetStringArgument(1, "");
    g_pClua->RunString(strScript.c_str());
    return 0;
}

// MH_是否已完成任务
LuaGlue Lua_IsCompleteQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    int isCom = 0; // 默认没完成
    ::SendMessage(theApp.m_hGWnd, WM_IS_QUEST_COMPLETE, (WPARAM)&strQuestName, (LPARAM)&isCom);
    g_pClua->PushInt(isCom);
    return 1;
}

// MH_交任务
LuaGlue Lua_CompleteQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_COMPLETE_QUEST, (WPARAM)&strQuestName, (LPARAM)&strNpcName);
    return 0;
}

//MH_接任务
LuaGlue Lua_AcceptQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_ACCEPT_QUEST, (WPARAM)&strQuestName, (LPARAM)&strNpcName);
    return 0;
}

// MH_任务对话
LuaGlue Lua_InteractiveQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_INTERACTIVE_QUEST, (WPARAM)&strQuestName, (LPARAM)&strNpcName);
    return 0;
}

//MH_是否在副本
LuaGlue Lua_IsInFB(lua_State *L) {
    int nWhereIsRole;
    ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhereIsRole, NULL);
    g_pClua->PushInt(nWhereIsRole);

    return 1;
}

// MH_加载脚本
LuaGlue Lua_LoadScript(lua_State *L) {
    std::string strScript = g_pClua->GetStringArgument(1, "");
    std::string strPath = martin->GetModulePath(NULL);
    strScript = strPath + "\\" + strScript;
    g_pClua->RunScript(strScript.c_str());

    return 0;
}

// MH_获取当前地图
LuaGlue Lua_GetRoleMap(lua_State *L) {
    std::string strMap;
    ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_锻造晓风短剑
LuaGlue Lua_锻造晓风短剑(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_锻造晓风短剑, NULL, NULL);
    return 0;
}

// MH_城镇飞图
LuaGlue Lua_CityFly(lua_State *L) {
    std::string strKey = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_CITY_FLY, (WPARAM)&strKey, NULL);
    return 0;
}

// MH_进入副本
LuaGlue Lua_IntoFB(lua_State *L) {
    std::string strZone = g_pClua->GetStringArgument(1, "");

    auto it = CBrushZones::s_fbMap.find(strZone.c_str());
    if (it != CBrushZones::s_fbMap.end()) { // 找到相关副本信息
        //martin->Debug(TEXT("0x%X"), it->second);
        ::SendMessage(theApp.m_hGWnd, WM_CHOOSE_FB, (WPARAM)it->second, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_START_FB, (WPARAM)it->second, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_INTO_FB, NULL, NULL);
    }

    return 0;
}

// MH_获取BOSS
LuaGlue Lua_GetBossName(lua_State *L) {
    // 获取BOSS名
    CBrushZones zone;
    ::SendMessage(theApp.m_hGWnd, WM_UPDATA_BOSS, (WPARAM)&zone, NULL);
    g_pClua->PushString(zone.m_strBossName.c_str());
    return 1;
}

//MH_获取当前房间
LuaGlue Lua_GetRoleRoom(lua_State *L) {
    int nRet = 0;
    ::SendMessage(theApp.m_hGWnd, WM_ROLE_ROOM, (WPARAM)&nRet, NULL);
    g_pClua->PushInt(nRet);
    return 1;
}

//MH_获取BOSS房间
LuaGlue Lua_GetBoosRoom(lua_State *L) {
    int nRet = 0;
    ::SendMessage(theApp.m_hGWnd, WM_BOSS_ROOM, (WPARAM)&nRet, NULL);
    g_pClua->PushInt(nRet);
    return 1;
}

//MH_获取当前副本
LuaGlue Lua_GetNowZone(lua_State *L) {
    std::string strZone;
    ::SendMessage(theApp.m_hGWnd, WM_GET_ZONE, (WPARAM)&strZone, NULL);
    g_pClua->PushString(strZone.c_str());
    return 1;
}

//MH_瞬移到BOSS
LuaGlue Lua_GotoBoss(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GOTO_BOSS, NULL, NULL);
    return 0;
}

//MH_过图
LuaGlue Lua_ByMap(lua_State *L) {
    const char* szKey = g_pClua->GetStringArgument(1);
    ::SendMessage(theApp.m_hGWnd, WM_BY_MAP, (WPARAM)szKey, NULL);
    return 0;
}

//MH_转向
LuaGlue Lua_Trun(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_TURN, NULL, NULL);
    return 0;
}

//MH_攻击
LuaGlue Lua_Attack(lua_State *L) {
    // 先获取是否装备了武器
    int nWeapon;
    ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);

    while (nWeapon == 0) {
        ::SendMessage(theApp.m_hGWnd, WM_WEAPON, NULL, NULL);
        Sleep(500);
        ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);
    }

    ::SendMessage(theApp.m_hGWnd, WM_ATTACK, NULL, NULL);

    // 直接发包攻击
    //int nPart;
    //nPart = g_pClua->GetIntArgument(1);
    //::SendMessage(theApp.m_hGWnd, WM_ATTACK_PACK, (WPARAM)nPart, NULL);

    return 0;
}

//MH_前进
LuaGlue Lua_Forward(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_FORWARD, NULL, NULL);
    return 0;
}

//MH_停止
LuaGlue Lua_Stop(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_STOP, NULL, NULL);
    return 0;
}

luaL_reg ConsoleGlue[] = {
        { "RegisterEvent", _RegisterEvent },
        { "MH_调试", Lua_Trac },
        { "MH_延时", Lua_Sleep },
        { "MH_是否工作", Lua_IsWork },
        { "MH_获取当前主线", Lua_GetCurrentQuest },
        { "MH_执行命令文本", Lua_DoScriptStr },
        { "MH_是否已完成任务", Lua_IsCompleteQuest },
        { "MH_是否在副本", Lua_IsInFB }, 
        { "MH_交任务", Lua_CompleteQuest },
        { "MH_获取可接主线", Lua_GetQuestTable },
        { "MH_接任务", Lua_AcceptQuest },
        { "MH_任务对话", Lua_InteractiveQuest },
        { "MH_加载脚本", Lua_LoadScript },
        { "MH_获取当前地图", Lua_GetRoleMap },
        { "MH_锻造晓风短剑", Lua_锻造晓风短剑 },
        { "MH_城镇飞图", Lua_CityFly },
        { "MH_进入副本", Lua_IntoFB },
        { "MH_获取BOSS", Lua_GetBossName },
        { "MH_获取当前房间", Lua_GetRoleRoom },
        { "MH_获取BOSS房间", Lua_GetBoosRoom },
        { "MH_获取当前副本", Lua_GetNowZone },
        { "MH_瞬移到BOSS", Lua_GotoBoss },
        { "MH_过图", Lua_ByMap },
        { "MH_转向", Lua_Trun },
        { "MH_攻击", Lua_Attack },
        { "MH_前进", Lua_Forward },
        { "MH_停止", Lua_Stop },
        { nullptr, NULL },
};

// 注册 函数
void AddLuaFunction() {
    for (int i = 0; ConsoleGlue[i].name; i++) {
        g_pClua->AddFunction(ConsoleGlue[i].name, ConsoleGlue[i].func);
    }
}

// Lua 事件触发器
void FireEvent(int nId, const char* args) {
    if (g_strEventHandle != "") {
        char buf[256];
        if (args) {
            sprintf_s(buf, 255, "%s(%d, %s)", g_strEventHandle.c_str(), nId, args);
        } else {
            sprintf_s(buf, 255, "%s(%d)", g_strEventHandle.c_str(), nId);
        }
        martin->Debug(buf);
        g_pClua->RunString(buf);
    }
}

// Lua 错误调试器
void LuaError_Output(const char* szBuffer) {
    char szTarget[1024] = { "Debug:" };
    strcat_s(szTarget, szBuffer);
    OutputDebugStringA(szTarget);
}

// Lua 自动挂机 Thread
unsigned int __stdcall ThreadAutoMatic(PVOID pM) {
    try {
        g_pClua->SetErrorHandler(LuaError_Output);

        std::string strPath = martin->GetModulePath(NULL);
        strPath += "\\S\\script";
        theApp.m_mainWnd->setText(theApp.AToUtf8("执行脚本中 ... "));
        theApp.m_questBtn->setText(theApp.AToUtf8("停止主线"));
        g_pClua->RunScript(strPath.c_str());
        FireEvent(EVENT_AUTO, nullptr);
    } catch (...) {
        //Interface_Output(TEXT("cLua::RunScript 异常!!"));
    }

    if (g_hLuaThread) {
        CloseHandle(g_hLuaThread);
        g_hLuaThread = NULL;
    }
    theApp.m_mainWnd->setText(theApp.AToUtf8("角色空闲中 ... "));
    theApp.m_questBtn->setText(theApp.AToUtf8("自动主线"));
    return 0;
}