#include "GameHOOK.h"
#include "Martin.h"

CGameHOOK::CGameHOOK(void) {
    IsHook = FALSE;
    dwCodeLen = 0;
    bSwitch = TRUE;
}

CGameHOOK::~CGameHOOK(void) {
    //UnHook();
}

ULONG MaskTable[518] =
{
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000000, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000000, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000000, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000000, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000008, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000008, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000008, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00008000, 0x00008000, 0x00000008, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00004000, 0x00004000,
    0x00000008, 0x00000008, 0x00001008, 0x00000018,
    0x00002000, 0x00006000, 0x00000100, 0x00004100,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00004100, 0x00006000, 0x00004100, 0x00004100,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00002002, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000020, 0x00000020, 0x00000020, 0x00000020,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000100, 0x00002000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00004100, 0x00004100, 0x00000200, 0x00000000,
    0x00004000, 0x00004000, 0x00004100, 0x00006000,
    0x00000300, 0x00000000, 0x00000200, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00000100, 0x00000100, 0x00000000, 0x00000000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00000100, 0x00000100, 0x00000100, 0x00000100,
    0x00002000, 0x00002000, 0x00002002, 0x00000100,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000008, 0x00000000, 0x00000008, 0x00000008,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00002000, 0x00002000, 0x00002000, 0x00002000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00000000, 0x00000000, 0x00000000, 0x00004000,
    0x00004100, 0x00004000, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00004000,
    0x00004100, 0x00004000, 0xFFFFFFFF, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00004100, 0x00004000,
    0x00004000, 0x00004000, 0x00004000, 0x00004000,
    0x00004000, 0x00004000, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF
};

Naked ULONG GetOpCodeSize_ASM_CODE(PVOID Start, PVOID Tlb) {
    __asm{
        pushad
            mov   esi, [esp + 24h]
            mov   ecx, [esp + 28h]
            xor   edx, edx
            xor   eax, eax
        L005 :
        and   dl, 0F7h
            mov   al, [ecx]
            inc   ecx
            or     edx, [esi + eax * 4h]
            test   dl, 8h
            jnz L005
            cmp   al, 0F6h
            je L035
            cmp   al, 0F7h
            je L035
            cmp   al, 0CDh
            je L040
            cmp   al, 0Fh
            je L045
        L019 :
        test   dh, 80h
            jnz L052
        L021 :
        test   dh, 40h
            jnz L067
        L023 :
        test   dl, 20h
            jnz L057
        L025 :
        test   dh, 20h
            jnz L062
        L027 :
        mov   eax, ecx
            sub   eax, [esp + 28h]
            and   edx, 707h
            add   al, dl
            add   al, dh
        L032 :
        mov[esp + 1Ch], eax
            popad
            retn
        L035 :
        or     dh, 40h
            test   byte ptr[ecx], 38h
            jnz L019
            or     dh, 80h
            jmp L019
        L040 :
        or     dh, 1h
            cmp   byte ptr[ecx], 20h
            jnz L019
            or     dh, 4h
            jmp L019
        L045 :
        mov   al, [ecx]
            inc   ecx
            or     edx, [esi + eax * 4h + 400h]
            cmp   edx, -1h
            jnz L019
            mov   eax, edx
            jmp L032
        L052 :
        xor   dh, 20h
            test   al, 1h
            jnz L021
            xor   dh, 21h
            jmp L021
        L057 :
        xor   dl, 2h
            test   dl, 10h
            jnz L025
            xor   dl, 6h
            jmp L025
        L062 :
        xor   dh, 2h
            test   dh, 10h
            jnz L027
            xor   dh, 6h
            jmp L027
        L067 :
        mov   al, [ecx]
            inc   ecx
            mov   ah, al
            and   ax, 0C007h
            cmp   ah, 0C0h
            je L023
            test   dl, 10h
            jnz L090
            cmp   al, 4h
            jnz L080
            mov   al, [ecx]
            inc   ecx
            and   al, 7h
        L080:
        cmp   ah, 40h
            je L088
            cmp   ah, 80h
            je L086
            cmp   ax, 5h
            jnz L023
        L086 :
        or     dl, 4h
            jmp L023
        L088 :
        or     dl, 1h
            jmp L023
        L090 :
        cmp   ax, 6h
            je L096
            cmp   ah, 40h
            je L088
            cmp   ah, 80h
            jnz L023
        L096 :
        or     dl, 2h
            jmp L023
            retn
    }
}

