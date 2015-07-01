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
    std::string strPos = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_STOP, (WPARAM)&strPos, NULL);
    return 0;
}

//MH_获取当前血比
LuaGlue Lua_GetHpPer(lua_State *L) {
    float fHpPer = 1.0f;
    ::SendMessage(theApp.m_hGWnd, WM_GET_HP_PER, (WPARAM)&fHpPer, NULL);
    g_pClua->PushNumber(static_cast<double>(fHpPer));
    return 1;
}

//MH_开启无敌
LuaGlue Lua_Invincible(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_INVINCIBLE, NULL, NULL);
    return 0;
}

//MH_关闭无敌
LuaGlue Lua_UnInvincible(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_UN_INVINCIBLE, NULL, NULL);
    return 0;
}

//MH_瞬移到坐标
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

//MH_获取当前坐标", Lua_GetPoint
LuaGlue Lua_GetPoint(lua_State *L) {
    POINT_TARGET target;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&target, NULL);
    g_pClua->PushNumber(target.fPontX);
    g_pClua->PushNumber(target.fPontY);
    g_pClua->PushNumber(target.fPontZ);
    return 3;
}

//MH_左移
LuaGlue Lua_GoLeft(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GO_LEFT, NULL, NULL);
    return 0;
}

//MH_右移
LuaGlue Lua_GoRight(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GO_RIGHT, NULL, NULL);
    return 0;
}

//MH_后退
LuaGlue Lua_GoBack(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GO_BACK, NULL, NULL);
    return 0;
}

