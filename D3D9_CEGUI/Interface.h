#pragma once
#include <windows.h>
/////////////////////////////////////////////////////////////////////////
// 文件名:   Interface.h
// 说明:     用来处理HOOK游戏窗口过程后的自定义消息
// 创建时间: 2015/06/10 20:36
//
// 更新日志: 
/////////////////////////////////////////////////////////////////////////

void MesageMapping(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void On_GetCurrentQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前主线
void On_GetQuestTable(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取可接主线
void On_IsQuestComplete(HWND hDlg, WPARAM wParam, LPARAM lParam); // 判断任务是否完成
void On_WhereRole(HWND hDlg, WPARAM wParam, LPARAM lParam); // 判断当前人物在城镇还是副本, 0: 城镇  2: FB
void On_CompleteQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // 交任务
void On_AcceptQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // 接任务
void On_InteractiveQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // 任务对话
void On_锻造晓风短剑(HWND hDlg, WPARAM wParam, LPARAM lParam); // 锻造晓风短剑
void On_MadeHpMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam); // 制造回复药
void On_CityFly(HWND hDlg, WPARAM wParam, LPARAM lParam); // 城镇传送
void On_ChooseFB(HWND hDlg, WPARAM wParam, LPARAM lParam); // 选择副本
void On_StartFB(HWND hDlg, WPARAM wParam, LPARAM lParam); // 开始副本
void On_IntoFB(HWND hDlg, WPARAM wParam, LPARAM lParam); // 进入副本
void On_UpdataBoss(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取 BOSS 名
void On_RoleRoom(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前房间
void On_BossRoom(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取BOSS房间
void On_GetZone(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前副本
void On_GetMap(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前地图
void On_GotoBoss(HWND hDlg, WPARAM wParam, LPARAM lParam); // 瞬移到BOSS
void On_ByMap(HWND hDlg, WPARAM wParam, LPARAM lParam); // 副本过图
void On_Turn(HWND hDlg, WPARAM wParam, LPARAM lParam); // 转向
void On_AttackPack(HWND hDlg, WPARAM wParam, LPARAM lParam); // 攻击
void On_Forward(HWND hDlg, WPARAM wParam, LPARAM lParam); // 前进
void On_Stop(HWND hDlg, WPARAM wParam, LPARAM lParam); // 前进
void On_Attack(HWND hDlg, WPARAM wParam, LPARAM lParam); // 攻击
void On_HaveWeapon(HWND hDlg, WPARAM wParam, LPARAM lParam); // 判断是否装备了武器
void On_Weapon(HWND hDlg, WPARAM wParam, LPARAM lParam); // 装备武器
void On_GetHpPer(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前血比
void On_Invincible(HWND hDlg, WPARAM wParam, LPARAM lParam); // 开启无敌
void On_UnInvincible(HWND hDlg, WPARAM wParam, LPARAM lParam); // 关闭无敌
void On_Teleport(HWND hDlg, WPARAM wParam, LPARAM lParam); // 瞬移到坐标
void On_GetPoint(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前坐标
void On_GoLeft(HWND hDlg, WPARAM wParam, LPARAM lParam); // 左移
void On_GoRight(HWND hDlg, WPARAM wParam, LPARAM lParam); // 右移
void On_GoBack(HWND hDlg, WPARAM wParam, LPARAM lParam); // 后退
void On_HaveMode(HWND hDlg, WPARAM wParam, LPARAM lParam); // 是否在菜单模式
void On_ChangeMode(HWND hDlg, WPARAM wParam, LPARAM lParam); // 切换菜单模式
void On_Roll(HWND hDlg, WPARAM wParam, LPARAM lParam); // 翻滚
void On_GetItemFormCrates(HWND hDlg, WPARAM wParam, LPARAM lParam); // 补给箱取物
void On_GetCollect(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取采集标志位
void On_Collect(HWND hDlg, WPARAM wParam, LPARAM lParam); // 采集
void On_GetCollects(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取采集物信息
void On_Barbecues(HWND hDlg, WPARAM wParam, LPARAM lParam); // 烤肉
void On_GetBagItemNum(HWND hDlg, WPARAM wParam, LPARAM lParam); // 獲取背包物品數量
void On_EatMeat(HWND hDlg, WPARAM wParam, LPARAM lParam); // 吃烤肉
void On_CommonUseItems(HWND hDlg, WPARAM wParam, LPARAM lParam); // 通用使用物品
void On_PrecisionAcceptQuest(HWND hDlg, WPARAM wParam, LPARAM lParam); // 精准接任务, 通过比对 NPC 的坐标
void On_BuySupply(HWND hDlg, WPARAM wParam, LPARAM lParam); // 补给物品
void On_KillMonster(HWND hDlg, WPARAM wParam, LPARAM lParam); // 击杀物品
void On_GetMonsterRoom(HWND hDlg, WPARAM wParam, LPARAM lParam); // 击杀物品
void On_GotoMonster(HWND hDlg, WPARAM wParam, LPARAM lParam); // 瞬移到标记怪
void On_TurnToMonster(HWND hDlg, WPARAM wParam, LPARAM lParam); // 转向到标记怪
void On_TurnToPoint(HWND hDlg, WPARAM wParam, LPARAM lParam); // 转向到标记怪
void On_AcceptOfferAReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // 接受悬赏任务
void On_GetCurrentReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前悬赏任务
void On_GetRewardBrushZone(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取悬赏副本
void On_GetCountRewardToday(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取今日已完成悬赏次数
void On_GetAcceptReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取可交悬赏
void On_AcceptReward(HWND hDlg, WPARAM wParam, LPARAM lParam); // 交悬赏
void On_升级到荆棘短剑(HWND hDlg, WPARAM wParam, LPARAM lParam); // 升级到荆棘短剑
void On_GetExperienceLimit(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取经验上限
void On_GetWarehouseItemNum(HWND hDlg, WPARAM wParam, LPARAM lParam); // 獲取仓库物品數量
void On_IntoMyManor(HWND hDlg, WPARAM wParam, LPARAM lParam); // 进入我的庄园
void On_LeaveManor(HWND hDlg, WPARAM wParam, LPARAM lParam); // 离开庄园
void On_UpgradeMushroom(HWND hDlg, WPARAM wParam, LPARAM lParam); // 升级育菇木床
void On_MoveInventoryItem(HWND hDlg, WPARAM wParam, LPARAM lParam); // 存仓
void On_GetBag(HWND hDlg, WPARAM wParam, LPARAM lParam); // 背包
void On_锻造村丁斗气锤(HWND hDlg, WPARAM wParam, LPARAM lParam); // 锻造村丁斗气锤
void On_EatMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam); // 吃回复药
void On_PayItems(HWND hDlg, WPARAM wParam, LPARAM lParam); // 交纳物品
void On_GetGlowingArticle(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取发光物品
void On_设置随行猫(HWND hDlg, WPARAM wParam, LPARAM lParam);
void On_装备斗气锤(HWND hDlg, WPARAM wParam, LPARAM lParam);
void On_TakeMedicine(HWND hDlg, WPARAM wParam, LPARAM lParam);  // 容错式喝药
void On_WearEquipment(HWND hDlg, WPARAM wParam, LPARAM lParam);  // 穿装备
void On_GetRoleLevel(HWND hDlg, WPARAM wParam, LPARAM lParam);  // 获取人物等级
void On_PrecisionCompleteQuest(HWND hDlg, WPARAM wParam, LPARAM lParam);  // 精准交任务, 通过比对 NPC 的坐标
void On_FirstAttackTrun(HWND hDlg, WPARAM wParam, LPARAM lParam);  // 开启第一击面向
void On_Login(HWND hDlg, WPARAM wParam, LPARAM lParam); // 开始游戏(非进入游戏, 开始游戏后还要选择频道)
void On_NewRole(HWND hDlg, WPARAM wParam, LPARAM lParam); // 新建角色
void On_CountsOfRoles(HWND hDlg, WPARAM wParam, LPARAM lParam); // 获取当前角色数量
void On_EnterChannel(HWND hDlg, WPARAM wParam, LPARAM lParam); // 确认频道, 确认后就进入游戏了
void On_IsOnLine(HWND hDlg, WPARAM wParam, LPARAM lParam); // 是否在线
void On_IsLoading(HWND hDlg, WPARAM wParam, LPARAM lParam); // 是否过图
//void On_InitRoleList(HWND hDlg, WPARAM wParam, LPARAM lParam); // 初始化列表
void On_IsSelect(HWND hDlg, WPARAM wParam, LPARAM lParam); // 是否在选择角色
void On_领取成长武器兑换券(HWND hDlg, WPARAM wParam, LPARAM lParam); // 领取成长武器兑换券
void On_兑换初心之剑(HWND hDlg, WPARAM wParam, LPARAM lParam); // 兑换初心之剑
void On_兑换进阶之剑(HWND hDlg, WPARAM wParam, LPARAM lParam); // 兑换进阶之剑
void On_ReturnSelectRole(HWND hDlg, WPARAM wParam, LPARAM lParam); // 返回角色选择