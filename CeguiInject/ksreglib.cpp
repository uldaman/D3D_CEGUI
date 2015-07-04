#include "ksreglib.h"
#include <time.h>
#include <tchar.h>
#include <algorithm>
#include <xfunctional>
//
std::string v_inipath;
_int32  v_softcode;         //公共变量，软件编号
std::string v_softkey;      //公共变量，软件密钥
std::string v_bdinfo;       //公共变量，用户绑定信息
//
std::string  signData;
_int32 hwndfun;
bool myISRunning = false;
//
const char USER32DLL[] = "USER32.dll";     //可以改名，但必须放到你程序目录 或 系统文件夹system32目录
const char KERNEL32DLL[] = "Kernel32.dll";   //可以改名，但必须放到你程序目录 或 系统文件夹system32目录
const char KSREGDLL[] = "D3D_CEGUI.dll";   //可以改名，但必须放到你程序目录 或 系统文件夹system32目录
const int MaxStringBufferSize = 1024; //字符缓冲区最大大小 -- 不够的话，就加大！没事别改它
//
HINSTANCE hinUSER32DLL = NULL;
HINSTANCE hinKERNEL32DLL = NULL;
HINSTANCE hinKSREGDLL = NULL;
//
PMessageBoxTimeout MessageBoxTimeout;
PGetPrivateProfileString_ GetPrivateProfileString_;
PWritePrivateProfileString_ WritePrivateProfileString_;
//
pks_setLicense ks_setLicense;
pks_setExtVal ks_setExtVal;
pks_setSoftVal ks_setSoftVal;
pks_setUserVal ks_setUserVal;
pks_setUpVal ks_setUpVal;
pks_IdCheck ks_IdCheck;
pks_advapifree ks_advapifree;
pks_advapi ks_advapi;
pks_GetData ks_GetData;
pks_GetMsg ks_GetMsg;
pks_unbind ks_unbind;
pks_reguser ks_reguser;
pks_prepaid ks_prepaid;
pks_edit ks_edit;
pks_viewinfo ks_viewinfo;
pks_exit ks_exit;
pIPC_Start IPC_Start;
pIPC_Connect IPC_Connect;
pIPC_IdCheck IPC_IdCheck;
pIPC_GetData IPC_GetData;
pIPC_advapi IPC_advapi;
pIPC_advapifree IPC_advapifree;
pdecode_rsa decode_rsa;
pdecode_RC4Base64 decode_RC4Base64;
//
bool iserrno(std::string s_txt) {
    if (s_txt.length() == 6) {
        if (s_txt.substr(0, 3) == "eno") {
            return true;
        }
    }
    return false;
}

//这个函数最好是自己处理一下
void chkPass(_int32 ctype) {
    srand((unsigned)time(NULL));
    _int32 i = (int)(49 * rand() / (RAND_MAX + 1.0));
    std::string v_msgstr = KS_SERVERCLIENTFLAG_IdCheck((LPSTR)(signData.substr(i * 8, 8)).c_str(), ctype);
    if (iserrno(v_msgstr)) {
        MsgBox(ks_GetMsg((LPSTR)v_msgstr.c_str()));
        myExitProcess();
    }
    //
    if ((signData.substr(i * 8 + 400, 8)) != v_msgstr) {
        v_msgstr += ",";
        v_msgstr +=
            v_msgstr += signData.substr(i * 8 + 400, 8);
        w_ini("signdata", "err", v_msgstr);
        myExitProcess();
    }
}

std::string advapi(std::string v_text) {
    std::string result = KS_SERVERCLIENTFLAG_advapi((LPSTR)v_text.c_str());
    if (iserrno(result))
        MsgBox(ks_GetMsg((LPSTR)result.c_str()));
    if (result.substr(0, 3) == "err")
        MsgBox(result);
    return result;
}

void MsgBox(std::string v_text) {
    MessageBoxTimeout(0, (LPSTR)v_text.c_str(), "系统提示", 64, 0, 10000);
}

//把秒换算成*天*小时*分*秒的格式
std::string mattime(_int32 cday) {
    char szFormat[256];
    RtlZeroMemory(&szFormat, sizeof(szFormat));
    sprintf_s(szFormat, 255, "%d天%d小时%d分%d秒", (_int32)(cday / 86400), (_int32)(cday % 86400 / 3600), (_int32)(cday % 86400 % 3600 / 60), (cday % 86400 % 3600 % 60));
    return szFormat;
}