//MH_拿起武器
LuaGlue Lua_TakeUpWeapons(lua_State *L) {
    // 先判断是否已经拿起了武器, 如果没有拿起, 则拿起武器
    int nWeapon;
    ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);

    while (nWeapon == 0) {
        // 判断是否在开关状态
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

//MH_收起武器
LuaGlue Lua_CollectWeapons(lua_State *L) {
    // 先判断是否已经拿起了武器, 如果拿起, 则收起
    int nWeapon;
    ::SendMessage(theApp.m_hGWnd, WM_HAVE_WEAPON, (WPARAM)&nWeapon, NULL);

    while (nWeapon != 0) {
        // 判断是否在开关状态
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

//MH_翻滚
LuaGlue Lua_Roll(lua_State *L) {
    // 先收起武器
    Lua_CollectWeapons(L);
    Sleep(500);
    ::SendMessage(theApp.m_hGWnd, WM_ROLL, NULL, NULL);
    return 0;
}

// MH_补给箱取物
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

//MH_采集所有物品
LuaGlue Lua_CollectAll(lua_State *L) {
    // 记录下当前坐标, 用于采集完返回
    POINT_TARGET Current_Point;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    ::SendMessage(theApp.m_hGWnd, WM_GET_COLLECTS, NULL, NULL); // 初始化采集信息

    for (auto& v : CMaterial::m_material_list) {
        // 先判断下是不是在FB里
        int nWhere;
        ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
        if (nWhere != 2 || g_isWork == false) {
            // 判断是否在庄园
            std::string strMap;
            ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
            if (strMap != "庄园") {
                goto MaterialEnd; // 如果不在庄园 则跳出
            }
        }

        //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- %f : %f : %f",
        //    v.strName.c_str(), v.nID, v.nKey, v.fPointX, v.fPointY, v.fPointZ);

        POINT_TARGET _Point = { v.fPointX, v.fPointY, v.fPointZ };
        int nID = v.nID;

        // 瞬移
        ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&_Point, NULL);
        Sleep(1000);

        // 采集
        for (int i = 0; i < 3; i++) {
            ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
            if (nWhere != 2 || g_isWork == false) {
                // 判断是否在庄园
                std::string strMap;
                ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
                if (strMap != "庄园") {
                    goto MaterialEnd; // 如果不在庄园 则跳出
                }
            }

            ::SendMessage(theApp.m_hGWnd, WM_COLLECT, (WPARAM)&nID, NULL);
            Sleep(500);

            // 判断是否在采集中, 是的话, 接着采集, 否则开始下一个
            BOOL bCollect = FALSE;
            ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
            //martin->Debug(TEXT("采集标识: %d"), bCollect);

            while (bCollect) { // 说明在采集中
                Sleep(1000);
                ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
            }

            Sleep(500);
        }

        Sleep(500);
    }

MaterialEnd:
    // 返回开始处
    ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&Current_Point, NULL);
    return 0;
}

// MH_采集目标点
LuaGlue Lua_CollectTar(lua_State *L) {
    float dPointX = static_cast<float>(g_pClua->GetNumberArgument(1));
    float dPointY = static_cast<float>(g_pClua->GetNumberArgument(2));

    // 记录下当前坐标, 用于采集完返回
    POINT_TARGET Current_Point;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    ::SendMessage(theApp.m_hGWnd, WM_GET_COLLECTS, NULL, NULL); // 初始化采集信息

    for (auto& v : CMaterial::m_material_list) {
        // 先判断下是不是在FB里
        int nWhere;
        ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
        if (nWhere != 2 || g_isWork == false) {
            // 再判断是否在庄园
            std::string strMap;
            ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
            if (strMap != "庄园") {
                goto MaterialEnd; // 如果不在庄园 则跳出
            }
        }

        //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- %f : %f : %f",
        //    v.strName.c_str(), v.nID, v.nKey, v.fPointX, v.fPointY, v.fPointZ);

        if (martin->Compare_Coord(dPointX, dPointY, v.fPointX, v.fPointY) < 5.0f) {
            POINT_TARGET _Point = { v.fPointX, v.fPointY, v.fPointZ };
            int nID = v.nID;

            // 瞬移
            ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&_Point, NULL);
            Sleep(1000);

            // 采集
            for (int i = 0; i < 3; i++) {
                ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
                if (nWhere != 2 || g_isWork == false) {
                    // 判断是否在庄园
                    std::string strMap;
                    ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
                    if (strMap != "庄园") {
                        goto MaterialEnd; // 如果不在庄园 则跳出
                    }
                }

                ::SendMessage(theApp.m_hGWnd, WM_COLLECT, (WPARAM)&nID, NULL);
                Sleep(500);

                // 判断是否在采集中, 是的话, 接着采集, 否则开始下一个
                BOOL bCollect = FALSE;
                ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                //martin->Debug(TEXT("采集标识: %d"), bCollect);

                while (bCollect) { // 说明在采集中
                    Sleep(1000);
                    ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                }

                Sleep(500);
            }
            goto MaterialEnd;
        }
    }

MaterialEnd:
    // 返回开始处
    ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&Current_Point, NULL);
    return 0;
}

// MH_烤肉
LuaGlue Lua_Barbecue(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_BARBECUES, NULL, NULL);
    return 0;
}

// MH_背包物品數量
LuaGlue Lua_GetBagItemNum(lua_State *L) {
    std::string strItem = g_pClua->GetStringArgument(1, "");
    int nNum = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_BAG_ITEM_NUM, (WPARAM)&nNum, (LPARAM)&strItem);
    g_pClua->PushInt(nNum);
    return 1;
}

// MH_吃烤肉
LuaGlue Lua_EatMeat(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_EAT_MEAT, NULL, NULL);
    return 0;
}

// MH_通用使用物品
LuaGlue Lua_CommonUseItems(lua_State *L) {
    std::string strItem = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_USE_ITEM, (WPARAM)&strItem, NULL);
    return 0;
}

