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
#define WM_GET_HP_PER                   WM_USER + 2327  // 获取当前血比
#define WM_INVINCIBLE                   WM_USER + 2328  // 开启无敌
#define WM_UN_INVINCIBLE                WM_USER + 2329  // 关闭无敌
#define WM_TELEPORT                     WM_USER + 2330  // 瞬移到坐标
#define WM_GET_POINT                    WM_USER + 2331  // 获取当前坐标
#define WM_GO_LEFT                      WM_USER + 2332  // 左
#define WM_GO_RIGHT                     WM_USER + 2333  // 右
#define WM_GO_BACK                      WM_USER + 2334  // 后
#define WM_HAVE_MODE                    WM_USER + 2335  // 是否在菜单模式
#define WM_CHANGE_MODE                  WM_USER + 2336  // 切换菜单模式
#define WM_ROLL                         WM_USER + 2337  // 翻滚
#define WM_GET_ITEM_FORM_CRATES         WM_USER + 2338  // 补给箱取物
#define WM_GETCOLLECT                   WM_USER + 2339  // 获取采集标志位
#define WM_COLLECT                      WM_USER + 2340  // 采集
#define WM_GET_COLLECTS                 WM_USER + 2341  // 初始化采集信息
#define WM_BARBECUES                    WM_USER + 2342  // 烤肉
#define WM_GET_BAG_ITEM_NUM             WM_USER + 2343  // 獲取背包物品數量
#define WM_EAT_MEAT                     WM_USER + 2344  // 吃烤肉
#define WM_USE_ITEM                     WM_USER + 2345  // 通用使用物品