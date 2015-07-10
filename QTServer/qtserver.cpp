#include "qtserver.h"
#include "QTableWidget.h"
#include "atlconv.h"
#include "caddaccount.h"
#include "coption.h"
#include "CMartin.h"
#include "QMessageBox"
#include "Xml.h"
#include "QFileDialog"
#include <process.h>
#include <tlhelp32.h>
#include "forcelib\ForceLib.h"

QTServer::QTServer(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    //
    GlobalAddAtom("shitnow");

    //���ñ�ͷ����С
    QStringList header;
    header << QStringLiteral("�˺�") << QStringLiteral("����") << QStringLiteral("������") << QStringLiteral("�ű�")
        << QStringLiteral("��ɫ") << QStringLiteral("���") << QStringLiteral("��ͼ") << QStringLiteral("״̬");
    ui.tableWidget->setColumnCount(header.count());
    ui.tableWidget->setHorizontalHeaderLabels(header);
    //ui.tableWidget->setRowCount(20); // ��������
    ui.tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    //ui.tableWidget->setColumnWidth(0, 150); //���õ�һ�п��
    //ui.tableWidget->setColumnWidth(1, 150); //���õڶ��п��
    //ui.tableWidget->setColumnWidth(2, 150); //���õ����п��
    //ui.tableWidget->setColumnWidth(3, 150);
    //ui.tableWidget->setColumnWidth(4, 150);
    //ui.tableWidget->setColumnWidth(5, 150);
    //ui.tableWidget->setColumnWidth(6, 150);
    //ui.tableWidget->horizontalHeader()->setStretchLastSection(true); //�����һ�����쵽�����б�ȫ��
    ui.tableWidget->horizontalHeader()->setSectionsClickable(false); //���ñ�ͷ���ɵ����Ĭ�ϵ�����������
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // ����������Ӧ���ڿ��

    //���ø�һ�б�һ��ɫ������һ��һ��
    ui.tableWidget->setAlternatingRowColors(true);

    //�ؼ��տ�ʼ��ʱ�����Ĭ���Դ����кţ������ȥ����ߵ��кţ���������Ĵ���
    QHeaderView* headerView = ui.tableWidget->verticalHeader();
    headerView->setHidden(true);
    //����Ĭ���и�
    //headerView->setDefaultSectionSize(30);

    //����ѡ�еķ�ʽ
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //���ܶԱ�����ݽ����޸�
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any, 12589); //�����κ�����12589�˿ڵ�ip
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(SlotNewConnect()));

    //�˵�������
    connect(ui.actionAddAccount, SIGNAL(triggered()), this, SLOT(SlotAddAccount()));
    connect(ui.actionOption, SIGNAL(triggered()), this, SLOT(SlotOptionSet()));
    connect(ui.actionExportAcc, SIGNAL(triggered()), this, SLOT(SlotExportAcc()));
    connect(ui.actionImportAcc, SIGNAL(triggered()), this, SLOT(SlotImportAcc()));
    connect(ui.tableWidget, &CMyTableWidget::SignalSendAddAcc, this, &QTServer::SlotAddAcc);

    // ����Ϊ������Ϸ·��
    SlotInitGamePath();

    // �б���P
    QObject::connect(ui.tableWidget, &CMyTableWidget::SignalStartNewGame, this, &QTServer::SlotStartNewGame);
}

QTServer::~QTServer() {

}

void QTServer::SlotNewConnect() {
    QTcpSocket* pTcpSocket = m_tcpServer->nextPendingConnection(); // �õ�ÿ����������socket
    m_tcpSocketList.append(pTcpSocket);
    connect(pTcpSocket, SIGNAL(disconnected()), this, SLOT(SlotClientClosed()));
    connect(pTcpSocket, SIGNAL(disconnected()), pTcpSocket, SLOT(deleteLater()));
    connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(SlotMessageRead()));
}

enum class SOCKET_MESSAGE { // socket ��Ϣ����
    GetScript,
};

typedef struct SOCKET_INFO {
    SOCKET_MESSAGE message;
    char szAcc[25];
    char szName[25];
    int nLevel;
    char szMap[25];
    int nMoney;
}*PSOCKET_INFO;