// MH_过滤式采集
LuaGlue lua_FilterCollect(lua_State *L) {
    std::string strFilter = g_pClua->GetStringArgument(1, "");

    // 记录下当前坐标, 用于采集完返回
    POINT_TARGET Current_Point;
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    ::SendMessage(theApp.m_hGWnd, WM_GET_COLLECTS, NULL, NULL); // 初始化采集信息

    for (auto& v : CMaterial::m_material_list) {
        // 先判断下是不是在FB里
        int nWhere;
        ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
        if (nWhere != 2 || g_isWork == false) {
            // 判断是否在庄园
            std::string strMap;
            ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
            if (strMap != "庄园") {
                goto MaterialEnd; // 如果不在庄园 则跳出
            }
        }

        //martin->Debug("%s -- ID: 0x%X -- Key: 0x%X -- %f : %f : %f",
        //    v.strName.c_str(), v.nID, v.nKey, v.fPointX, v.fPointY, v.fPointZ);
        // 类别 1:矿（挖矿工具）,2:药草,3:昆虫（捕虫工具）,5:蘑菇,6:蜂蜜,7:小石头,8:粪便,0xA:尸体,0xC:骨头,0x11:网
        std::string::size_type idx = v.strType.find(strFilter);
        if (idx != std::string::npos) { // 找到名称
            POINT_TARGET _Point = { v.fPointX, v.fPointY, v.fPointZ };
            int nID = v.nID;

            // 瞬移
            ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&_Point, NULL);
            Sleep(1000);

            // 采集
            for (int i = 0; i < 3; i++) {
                ::SendMessage(theApp.m_hGWnd, WM_WHERE_ROLE, (WPARAM)&nWhere, NULL);
                if (nWhere != 2 || g_isWork == false) {
                    // 判断是否在庄园
                    std::string strMap;
                    ::SendMessage(theApp.m_hGWnd, WM_GET_MAP, (WPARAM)&strMap, NULL);
                    if (strMap != "庄园") {
                        goto MaterialEnd; // 如果不在庄园 则跳出
                    }
                }

                ::SendMessage(theApp.m_hGWnd, WM_COLLECT, (WPARAM)&nID, NULL);
                Sleep(500);

                // 判断是否在采集中, 是的话, 接着采集, 否则开始下一个
                BOOL bCollect = FALSE;
                ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                //martin->Debug(TEXT("采集标识: %d"), bCollect);

                while (bCollect) { // 说明在采集中
                    Sleep(1000);
                    ::SendMessage(theApp.m_hGWnd, WM_GETCOLLECT, (WPARAM)&bCollect, NULL);
                } // 当前人物已空闲

                Sleep(500);
            } // 同一个目标点已经采集三次
        } // 一轮采集结束
        Sleep(500);
    }

MaterialEnd:
    // 返回开始处
    ::SendMessage(theApp.m_hGWnd, WM_TELEPORT, (WPARAM)&Current_Point, NULL);
    return 0;
}

// MH_制造回复药
LuaGlue lua_MadeHpMedicine(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_MADE_HP_MEDICINE, NULL, NULL);
    return 0;
}

// MH_补给物品
LuaGlue lua_BuySupply(lua_State *L) {
    SupplyInfo supplyInfo;
    supplyInfo.strSupplyName = g_pClua->GetStringArgument(1, "");
    supplyInfo.strNpcName = g_pClua->GetStringArgument(2, "");
    supplyInfo.strTypeName = g_pClua->GetStringArgument(3, "");

    int nNumOfSupply = g_pClua->GetIntArgument(4);

    ::SendMessage(theApp.m_hGWnd, WM_BUY_SUPPLY, (WPARAM)&supplyInfo, (LPARAM)&nNumOfSupply);
    return 0;
}

// MH_击杀怪物
LuaGlue lua_KillMonster(lua_State *L) {
    std::string strMonster = g_pClua->GetStringArgument(1, "");
    int nNumKill = g_pClua->GetIntArgument(2);
    for (int i = 0; i < nNumKill; i++) {
        ::SendMessage(theApp.m_hGWnd, WM_KILL_MONSTER, (WPARAM)&strMonster, NULL);
#define EVENT_KILL_MONSTER 1000 //击杀标记怪
        FireEvent(EVENT_KILL_MONSTER, strMonster.c_str());
        Sleep(1000);
    }

    return 0;
}