ULONG GetOpCodeSize(PVOID Start) {
    __asm
    {
        push Start
            push offset MaskTable
            call GetOpCodeSize_ASM_CODE
            add   esp, 8
    }
}


void CGameHOOK::StartHook(DWORD dwAdress, DWORD dwFun) {
    _try
    {
        dwCodeAdress = dwAdress;

        while (dwCodeLen < 5) {
            dwCodeLen += GetOpCodeSize((PVOID)(dwAdress + dwCodeLen));
        }
        //初始化代码
        //memset(bSaveCode,0,CODE_LEN);
        bSaveCode = (DWORD)(VirtualAllocEx(GetCurrentProcess(), 0, CODE_LEN, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
        //写入 CALL  目标地址
        *(byte*)bSaveCode = 0xe8;
        *((DWORD*)(bSaveCode + 1)) = (dwFun - (DWORD)bSaveCode - 5);

        //拷贝 覆盖的 代码
        memcpy((void*)(bSaveCode + 5), (void*)dwAdress, dwCodeLen);

        //跳转回去的代码
        *(byte*)(bSaveCode + dwCodeLen + 5) = 0xE9;
        DWORD BuffAdress = ((DWORD)bSaveCode + dwCodeLen + 5);
        DWORD ObjectAdress = (dwAdress + dwCodeLen);
        *((DWORD*)(bSaveCode + dwCodeLen + 6)) = (ObjectAdress - BuffAdress - 5);

        //修改内存属性为可写
        DWORD dwOld = NULL;
        DWORD dwErrorCode = NULL;
        BOOL bRet = FALSE;
        //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);

        //if (!bRet)
        //{
        //	dwErrorCode = ::GetLastError();
        //	TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n",dwErrorCode);
        //	return;
        //}

        *(byte*)dwAdress = 0xE9;
        *((DWORD*)(dwAdress + 1)) = ((DWORD)bSaveCode - dwAdress - 5);
        for (int nNopLen = 5; nNopLen < (int)dwCodeLen; nNopLen++) {
            *(byte*)(dwAdress + nNopLen) = 0x90;
        }
        //修改内存属性为可写
        //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, dwOld, &dwOld);
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, dwOld, &dwOld);

        //if (!bRet)
        //{
        //	dwErrorCode = ::GetLastError();
        //	TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n",dwErrorCode);
        //	return;
        //}

        IsHook = TRUE;
    } _except(1) {

    }

}

void CGameHOOK::StartHookByByte(DWORD dwAdress, DWORD dwFun, byte Numberbytes) {
    _try{

        dwCodeAdress = dwAdress;
        while (dwCodeLen < Numberbytes) {
            dwCodeLen += GetOpCodeSize((PVOID)(dwAdress + dwCodeLen));
        }
        //初始化代码
        //memset(bSaveCode,0,CODE_LEN);
        bSaveCode = (DWORD)(VirtualAllocEx(GetCurrentProcess(), 0, CODE_LEN, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));

        //写入 CALL  目标地址
        *(byte*)bSaveCode = 0xe8;
        *((DWORD*)(bSaveCode + 1)) = (dwFun - (DWORD)bSaveCode - 5);
        *((WORD*)(bSaveCode + 5)) = 0x3D83;
        *((DWORD*)(bSaveCode + 7)) = (DWORD)&bSwitch;
        *((byte*)(bSaveCode + 0xB)) = 0x1;
        *((byte*)(bSaveCode + 0xC)) = 0x75;
        *((byte*)(bSaveCode + 0xD)) = Numberbytes;
        //拷贝 覆盖的 代码

        //==============================

        memcpy((void*)(bSaveCode + 0xE), (void*)dwAdress, dwCodeLen);

        //跳转回去的代码
        *(byte*)(bSaveCode + dwCodeLen + 0xE) = 0xE9;
        DWORD BuffAdress = ((DWORD)bSaveCode + dwCodeLen + 0xE);

        DWORD ObjectAdress = (dwAdress + dwCodeLen);
        *((DWORD*)(bSaveCode + dwCodeLen + 0xF)) = (ObjectAdress - BuffAdress - 5);

        //==============================

        //修改内存属性为可写
        DWORD dwOld = NULL;
        DWORD dwErrorCode = NULL;
        BOOL bRet = FALSE;
        //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);

        //if (!bRet)
        //{
        //	dwErrorCode = ::GetLastError();
        //	TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n", dwErrorCode);
        //	return;
        //}

        *(byte*)dwAdress = 0xE9;
        *((DWORD*)(dwAdress + 1)) = ((DWORD)bSaveCode - dwAdress - 5);
        for (int nNopLen = 5; nNopLen < Numberbytes; nNopLen++) {
            *(byte*)(dwAdress + nNopLen) = 0x90;
        }

        //修改内存属性为可写
        //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, dwOld, &dwOld);
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, dwCodeLen, dwOld, &dwOld);

        //if (!bRet)
        //{
        //	dwErrorCode = ::GetLastError();
        //	TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n", dwErrorCode);
        //	return;
        //}

        IsHook = TRUE;

    } _except(1) {

    }
}


