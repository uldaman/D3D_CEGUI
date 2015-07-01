#include "LuaAPI.h"
#include "Base.h"
#include "DefMessage.h"
#include "Game.h"
#include <CEGUI\widgets\FrameWindow.h>
#include <CEGUI\widgets\PushButton.h>
#include "Role.h"
#include "BrushZones.h"
#include "DataType.h"
#include "Material.h"
#include "My_Ini.h"
#include "Bag.h"
#include "NearObject.h"

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
    // ��¼�µ�ǰ����, ���ڲɼ��귵��
    POINT_TARGET Current_Point;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    ::SendMessage(theApp.m_hGWnd, WM_GET_COLLECTS, NULL, NULL); // ��ʼ���ɼ���Ϣ

    for (auto& v : CMaterial::m_material_list) {
        // ���ж����ǲ�����FB��
        int nWhere;
        ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
        if (nWhere != 2 || g_isWork == false) {
            // �ж��Ƿ���ׯ԰
            std::string strMap;
            ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
            if (strMap != "ׯ԰") {
                goto MaterialEnd; // �������ׯ԰ ������
            }
        }

        //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- %f : %f : %f",
        //    v.strName.c_str(), v.nID, v.nKey, v.fPointX, v.fPointY, v.fPointZ);

        POINT_TARGET _Point = { v.fPointX, v.fPointY, v.fPointZ };
        int nID = v.nID;

        // ˲��
        ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&_Point, NULL);
        Sleep(1000);

        // �ɼ�
        for (int i = 0; i < 3; i++) {
            ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
            if (nWhere != 2 || g_isWork == false) {
                // �ж��Ƿ���ׯ԰
                std::string strMap;
                ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
                if (strMap != "ׯ԰") {
                    goto MaterialEnd; // �������ׯ԰ ������
                }
            }

            ::SendMessage(theApp.m_hGWnd, WM_COLLECT, (WPARAM)&nID, NULL);
            Sleep(500);

            // �ж��Ƿ��ڲɼ���, �ǵĻ�, ���Ųɼ�, ����ʼ��һ��
            BOOL bCollect = FALSE;
            ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
            //martin->Debug(TEXT("�ɼ���ʶ: %d"), bCollect);

            while (bCollect) { // ˵���ڲɼ���
                Sleep(1000);
                ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
            }

            Sleep(500);
        }

        Sleep(500);
    }

MaterialEnd:
    // ���ؿ�ʼ��
    ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&Current_Point, NULL);
    return 0;
}

// MH_�ɼ�Ŀ���
LuaGlue Lua_CollectTar(lua_State *L) {
    float dPointX = static_cast<float>(g_pClua->GetNumberArgument(1));
    float dPointY = static_cast<float>(g_pClua->GetNumberArgument(2));

    // ��¼�µ�ǰ����, ���ڲɼ��귵��
    POINT_TARGET Current_Point;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    ::SendMessage(theApp.m_hGWnd, WM_GET_COLLECTS, NULL, NULL); // ��ʼ���ɼ���Ϣ

    for (auto& v : CMaterial::m_material_list) {
        // ���ж����ǲ�����FB��
        int nWhere;
        ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
        if (nWhere != 2 || g_isWork == false) {
            // ���ж��Ƿ���ׯ԰
            std::string strMap;
            ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
            if (strMap != "ׯ԰") {
                goto MaterialEnd; // �������ׯ԰ ������
            }
        }

        //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- %f : %f : %f",
        //    v.strName.c_str(), v.nID, v.nKey, v.fPointX, v.fPointY, v.fPointZ);

        if (martin->Compare_Coord(dPointX, dPointY, v.fPointX, v.fPointY) < 5.0f) {
            POINT_TARGET _Point = { v.fPointX, v.fPointY, v.fPointZ };
            int nID = v.nID;

            // ˲��
            ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&_Point, NULL);
            Sleep(1000);

            // �ɼ�
            for (int i = 0; i < 3; i++) {
                ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
                if (nWhere != 2 || g_isWork == false) {
                    // �ж��Ƿ���ׯ԰
                    std::string strMap;
                    ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
                    if (strMap != "ׯ԰") {
                        goto MaterialEnd; // �������ׯ԰ ������
                    }
                }

                ::SendMessage(theApp.m_hGWnd, WM_COLLECT, (WPARAM)&nID, NULL);
                Sleep(500);

                // �ж��Ƿ��ڲɼ���, �ǵĻ�, ���Ųɼ�, ����ʼ��һ��
                BOOL bCollect = FALSE;
                ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                //martin->Debug(TEXT("�ɼ���ʶ: %d"), bCollect);

                while (bCollect) { // ˵���ڲɼ���
                    Sleep(1000);
                    ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                }

                Sleep(500);
            }
            goto MaterialEnd;
        }
    }