// MH_获取标记怪物房间
LuaGlue lua_GetMonsterRoom(lua_State *L) {
    int nMonsterRomm = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_MONSTER_ROOM, (WPARAM)&nMonsterRomm, NULL);
    g_pClua->PushInt(nMonsterRomm);
    return 1;
}

// MH_瞬移到标记怪
LuaGlue Lua_GotoMonster(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_GOTO_MONSTER, NULL, NULL);
    return 0;
}

// MH_转向标记怪
LuaGlue Lua_TrunToMonster(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_TURN_TO_MONSTER, NULL, NULL);
    return 0;
}

// MH_走到目标点
LuaGlue Lua_WalkToPoint(lua_State *L) {
    POINT_TARGET Current_Point; // 当前坐标
    ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);

    float fTargetPointX = static_cast<float>(g_pClua->GetNumberArgument(1));
    float fTargetPointY = static_cast<float>(g_pClua->GetNumberArgument(2));

    BOOL bIsWalk = FALSE;
    if (martin->Compare_Coord(fTargetPointX, fTargetPointY, Current_Point.fPontX, Current_Point.fPontY) > 3.0f) {
        // 转向
        ::SendMessage(theApp.m_hGWnd, WM_TURN_TO_POINT, (WPARAM)&fTargetPointX, (LPARAM)&fTargetPointY);
        // 前进
        Lua_Forward(L);
        bIsWalk = TRUE;
    }

    while (g_isWork ) {
        ::SendMessage(theApp.m_hGWnd, WM_GET_POINT, (WPARAM)&Current_Point, NULL);
        if (martin->Compare_Coord(fTargetPointX, fTargetPointY, Current_Point.fPontX, Current_Point.fPontY) < 3.0f) {
            if (bIsWalk) {
                g_pClua->PushString("前进");
                Lua_Stop(L);
            }
            break;
        }
        Sleep(100);
    }

    return 0;
}

// MH_接受悬赏任务
LuaGlue Lua_AcceptOfferARewardQuest(lua_State *L) {
    std::string strLevel = g_pClua->GetStringArgument(1, "");
    std::string strType = g_pClua->GetStringArgument(2, "");
    ::SendMessage(theApp.m_hGWnd, WM_ACCEPT_OFFER_A_REWARD, (WPARAM)&strLevel, (LPARAM)&strType);
    return 0;
}

// MH_获取当前悬赏
LuaGlue Lua_GetCurrentReward(lua_State* L) {
    std::string strMap = "";
    ::SendMessage(theApp.m_hGWnd, WM_GET_CURRENT_REWARD, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_进入悬赏副本
LuaGlue Lua_IntoRewardFB(lua_State *L) {
    std::string strReward = g_pClua->GetStringArgument(1, "");
    int nZone = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_REWARD_FB, (WPARAM)&strReward, (LPARAM)&nZone);

    if (nZone) { // 找到相关副本信息
        ::SendMessage(theApp.m_hGWnd, WM_CHOOSE_FB, (WPARAM)nZone, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_START_FB, (WPARAM)nZone, NULL);
        Sleep(1500);
        ::SendMessage(theApp.m_hGWnd, WM_INTO_FB, NULL, NULL);
    }

    return 0;
}

// MH_获取今日已完成悬赏次数
LuaGlue Lua_GetRewardCountToday(lua_State* L) {
    int nCountOfRewardToday = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_COUNT_REWARD_TODAY, (WPARAM)&nCountOfRewardToday, NULL);
    g_pClua->PushInt(nCountOfRewardToday);
    return 1;
}

// MH_获取完成悬赏
LuaGlue Lua_GetAcceptReward(lua_State* L) {
    std::string strMap = "";
    ::SendMessage(theApp.m_hGWnd, WM_GET_ACCEPT_REWARD, (WPARAM)&strMap, NULL);
    g_pClua->PushString(strMap.c_str());
    return 1;
}

