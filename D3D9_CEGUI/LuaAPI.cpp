#include "LuaAPI.h"
#include "Base.h"
#include "DefMessage.h"
#include "Game.h"
#include <CEGUI\widgets\FrameWindow.h>
#include <CEGUI\widgets\PushButton.h>
#include "Role.h"
#include "BrushZones.h"
#include "DataType.h"

//Lua����
LuaGlue Lua_Trac(lua_State *L) {
    if (g_pClua) {
        char szBuffer[1024] = { "Debug:" };
        strcat_s(szBuffer, g_pClua->GetStringArgument(1));
        OutputDebugStringA(szBuffer);
    }
    return 0;
}

//��ʱ
LuaGlue Lua_Sleep(lua_State *L) {
    if (g_pClua) {
        Sleep(g_pClua->GetIntArgument(1));
    }
    return 0;
}

//MH_�Ƿ���
LuaGlue Lua_IsWork(lua_State *L) {
    g_pClua->PushInt(g_isWork);

    return 1;
}

// ע�ắ��
LuaGlue _RegisterEvent(lua_State* L) {
    g_strEventHandle = g_pClua->GetStringArgument(1, "");
    return 0;
}

// MH_��ȡ��ǰ����
LuaGlue Lua_GetCurrentQuest(lua_State* L) {
    std::string strMap;
    ::SendMessage(theApp.m_hGWnd, WM_GET_CURRENT_QUEST, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_��ȡ�ɽ�����
LuaGlue Lua_GetQuestTable(lua_State* L) {
    std::string strMap;
    ::SendMessage(theApp.m_hGWnd, WM_GET_QUEST_TABLE, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_ִ�������ı�
LuaGlue Lua_DoScriptStr(lua_State* L) {
    std::string strScript = g_pClua->GetStringArgument(1, "");
    g_pClua->RunString(strScript.c_str());
    return 0;
}

// MH_�Ƿ����������
LuaGlue Lua_IsCompleteQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    int isCom = 0; // Ĭ��û���
    ::SendMessage(theApp.m_hGWnd, WM_IS_QUEST_COMPLETE, (WPARAM)&strQuestName, (LPARAM)&isCom);
    g_pClua->PushInt(isCom);
    return 1;
}

// MH_������
LuaGlue Lua_CompleteQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_COMPLETE_QUEST, (WPARAM)&strQuestName, (LPARAM)&strNpcName);
    return 0;
}

//MH_������
LuaGlue Lua_AcceptQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_ACCEPT_QUEST, (WPARAM)&strQuestName, (LPARAM)&strNpcName);
    return 0;
}

// MH_����Ի�
LuaGlue Lua_InteractiveQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_INTERACTIVE_QUEST, (WPARAM)&strQuestName, (LPARAM)&strNpcName);
    return 0;
}

//MH_�Ƿ��ڸ���
LuaGlue Lua_IsInFB(lua_State *L) {
    int nWhereIsRole;
    ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhereIsRole, NULL);
    g_pClua->PushInt(nWhereIsRole);

    return 1;
}

// MH_���ؽű�
LuaGlue Lua_LoadScript(lua_State *L) {
    std::string strScript = g_pClua->GetStringArgument(1, "");
    std::string strPath = martin->GetModulePath(NULL);
    strScript = strPath + "\\" + strScript;
    g_pClua->RunScript(strScript.c_str());

    return 0;
}

// MH_��ȡ��ǰ��ͼ
LuaGlue Lua_GetRoleMap(lua_State *L) {
    std::string strMap;
    ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_��������̽�
LuaGlue Lua_��������̽�(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_��������̽�, NULL, NULL);
    return 0;
}

// MH_�����ͼ
LuaGlue Lua_CityFly(lua_State *L) {
    std::string strKey = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_CITY_FLY, (WPARAM)&strKey, NULL);
    return 0;
}