void QTServer::SlotMessageRead() {
    USES_CONVERSION;
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->bytesAvailable() > 0) {
            QByteArray qba = m_tcpSocketList[i]->readAll(); // ��ȡm_tcpSocket�е���������
            PSOCKET_INFO data = (PSOCKET_INFO)qba.data();
            int nCount = ui.tableWidget->rowCount();
            if (nCount) {
                for (int nCurrentRow = 0; nCurrentRow < nCount; nCurrentRow++) {
                    QTableWidgetItem* pItem = ui.tableWidget->item(nCurrentRow, 0);
                    QString qstrAcc = pItem->data(Qt::DisplayRole).toString(); //�˺�
                    std::string strAcc = std::string((const char*)qstrAcc.toLocal8Bit());

                    if (strAcc == std::string(data->szAcc)) {
                        switch (data->message) {
                        case SOCKET_MESSAGE::GetScript:
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

void QTServer::SlotClientClosed() {
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->state() == QAbstractSocket::UnconnectedState) {
            m_tcpSocketList.removeAt(i);
        }
    }
}

void QTServer::SlotAddAccount() {
    CAddAccount* a = new CAddAccount;
    a->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(a, &CAddAccount::SignalNewAcc, this, &QTServer::SlotAddAcc);
    a->show();
}

void QTServer::SlotAddAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript) {
    QTableWidgetItem* _strAcc = new QTableWidgetItem(strAcc);
    //_strAcc->setText(QString::fromWCharArray(A2W(data)));
    _strAcc->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _strAcc->setData(Qt::UserRole, strPsw); //��������, ���� MFC �е� SetItemData

    QTableWidgetItem* _strArea = new QTableWidgetItem(strArea);
    _strArea->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTableWidgetItem* _strServer = new QTableWidgetItem(strServer);
    _strServer->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTableWidgetItem* _strScript = new QTableWidgetItem(strScript);
    _strScript->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTableWidgetItem* _strStatus = new QTableWidgetItem(QStringLiteral("����"));
    _strStatus->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //����rowCount()�õ���ǰ�е�������Ȼ���ڵ���insertRow(row);����
    int nIndex = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(nIndex);
    ui.tableWidget->setItem(nIndex, 0, _strAcc);
    ui.tableWidget->setItem(nIndex, 1, _strArea);
    ui.tableWidget->setItem(nIndex, 2, _strServer);
    ui.tableWidget->setItem(nIndex, 3, _strScript);
    ui.tableWidget->setItem(nIndex, 7, _strStatus);
}

void QTServer::SlotOptionSet() {
    COption* a = new COption(this, m_gamePath);
    QObject::connect(a, &COption::SignalNewGamePath, this, &QTServer::SlotInitGamePath);
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
}

void QTServer::SlotInitGamePath() {
    std::string strPath = martin->GetModulePath(NULL);
    strPath += "\\Config.ini";

    //-----------------------------------------------------------
    //    ��ȡ�����ļ���Ϣ
    //-----------------------------------------------------------
    martin->SetPathName(strPath.c_str());
    m_gamePath = QString::fromLocal8Bit(martin->GetString("Path", "Game").c_str());
}

#pragma pack(push, 1)
typedef struct {
    DWORD dwRet;
    DWORD Key;
    WCHAR DatiAcc[25];
    WCHAR DatiPwd[25];
    DWORD DatiErrorCode;
    DWORD DatiType;
    DWORD cmdtype;
    WCHAR acc[25];
    WCHAR psw[25];
    WCHAR area[25];
    WCHAR server[25];
}ShareLoginInfo, *PShareLoginInfo;
#pragma pack(pop,1)

enum SHARELGOININFOSTATE { //�Զ���¼dll(��)
    SHARELGOININFOSTATE_INFO = 1, //���ߵ�½����ʼ��½�˺�
    SHARELGOININFOSTATE_SUCCEED, //�ɹ���½
    SHARELGOININFOSTATE_CLOSE, //���ߵ�½���ر�
    SHARELGOINRET_ERROR_ACCDONGJIE, //������
    SHARELGOINRET_ERROR_PSWWRONG
};

static BOOL g_bInjectDll = FALSE;

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

unsigned __stdcall ThreadFun_InsertDLL(void * pParam) {
    PROCESSENTRY32 pe32;
    while (!GetProcessOf("MHOClient.exe", &pe32)) {
        //if (GetAsyncKeyState(VK_ESCAPE)) {
        //    return;
        //}
        if (g_bInjectDll == FALSE) {
            return 0;
        }
        Sleep(10);
    }

    THREADENTRY32 te32;
    while (!GetThreadOf(pe32.th32ProcessID, &te32)) {
        if (g_bInjectDll == FALSE) {
            return 0;
        }
        Sleep(2);
    }

    PROCESS_INFORMATION PI;
    PI.dwProcessId = pe32.th32ProcessID;
    PI.dwThreadId = te32.th32ThreadID;
    PI.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);

    std::string strDll = martin->GetModulePath(NULL);
    strDll += "\\D3D9_CEGUI.dll";

    if (!ForceLibrary(strDll.c_str(), &PI)) {
        TerminateProcess(PI.hProcess, 0);
        ::MessageBox(NULL, "�޷��������...", "Tatnium Error", MB_ICONERROR);
    }

    CloseHandle(PI.hProcess);

    return 0;
}

void QTServer::SlotStartNewGame(const int &nRow) {
    QString gamePath = m_gamePath;
    std::string QxDllpath = (const char*)(gamePath.replace("/", "\\").toLocal8Bit());
    QxDllpath += "\\TCLS\\Tenio.ini";
    WritePrivateProfileString("DefaultValue", "Dlls", "TCLS.dll,TenBase.dll,Dir.dll,TenTPF.dll,MemoryAlloctor.dll,June.dll,log.dll,qxpatch.dll", QxDllpath.c_str());
    HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x255, "GW_APSInfo");

    DWORD dwMyPid = ::GetCurrentProcessId();
    PShareLoginInfo pLogMsg = (PShareLoginInfo)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    RtlZeroMemory(pLogMsg, sizeof(PShareLoginInfo));
    pLogMsg->cmdtype = SHARELGOININFOSTATE_INFO;
    pLogMsg->dwRet = 0;
    pLogMsg->Key = (dwMyPid * 22) >> 2;
    pLogMsg->DatiType = 0;
    pLogMsg->DatiErrorCode = 0;

    USES_CONVERSION;
    QTableWidgetItem* _strAcc = ui.tableWidget->item(nRow, 0);
    QString strAcc = _strAcc->data(Qt::DisplayRole).toString();
    QString strPsw = _strAcc->data(Qt::UserRole).toString();

    QTableWidgetItem* _strArea = ui.tableWidget->item(nRow, 1);
    QString strArea = _strArea->data(Qt::DisplayRole).toString();

    QTableWidgetItem* _strServer = ui.tableWidget->item(nRow, 2);
    QString strServer = _strServer->data(Qt::DisplayRole).toString();

    QTableWidgetItem* _strScript = ui.tableWidget->item(nRow, 3);
    //QString strScript = _strScript->data(Qt::DisplayRole).toString();

    QTableWidgetItem* _strStatus = ui.tableWidget->item(nRow, 7);
    //QString strStatus = _strStatus->data(Qt::DisplayRole).toString();

    std::string acc = ((const char*)strAcc.toLocal8Bit());
    std::string psw = ((const char*)strPsw.toLocal8Bit());
    wcscpy_s(pLogMsg->acc, (acc.length() + 1) * 2, A2W(acc.c_str()));
    wcscpy_s(pLogMsg->psw, (psw.length() + 1) * 2, A2W(psw.c_str()));

    std::string area = ((const char*)strArea.toLocal8Bit());
    std::string server = ((const char*)strServer.toLocal8Bit());
    wcscpy_s(pLogMsg->area, (area.length() + 1) * 2, A2W(area.c_str()));
    wcscpy_s(pLogMsg->server, (server.length() + 1) * 2, A2W(server.c_str()));

    //wcscpy_s(pLogMsg->DatiAcc, wcslen(cwDatiAcc) + 1, cwDatiAcc);
    //wcscpy_s(pLogMsg->DatiPwd, wcslen(cwDatiPwd) + 1, cwDatiPwd);

    g_bInjectDll = TRUE;
    ::CloseHandle((HANDLE)_beginthreadex(NULL, 0, ThreadFun_InsertDLL, NULL, 0, NULL));

    QString loginPath = m_gamePath;
    std::string strLoginPath = (const char*)(loginPath.replace("/", "\\").toLocal8Bit());
    strLoginPath += "\\TCLS\\Client.exe";
    STARTUPINFO StartupInfo = { sizeof(STARTUPINFO) }; // ��һ�������� STARTUPINFO.cb
    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = TRUE;
    PROCESS_INFORMATION ProcessInformation;
    BOOL bRet = ::CreateProcess(
        strLoginPath.c_str(),
        NULL,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT | CREATE_DEFAULT_ERROR_MODE,
        NULL,
        NULL,
        &StartupInfo,
        &ProcessInformation);
    if (bRet == 0) {
        g_bInjectDll = FALSE;
        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("������Ϸʧ��! ���Ժ�����!"));
        return;
    }

    ::CloseHandle(ProcessInformation.hThread);
    ::CloseHandle(ProcessInformation.hProcess);

    int RunTimeout = 0;
    while (pLogMsg->cmdtype == SHARELGOININFOSTATE_INFO) { //�ȴ�����״̬
        Sleep(1000);
        RunTimeout += 1000;

        if (RunTimeout >= 5000) {
            if (WhetherIsUpdated()) { // �����Ϸ�Ƿ����
                g_bInjectDll = FALSE;
                QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("��Ϸ�и���! ��������!"));
                return;
            }
        }

        if (RunTimeout > 180000) {
            g_bInjectDll = FALSE;
            _strStatus->setData(Qt::DisplayRole, QStringLiteral("��¼��ʱ"));
            QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("��¼��ʱ! �����˺���Ϣ!!"));
            return;
        }
    }

    switch (pLogMsg->cmdtype) {
    case SHARELGOININFOSTATE_SUCCEED: // �ɹ���½
        _strStatus->setData(Qt::DisplayRole, QStringLiteral("�ɹ���¼"));
        //QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("�ɹ���¼!"));
        return;
    case SHARELGOINRET_ERROR_ACCDONGJIE:
        g_bInjectDll = FALSE;
        _strStatus->setData(Qt::DisplayRole, QStringLiteral("�˺Ŷ���"));
        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("�˺ű�����!"));
        return;
    case SHARELGOINRET_ERROR_PSWWRONG://�������
        g_bInjectDll = FALSE;
        _strStatus->setData(Qt::DisplayRole, QStringLiteral("�������"));
        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("�������!"));
        return;
    }
}