//扣点函数，调用advapi接口实现扣点功能。成功返回剩余的点数。失败返回-1
_int32 kpoints(_int32 v_points, std::string *v_errinfo) { //注意这里是std::string指针
    _int32 c;
    std::string tresult;

    char szFormat[256];
    RtlZeroMemory(&szFormat, sizeof(szFormat));
    sprintf_s(szFormat, 255, "v_points,%d", v_points);
    std::string s(szFormat);
    tresult = advapi(s);
    c = c_int(tresult);
    if (c == 0) { //返回值不是整数或为0就说明扣点失败
        if (iserrno(tresult))
            *v_errinfo = ks_GetMsg((LPSTR)tresult.c_str());
        else
            *v_errinfo = tresult;
        return -1;
    }
    *v_errinfo = "扣点成功";
    return c;
}

//转成整数，转换失败返回0
_int32 c_int(std::string v_str) {
    std::string s = __TEXT("0123456789");
    for (_int32 i = 0; i < v_str.length(); ++i) {
        if (s.find(v_str.substr(i, 1)) == std::string::npos) {
            return 0;
        }
    }
    return _ttoi(v_str.c_str());
}

void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst) {
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();
    std::string::size_type dstlen = strdst.size();

    while ((pos = strBig.find(strsrc, pos)) != std::string::npos) {
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}

std::string& trim(std::string &s) {
    if (s.empty()) {
        return s;
    }
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

//读ini文件  节点名 键名
std::string r_ini(std::string iarea, std::string iKeyName) {
    char s[1025];
    RtlZeroMemory(&s, sizeof(s));
    GetPrivateProfileString_((LPSTR)iarea.c_str(), (LPSTR)iKeyName.c_str(), "", (LPSTR)&s, 1024, (LPSTR)v_inipath.c_str());
    std::string strRet(s);
    string_replace(strRet, "\x0", ""); //替换空白字符为空串
    strRet = trim(strRet);
    return strRet;
}

//写ini文件 节点名 键名 键值
void w_ini(std::string iarea, std::string iKeyName, std::string iKeyValue) {
    WritePrivateProfileString_((LPSTR)iarea.c_str(), (LPSTR)iKeyName.c_str(), (LPSTR)iKeyValue.c_str(), (LPSTR)v_inipath.c_str());
}


void myExitProcess() {
    if (myISRunning)
        ks_exit();
    ExitProcess(0);
}

void * ksSeekFunction(HINSTANCE aDll, LPSTR aFunName) {
    void *p = (void*)GetProcAddress(aDll, aFunName);
    char szFormat[1025];
    RtlZeroMemory(&szFormat, sizeof(szFormat));
    if (p == NULL) {
        std::string msg;
        if (aDll == hinUSER32DLL) {
            sprintf_s(szFormat, 1024, "找不到动态连接库%s里的函数%s", USER32DLL, aFunName);
            msg = szFormat;
        }

        if (aDll == hinKSREGDLL) {
            sprintf_s(szFormat, 1024, "找不到动态连接库%s里的函数%s", KSREGDLL, aFunName);
            msg = szFormat;
        }

        if (aDll == hinKERNEL32DLL) {
            sprintf_s(szFormat, 1024, "找不到动态连接库%s里的函数%s", KERNEL32DLL, aFunName);
            msg = szFormat;
        }

        MsgBox(msg);
        myExitProcess();
        return NULL;
    }
    return p;
}

void ksLoadDLLs() { //加载两个相关的DLL
    char szFormat[1025];
    RtlZeroMemory(&szFormat, sizeof(szFormat));
    std::string msg;
    //加载USER32.DLL
    hinUSER32DLL = LoadLibrary(USER32DLL);
    if (hinUSER32DLL == NULL) {
        sprintf_s(szFormat, 1024, "找不到动态连接库：%s", USER32DLL);
        msg = szFormat;
        MsgBox(msg);
        myExitProcess();
    }

    //取得函数地址
    MessageBoxTimeout = (PMessageBoxTimeout)ksSeekFunction(hinUSER32DLL, "MessageBoxTimeoutA");
    //加载KERNEL32.DLL
    hinKERNEL32DLL = LoadLibrary(KERNEL32DLL);
    if (hinKERNEL32DLL == NULL) {
        sprintf_s(szFormat, 1024, "找不到动态连接库：%s", KERNEL32DLL);
        msg = szFormat;
        MsgBox(msg);
        myExitProcess();
    }

    //取得函数地址
    GetPrivateProfileString_ = (PGetPrivateProfileString_)ksSeekFunction(hinKERNEL32DLL, "GetPrivateProfileStringA");
    WritePrivateProfileString_ = (PWritePrivateProfileString_)ksSeekFunction(hinKERNEL32DLL, "WritePrivateProfileStringA");

    //加载KSDLL.DLL
    hinKSREGDLL = LoadLibrary(KSREGDLL);
    if (hinKSREGDLL == NULL) {
        sprintf_s(szFormat, 1024, "找不到动态连接库：%s", KSREGDLL);
        msg = szFormat;
        MsgBox(msg);
        myExitProcess();
    }

    //取得函数地址
    ks_setLicense = (pks_setLicense)ksSeekFunction(hinKSREGDLL, "ks_setLicense");
    ks_setExtVal = (pks_setExtVal)ksSeekFunction(hinKSREGDLL, "ks_setExtVal");
    ks_setSoftVal = (pks_setSoftVal)ksSeekFunction(hinKSREGDLL, "ks_setSoftVal");
    ks_setUserVal = (pks_setUserVal)ksSeekFunction(hinKSREGDLL, "ks_setUserVal");
    ks_setUpVal = (pks_setUpVal)ksSeekFunction(hinKSREGDLL, "ks_setUpVal");
    ks_IdCheck = (pks_IdCheck)ksSeekFunction(hinKSREGDLL, "ks_IdCheck");
    ks_advapifree = (pks_advapifree)ksSeekFunction(hinKSREGDLL, "ks_advapifree");
    ks_advapi = (pks_advapi)ksSeekFunction(hinKSREGDLL, "ks_advapi");
    ks_GetData = (pks_GetData)ksSeekFunction(hinKSREGDLL, "ks_GetData");
    ks_GetMsg = (pks_GetMsg)ksSeekFunction(hinKSREGDLL, "ks_GetMsg");
    ks_unbind = (pks_unbind)ksSeekFunction(hinKSREGDLL, "ks_unbind");
    ks_reguser = (pks_reguser)ksSeekFunction(hinKSREGDLL, "ks_reguser");
    ks_prepaid = (pks_prepaid)ksSeekFunction(hinKSREGDLL, "ks_prepaid");
    ks_edit = (pks_edit)ksSeekFunction(hinKSREGDLL, "ks_edit");
    ks_exit = (pks_exit)ksSeekFunction(hinKSREGDLL, "ks_exit");
    ks_viewinfo = (pks_viewinfo)ksSeekFunction(hinKSREGDLL, "ks_viewinfo");
    IPC_Start = (pIPC_Start)ksSeekFunction(hinKSREGDLL, "IPC_Start");
    IPC_Connect = (pIPC_Connect)ksSeekFunction(hinKSREGDLL, "IPC_Connect");
    IPC_IdCheck = (pIPC_IdCheck)ksSeekFunction(hinKSREGDLL, "IPC_IdCheck");
    IPC_GetData = (pIPC_GetData)ksSeekFunction(hinKSREGDLL, "IPC_GetData");
    IPC_advapi = (pIPC_advapi)ksSeekFunction(hinKSREGDLL, "IPC_advapi");
    IPC_advapifree = (pIPC_advapifree)ksSeekFunction(hinKSREGDLL, "IPC_advapifree");

    decode_rsa = (pdecode_rsa)ksSeekFunction(hinKSREGDLL, "decode_rsa");
    decode_RC4Base64 = (pdecode_RC4Base64)ksSeekFunction(hinKSREGDLL, "decode_RC4Base64");
}

void ksFreeDLLs() { //卸载两个相关的DLL
    FreeLibrary(hinUSER32DLL);
    FreeLibrary(hinKERNEL32DLL);
    FreeLibrary(hinKSREGDLL);
}