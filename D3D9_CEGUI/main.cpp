/*
    Project : Direct3D StarterKit v3.0
    Author	: Matthew L (Azorbix)
    Date	: June 10th, 2005

    Credits :
    Tetsuo:			Help with hooking the device
    LanceVorgin:	His name is funny
    p47r!ck:		Hes German
    Hybrid:			Knows DirectX9
    Dom1n1k:		Helped with detourfunc
    Da_BuzZ:		Helped alot with d3d8
    Sparten:		Bugfix with GetDirect3D()

    Dockman:		A Game-Deception Head Honcho
    Absolution:		A Game-Deception Head Honcho
    UNI:			The Game-Deception Head Honcho Fries Supreme!
    Game-Deception

    Tools used:
    Microsoft Visual Studio .NET 2003
    DirectX9 SDK Update (summer 2004)

    Information:
    This StarterKit was developed for Game-Deception
    visit us at http://www.game-deception.com
    */

#include <windows.h>
#include <fstream>
#include <stdio.h>
#pragma warning(disable:4996)

#include "main.h"
#include "d3d9.h"
#include "Martin.h"

//Globals
char dlldir[320];

bool WINAPI DllMain(HMODULE hDll, DWORD dwReason, PVOID pvReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hDll);

        GetModuleFileName(hDll, dlldir, 512);
        for (int i = strlen(dlldir); i > 0; i--) {
            if (dlldir[i] == '\\') {
                dlldir[i + 1] = 0;
                break;
            }
        } // 去掉路径的文件名

        martin->m_ofile.open(GetDirectoryFile("ttnlog.txt"), std::ios::app);

        martin->add_log("\n---------------------\nTatniumD3D Started...\n---------------------");

        HMODULE hMod = LoadLibrary("d3d9.dll");

        martin->add_log("\n---------------------\nDirect3DCreate9 --> 0x%X...\n---------------------", GetProcAddress(hMod, "Direct3DCreate9"));

        oDirect3DCreate9 = (tDirect3DCreate9)DetourFunc(
            (BYTE*)GetProcAddress(hMod, "Direct3DCreate9"), // 获取 Direct3DCreate9 地址
            (BYTE*)hkDirect3DCreate9,
            5); // HOOK Direct3DCreate9        
        return true;
    } else if (dwReason == DLL_PROCESS_DETACH) {
        martin->add_log("---------------------\nTatniumD3D Exiting...\n---------------------\n");
        if (martin->m_ofile) {
            martin->m_ofile.close();
        }
    }
    return false;
}

char *GetDirectoryFile(char *filename) {
    static char path[320];
    strcpy(path, dlldir);
    strcat(path, filename);
    return path;
}

void *DetourFunc(BYTE *src, const BYTE *dst, const int len) {
    BYTE *jmp = (BYTE*)malloc(len + 5);
    DWORD dwback;

    VirtualProtect(src, len, PAGE_READWRITE, &dwback);

    memcpy(jmp, src, len);	
    jmp += len;

    jmp[0] = 0xE9;
    *(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;

    src[0] = 0xE9;
    *(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;

    VirtualProtect(src, len, dwback, &dwback);

    return (jmp - len);
}

bool RetourFunc(BYTE *src, BYTE *restore, const int len) {
    DWORD dwback;

    if (!VirtualProtect(src, len, PAGE_READWRITE, &dwback)) { return false; }
    if (!memcpy(src, restore, len)) { return false; }

    restore[0] = 0xE9;
    *(DWORD*)(restore + 1) = (DWORD)(src - restore) - 5;

    if (!VirtualProtect(src, len, dwback, &dwback)) { return false; }

    return true;
}