//void QTServer::SlotStartNewGame(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer) {
//    //if (martin->CreatProcessInsertDLL("F:\\ty\\bootloader.exe", "\"F:\\ty\\bootloader.exe\"  0", "Q:\\Ty\\TyInject\\Debug\\Inject.dll", "F:\\ty/")) {
//    //    // ������سɹ�, ���_�� DLL ע�뾀��
//    //}
//
//    QString gamePath = m_gamePath;
//    std::string QxDllpath = (const char*)(gamePath.replace("/", "\\").toLocal8Bit());
//    QxDllpath += "\\TCLS\\Tenio.ini";
//    WritePrivateProfileString("DefaultValue", "Dlls", "TCLS.dll,TenBase.dll,Dir.dll,TenTPF.dll,MemoryAlloctor.dll,June.dll,log.dll,qxpatch.dll", QxDllpath.c_str());
//    HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0x255, "GW_APSInfo");
//
//    DWORD dwMyPid = ::GetCurrentProcessId();
//    PShareLoginInfo pLogMsg = (PShareLoginInfo)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
//    RtlZeroMemory(pLogMsg, sizeof(PShareLoginInfo));
//    pLogMsg->cmdtype = SHARELGOININFOSTATE_INFO;
//    pLogMsg->dwRet = 0;
//    pLogMsg->Key = (dwMyPid * 22) >> 2;
//    pLogMsg->DatiType = 0;
//    pLogMsg->DatiErrorCode = 0;
//
//    USES_CONVERSION;
//
//    std::string acc = ((const char*)strAcc.toLocal8Bit());
//    std::string psw = ((const char*)strPsw.toLocal8Bit());
//    wcscpy_s(pLogMsg->acc, (acc.length() + 1) * 2, A2W(acc.c_str()));
//    wcscpy_s(pLogMsg->psw, (psw.length() + 1) * 2, A2W(psw.c_str()));
//
//    std::string area = ((const char*)strArea.toLocal8Bit());
//    std::string server = ((const char*)strServer.toLocal8Bit());
//    wcscpy_s(pLogMsg->area, (area.length() + 1) * 2, A2W(area.c_str()));
//    wcscpy_s(pLogMsg->server, (server.length() + 1) * 2, A2W(server.c_str()));
//
//    //wcscpy_s(pLogMsg->DatiAcc, wcslen(cwDatiAcc) + 1, cwDatiAcc);
//    //wcscpy_s(pLogMsg->DatiPwd, wcslen(cwDatiPwd) + 1, cwDatiPwd);
//
//    QString loginPath = m_gamePath;
//    std::string strLoginPath = (const char*)(loginPath.replace("/", "\\").toLocal8Bit());
//    strLoginPath += "\\TCLS\\Client.exe";
//    STARTUPINFO StartupInfo = { sizeof(STARTUPINFO) }; // ��һ�������� STARTUPINFO.cb
//    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
//    StartupInfo.wShowWindow = TRUE;
//    PROCESS_INFORMATION ProcessInformation;
//    BOOL bRet = ::CreateProcess(
//        strLoginPath.c_str(),
//        NULL,
//        NULL,
//        NULL,
//        FALSE,
//        CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT | CREATE_DEFAULT_ERROR_MODE,
//        NULL,
//        NULL,
//        &StartupInfo,
//        &ProcessInformation);
//    if (bRet == 0) {
//        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("������Ϸʧ��! ���Ժ�����!"));
//        return;
//    }
//
//    ::CloseHandle(ProcessInformation.hThread);
//    ::CloseHandle(ProcessInformation.hProcess);
//
//    int RunTimeout = 0;
//    while (pLogMsg->cmdtype == SHARELGOININFOSTATE_INFO) { //�ȴ�����״̬
//        Sleep(1000);
//        RunTimeout += 1000;
//
//        if (RunTimeout >= 5000) {
//            if (WhetherIsUpdated()) { // �����Ϸ�Ƿ����
//                QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("��Ϸ�и���! ��������!"));
//                return;
//            }
//        }
//
//        if (RunTimeout > 180000) {
//            QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("��¼��ʱ! �����˺���Ϣ!!"));
//            return;
//        }
//    }
//
//    switch (pLogMsg->cmdtype) {
//    case SHARELGOININFOSTATE_SUCCEED: // �ɹ���½
//        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("�ɹ���¼!"));
//        break;
//    case SHARELGOINRET_ERROR_ACCDONGJIE:
//        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("�˺ű�����!"));
//        return;
//    case SHARELGOINRET_ERROR_PSWWRONG://�������
//        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("�������!"));
//        return;
//    }
//}