// MH_���븱��
LuaGlue Lua_IntoFB(lua_State *L) {
    std::string strZone = g_pClua->GetStringArgument(1, "");

    auto it = CBrushZones::s_fbMap.find(strZone.c_str());
    if (it != CBrushZones::s_fbMap.end()) { // �ҵ���ظ�����Ϣ
        //martin->Debug(TEXT("0x%X"), it->second);
        ::SendMessage(theApp.m_hGWnd, WM_CHOOSE_FB, (WPARAM)it->second, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_START_FB, (WPARAM)it->second, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_INTO_FB, NULL, NULL);
    }

    return 0;
}

// MH_��ȡBOSS
LuaGlue Lua_GetBossName(lua_State *L) {
    // ��ȡBOSS��
    CBrushZones zone;
    ::SendMessage(theApp.m_hGWnd, WM_UPDATA_BOSS, (WPARAM)&zone, NULL);
    g_pClua->PushString(zone.m_strBossName.c_str());
    return 1;
}

//MH_��ȡ��ǰ����
LuaGlue Lua_GetRoleRoom(lua_State *L) {
    int nRet = 0;
    ::SendMessage(theApp.m_hGWnd, WM_ROLE_ROOM, (WPARAM)&nRet, NULL);
    g_pClua->PushInt(nRet);
    return 1;
}

//MH_��ȡBOSS����
LuaGlue Lua_GetBoosRoom(lua_State *L) {
    int nRet = 0;
    ::SendMessage(theApp.m_hGWnd, WM_BOSS_ROOM, (WPARAM)&nRet, NULL);
    g_pClua->PushInt(nRet);
    return 1;
}

//MH_��ȡ��ǰ����
LuaGlue Lua_GetNowZone(lua_State *L) {
    std::string strZone;
    ::SendMessage(theApp.m_hGWnd, WM_GET_ZONE, (WPARAM)&strZone, NULL);
    g_pClua->PushString(strZone.c_str());
    return 1;
}

//MH_˲�Ƶ�BOSS
LuaGlue Lua_GotoBoss(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GOTO_BOSS, NULL, NULL);
    return 0;
}

//MH_��ͼ
LuaGlue Lua_ByMap(lua_State *L) {
    const char* szKey = g_pClua->GetStringArgument(1);
    ::SendMessage(theApp.m_hGWnd, WM_BY_MAP, (WPARAM)szKey, NULL);
    return 0;
}

//MH_ת��
LuaGlue Lua_Trun(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_TURN, NULL, NULL);
    return 0;
}

//MH_����
LuaGlue Lua_Attack(lua_State *L) {
    // �Ȼ�ȡ�Ƿ�װ��������
    int nWeapon;
    ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);

    while (nWeapon == 0) {
        ::SendMessage(theApp.m_hGWnd, WM_WEAPON, NULL, NULL);
        Sleep(500);
        ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);
    }

    ::SendMessage(theApp.m_hGWnd, WM_ATTACK, NULL, NULL);

    // ֱ�ӷ�������
    //int nPart;
    //nPart = g_pClua->GetIntArgument(1);
    //::SendMessage(theApp.m_hGWnd, WM_ATTACK_PACK, (WPARAM)nPart, NULL);

    return 0;
}

//MH_ǰ��
LuaGlue Lua_Forward(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_FORWARD, NULL, NULL);
    return 0;
}

//MH_ֹͣ
LuaGlue Lua_Stop(lua_State *L) {
    std::string strPos = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_STOP, (WPARAM)&strPos, NULL);
    return 0;
}

//MH_��ȡ��ǰѪ��
LuaGlue Lua_GetHpPer(lua_State *L) {
    float fHpPer = 1.0f;
    ::SendMessage(theApp.m_hGWnd, WM_GET_HP_PER, (WPARAM)&fHpPer, NULL);
    g_pClua->PushNumber(static_cast<double>(fHpPer));
    return 1;
}

//MH_�����޵�
LuaGlue Lua_Invincible(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_INVINCIBLE, NULL, NULL);
    return 0;
}