MaterialEnd:
    // ���ؿ�ʼ��
    ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&Current_Point, NULL);
    return 0;
}

// MH_����
LuaGlue Lua_Barbecue(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_BARBECUES, NULL, NULL);
    return 0;
}

// MH_������Ʒ����
LuaGlue Lua_GetBagItemNum(lua_State *L) {
    std::string strItem = g_pClua->GetStringArgument(1, "");
    int nNum = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_BAG_ITEM_NUM, (WPARAM)&nNum, (LPARAM)&strItem);
    g_pClua->PushInt(nNum);
    return 1;
}

// MH_�Կ���
LuaGlue Lua_EatMeat(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_EAT_MEAT, NULL, NULL);
    return 0;
}

// MH_ͨ��ʹ����Ʒ
LuaGlue Lua_CommonUseItems(lua_State *L) {
    std::string strItem = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_USE_ITEM, (WPARAM)&strItem, NULL);
    return 0;
}

// MH_����ʽ�ɼ�
LuaGlue lua_FilterCollect(lua_State *L) {
    std::string strFilter = g_pClua->GetStringArgument(1, "");

    // ��¼�µ�ǰ����, ���ڲɼ��귵��
    POINT_TARGET Current_Point;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    ::SendMessage(theApp.m_hGWnd, WM_GET_COLLECTS, NULL, NULL); // ��ʼ���ɼ���Ϣ

    for (auto& v : CMaterial::m_material_list) {
        // ���ж����ǲ�����FB��
        int nWhere;
        ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
        if (nWhere != 2 || g_isWork == false) {
            // �ж��Ƿ���ׯ԰
            std::string strMap;
            ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
            if (strMap != "ׯ԰") {
                goto MaterialEnd; // �������ׯ԰ ������
            }
        }

        //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- %f : %f : %f",
        //    v.strName.c_str(), v.nID, v.nKey, v.fPointX, v.fPointY, v.fPointZ);
        // ��� 1:���ڿ󹤾ߣ�,2:ҩ��,3:���棨���湤�ߣ�,5:Ģ��,6:����,7:Сʯͷ,8:���,0xA:ʬ��,0xC:��ͷ,0x11:��
        std::string::size_type idx = v.strType.find(strFilter);
        if (idx != std::string::npos) { // �ҵ�����
            POINT_TARGET _Point = { v.fPointX, v.fPointY, v.fPointZ };
            int nID = v.nID;

            // ˲��
            ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&_Point, NULL);
            Sleep(1000);

            // �ɼ�
            for (int i = 0; i < 3; i++) {
                ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
                if (nWhere != 2 || g_isWork == false) {
                    // �ж��Ƿ���ׯ԰
                    std::string strMap;
                    ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
                    if (strMap != "ׯ԰") {
                        goto MaterialEnd; // �������ׯ԰ ������
                    }
                }

                ::SendMessage(theApp.m_hGWnd, WM_COLLECT, (WPARAM)&nID, NULL);
                Sleep(500);

                // �ж��Ƿ��ڲɼ���, �ǵĻ�, ���Ųɼ�, ����ʼ��һ��
                BOOL bCollect = FALSE;
                ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                //martin->Debug(TEXT("�ɼ���ʶ: %d"), bCollect);

                while (bCollect) { // ˵���ڲɼ���
                    Sleep(1000);
                    ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                } // ��ǰ�����ѿ���

                Sleep(500);
            } // ͬһ��Ŀ����Ѿ��ɼ�����
        } // һ�ֲɼ�����
        Sleep(500);
    }