BOOL QTServer::WhetherIsUpdated() {
    std::list<_Xml> lAllVal;
    std::vector<std::string> arrFindXmlKeyName;
    arrFindXmlKeyName.swap(std::vector<std::string>());
    arrFindXmlKeyName.push_back("VersionDemoStr");

    QString gamePath = m_gamePath;
    std::string strVer = (const char*)(gamePath.replace("/", "\\").toLocal8Bit());
    strVer += "\\TCLS\\mmog_data.xml";

    CXml::DeadXml(lAllVal, arrFindXmlKeyName, strVer);
    if (lAllVal.front().Val != g_strVersion) {
        //MessageBox(NULL, "��Ϸ�и���! ��������!", "��ʾ", MB_OK);
        //ExitProcess(0);
        return TRUE;
    }
    return FALSE;
}

void QTServer::SlotExportAcc() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "user.ini");

    if (!fileName.isEmpty()) {
        std::string strUser = (const char*)(fileName.replace("/", "\\").toLocal8Bit());
        martin->SetPathName(strUser.c_str());
        martin->DeleteSection("user");

        int nCount = ui.tableWidget->rowCount();
        if (nCount) {
            for (int nCurrentRow = 0; nCurrentRow < nCount; nCurrentRow++) {
                std::vector<std::string> userVector;
                QTableWidgetItem* pItem = ui.tableWidget->item(nCurrentRow, 0); 
                QString strAcc = pItem->data(Qt::DisplayRole).toString(); //�˺�
                QString strPsw = pItem->data(Qt::UserRole).toString(); //����
                userVector.push_back((const char*)strPsw.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 1);
                QString strArea = pItem->data(Qt::DisplayRole).toString(); // ����
                userVector.push_back((const char*)strArea.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 2);
                QString strServer = pItem->data(Qt::DisplayRole).toString(); // ��
                userVector.push_back((const char*)strServer.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 3);
                QString strScript = pItem->data(Qt::DisplayRole).toString(); // �ű�
                userVector.push_back((const char*)strScript.toLocal8Bit());

                pItem = ui.tableWidget->item(nCurrentRow, 7);
                QString strStatus = pItem->data(Qt::DisplayRole).toString(); // ״̬
                userVector.push_back((const char*)strStatus.toLocal8Bit());
                
                martin->WriteArray("user", (const char*)strAcc.toLocal8Bit(), &userVector);
            }
        }
    }
}

