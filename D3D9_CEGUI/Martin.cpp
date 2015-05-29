#include "Martin.h"


///////////////////////////////////////////////////////////////
CMartin* CMartin::m_cInstance = NULL;
CMartin* martin = CMartin::GetInstance();

CMartin* CMartin::GetInstance() {
    if (m_cInstance == NULL) {
        m_cInstance = new CMartin;
    }

    return m_cInstance;
}
///////////////////////////////////////////////////////////////

#pragma warning(push)
#pragma warning(disable : 4996)

BOOL CMartin::BreakLdrModuleLink(DWORD dwBaseAddr) {
    PLDR_MODULE pLMFNode = NULL, pLNode = NULL;
    PLDR_MODULE pLMHNode = NULL, pLMPNode = NULL;
    PLDR_MODULE pLMTNode = NULL;
    BOOL bSuccess = FALSE;

    //��ȡLDR_MODULE����ͷָ��
    __asm {
        pushad;
        pushfd;
        xor edx, edx;
        mov ebx, fs:[edx + 0x30];
        mov ecx, [ebx + 0x0C];
        lea edx, [ecx + 0x0C];
        mov ecx, [ecx + 0x0C];
        mov pLMHNode, edx;
        mov pLMFNode, ecx;
        popfd;
        popad;
    }

    //����Ŀ��
    PLDR_MODULE pLMNode = pLMFNode;
    pLMPNode = pLMHNode;
    do {
        //�Ƚ��Ƿ���Ŀ��ģ��
        if ((DWORD)pLMNode->BaseAddress == dwBaseAddr) {
            bSuccess = TRUE;
            break;
        }
        pLMPNode = pLMNode;
        pLMNode = (PLDR_MODULE)pLMNode->InLoadOrderModuleList.Flink;
    } while (pLMNode != pLMHNode);

    if (!bSuccess) {
        OutputDebugString(TEXT("cannot find the dest module!"));
        return bSuccess; //δ�ҵ�Ŀ��ģ��
    }

    //�Ͽ�InLoadOrderModuleList��
    //�ؽ�Flink
    pLMTNode = (PLDR_MODULE)pLMNode->InLoadOrderModuleList.Flink;
    pLMPNode->InLoadOrderModuleList.Flink = (PLIST_ENTRY)pLMTNode;
    //�ؽ�Blink
    ((PLDR_MODULE)(pLMNode->InLoadOrderModuleList.Flink))->InLoadOrderModuleList.Blink =
        pLMNode->InLoadOrderModuleList.Blink;

    //�Ͽ�InMemoryOrderModuleList��
    //�ؽ�Flink
    pLMPNode->InMemoryOrderModuleList.Flink =
        pLMNode->InMemoryOrderModuleList.Flink;
    //�ؽ�Blink
    pLMTNode = (PLML)(pLMNode->InMemoryOrderModuleList.Flink - sizeof(LIST_ENTRY));
    pLMTNode->InMemoryOrderModuleList.Blink =
        pLMNode->InMemoryOrderModuleList.Blink;

    //�Ͽ�InInitializationOrderModuleList��
    //�ؽ�Flink
    pLMPNode->InInitializationOrderModuleList.Flink =
        pLMNode->InInitializationOrderModuleList.Flink;

    //�ؽ�Blink
    pLMTNode = (PLML)(pLMNode->InInitializationOrderModuleList.Flink - 2 * sizeof(LIST_ENTRY));
    pLMTNode->InInitializationOrderModuleList.Blink = pLMNode->InInitializationOrderModuleList.Blink;
}

void CMartin::ModuleHide(HMODULE hInjectDll) {
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)hInjectDll, 1024, PAGE_READWRITE, &dwOldProtect);
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hInjectDll;

    //ĨȥMZ��־
    pDosHeader->e_magic = 0;

    //DOSͷ�������PEͷ
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(pDosHeader + 1);

    //ĨȥPE��־
    pNtHeader->Signature = 0;

    VirtualProtect((LPVOID)hInjectDll, 1024, dwOldProtect, &dwOldProtect);

    //�Ͽ�LDR_MODULE
    this->BreakLdrModuleLink((DWORD)hInjectDll);
}

void CMartin::Debug(const char* szFormat, ...) {
    char szBuffer[1024] = { "Debug:" };
    va_list pArgList;

    va_start(pArgList, szFormat);

    _vsnprintf(szBuffer + strlen(szBuffer), 1024 - strlen(szBuffer) * 2, szFormat, pArgList);

    va_end(pArgList);

    add_log(szBuffer);

#ifdef _DEBUG
    return OutputDebugString(szBuffer);
#endif
}

void CMartin::add_log(const char *fmt, ...) {
    if (m_ofile.is_open()) {
        if (!fmt) { return; }

        va_list va_alist;
        char logbuf[256] = { 0 };

        va_start(va_alist, fmt);
        _vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
        va_end(va_alist);

        m_ofile << logbuf << std::endl;
    }
}