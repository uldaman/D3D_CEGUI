#include <windows.h>
#include <winbase.h>
#include "ceguiinject.h"
#include <minwindef.h>
#include <libloaderapi.h>
#include <QFile>
#include <QFileDialog>
#include <QtDebug>
#include <process.h>
#include <tlhelp32.h>
#include <QMessageBox>
#include "forcelib\ForceLib.h"
#include "My_Ini.h"
#include <QVBoxLayout>  
#include <QMenuBar>
#include "cqvip.h"
#include "ksreglib.h"
#include <time.h>
#include <memory>

CeguiInject::CeguiInject(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);
    QString strOutput = QStringLiteral("说明: 首次使用请先点击安装插件.");
    ui.label_output->setText(strOutput);
    ui.radioButton_d3d9->setChecked(true);

    ///////////////////////////////////////////////////////////////////////////////

    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
    strDll = std::string((const char*)qstrDll.toLocal8Bit());
    strDll += "\\Config.ini";
    CMy_Ini obj_ini(strDll.c_str());
    QString fileName = QString::fromLocal8Bit(obj_ini.GetString("Path", "Game").c_str());
    ui.lineEdit_path->setText(fileName);
    m_vipCard = QString::fromLocal8Bit(obj_ini.GetString("Vip", "Card").c_str());

    ///////////////////////////////////////////////////////////////////////////////

    m_layout = new QVBoxLayout(this);
    m_menuBar = new QMenuBar(this);
    m_menuBar->setGeometry(QRect(0, 0, 400, 24));
    m_menu = m_menuBar->addMenu(QStringLiteral("设置"));
    m_actionNew = m_menu->addAction(QStringLiteral("账号"));
    m_layout->setMenuBar(m_menuBar);
    setLayout(m_layout);
    connect(m_actionNew, SIGNAL(triggered()), this, SLOT(OpenVip()));

    ksLoadDLLs();
    InitReg();
}

CeguiInject::~CeguiInject() {
    ksFreeDLLs();
}

bool fileExists(const char filename[]) {
    WIN32_FIND_DATA finddata;
    HANDLE handle = FindFirstFile(filename, &finddata);
    return (handle != INVALID_HANDLE_VALUE);
}

bool GetProcessOf(const char exename[], PROCESSENTRY32 *process) {
    HANDLE handle;
    process->dwSize = sizeof(PROCESSENTRY32);
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(handle, process)) {
        do {
            if (lstrcmp(process->szExeFile, exename) == 0) {
                CloseHandle(handle);
                return true;
            }
        } while (Process32Next(handle, process));
    }

    CloseHandle(handle);
    return false;
}

bool GetThreadOf(DWORD ProcessID, THREADENTRY32* thread) {
    HANDLE handle;
    thread->dwSize = sizeof(THREADENTRY32);
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if (Thread32First(handle, thread)) {
        do {
            if (thread->th32OwnerProcessID == ProcessID) {
                CloseHandle(handle);
                return true;
            }
        } while (Thread32Next(handle, thread));
    }

    CloseHandle(handle);
    return false;
}

