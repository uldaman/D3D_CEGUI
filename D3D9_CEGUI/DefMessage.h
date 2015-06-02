#pragma once

#define WM_GET_CURRENT_QUEST            WM_USER + 2301  // 获取当前主线
#define WM_IS_QUEST_COMPLETE            WM_USER + 2302  // 判断任务是否已完成
#define WM_WHERE_ROLE                   WM_USER + 2303  // 判断当前人物在城镇还是副本, 0: 城镇  2: FB
#define WM_COMPLETE_QUEST               WM_USER + 2304  // 交任务
#define WM_GET_QUEST_TABLE              WM_USER + 2305  // 获取当前可接主线
#define WM_ACCEPT_QUEST                 WM_USER + 2306  // 接任务
#define WM_INTERACTIVE_QUEST            WM_USER + 2307  // 任务对话