//MH_�ر��޵�
LuaGlue Lua_UnInvincible(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_UN_INVINCIBLE, NULL, NULL);
    return 0;
}

//MH_˲�Ƶ�����
LuaGlue Lua_TeleportToPoint(lua_State *L) {
    float fx = static_cast<float>(g_pClua->GetNumberArgument(1));
    float fy = static_cast<float>(g_pClua->GetNumberArgument(2));
    float fz = static_cast<float>(g_pClua->GetNumberArgument(3));
    POINT_TARGET target;
    target.fPontX = fx;
    target.fPontY = fy;
    target.fPontZ = fz;
    ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&target, NULL);
    return 0;
}

//MH_��ȡ��ǰ����", Lua_GetPoint
LuaGlue Lua_GetPoint(lua_State *L) {
    POINT_TARGET target;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&target, NULL);
    g_pClua->PushNumber(target.fPontX);
    g_pClua->PushNumber(target.fPontY);
    g_pClua->PushNumber(target.fPontZ);
    return 3;
}

//MH_����
LuaGlue Lua_GoLeft(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GO_LEFT, NULL, NULL);
    return 0;
}

//MH_����
LuaGlue Lua_GoRight(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GO_RIGHT, NULL, NULL);
    return 0;
}

//MH_����
LuaGlue Lua_GoBack(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GO_BACK, NULL, NULL);
    return 0;
}

//MH_��������
LuaGlue Lua_TakeUpWeapons(lua_State *L) {
    // ���ж��Ƿ��Ѿ�����������, ���û������, ����������
    int nWeapon;
    ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);

    while (nWeapon == 0) {
        // �ж��Ƿ��ڿ���״̬
        int nMode;
        ::SendMessage(theApp.m_hGWnd, WM_HAVE_MODE, (WPARAM)&nMode, NULL);

        if (nMode == 1) {
            ::SendMessage(theApp.m_hGWnd, WM_CHANGE_MODE, NULL, NULL);
        }

        ::SendMessage(theApp.m_hGWnd, WM_WEAPON, NULL, NULL);
        Sleep(500);
        ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);
    }

    return 0;
}

//MH_��������
LuaGlue Lua_CollectWeapons(lua_State *L) {
    // ���ж��Ƿ��Ѿ�����������, �������, ������
    int nWeapon;
    ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);

    while (nWeapon != 0) {
        // �ж��Ƿ��ڿ���״̬
        int nMode;
        ::SendMessage(theApp.m_hGWnd, WM_HAVE_MODE, (WPARAM)&nMode, NULL);

        if (nMode == 1) {
            ::SendMessage(theApp.m_hGWnd, WM_CHANGE_MODE, NULL, NULL);
        }

        ::SendMessage(theApp.m_hGWnd, WM_WEAPON, NULL, NULL);
        Sleep(500);
        ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);
    }

    return 0;
}

//MH_����
LuaGlue Lua_Roll(lua_State *L) {
    // ����������
    Lua_CollectWeapons(L);
    Sleep(500);
    ::SendMessage(theApp.m_hGWnd, WM_ROLL, NULL, NULL);
    return 0;
}

// MH_������ȡ��
LuaGlue Lua_GetItemFormCrates(lua_State *L) {
    std::string strItems = g_pClua->GetStringArgument(1, "");
    std::vector<std::string> vctItems = martin->split(strItems, "|");
    for (auto& v : vctItems) {
        //std::string strItem = v.c_str();
        ::SendMessage(theApp.m_hGWnd, WM_GET_ITEM_FORM_CRATES, (WPARAM)&v, NULL);
        Sleep(500);
    }
    
    return 0;
}

//MH_�ɼ�������Ʒ
LuaGlue Lua_CollectAll(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_COLLECT_ALL, NULL, NULL);
    return 0;
}