MaterialEnd:
    // ���ؿ�ʼ��
    ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&Current_Point, NULL);
    return 0;
}

// MH_����ظ�ҩ
LuaGlue lua_MadeHpMedicine(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_MADE_HP_MEDICINE, NULL, NULL);
    return 0;
}

// MH_������Ʒ
LuaGlue lua_BuySupply(lua_State *L) {
    SupplyInfo supplyInfo;
    supplyInfo.strSupplyName = g_pClua->GetStringArgument(1, "");
    supplyInfo.strNpcName = g_pClua->GetStringArgument(2, "");
    supplyInfo.strTypeName = g_pClua->GetStringArgument(3, "");

    int nNumOfSupply = g_pClua->GetIntArgument(4);

    ::SendMessage(theApp.m_hGWnd, WM_BUY_SUPPLY, (WPARAM)&supplyInfo, (LPARAM)&nNumOfSupply);
    return 0;
}

// MH_��ɱ����
LuaGlue lua_KillMonster(lua_State *L) {
    std::string strMonster = g_pClua->GetStringArgument(1, "");
    int nNumKill = g_pClua->GetIntArgument(2);
    for (int i = 0; i < nNumKill; i++) {
        ::SendMessage(theApp.m_hGWnd, WM_KILL_MONSTER, (WPARAM)&strMonster, NULL);
#define EVENT_KILL_MONSTER 1000 //��ɱ��ǹ�
        FireEvent(EVENT_KILL_MONSTER, strMonster.c_str());
        Sleep(1000);
    }

    return 0;
}

// MH_��ȡ��ǹ��﷿��
LuaGlue lua_GetMonsterRoom(lua_State *L) {
    int nMonsterRomm = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_MONSTER_ROOM, (WPARAM)&nMonsterRomm, NULL);
    g_pClua->PushInt(nMonsterRomm);
    return 1;
}

// MH_˲�Ƶ���ǹ�
LuaGlue Lua_GotoMonster(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GOTO_MONSTER, NULL, NULL);
    return 0;
}

// MH_ת���ǹ�
LuaGlue Lua_TrunToMonster(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_TURN_TO_MONSTER, NULL, NULL);
    return 0;
}

// MH_�ߵ�Ŀ���
LuaGlue Lua_WalkToPoint(lua_State *L) {
    POINT_TARGET Current_Point; // ��ǰ����
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    float fTargetPointX = static_cast<float>(g_pClua->GetNumberArgument(1));
    float fTargetPointY = static_cast<float>(g_pClua->GetNumberArgument(2));

    BOOL bIsWalk = FALSE;
    if (martin->Compare_Coord(fTargetPointX, fTargetPointY, Current_Point.fPontX, Current_Point.fPontY) > 3.0f) {
        // ת��
        ::SendMessage(theApp.m_hGWnd, WM_TURN_TO_POINT, (WPARAM)&fTargetPointX, (LPARAM)&fTargetPointY);
        // ǰ��
        Lua_Forward(L);
        bIsWalk = TRUE;
    }

    while (g_isWork ) {
        ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);
        if (martin->Compare_Coord(fTargetPointX, fTargetPointY, Current_Point.fPontX, Current_Point.fPontY) < 3.0f) {
            if (bIsWalk) {
                g_pClua->PushString("ǰ��");
                Lua_Stop(L);
            }
            break;
        }
        Sleep(100);
    }

    return 0;
}

// MH_������������
LuaGlue Lua_AcceptOfferARewardQuest(lua_State *L) {
    std::string strLevel = g_pClua->GetStringArgument(1, "");
    std::string strType = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_ACCEPT_OFFER_A_REWARD, (WPARAM)&strLevel, (LPARAM)&strType);
    return 0;
}