void CeguiInject::runGame() {
    if (RegVip() == FALSE) {
        return;
    }
    ks_exit();

    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
    strDll = std::string((const char*)qstrDll.toLocal8Bit());

    if (ui.radioButton_d3d9->isChecked()) {
        strDll += "\\D3D9_CEGUI.dll";
    } else if (ui.radioButton_d3d8->isChecked()) {
        strDll += "\\D3D8_CEGUI.dll";
    }

    if (!fileExists(strDll.c_str())) {
        ::MessageBox(NULL, "没有找到 DLL 文件 . . ", "Tatnium Error", MB_ICONERROR);
        return;
    }

    //if (IDCANCEL == ::MessageBox(0, "点击 \"确定\" 后开始等待游戏启动\n\n等待中按键盘 \"esc\" 键取消等待...", "Tatnium Injector", MB_OK)) {
    //    return;
    //}

    QString strOutput = QStringLiteral("点击 \"Yes\" 开始等待游戏启动(手动),\n等待中可按键盘 \"esc\" 键取消等待...");
    if (QMessageBox::No == QMessageBox::question(this, QStringLiteral("是否开启插件?"), strOutput, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)) {
        return;
    }
    
    QString strGame = ui.lineEdit_path->text();
    if (strGame.isEmpty()) {
        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("没有正确选择游戏路径!"));
        return;
    }

    strSplit = "/";
    index = strGame.lastIndexOf(strSplit);
    strGame = strGame.right(strGame.length() - index - 1);
    std::string szGame = std::string((const char*)strGame.toLocal8Bit());

    PROCESSENTRY32 pe32;
    while (!GetProcessOf(szGame.c_str(), &pe32)) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return;
        }
        Sleep(10);
    }

    THREADENTRY32 te32;
    while (!GetThreadOf(pe32.th32ProcessID, &te32)) {
        Sleep(2);
    }

    PROCESS_INFORMATION PI;
    PI.dwProcessId = pe32.th32ProcessID;
    PI.dwThreadId = te32.th32ThreadID;
    PI.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);

    if (!ForceLibrary(strDll.c_str(), &PI)) {
        TerminateProcess(PI.hProcess, 0);
        ::MessageBox(NULL, "无法开启插件...", "Tatnium Error", MB_ICONERROR);
    }

    CloseHandle(PI.hProcess);

    //::CloseHandle((HANDLE)_beginthreadex(NULL, 0, ThreadFun_WaritGame, NULL, 0, NULL));
}

void CeguiInject::selectPath() {
    if (RegVip() == FALSE) {
        return;
    }
    ks_exit();

    QString fileName = QFileDialog::getOpenFileName(this, "Open File", NULL, "file (*.exe)");
    if (!fileName.isEmpty()) {
        char dllname[MAX_PATH];
        GetModuleFileName(NULL, dllname, MAX_PATH);
        std::string strDll = dllname;
        //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
        QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
        QString strSplit = "\\";
        int index = qstrDll.lastIndexOf(strSplit);
        qstrDll = qstrDll.left(index);
        //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
        strDll = std::string((const char*)qstrDll.toLocal8Bit());
        strDll += "\\Config.ini";
        CMy_Ini obj_ini(strDll.c_str());
        obj_ini.DeleteSection(TEXT("Path"));
        obj_ini.WriteString("Path", "Game", (const char*)fileName.toLocal8Bit());
        ui.lineEdit_path->setText(fileName);
    }
}

void CeguiInject::OpenVip() {
    CQVip oQvip;
    QObject::connect(&oQvip, &CQVip::newVip, this, &CeguiInject::receiveVip);
    oQvip.exec();
}

