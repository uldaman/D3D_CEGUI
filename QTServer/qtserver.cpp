#include "qtserver.h"
#include "QTableWidget.h"
#include "atlconv.h"
#include "caddaccount.h"
#include "coption.h"
#include "CMartin.h"
#include "QMessageBox"
#include "Xml.h"

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
    connect(ui.tableWidget, &CMyTableWidget::SignalSendAddAcc, this, &QTServer::SlotAddAcc);

    // ����Ϊ������Ϸ·��
    SlotInitGamePath();

    // �б���P
    QObject::connect(ui.tableWidget, &CMyTableWidget::SignalStartNewGame, this, &QTServer::SlotStartNewGame);
}

QTServer::~QTServer() {

}

void QTServer::SlotNewConnect() {
    QTcpSocket* pTcpSocket = m_tcpServer->nextPendingConnection();                     //�õ�ÿ����������socket
    m_tcpSocketList.append(pTcpSocket);
    connect(pTcpSocket, SIGNAL(disconnected()), this, SLOT(SlotClientClosed()));
    connect(pTcpSocket, SIGNAL(disconnected()), pTcpSocket, SLOT(deleteLater()));
    connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(SlotMessageRead()));
}

void QTServer::SlotMessageRead() {
    USES_CONVERSION;
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->bytesAvailable() > 0) {
            QByteArray qba = m_tcpSocketList[i]->readAll();                    //��ȡm_tcpSocket�е���������
            char* data = qba.data();
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromWCharArray(A2W(data)));
            //item->setText(QString::fromWCharArray(A2W(data)));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setData(Qt::UserRole, 6); //��������, ���� MFC �е� SetItemData
            ui.tableWidget->setItem(0, 0, item);
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

    //����rowCount()�õ���ǰ�е�������Ȼ���ڵ���insertRow(row);����
    int nIndex = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(nIndex);
    ui.tableWidget->setItem(nIndex, 0, _strAcc);
    ui.tableWidget->setItem(nIndex, 1, _strArea);
    ui.tableWidget->setItem(nIndex, 2, _strServer);
    ui.tableWidget->setItem(nIndex, 3, _strScript);
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

void QTServer::SlotStartNewGame(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer) {
    //if (martin->CreatProcessInsertDLL("F:\\ty\\bootloader.exe", "\"F:\\ty\\bootloader.exe\"  0", "Q:\\Ty\\TyInject\\Debug\\Inject.dll", "F:\\ty/")) {
    //    // ������سɹ�, ���_�� DLL ע�뾀��
    //}
    if (WhetherIsUpdated()) {
        QMessageBox::about(this, QStringLiteral("��ʾ"), QStringLiteral("��Ϸ�и���! ��������!"));
        return;
    }

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
}

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