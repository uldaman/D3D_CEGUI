#pragma once
#include <windows.h>

//基址
const DWORD BASE_GAME = 0x02517F58;   // 游戏基址   地址: 55D6C0
const DWORD BASE_TASK = 0x025182E8;   // 任务基址   地址: 535C54
const DWORD BASE_KEYBOARD_HANDLER = 0x020190CC;   // 按键处理类基址   地址: 6B91CB
const DWORD BASE_CAMERA = 0x022AFE28;   // 摄像机相关基址   地址: 150B0FC
const DWORD BASE_LOADING_FLAG = 0x0208FDB4;   // 正在过图标志（0：不在过图，1:正在过图。）   地址: 75C23E
const DWORD BASE_CURRENT_MAP_OBJECTS = 0x02019108;   // 当前地图中的所有对象遍历基址   地址: 6B4632
const DWORD BASE_CURRENT_MAP_OBJECTS2 = 0x0250F984;   // 当前地图中的所有对象遍历2基址   地址: 1B8D2A4
const DWORD BASE_AUCTION = 0x0251824C;   // 拍卖行数据基址   地址: 46E190
const DWORD BASE_SUPPLY_BOX = 0x02019180;   // 补给箱基址   地址: 6B4800
const DWORD BASE_REWARD_TASK = 0x0251832C;   // 悬赏任务信息基址   地址: 559A3F
//调用
const DWORD CALL_VALUE_DECRYPT = 0x05F3C30;   // 加密值解密函数   地址: 55D700
const DWORD CALL_VALUE_DECRYPT2 = 0x0469890;   // 加密值解密函数2   地址: 53954E
const DWORD CALL_KEYBOARD_EVENT_HANDLE = 0x016AB920;   // 按键消息处理   地址: 16ABCD0
const DWORD CALL_TELESPORT = 0x0934C60;   // 瞬移CALL   地址: 94C145
const DWORD CALL_SEND_PACKET = 0x069BBC0;   // 发包CALL（取左边的值）   地址: 69BBC0
const DWORD CALL_INJURE = 0x01338430;   // 攻击伤害CALL   地址: 1514488
const DWORD CALL_COMMON_FUNCTION = 0x012E8300;   // 通用调用函数   地址: 12EB4AB
const DWORD CALL_SWITCH_REGION = 0x0137EAE0;   // 顺图   地址: 139AD3F
const DWORD CALL_COLLECTING = 0x05EB1D0;   // 采集物品   地址: 61A24A
const DWORD CALL_COLLECTING2 = 0x01B5FEE0;   // 采集物品2   地址: 5EBE40
const DWORD CALL_MOVE_INVENTORY_ITEM = 0x05FB3A0;   // 将背包物品存入仓库   地址: 54811C
const DWORD CALL_GET_OBJECT_IDLE_STATE = 0x015802A0;   // 获取对象空闲标识（1：空闲，0：繁忙）   地址: 153A663
const DWORD CALL_ATTACK = 0x014A4320;   // 左键攻击CALL（取左边的值）   地址: 14A4320
const DWORD CALL_GET_GLOBAL_VARIABLE = 0x076E620;   // 根据名称获取游戏中的全局变量   地址: 441848
const DWORD CALL_GET_ROLE_LIST_INFO = 0x0139BB80;   // 获取角色列表相关的指针   地址: 51C762
const DWORD CALL_GET_REWARD_TASK_STATUS = 0x055A2C0;   // 获取悬赏任务状态   地址: 559E0E
const DWORD CALL_GET_FARM_INFO = 0x01324720;   // 获取庄园信息指针   地址: 1324CDE
const DWORD CALL_GET_COLLECTED_TIME = 0x0469890;   // 获取猎友庄园已采集次数   地址: 6266DE
const DWORD CALL_DO_ACTION = 0x02A7B55D;   // 执行攻击，闪避等动作   地址: 14F1648
const DWORD CALL_GET_UI_MODE = 0x01528F40;   // 获取菜单开启状态（鼠标指针显示）   地址: 13ADFAA
const DWORD CALL_BAKE_1 = 0x0612DA0;   // 烤肉1   地址: 5FB1B7
const DWORD CALL_PLAY_ACTION = 0x01496910;   // 开始烤肉等动画   地址: 138B98F
//偏移
const DWORD OFFSET_ROLE_INFO_1 = 0x0C8;   // 当前人物指针偏移1   地址: 55D6C6
const DWORD OFFSET_ROLE_INFO_2 = 0x028;   // 当前人物指针偏移2(取byte)   地址: 55D6CC
const DWORD OFFSET_ROLE_INFO_3 = 0x0A8;   // 当前人物指针偏移3   地址: 45EA38
const DWORD OFFSET_ROLE_INFO_4 = 0x0214;   // 当前人物指针偏移4   地址: 627922
const DWORD OFFSET_ROLE_LEVEL = 0x0434;   // 人物等级加密数值偏移   地址: 55D788
const DWORD OFFSET_GET_ROLE_NAME = 0x0B0;   // 获取人物名称的CALL相对于HandlerTable的偏移   地址: 55DA7E
const DWORD OFFSET_ROLE_HP = 0x04DC;   // 人物血量偏移   地址: 55E14C
const DWORD OFFSET_NEARBY_OBJECT = 0x050;   // 周围对象叉树偏移(取byte)   地址: 94FA7E
const DWORD OFFSET_NEARBY_OBJECT_ROOT = 0x09C;   // 周围对象叉树的根偏移   地址: 928BF4
const DWORD OFFSET_COOR = 0x060;   // 坐标相对于对象指针的偏移（取byte）   地址: 1BF4DDA
const DWORD OFFSET_ROLE_ENDURE = 0x0576;   // 人物最大耐力   地址: 55D739
const DWORD OFFSET_ROLE_CURHP = 0x04D4;   // 人物当前血量   地址: 55D71A
const DWORD OFFSET_ROLE_CURENDURE = 0x056E;   // 人物当前耐力   地址: 55D758
const DWORD OFFSET_KEYBOARD_HANDLER = 0x048;   // 按键处理类偏移（取byte）   地址: 16A5237
const DWORD OFFSET_CAREMA_1 = 0x0D0;   // 摄像机类偏移1   地址: 150B102
const DWORD OFFSET_CAREMA_2 = 0x05C;   // 摄像机类偏移2（取byte）   地址: 150B108
const DWORD OFFSET_CAREMA_ANGLE = 0x0160;   // 摄像机类视角偏移   地址: 13A4460
const DWORD OFFSET_SEND_PACKET_ECX_1 = 0x0435C;   // 发包ECX偏移1   地址: 54740F
const DWORD OFFSET_SEND_PACKET_ECX_2 = 0x0F8;   // 发包ECX偏移2   地址: 5FA4AA
const DWORD OFFSET_SEND_PACKET_ECX_3 = 0x01C;   // 发包ECX偏移3（取byte）   地址: 62C7AF
const DWORD OFFSET_CITY_FLAG_1 = 0x0435C;   // 城镇标识偏移1   地址: 547AE6
const DWORD OFFSET_CITY_FLAG_2 = 0x0F8;   // 城镇标识偏移2   地址: 5FC36C
const DWORD OFFSET_CITY_FLAG_3 = 0x01C;   // 城镇标识偏移3(取byte)   地址: 62C6B7
const DWORD OFFSET_CITY_FLAG_4 = 0x024;   // 城镇标识偏移4(取byte)   地址: 69BBC8
const DWORD OFFSET_CITY_FLAG_5 = 0x088;   // 城镇标识偏移5   地址: 69BCCB
const DWORD OFFSET_SELECT_COPY = 0x0174;   // 选择副本偏移   地址: 133933A
const DWORD OFFSET_ATTACK = 0x01A2A;   // 角色攻击力偏移   地址: 55D6EE
const DWORD OFFSET_GET_TELESPORT_PTR = 0x080;   // 获取瞬移写入数据的指针   地址: 15575F6
const DWORD OFFSET_GET_SWITCH_REGION_ECX = 0x0178;   // 获取顺图的ECX   地址: 14A4D2A
const DWORD OFFSET_CURRENT_MAP_OBJECTS2 = 0x074;   // 当前地图中的所有对象遍历2偏移（取BYTE）   地址: 46533C
const DWORD OFFSET_COLLECTING_PARAM_1 = 0x09C;   // 采集CALL的参数偏移1   地址: 46549C
const DWORD OFFSET_COLLECTING_PARAM_2 = 0x064;   // 采集CALL的参数偏移2(取byte)   地址: 4654A2
const DWORD OFFSET_COLLECTING_ACTION = 0x020B4;   // 当前正在进行采集的动作信息   地址: 1BB4BCB
const DWORD OFFSET_GET_OBJECT_DETAIL = 0x025C;   // 根据对象指针获取对象详情指针   地址: 150D2E7
const DWORD OFFSET_CURRENT_MAP_ENTITY_COUNT = 0x0600C0;   // 当前地图中的对象数量偏移   地址: 928587
const DWORD OFFSET_CURRENT_MAP_ENTITY_ARRAY = 0x05C;   // 当前地图中的对象数组首地址偏移（取BYTE）   地址: 928596
const DWORD OFFSET_OBJECT_ENG_NAME = 0x0EC;   // 对象英文名偏移   地址: 92B05C
const DWORD OFFSET_WEAPON = 0x01440;   // 人物当前手持武器的Key偏移   地址: 1361929
const DWORD OFFSET_ROLE_IDLE_STATE_1 = 0x01B80;   // 人物是否空闲偏移1   地址: 1381E83
const DWORD OFFSET_ROLE_IDLE_STATE_2 = 0x024;   // 人物是否空闲偏移2（取byte）   地址: 150549A
const DWORD OFFSET_ROLE_IDLE_STATE_3 = 0x0135C;   // 人物是否空闲偏移3   地址: 1506004
const DWORD OFFSET_ATTACK_PARAM1 = 0x01D90;   // 左键攻击参数1偏移   地址: 1381EB2
const DWORD OFFSET_ATTACK_PARAM2_1 = 0x0D8;   // 左键攻击参数2偏移1   地址: 14C50F9
const DWORD OFFSET_ATTACK_PARAM2_2 = 0x031C;   // 左键攻击参数2偏移2   地址: 14F139B
const DWORD OFFSET_IS_DEAD = 0x0F4;   // 对象死亡判断CALL在虚表中的偏移   地址: 1361799
const DWORD OFFSET_ATTACK_PART = 0x048;   // 攻击部位偏移(取byte)   地址: 13303BE
const DWORD OFFSET_NO_DELAY_USE_ITEM_PACKET3_PARAM1 = 0x011C;   // 无延迟使用物品第3个封包的参数1偏移   地址: 1BBB7E8
const DWORD OFFSET_GET_TIMESTAMP = 0x0228;   // 获取时间戳函数在虚表中的偏移   地址: 164A873
const DWORD OFFSET_GET_COLLECT_ITEM_TYPE = 0x01AC;   // 获取采集物类别   地址: 46538B
const DWORD OFFSET_GET_SUPPLY_BOX = 0x0164;   // 获取补给箱的函数在虚表中的偏移   地址: 6390FA
const DWORD OFFSET_GET_ROLE_LIST = 0x028;   // 获取角色列表的函数在虚表中的偏移（取byte）   地址: 51C76D
const DWORD OFFSET_GET_ALL_REWARD_TASK = 0x0D8;   // 获取所有悬赏任务信息的函数在虚表中的偏移   地址: 1C26739
const DWORD OFFSET_ROLE_FARM = 0x03F88;   // 庄园信息偏移   地址: 5EA71A
const DWORD OFFSET_GET_COLLECTED_TIME_ECX = 0x01A5A;   // 获取猎友庄园已采集次数   地址: 6266BC
const DWORD OFFSET_DODGE_ACTION = 0x0334;   // 闪避动作   地址: 14F1642
const DWORD OFFSET_EXP_LIMIT = 0x019B0;   // 当天经验限制剩余   地址: 539549
//常量
const DWORD SIZE_SALE_ITEM = 0x068;   // 商店物品信息结构体大小（取byte）   地址: 516E21
//挂钩处
const DWORD HOOK_TELESPORT = 0x09E8D1B;   // 瞬移Hook处(取左边的值)   地址: 9E8D1B
const DWORD HOOK_INJURE = 0x01514480;   // 伤害包发送HOOK(取左边的值)   地址: 1514480
const DWORD HOOK_INVINCIBLE = 0x013849A5;   // 当前人物受伤HOOK(取左边的值)（Nop掉6个字节可实现无敌）   地址: 13849A5
const DWORD HOOK_SWITCH_REGION = 0x0139AD35;   // 顺图脚本录制HOOK处(取左边的值)   地址: 139AD35
const DWORD HOOK_ABNORMAL_STATE = 0x024FF6F77;   // 屏蔽迷糊、颤抖、麻痹、睡眠等不正常状态   地址: 1524F99