void CeguiInject::InitReg() {
    // 初始化验证
    std::string LicenseKey, v_rsamod, v_rsapubkey;
    std::string v_pccode, s_notice;
    _int32 v_cstime, v_is2svr;
    // ★★★★★★如若你觉得验证模块取的机器码不够安全或经常变动，你可以自己写函数取机器码这个变量，要求最少五个字符，否则请留空
    v_pccode = __TEXT("");

    // ★★★★★★记录日志数据的文件 c:\kss.ini
    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
    std::string strIniPath = std::string((const char*)qstrDll.toLocal8Bit());
    strIniPath += TEXT("\\kss.ini");
    v_inipath = strIniPath;

    // ★★★★★★连接服务器超时默认为6000毫秒
    v_cstime = 31 * 1000;

    // ★★★★★★如果你装有验证备服，这里请填1，否则填0
    v_is2svr = 0;

    // ★★★★★★此参数请查阅管理端【软件列表】里[软件编号]的值
    v_softcode = 1000004;

    // ★★★★★★此参数请查阅管理端【软件列表】里[软件密钥]的值
    v_softkey = "Kq48cq8t1rqAkjYarYmC8KsP";

    //★★★★★★ 800商业版用户，下边两个参数设置请参见 http://www.hphu.com/news_14.html
    //五元服作者和体验用户请不要修改RSA参数
    /*    v_rsamod = __TEXT("80994089576198245488509154749313953201376381432243611978096896085511546099913");  // v_rsa mod = __TEXT("") 就是关闭RSA功能，服务端也应关闭RSA
    v_rsapubkey = __TEXT("65537");  //v_rsapubkey = __TEXT("")  就是关闭RSA功能，服务端也应关闭RSA*/
    v_rsamod = "56591083613825005903100788459095430353163052008239248775218519910075636714049";  // v_rsa mod = __TEXT("") 就是关闭RSA功能，服务端也应关闭RSA
    v_rsapubkey = "130859";  //v_rsapubkey = __TEXT("")  就是关闭RSA功能，服务端也应关闭RSA

    // ★★★★★★ 该数据从管理端获取后设置到这里：【软件列表】->右上角【新签名数据】按钮单击即可获取。
    signData = "";
    signData += "a4d2bd9314324ad47f748acf6d2d34504d38550fc7259cfd2d37c7a7678db6bd9cdb86cdb868f51582b82ff6eaa0e7e53d84";
    signData += "74df93827e4b07f8a50d295dd0ddd35ea1b69a510e9dda2a398b47b6de07f47cbd4e3a9889abea8c8ac2b45643190314c501";
    signData += "589219d7559eb2f02db5edf81ce9f0bb508faf6ea974c7b3bc813e84d54cc8ed68984fbfdb717822fd3c0fcc4db0d4eeb8e0";
    signData += "8dfbe6c3d7b83b3f5262ed2efa4107b424d848a445c7c235ada498661e5ec71ce5439d4c7078a8f90c52dca80b29ceac3c46";
    signData += "be3a7abf9dbd5145a0bdeffb4fd43fbfd17861acc75753a5f13df5145e6207f56471f3d6a91c0401b86de7a589b86001724f";
    signData += "6ab5b7fdd091c37af893889d98cb544931a4f591a96be5db264b744fc6b10f84ffac726a57fe446c668defa104ec06e4a62c";
    signData += "a3d1a70052872b9cd6040abcb61116b3c76fadd53ce6779f35087eb9fd50dc680d80ce76f96c9584de8a81be555ef2c8b92c";
    signData += "505db2246d37c6051543b70bc7b804d0e0636cb879bd874cd5ddc1bef4a0613415c8acf002ffdbcf64c23a07974d54258e7a";

    v_bdinfo = "";           // 用户的绑定信息。
    // 1、如果这里的值不为空，该数据会由服务端效验，也就是说如果服务端数据库里相应用户的绑定信息与该值不相同，会被服务端认为非法，也就是验证不能通过。
    // 2、如果这里的值为空，登陆成功后通过ks_GetData (4)取得服务器返回的用户绑定信息，也就是说你可以用ks_GetData (4)的值来处理你自己的应用。

    //★★★★★★ 800商业版用户，下边的参数里的字符串请修改为你自己的LicenseKey
    //五元服作者和体验用户请不要修改该参数
    LicenseKey = "";
    LicenseKey += "q6pEBYnyqtXar6uPbSTzmTXIL25+i4ouvmcSRzgVDwF/RL4XqmFoxB5I5kl8Tm3OR7G76cEnIH3A5CLL";
    LicenseKey += "XLAXm3eUh5cgEu9y7smCUUwt+o+Z67TqVv9EKUesgy7Q2ZpJh5XExlxf1zo9+5xmM9FFIx2isYXhg9gu";
    LicenseKey += "zD4rwg9L+er0HuSbmqlmpQLqS2OlN/z/Z4ByNp4XuahZmD8KOfUBIMXkX0ImxU79Dez4qvt7uZFZQeM3";
    LicenseKey += "dwPo7cjrvuo0prmKBJYTtlfrX9Dq+dGNorYjE6EsFnF3DKlfRdzGUWoS9IGrRdI37UZFHYoBVWfJl0Ry";
    LicenseKey += "2qUZVbiHkptKTH7lSKjnSSRHzto5QWVm/qdtDRfLR18lIQKJo7aAfvmkgWyEvVTt6l2UuVuxs6PUW4XK";
    LicenseKey += "Jfa5CgD0eeC7ICQmTAZ8AyH1SthbcvKF8aA1u5cMEizB0XRxKMyXP/bYKOqOftPbBQILj9Ya1Xo6NWwQ";
    LicenseKey += "9K6gZBdHy9y3OAj0D1gbhOuoHFeVO//2QJfhZ3H7bzeXtA5UI/rimJXMHCko2qoypXLa3z33KjSsCNfL";
    LicenseKey += "SaW1ALhe6Yz05joWKLBV5kxpFDzlbY9246ej29kEukVEqd0bAPDmLxknof4Wi3YDE/6kZ3erhBD0rH0Q";
    LicenseKey += "Av4ELHBuUsLTomIcQVTqlA+qKzHcVs0x8cRuUtfS+Mp6giLJZAvRS7oTYvCnhkJa+V9bXjV0msYIKivh";
    LicenseKey += "I4xYiSVu1sVntQvori5I0dAr0NoPwf157udfIa7d/SrgaFl8gvoWfUt56r5gkKNRDoR/EianEY8Np4Wa";
    LicenseKey += "SOFisKZqTB9MNkFnoWLfNz0G/B49uf/qEOONhIpAmrLprRfgYRWKFiSXU1xhbzbNPEZ88w0FLZQPWDP3";
    LicenseKey += "58dybdT7Z3N4Si+IIwrXJZV/DnsorJMlTEWJsztZOOh2yw96C229FwKrdKAkpGZPomfeFOmNduDG9KNA";
    LicenseKey += "YZ7DIZSn27PJOtO0vZ5GL1pciOGjGbxSyzXShvk41tEv9HFtNagDaVlWjIsN9iSuacSCFmEmxyvgIZDX";
    LicenseKey += "ANM64Jz31sthq+m3iNTZuy7xKcN+bFJJmpqVVYBk62YrIvbG0hlRNXx7XgPxaJ1Dh0IQTqgRzJYG/+bq";
    LicenseKey += "Rvdz3k7GAMmLkQk6dQsQEISX8lT5diZ4jSoYF+c7j3TBNrvKNdxIEbXr903+gDvno6zyvqnwtY2q/sX6";
    LicenseKey += "/FbNTz9zJV8f6Hh9dlhBiXUrkT3hGVWgBXIoNx2n4yv7ruhmrZ8xGjnKd5OTyZnvUkMZJuweKBg2AMsq";
    LicenseKey += "Y7jHM8o/KoOqeA0fv1QGpd2I7ZFAo8Nr/g1gnnJ18ybTvJ/zQ1QQlcsmOyAPYJx5keH4wbTvGn15zmtm";
    LicenseKey += "XW3TzZ6Rm6ORpTYL8JTlo+nWHwCupQbirkouByZJx+RuG0XIGYelS6W3TGtNDDM3/eOZbj9C4xgL+fkq";
    LicenseKey += "GDzfVz/8pWGt7ZTeJ+EDDzlEwUF6d+MXH5a5SxWNgbS3ZhZY5sp8I5D/ANe5YETCP4lc32ck1HbbrFt8";
    LicenseKey += "Jwyz2QFNrMZqq6R8VpQsEdRDEyJA80RNqO33N2RNa6f9TceRVZ2o/amPyo8xzvzgnaA4Vbk0tAYvrS7M";
    LicenseKey += "BlukmT7iOJE0wjHuwhBWvbstGjKCKefPcbKekdYWnnx+sfuAd+W47Gyp9WrD1K6XMsGRWWH5K6d3BD8n";
    LicenseKey += "HEsLFVDXLJ5s5GwY+559KXbqZQ==";

    //KS授权信息
    ks_setLicense((LPSTR)LicenseKey.c_str());

    //初始化扩展参数，一般情况下无需修改
    ks_setExtVal(0, (LPSTR)v_pccode.c_str()
        , (LPSTR)v_inipath.c_str()
        , v_cstime, v_is2svr, (LPSTR)v_rsamod.c_str()
        , (LPSTR)v_rsapubkey.c_str()
        , "", "", "");

    // 无论调用多少次ks_GetData（参数大于10000000），只会连接一次网络（无论参数是否相同）
    // 以下五行代码视你具体需求，你可以决定是否保留
    // s_isup = ks_GetData(v_softcode * 10 + 1);   //服务端软件是否强制更新
    // s_version = ks_GetData(v_softcode * 10 + 2);  //服务端软件版本
    // s_downurl = ks_GetData(v_softcode * 10 + 3);   //服务端软件下载地址
    s_notice = ks_GetData(v_softcode * 10 + 4);  //服务端软件公告
    s_notice = TEXT("公告: ") + s_notice;
    // MsgBox(s_notice);
}