// MH_��ȡ��ǰ����
LuaGlue Lua_GetCurrentReward(lua_State* L) {
    std::string strMap = "";
    ::SendMessage(theApp.m_hGWnd, WM_GET_CURRENT_REWARD, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_�������͸���
LuaGlue Lua_IntoRewardFB(lua_State *L) {
    std::string strReward = g_pClua->GetStringArgument(1, "");
    int nZone = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_REWARD_FB, (WPARAM)&strReward, (LPARAM)&nZone);

    if (nZone) { // �ҵ���ظ�����Ϣ
        ::SendMessage(theApp.m_hGWnd, WM_CHOOSE_FB, (WPARAM)nZone, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_START_FB, (WPARAM)nZone, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_INTO_FB, NULL, NULL);
    }

    return 0;
}

// MH_��ȡ������������ʹ���
LuaGlue Lua_GetRewardCountToday(lua_State* L) {
    int nCountOfRewardToday = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_COUNT_REWARD_TODAY, (WPARAM)&nCountOfRewardToday, NULL);
    g_pClua->PushInt(nCountOfRewardToday);
    return 1;
}

// MH_��ȡ�������
LuaGlue Lua_GetAcceptReward(lua_State* L) {
    std::string strMap = "";
    ::SendMessage(theApp.m_hGWnd, WM_GET_ACCEPT_REWARD, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_����������
LuaGlue Lua_AcceptReward(lua_State* L) {
    std::string strReward = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_ACCEPT_REWARD, (WPARAM)&strReward, NULL);
    return 0;
}

// MH_�����������̽�
LuaGlue Lua_�����������̽�(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_�����������̽�, NULL, NULL);
    return 0;
}

// MH_���밤�ܸ���
LuaGlue Lua_IntoIdFB(lua_State *L) {
    int BrushZones = 0;
    BrushZones = g_pClua->GetIntArgument(1);
    if (BrushZones) {
        ::SendMessage(theApp.m_hGWnd, WM_CHOOSE_FB, (WPARAM)BrushZones, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_START_FB, (WPARAM)BrushZones, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_INTO_FB, NULL, NULL);
    }
    return 0;
}

// MH_��ȡ��������
LuaGlue Lua_GetExperienceLimit(lua_State* L) {
    int nRet = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_EXP_LIMIT, (WPARAM)&nRet, NULL);
    g_pClua->PushInt(nRet);
    return 1;
}

// MH_�ֿ���Ʒ����
LuaGlue Lua_GetWarehouseItemNum(lua_State *L) {
    std::string strItem = g_pClua->GetStringArgument(1, "");
    int nNum = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_WAREHOUSE_ITEM_NUM, (WPARAM)&nNum, (LPARAM)&strItem);
    g_pClua->PushInt(nNum);
    return 1;
}

// MH_�����ҵ�ׯ԰
LuaGlue Lua_IntoMyManor(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_INTO_MY_MANOR, NULL, NULL);
    return 0;
}

// MH_�뿪ׯ԰
LuaGlue Lua_LeaveManor(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_LEAVE_MANOR, NULL, NULL);
    return 0;
}

// MH_��������ľ��
LuaGlue Lua_UpgradeMushroom(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_UPGRADE_MUSHROOM, NULL, NULL);
    return 0;
}

// MH_���
LuaGlue Lua_MoveInventoryItem(lua_State *L) {
    std::string strItems = g_strServerExePath + "\\item.ini";
    CMy_Ini obj_ini(strItems.c_str());
    strItems = obj_ini.GetString("Item", "���");
    std::vector<std::string> vctItems = martin->split(strItems, "|");
    for (auto& v : vctItems) {
        std::list<BagItem> bagItem_list;
        ::SendMessage(theApp.m_hGWnd, WM_GETBAG, (WPARAM)&bagItem_list, NULL);
        for (auto p = bagItem_list.begin(); p != bagItem_list.end(); ++p) {
            std::string::size_type idx = v.find((*p).strName);
            if (idx != std::string::npos) {
                ::SendMessage(theApp.m_hGWnd, WM_MOVE_ITEM_IN_WAREHOUSE, (WPARAM)&(*p), NULL);
                Sleep(1000);
            }
        }
    }
    
    return 0;
}