luaL_reg ConsoleGlue[] = {
        { "RegisterEvent", _RegisterEvent },
        { "MH_����", Lua_Trac },
        { "MH_��ʱ", Lua_Sleep },
        { "MH_�Ƿ���", Lua_IsWork },
        { "MH_��ȡ��ǰ����", Lua_GetCurrentQuest },
        { "MH_ִ�������ı�", Lua_DoScriptStr },
        { "MH_�Ƿ����������", Lua_IsCompleteQuest },
        { "MH_�Ƿ��ڸ���", Lua_IsInFB }, 
        { "MH_������", Lua_CompleteQuest },
        { "MH_��ȡ�ɽ�����", Lua_GetQuestTable },
        { "MH_������", Lua_AcceptQuest },
        { "MH_����Ի�", Lua_InteractiveQuest },
        { "MH_���ؽű�", Lua_LoadScript },
        { "MH_��ȡ��ǰ��ͼ", Lua_GetRoleMap },
        { "MH_��������̽�", Lua_��������̽� },
        { "MH_�����ͼ", Lua_CityFly },
        { "MH_���븱��", Lua_IntoFB },
        { "MH_��ȡBOSS", Lua_GetBossName },
        { "MH_��ȡ��ǰ����", Lua_GetRoleRoom },
        { "MH_��ȡBOSS����", Lua_GetBoosRoom },
        { "MH_��ȡ��ǰ����", Lua_GetNowZone },
        { "MH_˲�Ƶ�BOSS", Lua_GotoBoss },
        { "MH_��ͼ", Lua_ByMap },
        { "MH_ת��", Lua_Trun },
        { "MH_����", Lua_Attack },
        { "MH_ǰ��", Lua_Forward },
        { "MH_ֹͣ", Lua_Stop },
        { "MH_��ȡ��ǰѪ��", Lua_GetHpPer },
        { "MH_�����޵�", Lua_Invincible },
        { "MH_�ر��޵�", Lua_UnInvincible },
        { "MH_˲�Ƶ�����", Lua_TeleportToPoint },
        { "MH_��ȡ��ǰ����", Lua_GetPoint },
        { "MH_����", Lua_GoLeft },
        { "MH_����", Lua_GoRight },
        { "MH_����", Lua_GoBack },
        { "MH_��������", Lua_TakeUpWeapons },
        { "MH_��������", Lua_CollectWeapons },
        { "MH_����", Lua_Roll },
        { "MH_������ȡ��", Lua_GetItemFormCrates },
        { "MH_�ɼ�������Ʒ", Lua_CollectAll },
        { nullptr, NULL },
};

// ע�� ����
void AddLuaFunction() {
    for (int i = 0; ConsoleGlue[i].name; i++) {
        g_pClua->AddFunction(ConsoleGlue[i].name, ConsoleGlue[i].func);
    }
}

// Lua �¼�������
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

// Lua ���������
void LuaError_Output(const char* szBuffer) {
    char szTarget[1024] = { "Debug:" };
    strcat_s(szTarget, szBuffer);
    OutputDebugStringA(szTarget);
}

// Lua �Զ��һ� Thread
unsigned int __stdcall ThreadAutoMatic(PVOID pM) {
    try {
        g_pClua->SetErrorHandler(LuaError_Output);

        std::string strPath = martin->GetModulePath(NULL);
        strPath += "\\S\\script";
        theApp.m_mainWnd->setText(theApp.AToUtf8("ִ�нű��� ... "));
        theApp.m_questBtn->setText(theApp.AToUtf8("ֹͣ����"));
        g_pClua->RunScript(strPath.c_str());
        FireEvent(EVENT_AUTO, nullptr);
    } catch (...) {
        //Interface_Output(TEXT("cLua::RunScript �쳣!!"));
    }

    if (g_hLuaThread) {
        CloseHandle(g_hLuaThread);
        g_hLuaThread = NULL;
    }
    theApp.m_mainWnd->setText(theApp.AToUtf8("��ɫ������ ... "));
    theApp.m_questBtn->setText(theApp.AToUtf8("�Զ�����"));
    return 0;
}