BOOL CeguiInject::RegVip() {
    std::string str;
    _int32 i_rnd;
    std::string v_msgstr;
    ks_setSoftVal(v_softcode, (LPSTR)v_softkey.c_str());

    //--  传递用户相关信息给
    std::string strVipCard = std::string((const char*)m_vipCard.toLocal8Bit());
    strVipCard.erase(0, strVipCard.find_first_not_of(" "));
    strVipCard.erase(strVipCard.find_last_not_of(" ") + 1);

    ks_setUserVal(1, (LPSTR)strVipCard.c_str(), "", (LPSTR)v_bdinfo.c_str());
    ////--  设置自动升级相关信息给DLL，不用自动升级功能的话，下边一段完全可以删掉
    ////--  参数：1本登陆窗口的窗口句柄, 2当前软件的版本号, 3用户是否选择了检查更新
    //ks_setUpVal((_int32)this->m_hWnd, v_softversion, (_int32)(m_Checkupdate.GetCheck()));

    //--  开始验证
    srand((unsigned)time(NULL));
    //i_rnd = (int)(49 * rand() / (RAND_MAX + 1.0));
    i_rnd = rand() % 50;

    v_msgstr = ks_IdCheck((LPSTR)(signData.substr(i_rnd * 8, 8)).c_str(), 1);
    if (iserrno(v_msgstr)) {
        MsgBox(ks_GetMsg((LPSTR)v_msgstr.c_str()));
        return FALSE;
    }

    std::string lsS = v_msgstr;
    //if(signData.Mid(i_rnd * 8 + 400, 8) != v_msgstr) {
    if (signData.substr((i_rnd + 50) * 8, 8) != v_msgstr) {
        lsS += __TEXT(",");
        lsS += signData.substr((i_rnd + 50) * 8, 8);
        w_ini(__TEXT("signdata"), "err", lsS);
        myExitProcess(); //掐进程
    }
    return TRUE;
}

