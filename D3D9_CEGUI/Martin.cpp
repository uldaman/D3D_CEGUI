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

    //获取LDR_MODULE链的头指针
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

    //查找目标
    PLDR_MODULE pLMNode = pLMFNode;
    pLMPNode = pLMHNode;
    do {
        //比较是否是目标模块
        if ((DWORD)pLMNode->BaseAddress == dwBaseAddr) {
            bSuccess = TRUE;
            break;
        }
        pLMPNode = pLMNode;
        pLMNode = (PLDR_MODULE)pLMNode->InLoadOrderModuleList.Flink;
    } while (pLMNode != pLMHNode);

    if (!bSuccess) {
        OutputDebugString(TEXT("cannot find the dest module!"));
        return bSuccess; //未找到目标模块
    }

    //断开InLoadOrderModuleList链
    //重建Flink
    pLMTNode = (PLDR_MODULE)pLMNode->InLoadOrderModuleList.Flink;
    pLMPNode->InLoadOrderModuleList.Flink = (PLIST_ENTRY)pLMTNode;
    //重建Blink
    ((PLDR_MODULE)(pLMNode->InLoadOrderModuleList.Flink))->InLoadOrderModuleList.Blink =
        pLMNode->InLoadOrderModuleList.Blink;

    //断开InMemoryOrderModuleList链
    //重建Flink
    pLMPNode->InMemoryOrderModuleList.Flink =
        pLMNode->InMemoryOrderModuleList.Flink;
    //重建Blink
    pLMTNode = (PLML)(pLMNode->InMemoryOrderModuleList.Flink - sizeof(LIST_ENTRY));
    pLMTNode->InMemoryOrderModuleList.Blink =
        pLMNode->InMemoryOrderModuleList.Blink;

    //断开InInitializationOrderModuleList链
    //重建Flink
    pLMPNode->InInitializationOrderModuleList.Flink =
        pLMNode->InInitializationOrderModuleList.Flink;

    //重建Blink
    pLMTNode = (PLML)(pLMNode->InInitializationOrderModuleList.Flink - 2 * sizeof(LIST_ENTRY));
    pLMTNode->InInitializationOrderModuleList.Blink = pLMNode->InInitializationOrderModuleList.Blink;
}

void CMartin::ModuleHide(HMODULE hInjectDll) {
    DWORD dwOldProtect;
    VirtualProtect((LPVOID)hInjectDll, 1024, PAGE_READWRITE, &dwOldProtect);
    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hInjectDll;

    //抹去MZ标志
    pDosHeader->e_magic = 0;

    //DOS头后面就是PE头
    PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(pDosHeader + 1);

    //抹去PE标志
    pNtHeader->Signature = 0;

    VirtualProtect((LPVOID)hInjectDll, 1024, dwOldProtect, &dwOldProtect);

    //断开LDR_MODULE
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

std::string CMartin::GetModulePath(HMODULE hModule) {
    char szPath[MAX_PATH];
    RtlZeroMemory(szPath, sizeof(szPath));
    GetModuleFileName(hModule, szPath, MAX_PATH);
    (strrchr(szPath, '\\'))[0] = 0;
    return szPath;
}

std::vector<std::string> CMartin::split(std::string str, std::string pattern) {
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    UINT size = str.size();

    for (UINT i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

// 两坐标点间距离
float CMartin::Compare_Coord(float x1, float y1, float x2, float y2) {
    if (x1 == x2) {
        return abs(y1 - y2);	//上 下
    } else if (y1 == y2) {
        return abs(x1 - x2);	//左 右
    } else {
        float subX = abs(x1 - x2);
        float subY = abs(y1 - y2);
        return (sqrt(pow(subX, 2) + pow(subY, 2))); //三角函数 求边长
    }
}