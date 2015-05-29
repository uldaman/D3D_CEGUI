#pragma once
#include <windows.h>

//基址
const DWORD BASE_GAME = 0x02582944;   // 游戏基址   地址: 55D4A0
const DWORD BASE_TASK = 0x02582CD0;   // 任务基址   地址: 535334
const DWORD BASE_KEYBOARD_HANDLER = 0x0208C0B4;   // 按键处理类基址   地址: 6B255B
const DWORD BASE_CAMERA = 0x0231A698;   // 摄像机相关基址   地址: 1578C26
const DWORD BASE_LOADING_FLAG = 0x020FA884;   // 正在过图标志（0：不在过图，1:正在过图。）   地址: 75C133
const DWORD BASE_CURRENT_MAP_OBJECTS = 0x0208C0F0;   // 当前地图中的所有对象遍历基址   地址: 6AD7FD
const DWORD BASE_CURRENT_MAP_OBJECTS2 = 0x0257A028;   // 当前地图中的所有对象遍历2基址   地址: 1C1D134
const DWORD BASE_AUCTION = 0x02582C34;   // 拍卖行数据基址   地址: 46E960
const DWORD BASE_SUPPLY_BOX = 0x0208C168;   // 补给箱基址   地址: 6AD9D5
//调用
const DWORD CALL_VALUE_DECRYPT = 0x0560FA0;   // 加密值解密函数   地址: 55D4E0
const DWORD CALL_KEYBOARD_EVENT_HANDLE = 0x0172E980;   // 按键消息处理   地址: 172ED2E
const DWORD CALL_TELESPORT = 0x0935390;   // 瞬移CALL   地址: 94D5A3
const DWORD CALL_SEND_PACKET = 0x0697460;   // 发包CALL（取左边的值）   地址: 697460
const DWORD CALL_INJURE = 0x01395D40;   // 攻击伤害CALL   地址: 158269A
const DWORD CALL_COMMON_FUNCTION = 0x01343230;   // 通用调用函数   地址: 134635C
const DWORD CALL_SWITCH_REGION = 0x013DDB70;   // 顺图   地址: 13FB09F
const DWORD CALL_COLLECTING = 0x05EDD00;   // 采集物品   地址: 61CD98
const DWORD CALL_COLLECTING2 = 0x01BEF910;   // 采集物品2   地址: 5EE9E5
const DWORD CALL_MOVE_INVENTORY_ITEM = 0x05FE660;   // 将背包物品存入仓库   地址: 54772B
const DWORD CALL_GET_OBJECT_IDLE_STATE = 0x0169E3B0;   // 获取对象空闲标识（1：空闲，0：繁忙）   地址: 15AA410
const DWORD CALL_ATTACK = 0x0150C2E0;   // 左键攻击CALL（取左边的值）   地址: 150C2E0
const DWORD CALL_GET_GLOBAL_VARIABLE = 0x076EDB0;   // 根据名称获取游戏中的全局变量   地址: 441779
const DWORD CALL_GET_ROLE_LIST_INFO = 0x013FC020;   // 获取角色列表相关的指针   地址: 51BED2
//偏移
const DWORD OFFSET_ROLE_INFO_1 = 0x0C8;   // 当前人物指针偏移1   地址: 55D4A6
const DWORD OFFSET_ROLE_INFO_2 = 0x028;   // 当前人物指针偏移2(取byte)   地址: 55D4AC
const DWORD OFFSET_ROLE_INFO_3 = 0x0A8;   // 当前人物指针偏移3   地址: 45F1A2
const DWORD OFFSET_ROLE_INFO_4 = 0x0214;   // 当前人物指针偏移4   地址: 62A3B2
const DWORD OFFSET_ROLE_LEVEL = 0x0434;   // 人物等级加密数值偏移   地址: 55D568
const DWORD OFFSET_GET_ROLE_NAME = 0x0B0;   // 获取人物名称的CALL相对于HandlerTable的偏移   地址: 55D84E
const DWORD OFFSET_ROLE_HP = 0x04DC;   // 人物血量偏移   地址: 55DF1C
const DWORD OFFSET_NEARBY_OBJECT = 0x050;   // 周围对象叉树偏移(取byte)   地址: 9510DB
const DWORD OFFSET_NEARBY_OBJECT_ROOT = 0x09C;   // 周围对象叉树的根偏移   地址: 929023
const DWORD OFFSET_COOR = 0x060;   // 坐标相对于对象指针的偏移（取byte）   地址: 1C85DA8
const DWORD OFFSET_ROLE_ENDURE = 0x0576;   // 人物最大耐力   地址: 55D519
const DWORD OFFSET_ROLE_CURHP = 0x04D4;   // 人物当前血量   地址: 55D4FA
const DWORD OFFSET_ROLE_CURENDURE = 0x056E;   // 人物当前耐力   地址: 55D538
const DWORD OFFSET_KEYBOARD_HANDLER = 0x048;   // 按键处理类偏移（取byte）   地址: 1728035
const DWORD OFFSET_CAREMA_1 = 0x0D0;   // 摄像机类偏移1   地址: 1578C2C
const DWORD OFFSET_CAREMA_2 = 0x05C;   // 摄像机类偏移2（取byte）   地址: 1578C32
const DWORD OFFSET_CAREMA_ANGLE = 0x0160;   // 摄像机类视角偏移   地址: 14048F1
const DWORD OFFSET_SEND_PACKET_ECX_1 = 0x042F4;   // 发包ECX偏移1   地址: 546A3E
const DWORD OFFSET_SEND_PACKET_ECX_2 = 0x0F8;   // 发包ECX偏移2   地址: 5FD75C
const DWORD OFFSET_SEND_PACKET_ECX_3 = 0x01C;   // 发包ECX偏移3（取byte）   地址: 62EF7B
const DWORD OFFSET_CITY_FLAG_1 = 0x042F4;   // 城镇标识偏移1   地址: 547106
const DWORD OFFSET_CITY_FLAG_2 = 0x0F8;   // 城镇标识偏移2   地址: 5FF63E
const DWORD OFFSET_CITY_FLAG_3 = 0x01C;   // 城镇标识偏移3(取byte)   地址: 62EE87
const DWORD OFFSET_CITY_FLAG_4 = 0x024;   // 城镇标识偏移4(取byte)   地址: 697465
const DWORD OFFSET_CITY_FLAG_5 = 0x088;   // 城镇标识偏移5   地址: 69756B
const DWORD OFFSET_SELECT_COPY = 0x0174;   // 选择副本偏移   地址: 1396D37
const DWORD OFFSET_ATTACK = 0x01A2A;   // 角色攻击力偏移   地址: 55D4CE
const DWORD OFFSET_GET_TELESPORT_PTR = 0x080;   // 获取瞬移写入数据的指针   地址: 157F69E
const DWORD OFFSET_GET_SWITCH_REGION_ECX = 0x0178;   // 获取顺图的ECX   地址: 150C266
const DWORD OFFSET_CURRENT_MAP_OBJECTS2 = 0x074;   // 当前地图中的所有对象遍历2偏移（取BYTE）   地址: 465A84
const DWORD OFFSET_COLLECTING_PARAM_1 = 0x09C;   // 采集CALL的参数偏移1   地址: 465B6E
const DWORD OFFSET_COLLECTING_PARAM_2 = 0x064;   // 采集CALL的参数偏移2(取byte)   地址: 465B74
const DWORD OFFSET_COLLECTING_ACTION = 0x0204C;   // 当前正在进行采集的动作信息   地址: 1C452CB
const DWORD OFFSET_GET_OBJECT_DETAIL = 0x025C;   // 根据对象指针获取对象详情指针   地址: 157AEB7
const DWORD OFFSET_CURRENT_MAP_ENTITY_COUNT = 0x0600C0;   // 当前地图中的对象数量偏移   地址: 9289B7
const DWORD OFFSET_CURRENT_MAP_ENTITY_ARRAY = 0x05C;   // 当前地图中的对象数组首地址偏移（取BYTE）   地址: 9289C6
const DWORD OFFSET_OBJECT_ENG_NAME = 0x0EC;   // 对象英文名偏移   地址: 92B29A
const DWORD OFFSET_WEAPON = 0x01440;   // 人物当前手持武器的Key偏移   地址: 13C042A
const DWORD OFFSET_ROLE_IDLE_STATE_1 = 0x01B80;   // 人物是否空闲偏移1   地址: 13E0F9D
const DWORD OFFSET_ROLE_IDLE_STATE_2 = 0x024;   // 人物是否空闲偏移2（取byte）   地址: 1572A12
const DWORD OFFSET_ROLE_IDLE_STATE_3 = 0x0135C;   // 人物是否空闲偏移3   地址: 1573622
const DWORD OFFSET_ATTACK_PARAM1 = 0x01D90;   // 左键攻击参数1偏移   地址: 13E0FCC
const DWORD OFFSET_ATTACK_PARAM2_1 = 0x0D8;   // 左键攻击参数2偏移1   地址: 152E967
const DWORD OFFSET_ATTACK_PARAM2_2 = 0x031C;   // 左键攻击参数2偏移2   地址: 155E092
const DWORD OFFSET_IS_DEAD = 0x0F4;   // 对象死亡判断CALL在虚表中的偏移   地址: 13C0291
const DWORD OFFSET_ATTACK_PART = 0x048;   // 攻击部位偏移(取byte)   地址: 138DBDD
const DWORD OFFSET_NO_DELAY_USE_ITEM_PACKET3_PARAM1 = 0x011C;   // 无延迟使用物品第3个封包的参数1偏移   地址: 1C4BF58
const DWORD OFFSET_GET_TIMESTAMP = 0x0228;   // 获取时间戳函数在虚表中的偏移   地址: 16C9851
const DWORD OFFSET_GET_COLLECT_ITEM_TYPE = 0x01AC;   // 获取采集物类别   地址: 465AD5
const DWORD OFFSET_GET_SUPPLY_BOX = 0x0164;   // 获取补给箱的函数在虚表中的偏移   地址: 63BB54
const DWORD OFFSET_GET_ROLE_LIST = 0x028;   // 获取角色列表的函数在虚表中的偏移（取byte）   地址: 51BEDD
//常量
const DWORD SIZE_SALE_ITEM = 0x068;   // 商店物品信息结构体大小（取byte）   地址: 5164D1
//挂钩处
const DWORD HOOK_TELESPORT = 0x094D596;   // 瞬移Hook处(取左边的值)   地址: 94D596
const DWORD HOOK_INJURE = 0x01582692;   // 伤害包发送HOOK(取左边的值)   地址: 1582692
const DWORD HOOK_INVINCIBLE = 0x013E3C61;   // 当前人物受伤HOOK(取左边的值)（Nop掉6个字节可实现无敌）   地址: 13E3C61
const DWORD HOOK_SWITCH_REGION = 0x013FB095;   // 顺图脚本录制HOOK处   地址: 13FB095