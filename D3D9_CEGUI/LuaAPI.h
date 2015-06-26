#pragma once
#include "Clua.h"
#include "GlobalVariable.h"
#include <windows.h>
#include "Martin.h"

#pragma pack (push,1)
typedef struct _luaL_reg {
    const char* name;
    LuaFunctionType func;
}luaL_reg, *pluaL_reg;
#pragma pack(pop)

extern luaL_reg ConsoleGlue[];

#define EVENT_SAMPLE    1000
#define EVENT_AUTO      1001

unsigned int __stdcall ThreadAutoMatic(PVOID pM);
void AddLuaFunction();
void FireEvent(const int nId, const char* args);