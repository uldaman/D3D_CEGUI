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
#define WM_PRECISION_ACCEPT_QUEST       WM_USER + 2346  // 精准接任务, 通过比对 NPC 的坐标
#define WM_MADE_HP_MEDICINE             WM_USER + 2347  // 制作回复药
#define WM_BUY_SUPPLY                   WM_USER + 2348  // 补给物品
#define WM_KILL_MONSTER                 WM_USER + 2349  // 击杀怪物
#define WM_GET_MONSTER_ROOM             WM_USER + 2350  // 获取标记怪物房间
#define WM_GOTO_MONSTER                 WM_USER + 2351  // 瞬移到标记怪
#define WM_TURN_TO_MONSTER              WM_USER + 2352  // 转向标记怪
#define WM_TURN_TO_POINT                WM_USER + 2353  // 转向坐标点
#define WM_ACCEPT_OFFER_A_REWARD        WM_USER + 2354  // 悬赏任务
#define WM_GET_CURRENT_REWARD           WM_USER + 2355  // 获取当前悬赏任务
#define WM_GET_REWARD_FB                WM_USER + 2356  // 获取悬赏副本
#define WM_GET_COUNT_REWARD_TODAY       WM_USER + 2357  // 获取今日已完成悬赏次数
#define WM_GET_ACCEPT_REWARD            WM_USER + 2358  // 获取可交悬赏
#define WM_ACCEPT_REWARD                WM_USER + 2359  // 交悬赏
#define WM_升级到荆棘短剑               WM_USER + 2360  // 升级到荆棘短剑
#define WM_GET_EXP_LIMIT                WM_USER + 2361  // 获取经验上限
#define WM_GET_WAREHOUSE_ITEM_NUM       WM_USER + 2362  // 仓库物品数量
#define WM_INTO_MY_MANOR                WM_USER + 2363  // 进入我的庄园
#define WM_LEAVE_MANOR                  WM_USER + 2364  // 离开庄园
#define WM_UPGRADE_MUSHROOM             WM_USER + 2365  // 升级育菇木床
#define WM_MOVE_ITEM_IN_WAREHOUSE       WM_USER + 2366  // 存仓
#define WM_GETBAG                       WM_USER + 2367  // 初始化背包
#define WM_锻造村丁斗气锤               WM_USER + 2368
#define WM_EAT_MEDICINE                 WM_USER + 2369  // 无延迟吃回复药
#define WM_PAY_ITEMS                    WM_USER + 2370  // 交纳物品
#define WM_GET_GLOWING_ARTICLE          WM_USER + 2371  // 获取发光物品
#define WM_设置随行猫                   WM_USER + 2372
#define WM_装备斗气锤                   WM_USER + 2373
#define WM_TAKE_MEDICINE                WM_USER + 2374  // 容错式喝药
#define WM_WEAR_EQUIPMENT               WM_USER + 2375  // 穿装备
#define WM_GET_ROLE_LEVEL               WM_USER + 2376  // 获取人物等级
#define WM_PRECISION_COMPLETE_QUEST     WM_USER + 2377  // 精准交任务, 通过比对 NPC 的坐标
#define WM_FIRST_ATTACK_TRUN            WM_USER + 2378  // 开启第一击面向
#define WM_LOGIN                        WM_USER + 2379  // 登录游戏
#define WM_NEW_ROLE                     WM_USER + 2380  // 新建角色
#define WM_COUNTS_OF_ROLES              WM_USER + 2381  // 当前角色数量
#define WM_ENTER_CHANNEL                WM_USER + 2382  // 确认频道
#define WM_IS_ONLINE                    WM_USER + 2383  // 是否在线
#define WM_IS_LOADING                   WM_USER + 2384  // 是否过图
//#define WM_INIT_ROLE_LIST               WM_USER + 2385  // 初始化角色列表
#define WM_IS_SELECT                    WM_USER + 2386  // 是否在选择角色
#define WM_领取成长武器兑换券           WM_USER + 2387  // 领取成长武器兑换券
#define WM_兑换初心之剑                 WM_USER + 2388  // 兑换初心之剑
#define WM_兑换进阶之剑                 WM_USER + 2389  // 兑换进阶之剑