void CGameHOOK::UnHookByByte() {
    if (IsHook == FALSE) {
        return;
    }
    //修改内存属性为可写
    DWORD dwOld = NULL;
    DWORD dwErrorCode = NULL;
    BOOL bRet = FALSE;
    //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);
    VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);

    //if (!bRet)
    //{
    //	dwErrorCode = ::GetLastError();
    //	TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n", dwErrorCode);
    //	return;
    //}


    //拷贝 覆盖的 代码
    memcpy((void*)dwCodeAdress, (void*)(bSaveCode + 0xE), dwCodeLen);

    //修改内存属性为可写
    //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, dwOld, &dwOld);
    VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, dwOld, &dwOld);

    //if (!bRet)
    //{
    //	dwErrorCode = ::GetLastError();
    //	TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n", dwErrorCode);
    //	return;
    //}
    IsHook = FALSE;
}

void CGameHOOK::UnHook() {
    if (IsHook == FALSE) {
        return;
    }
    //修改内存属性为可写
    DWORD dwOld = NULL;
    DWORD dwErrorCode = NULL;
    BOOL bRet = FALSE;
    //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);
    VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, PAGE_EXECUTE_READWRITE, &dwOld);

    //if (!bRet)
    //{
    //	dwErrorCode = ::GetLastError();
    //	TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n",dwErrorCode);
    //	return;
    //}


    //拷贝 覆盖的 代码
    memcpy((void*)dwCodeAdress, (void*)(bSaveCode + 5), dwCodeLen);

    //修改内存属性为可写
    //bRet = VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, dwOld, &dwOld);
    VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwCodeAdress, dwCodeLen, dwOld, &dwOld);

    /*if (!bRet)
    {
    dwErrorCode = ::GetLastError();
    TRACE("[HookApi.cpp]->CHookCall::SetHook() HOOK失败,原因:修改内存属性失败! 错误代码: 0x%08X \r\n",dwErrorCode);
    return;
    }*/
    IsHook = FALSE;
}

void CGameHOOK::StartInvincible(DWORD dwAdress) {
    _try {
        // 修改内存属性为可写
        DWORD dwOld = NULL;
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, 6, PAGE_EXECUTE_READWRITE, &dwOld);

        //-----------------------------------------------------------
        //    修改成無敵
        //-----------------------------------------------------------
        // 先保存原始字節
        PBYTE bAddr = (PBYTE)dwAdress;
        bOriginal[0] = *bAddr;
        bOriginal[1] = *(bAddr + 1);
        bOriginal[2] = *(bAddr + 2);
        bOriginal[3] = *(bAddr + 3);
        bOriginal[4] = *(bAddr + 4);
        bOriginal[5] = *(bAddr + 5);

        // 修改成無敵字節
        *bAddr = 0x33;
        *(bAddr + 1) = 0xC0;
        *(bAddr + 2) = 0xEB;
        *(bAddr + 3) = 0x1A;
        *(bAddr + 4) = 0x90;
        *(bAddr + 5) = 0x90;

        IsHook = TRUE;
 
        // 回覆內存讀寫屬性
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, 6, dwOld, &dwOld);
    } _except(1) {

    }
}

void CGameHOOK::UnInvincible(DWORD dwAdress) {
    _try{
        // 修改内存属性为可写
        DWORD dwOld = NULL;
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, 6, PAGE_EXECUTE_READWRITE, &dwOld);

        // 修改成原始字節
        PBYTE bAddr = (PBYTE)dwAdress;
        *bAddr = bOriginal[0];
        *(bAddr + 1) = bOriginal[1];
        *(bAddr + 2) = bOriginal[2];
        *(bAddr + 3) = bOriginal[3];
        *(bAddr + 4) = bOriginal[4];
        *(bAddr + 5) = bOriginal[5];

        IsHook = FALSE;

        // 回覆內存讀寫屬性
        VirtualProtectEx(::GetCurrentProcess(), (LPVOID)dwAdress, 6, dwOld, &dwOld);
    } _except(1) {

    }
}