// MH_交悬赏任务
LuaGlue Lua_AcceptReward(lua_State* L) {
    std::string strReward = g_pClua->GetStringArgument(1, "");
    ::SendMessage(theApp.m_hGWnd, WM_ACCEPT_REWARD, (WPARAM)&strReward, NULL);
    return 0;
}

// MH_升级到荆棘短剑
LuaGlue Lua_升级到荆棘短剑(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_升级到荆棘短剑, NULL, NULL);
    return 0;
}

// MH_进入挨弟副本
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

// MH_获取经验上限
LuaGlue Lua_GetExperienceLimit(lua_State* L) {
    int nRet = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_EXP_LIMIT, (WPARAM)&nRet, NULL);
    g_pClua->PushInt(nRet);
    return 1;
}

// MH_仓库物品数量
LuaGlue Lua_GetWarehouseItemNum(lua_State *L) {
    std::string strItem = g_pClua->GetStringArgument(1, "");
    int nNum = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_WAREHOUSE_ITEM_NUM, (WPARAM)&nNum, (LPARAM)&strItem);
    g_pClua->PushInt(nNum);
    return 1;
}

// MH_进入我的庄园
LuaGlue Lua_IntoMyManor(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_INTO_MY_MANOR, NULL, NULL);
    return 0;
}

// MH_离开庄园
LuaGlue Lua_LeaveManor(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_LEAVE_MANOR, NULL, NULL);
    return 0;
}

// MH_升级育菇木床
LuaGlue Lua_UpgradeMushroom(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_UPGRADE_MUSHROOM, NULL, NULL);
    return 0;
}

// MH_存仓
LuaGlue Lua_MoveInventoryItem(lua_State *L) {
    std::string strItems = g_strServerExePath + "\\item.ini";
    CMy_Ini obj_ini(strItems.c_str());
    strItems = obj_ini.GetString("Item", "存仓");
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

// MH_锻造村丁斗气锤
LuaGlue Lua_锻造村丁斗气锤(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_锻造村丁斗气锤, NULL, NULL);
    return 0;
}

// MH_吃回复药
LuaGlue Lua_EatMedicine(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_EAT_MEDICINE, NULL, NULL);
    return 0;
}

// MH_交纳物品
LuaGlue Lua_PayItems(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_PAY_ITEMS, NULL, NULL);
    return 0;
}

// MH_获取发光物品
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

// MH_设置随行猫
LuaGlue Lua_设置随行猫(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_设置随行猫, NULL, NULL);
    return 0;
}
// MH_装备斗气锤
LuaGlue Lua_装备斗气锤(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_装备斗气锤, NULL, NULL);
    return 0;
}

// MH_容错式喝药
LuaGlue Lua_TakeMedicine(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_TAKE_MEDICINE, NULL, NULL);
    return 0;
}

// MH_穿装备
LuaGlue Lua_WearEquipment(lua_State *L) {
    std::string strEquipment = g_pClua->GetStringArgument(1, "");
    std::string strPlace = g_pClua->GetStringArgument(2, "");
    // 0:武器，1：头部，2：手腕，3：胸部，4：腰部，5：脚部
    ::SendMessage(theApp.m_hGWnd, WM_WEAR_EQUIPMENT, (WPARAM)&strEquipment, (LPARAM)&strPlace);
    return 0;
}

// MH_获取人物等级
LuaGlue Lua_GetRoleLevel(lua_State *L) {
    int nNum = 0;
    ::SendMessage(theApp.m_hGWnd, WM_GET_ROLE_LEVEL, (WPARAM)&nNum, NULL);
    g_pClua->PushInt(nNum);
    return 1;
}

// MH_精准接任务
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

// MH_精准交任务
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

