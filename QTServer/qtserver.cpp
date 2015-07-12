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
#include "DataType.h"
#include "cthreadinjectdll.h"


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
    QObject::connect(ui.tableWidget, &CMyTableWidget::SignalStopScript, this, &QTServer::SlotStopScript);
    QObject::connect(ui.tableWidget, &CMyTableWidget::SignalStartScript, this, &QTServer::SlotStartScript);
}

QTServer::~QTServer() {

}

void QTServer::SlotNewConnect() {
    QTcpSocket* pTcpSocket = m_tcpServer->nextPendingConnection(); // �õ�ÿ����������socket
    //pTcpSocket->waitForConnected();
    //martin->Debug("State:%d ", pTcpSocket->state());
    m_tcpSocketList.append(pTcpSocket);
    connect(pTcpSocket, SIGNAL(disconnected()), this, SLOT(SlotClientClosed()));
    connect(pTcpSocket, SIGNAL(disconnected()), pTcpSocket, SLOT(deleteLater()));
    connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(SlotMessageRead()));
}

void QTServer::SlotMessageRead() {
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->bytesAvailable() > 0) {
            QByteArray qba = m_tcpSocketList[i]->readAll(); // ��ȡm_tcpSocket�е���������
            PSOCKET_INFO data = (PSOCKET_INFO)qba.data();
            int nCount = ui.tableWidget->rowCount();
            if (nCount) {
                for (int nCurrentRow = 0; nCurrentRow < nCount; nCurrentRow++) {
                    QTableWidgetItem* pItemAcc = ui.tableWidget->item(nCurrentRow, 0);
                    QString qstrAcc = pItemAcc->data(Qt::DisplayRole).toString(); //�˺�
                    std::string strAcc = std::string((const char*)qstrAcc.toLocal8Bit());

                    if (strAcc == std::string(data->szAccOrScript)) {
                        pItemAcc->setData(Qt::UserRole + 0x200, (int)m_tcpSocketList[i]);

                        switch (data->message) {
                        case SOCKET_MESSAGE::GetScript:
                            SOCKET_INFO socket_info;
                            RtlZeroMemory(&socket_info, sizeof(SOCKET_INFO));
                            socket_info.message = SOCKET_MESSAGE::GetScript;
                            QTableWidgetItem* pItemScript = ui.tableWidget->item(nCurrentRow, 3);
                            QString qstrScript = pItemScript->data(Qt::DisplayRole).toString(); // �ű�
                            std::string strScript = std::string((const char*)qstrScript.toLocal8Bit());
                            strcpy_s(socket_info.szAccOrScript, strScript.c_str());
                            QByteArray datasend;
                            datasend.append((const char*)&socket_info);
                            m_tcpSocketList[i]->write((const char*)&socket_info, sizeof(SOCKET_INFO));
                            //m_tcpSocketList[i]->waitForBytesWritten();
                            //martin->Debug("State:%d ", m_tcpSocketList[i]->state());
                            m_tcpSocketList[i]->flush();

                            QTableWidgetItem* pItemStatus = ui.tableWidget->item(nCurrentRow, 7);
                            pItemStatus->setData(Qt::DisplayRole, QStringLiteral("�һ���")); // �ű�
                            break;
                        }
                        break;
                    }
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

    std::vector<DWORD> processVec = martin->GetProcessIdVec("CryENGINE");
    g_processVec.swap(QVector<DWORD>());
    for (auto v : processVec) {
        g_processVec.append(v);
    }

    g_bInjectDll = TRUE;
    //::CloseHandle((HANDLE)_beginthreadex(NULL, 0, ThreadFun_InsertDLL, NULL, 0, NULL));
    CThreadInjectDll* thread = new CThreadInjectDll(this);
    thread->pItem = _strAcc;
    connect(thread, &CThreadInjectDll::SignalDone, this, &QTServer::SlotGuardDog);
    connect(thread, &CThreadInjectDll::finished, thread, &CThreadInjectDll::deleteLater);
    thread->start();

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
        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("������Ϸʧ��! �������̨��������!"));
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
        _strStatus->setData(Qt::DisplayRole, QStringLiteral("������Ϸ"));
        //QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("������Ϸ!"));
        // ����������Ź�
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

    CloseHandle(hMapping);
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

            if (strContent[4] != "�˺Ŷ���") {
                if (strContent[4] != "�������") {
                    strContent[4] = "����";
                }
            }

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

void QTServer::SlotGuardDog(QTableWidgetItem* pItem) {
    // �յ�������Ϣ, ˵��ע��ɹ���, �������Ź�
    int nCount = ui.tableWidget->rowCount();
    if (nCount) {
        for (int nCurrentRow = 0; nCurrentRow < nCount; nCurrentRow++) {
            QTableWidgetItem* pItemAcc = ui.tableWidget->item(nCurrentRow, 0);
            if (pItemAcc == pItem) {
                HWND hGameWnd = (HWND)(pItemAcc->data(Qt::UserRole + 0x100)).toInt();
                QTableWidgetItem* _strStatus = ui.tableWidget->item(nCurrentRow, 7);
                _strStatus->setData(Qt::DisplayRole, QStringLiteral("�ɹ���½"));
                break;
            }
        }
    }
}

void QTServer::SlotStopScript(const int &nRow) {
    QTableWidgetItem* pItemAcc = ui.tableWidget->item(nRow, 0);
    QTcpSocket* pTcpSocket = (QTcpSocket*)(pItemAcc->data(Qt::UserRole + 0x200)).toInt();
    if (pTcpSocket) {
        SOCKET_INFO socket_info;
        RtlZeroMemory(&socket_info, sizeof(SOCKET_INFO));
        socket_info.message = SOCKET_MESSAGE::StopScript;
        QByteArray datasend;
        datasend.append((const char*)&socket_info);
        pTcpSocket->write((const char*)&socket_info, sizeof(SOCKET_INFO));
        pTcpSocket->flush();
        QTableWidgetItem* pItemStatus = ui.tableWidget->item(nRow, 7);
        pItemStatus->setData(Qt::DisplayRole, QStringLiteral("�ɹ���½"));
    }
}

void QTServer::SlotStartScript(const int &nRow) {
    QTableWidgetItem* pItemAcc = ui.tableWidget->item(nRow, 0);
    QTcpSocket* pTcpSocket = (QTcpSocket*)(pItemAcc->data(Qt::UserRole + 0x200)).toInt();
    if (pTcpSocket) {
        SOCKET_INFO socket_info;
        RtlZeroMemory(&socket_info, sizeof(SOCKET_INFO));
        socket_info.message = SOCKET_MESSAGE::StartScript;
        QTableWidgetItem* pItemScript = ui.tableWidget->item(nRow, 3);
        QString qstrScript = pItemScript->data(Qt::DisplayRole).toString(); // �ű�
        std::string strScript = std::string((const char*)qstrScript.toLocal8Bit());
        strcpy_s(socket_info.szAccOrScript, strScript.c_str());
        QByteArray datasend;
        datasend.append((const char*)&socket_info);
        pTcpSocket->write((const char*)&socket_info, sizeof(SOCKET_INFO));
        pTcpSocket->flush();
        QTableWidgetItem* pItemStatus = ui.tableWidget->item(nRow, 7);
        pItemStatus->setData(Qt::DisplayRole, QStringLiteral("�һ���"));
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