// MH_����嶡������
LuaGlue Lua_����嶡������(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_����嶡������, NULL, NULL);
    return 0;
}

// MH_�Իظ�ҩ
LuaGlue Lua_EatMedicine(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_EAT_MEDICINE, NULL, NULL);
    return 0;
}

// MH_������Ʒ
LuaGlue Lua_PayItems(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_PAY_ITEMS, NULL, NULL);
    return 0;
}

// MH_��ȡ������Ʒ
LuaGlue Lua_GetGlowingArticle(lua_State *L) {
    //POINT_TARGET target;
    CNearObject oNearObject;
    ::SendMessage(theApp.m_hGWnd, WM_GET_GLOWING_ARTICLE, /*(WPARAM)&target*/(WPARAM)&oNearObject, NULL);
    std::vector<GlowingArticle> glowingArticle_vector = oNearObject.GetGlowingArticleInfo();
    if (glowingArticle_vector.empty()) {
        g_pClua->PushNumber(0.0);
        g_pClua->PushNumber(0.0);
        g_pClua->PushNumber(0.0);
        return 3;
    }

    int nSize = glowingArticle_vector.size();
    if (g_nCountOfGlowingArticle >= nSize) {
        g_nCountOfGlowingArticle = 0;
    }
    g_pClua->PushNumber(glowingArticle_vector[g_nCountOfGlowingArticle].fNpcPointX);
    g_pClua->PushNumber(glowingArticle_vector[g_nCountOfGlowingArticle].fNpcPointY);
    g_pClua->PushNumber(glowingArticle_vector[g_nCountOfGlowingArticle].fNpcPointZ);
    g_nCountOfGlowingArticle++;
    return 3;
}

// MH_��������è
LuaGlue Lua_��������è(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_��������è, NULL, NULL);
    return 0;
}
// MH_װ��������
LuaGlue Lua_װ��������(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_װ��������, NULL, NULL);
    return 0;
}

// MH_�ݴ�ʽ��ҩ
LuaGlue Lua_TakeMedicine(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_TAKE_MEDICINE, NULL, NULL);
    return 0;
}

// MH_��װ��
LuaGlue Lua_WearEquipment(lua_State *L) {
    std::string strEquipment = g_pClua->GetStringArgument(1, "");
    std::string strPlace = g_pClua->GetStringArgument(2, "");
    // 0:������1��ͷ����2������3���ز���4��������5���Ų�
    ::SendMessage(theApp.m_hGWnd, WM_WEAR_EQUIPMENT, (WPARAM)&strEquipment, (LPARAM)&strPlace);
    return 0;
}

// MH_��ȡ����ȼ�
LuaGlue Lua_GetRoleLevel(lua_State *L) {
    int nNum = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_ROLE_LEVEL, (WPARAM)&nNum, NULL);
    g_pClua->PushInt(nNum);
    return 1;
}

// MH_��׼������
LuaGlue Lua_PrecisionAcceptQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    QuestInfo questInfo;
    questInfo.strQuestName = strQuestName;
    questInfo.strNpcName = strNpcName;

    float fNpcPointX = static_cast<float>(g_pClua->GetNumberArgument(3));
    float fNpcPointY = static_cast<float>(g_pClua->GetNumberArgument(4));
    POINT_TARGET target;
    target.fPontX = fNpcPointX;
    target.fPontY = fNpcPointY;
    target.fPontZ = 0.0f;

    ::SendMessage(theApp.m_hGWnd, WM_PRECISION_ACCEPT_QUEST, (WPARAM)&questInfo, (LPARAM)&target);
    return 0;
}

