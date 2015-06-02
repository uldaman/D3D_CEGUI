#include "GlobalVariable.h"
#include "Martin.h"
#include "Base.h"


cLua*                   g_pClua = new cLua;
HANDLE                  g_hLuaThread = NULL;    // 执行脚本的 Lua 线程句柄
BOOL                    g_isWork = FALSE;
std::string             g_strEventHandle = "";

std::string BossName[] = { "祸星龙", "星龙", "骇狩蛛", "岩龙", "红电龙", "尾晶蝎", "雪狮子王", \
"一角龙", "黑狼鸟", "紫毒鸟", "将军镰蟹", "沙雷鸟", "青怪鸟", "眠鸟", "金毛兽王", "大名盾蟹", \
"电龙", "沙龙王", "毒怪鸟", "鬼狩蛛", "雌火龙", "桃毛兽王", "沙狸兽", "大怪鸟", "黄速龙王", \
"蓝速龙王", "红速龙王", "大野猪王", "野猪王", "河狸兽", "冰雷鸟", "银眠鸟", "" };