// MH_开启第一击面向
LuaGlue Lua_FirstAttackTrun(lua_State *L) {
    ::SendMessage(theApp.m_hGWnd, WM_FIRST_ATTACK_TRUN, NULL, NULL);
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
        { "MH_获取当前血比", Lua_GetHpPer },
        { "MH_开启无敌", Lua_Invincible },
        { "MH_关闭无敌", Lua_UnInvincible },
        { "MH_瞬移到坐标", Lua_TeleportToPoint },
        { "MH_获取当前坐标", Lua_GetPoint },
        { "MH_左移", Lua_GoLeft },
        { "MH_右移", Lua_GoRight },
        { "MH_后退", Lua_GoBack },
        { "MH_拿起武器", Lua_TakeUpWeapons },
        { "MH_收起武器", Lua_CollectWeapons },
        { "MH_翻滚", Lua_Roll },
        { "MH_补给箱取物", Lua_GetItemFormCrates },
        { "MH_采集所有物品", Lua_CollectAll },
        { "MH_采集目标点", Lua_CollectTar },
        { "MH_烤肉", Lua_Barbecue },
        { "MH_背包物品数量", Lua_GetBagItemNum },
        { "MH_吃烤肉", Lua_EatMeat },
        { "MH_通用使用物品", Lua_CommonUseItems },
        { "MH_过滤式采集", lua_FilterCollect },
        { "MH_制造回复药", lua_MadeHpMedicine },
        { "MH_补给物品", lua_BuySupply },
        { "MH_击杀怪物", lua_KillMonster },
        { "MH_获取标记怪物房间", lua_GetMonsterRoom }, //内部接口
        { "MH_瞬移到标记怪", Lua_GotoMonster }, //内部接口
        { "MH_转向标记怪", Lua_TrunToMonster }, //内部接口
        { "MH_走到目标点", Lua_WalkToPoint },
        { "MH_接受悬赏任务", Lua_AcceptOfferARewardQuest },
        { "MH_获取当前悬赏", Lua_GetCurrentReward },
        { "MH_进入悬赏副本", Lua_IntoRewardFB },
        { "MH_获取今日已完成悬赏次数", Lua_GetRewardCountToday },
        { "MH_获取完成悬赏", Lua_GetAcceptReward },
        { "MH_交悬赏任务", Lua_AcceptReward },
        { "MH_升级到荆棘短剑", Lua_升级到荆棘短剑 },
        { "MH_进入挨弟副本", Lua_IntoIdFB },
        { "MH_获取经验上限", Lua_GetExperienceLimit },
        { "MH_仓库物品数量", Lua_GetWarehouseItemNum },
        { "MH_进入我的庄园", Lua_IntoMyManor },
        { "MH_离开庄园", Lua_LeaveManor },
        { "MH_升级育菇木床", Lua_UpgradeMushroom },
        { "MH_存仓", Lua_MoveInventoryItem },
        { "MH_锻造村丁斗气锤", Lua_锻造村丁斗气锤 },
        { "MH_吃回复药", Lua_EatMedicine },
        { "MH_交纳物品", Lua_PayItems },
        { "MH_获取发光物品", Lua_GetGlowingArticle },
        { "MH_设置随行猫", Lua_设置随行猫 },
        { "MH_装备斗气锤", Lua_装备斗气锤 },
        { "MH_容错式喝药", Lua_TakeMedicine },
        { "MH_穿装备", Lua_WearEquipment },
        { "MH_获取人物等级", Lua_GetRoleLevel },
        { "MH_精准接任务", Lua_PrecisionAcceptQuest },
        { "MH_精准交任务", Lua_PrecisionCompleteQuest },
        { "MH_开启第一击面向", Lua_FirstAttackTrun },
        { nullptr, NULL },
};

// 注册 函数
void AddLuaFunction() {
    for (int i = 0; ConsoleGlue[i].name; i++) {
        g_pClua->AddFunction(ConsoleGlue[i].name, ConsoleGlue[i].func);
    }
}

// Lua 事件触发器
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