// MH_��׼������
LuaGlue Lua_PrecisionCompleteQuest(lua_State *L) {
    std::string strQuestName = g_pClua->GetStringArgument(1, "");
    std::string strNpcName = g_pClua->GetStringArgument(2, "");
    QuestInfo questInfo;
    questInfo.strQuestName = strQuestName;
    questInfo.strNpcName = strNpcName;

    float fNpcPointX = static_cast<float>(g_pClua->GetNumberArgument(3));
    float fNpcPointY = static_cast<float>(g_pClua->GetNumberArgument(4));
    POINT_TARGET target;
    target.fPontX = fNpcPointX;
    target.fPontY = fNpcPointY;
    target.fPontZ = 0.0f;

    ::SendMessage(theApp.m_hGWnd, WM_PRECISION_COMPLETE_QUEST, (WPARAM)&questInfo, (LPARAM)&target);
    return 0;
}

// MH_������һ������
LuaGlue Lua_FirstAttackTrun(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_FIRST_ATTACK_TRUN, NULL, NULL);
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
        { "MH_�ɼ�Ŀ���", Lua_CollectTar },
        { "MH_����", Lua_Barbecue },
        { "MH_������Ʒ����", Lua_GetBagItemNum },
        { "MH_�Կ���", Lua_EatMeat },
        { "MH_ͨ��ʹ����Ʒ", Lua_CommonUseItems },
        { "MH_����ʽ�ɼ�", lua_FilterCollect },
        { "MH_����ظ�ҩ", lua_MadeHpMedicine },
        { "MH_������Ʒ", lua_BuySupply },
        { "MH_��ɱ����", lua_KillMonster },
        { "MH_��ȡ��ǹ��﷿��", lua_GetMonsterRoom }, //�ڲ��ӿ�
        { "MH_˲�Ƶ���ǹ�", Lua_GotoMonster }, //�ڲ��ӿ�
        { "MH_ת���ǹ�", Lua_TrunToMonster }, //�ڲ��ӿ�
        { "MH_�ߵ�Ŀ���", Lua_WalkToPoint },
        { "MH_������������", Lua_AcceptOfferARewardQuest },
        { "MH_��ȡ��ǰ����", Lua_GetCurrentReward },
        { "MH_�������͸���", Lua_IntoRewardFB },
        { "MH_��ȡ������������ʹ���", Lua_GetRewardCountToday },
        { "MH_��ȡ�������", Lua_GetAcceptReward },
        { "MH_����������", Lua_AcceptReward },
        { "MH_�����������̽�", Lua_�����������̽� },
        { "MH_���밤�ܸ���", Lua_IntoIdFB },
        { "MH_��ȡ��������", Lua_GetExperienceLimit },
        { "MH_�ֿ���Ʒ����", Lua_GetWarehouseItemNum },
        { "MH_�����ҵ�ׯ԰", Lua_IntoMyManor },
        { "MH_�뿪ׯ԰", Lua_LeaveManor },
        { "MH_��������ľ��", Lua_UpgradeMushroom },
        { "MH_���", Lua_MoveInventoryItem },
        { "MH_����嶡������", Lua_����嶡������ },
        { "MH_�Իظ�ҩ", Lua_EatMedicine },
        { "MH_������Ʒ", Lua_PayItems },
        { "MH_��ȡ������Ʒ", Lua_GetGlowingArticle },
        { "MH_��������è", Lua_��������è },
        { "MH_װ��������", Lua_װ�������� },
        { "MH_�ݴ�ʽ��ҩ", Lua_TakeMedicine },
        { "MH_��װ��", Lua_WearEquipment },
        { "MH_��ȡ����ȼ�", Lua_GetRoleLevel },
        { "MH_��׼������", Lua_PrecisionAcceptQuest },
        { "MH_��׼������", Lua_PrecisionCompleteQuest },
        { "MH_������һ������", Lua_FirstAttackTrun },
        { nullptr, NULL },
};

// ע�� ����
void AddLuaFunction() {
    for (int i = 0; ConsoleGlue[i].name; i++) {
        g_pClua->AddFunction(ConsoleGlue[i].name, ConsoleGlue[i].func);
    }
}

// Lua �¼�������
void FireEvent(const int nId, const char* args) {
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