void QTServer::SlotImportAcc() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "user.ini", "ini (*.ini)");

    if (!fileName.isEmpty()) {
        std::string strUser = (const char*)(fileName.replace("/", "\\").toLocal8Bit());
        martin->SetPathName(strUser.c_str());

        std::vector<std::string> strFilterName;
        std::vector<std::string> strContent;
        martin->GetKeyNames("user", &strFilterName);
        for (auto& v : strFilterName) {
            QTableWidgetItem* _strAcc = new QTableWidgetItem(QString::fromLocal8Bit(v.c_str()));
            _strAcc->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            martin->GetArray("user", v.c_str(), &strContent);
            _strAcc->setData(Qt::UserRole, QString::fromLocal8Bit(strContent[0].c_str()));

            QTableWidgetItem* _strArea = new QTableWidgetItem(QString::fromLocal8Bit(strContent[1].c_str()));
            _strArea->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            QTableWidgetItem* _strServer = new QTableWidgetItem(QString::fromLocal8Bit(strContent[2].c_str()));
            _strServer->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            QTableWidgetItem* _strScript = new QTableWidgetItem(QString::fromLocal8Bit(strContent[3].c_str()));
            _strScript->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

            QTableWidgetItem* _strStatus = new QTableWidgetItem(QString::fromLocal8Bit(strContent[4].c_str()));
            _strStatus->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            //����rowCount()�õ���ǰ�е�������Ȼ���ڵ���insertRow(row);����
            int nIndex = ui.tableWidget->rowCount();
            ui.tableWidget->insertRow(nIndex);
            ui.tableWidget->setItem(nIndex, 0, _strAcc);
            ui.tableWidget->setItem(nIndex, 1, _strArea);
            ui.tableWidget->setItem(nIndex, 2, _strServer);
            ui.tableWidget->setItem(nIndex, 3, _strScript);
            ui.tableWidget->setItem(nIndex, 7, _strStatus);
        }
    }
}

//std::string QTServer::GetGetCurentModulePath() {
//    //-----------------------------------------------------------
//    //    �@ȡ��ǰ����ȫ·��
//    //-----------------------------------------------------------
//    char dllname[MAX_PATH];
//    GetModuleFileName(NULL, dllname, MAX_PATH);
//
//    //-----------------------------------------------------------
//    //    �D�Q�� QString, Ȼ��ȥ��·���е��ļ���, ������ǰĿ�
//    //-----------------------------------------------------------
//    std::string strDll = dllname;
//    //QString qstrDll = QString::fromStdString(strDll); // ���÷��������������
//    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
//    QString strSplit = "\\";
//    int index = qstrDll.lastIndexOf(strSplit);
//    qstrDll = qstrDll.left(index);
//    //strDll = qstrDll.toStdString(); // ���÷�����ɳ������
//    strDll = std::string((const char*)qstrDll.toLocal8Bit());
//    return strDll;
//}