BOOL CopyFolder(const char* lpszFromPath, const char* lpszToPath) {
    int nLengthFrm = strlen(lpszFromPath);
    std::auto_ptr<char> NewPathFrm(new char[nLengthFrm * 2]);
    RtlZeroMemory(NewPathFrm.get(), nLengthFrm * 2);
    strcpy_s(NewPathFrm.get(), nLengthFrm + 1, lpszFromPath);
    NewPathFrm.get()[nLengthFrm] = '\0';
    NewPathFrm.get()[nLengthFrm + 1] = '\0';
    SHFILEOPSTRUCT FileOp;
    RtlZeroMemory((void*)&FileOp, sizeof(SHFILEOPSTRUCT));
    FileOp.fFlags = FOF_NOCONFIRMATION;
    FileOp.hNameMappings = NULL;
    FileOp.hwnd = NULL;
    FileOp.lpszProgressTitle = NULL;
    FileOp.pFrom = NewPathFrm.get();
    FileOp.pTo = lpszToPath;
    FileOp.wFunc = FO_COPY;
    return SHFileOperation(&FileOp) == 0;
}

void CeguiInject::installDll() {
    if (RegVip() == FALSE) {
        return;
    }
    ks_exit();

    QString strGame = ui.lineEdit_path->text();
    if (strGame.isEmpty()) {
        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("没有正确选择游戏路径!"));
        return;
    }

    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
    strDll = std::string((const char*)qstrDll.toLocal8Bit());

    strSplit = "/";
    index = strGame.lastIndexOf(strSplit);
    strGame = strGame.left(index);
    strGame.replace("/", "\\");
    std::string szGame = std::string((const char*)strGame.toLocal8Bit());
    
    CopyFolder((strDll + "\\datafiles").c_str(), szGame.c_str());
    Sleep(500);
    CopyFolder((strDll + "\\S").c_str(), szGame.c_str());
    Sleep(500);

    strSplit = "\\";
    index = strGame.lastIndexOf(strSplit);
    strGame = strGame.left(index);
    szGame = std::string((const char*)strGame.toLocal8Bit());
    CopyFolder((strDll + "\\Bin32").c_str(), szGame.c_str());
    Sleep(500);

    QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("辅助安装完毕!"));
}