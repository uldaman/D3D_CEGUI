#pragma once

#define WM_GET_CURRENT_QUEST            WM_USER + 2301  // 获取当前主线
#define WM_IS_QUEST_COMPLETE            WM_USER + 2302  // 判断任务是否已完成
#define WM_WHERE_ROLE                   WM_USER + 2303  // 判断当前人物在城镇还是副本, 0: 城镇  2: FB
#define WM_COMPLETE_QUEST               WM_USER + 2304  // 交任务
#define WM_GET_QUEST_TABLE              WM_USER + 2305  // 获取当前可接主线
#define WM_ACCEPT_QUEST                 WM_USER + 2306  // 接任务
#define WM_INTERACTIVE_QUEST            WM_USER + 2307  // 任务对话
#define WM_锻造晓风短剑                 WM_USER + 2308
#define WM_CITY_FLY                     WM_USER + 2309  // 城镇传送
#define WM_CHOOSE_FB                    WM_USER + 2310  // 选择副本
#define WM_START_FB                     WM_USER + 2311  // 开始副本
#define WM_INTO_FB                      WM_USER + 2312  // 进入副本
#define WM_UPDATA_BOSS                  WM_USER + 2313  // 获取 BOSS 名
#define WM_ROLE_ROOM                    WM_USER + 2314  // 获取当前房间
#define WM_BOSS_ROOM                    WM_USER + 2315  // 获取BOSS房间
#define WM_GET_ZONE                     WM_USER + 2316  // 获取当前副本
#define WM_GET_MAP                      WM_USER + 2317  // 获取当前地图
#define WM_GOTO_BOSS                    WM_USER + 2318  // 瞬移到BOSS
#define WM_BY_MAP                       WM_USER + 2319  // 副本过图
#define WM_TURN                         WM_USER + 2320  // 转向
#define WM_ATTACK_PACK                  WM_USER + 2321  // 攻击
#define WM_FORWARD                      WM_USER + 2322  // 前进
#define WM_STOP                         WM_USER + 2323  // 停止
#define WM_ATTACK                       WM_USER + 2324  // 攻击
#define WM_HAVE_WEAPON                  WM_USER + 2325  // 判断是否装备了武器
#define WM_WEAPON                       WM_USER + 2326  // 装备武器