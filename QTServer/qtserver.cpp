#include "qtserver.h"
#include "QTableWidget.h"
#include "atlconv.h"
#include "caddaccount.h"
#include "coption.h"
#include "CMartin.h"
#include "Xml.h"
#include "QMessageBox"

QTServer::QTServer(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    //
    GlobalAddAtom("shitnow");

    //���ñ�ͷ����С
    QStringList header;
    header << QStringLiteral("�˺�") << QStringLiteral("����") << QStringLiteral("������")
        << QStringLiteral("��ɫ") << QStringLiteral("���") << QStringLiteral("��ͼ") << QStringLiteral("�ű�");
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
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(new_connect()));

    //�˵�������
    connect(ui.actionAddAccount, SIGNAL(triggered()), this, SLOT(AddAccount()));
    connect(ui.actionOption, SIGNAL(triggered()), this, SLOT(OptionSet()));
    connect(ui.tableWidget, &CMyTableWidget::send_addAcc, this, &QTServer::addAcc);

    // ����Ϊ������Ϸ·��
    initGamePath();

    // �б���P
    QObject::connect(ui.tableWidget, &CMyTableWidget::startNewGame, this, &QTServer::startNewGame);
}

QTServer::~QTServer() {

}

void QTServer::new_connect() {
    QTcpSocket* pTcpSocket = m_tcpServer->nextPendingConnection();                     //�õ�ÿ����������socket
    m_tcpSocketList.append(pTcpSocket);
    connect(pTcpSocket, SIGNAL(disconnected()), this, SLOT(client_closed()));
    connect(pTcpSocket, SIGNAL(disconnected()), pTcpSocket, SLOT(deleteLater()));
    connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(message_read()));
}

void QTServer::message_read() {
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

void QTServer::client_closed() {
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->state() == QAbstractSocket::UnconnectedState) {
            m_tcpSocketList.removeAt(i);
        }
    }
}


void QTServer::AddAccount() {
    CAddAccount* a = new CAddAccount(this);
    a->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(a, &CAddAccount::newAcc, this, &QTServer::addAcc);
    a->show();
}

void QTServer::addAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer) {
    QTableWidgetItem* _strAcc = new QTableWidgetItem(strAcc);
    //_strAcc->setText(QString::fromWCharArray(A2W(data)));
    _strAcc->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _strAcc->setData(Qt::UserRole, strPsw); //��������, ���� MFC �е� SetItemData

    QTableWidgetItem* _strArea = new QTableWidgetItem(strArea);
    _strArea->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QTableWidgetItem* _strServer = new QTableWidgetItem(strServer);
    _strServer->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    //����rowCount()�õ���ǰ�е�������Ȼ���ڵ���insertRow(row);����
    int nIndex = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(nIndex);
    ui.tableWidget->setItem(nIndex, 0, _strAcc);
    ui.tableWidget->setItem(nIndex, 1, _strArea);
    ui.tableWidget->setItem(nIndex, 2, _strServer);
}

void QTServer::OptionSet() {
    COption* a = new COption(this, m_gamePath);
    QObject::connect(a, &COption::newGamePath, this, &QTServer::initGamePath);
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
}

void QTServer::initGamePath() {
    //-----------------------------------------------------------
    //    �@ȡ��ǰ����ȫ·��
    //-----------------------------------------------------------
    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);

    //-----------------------------------------------------------
    //    �D�Q�� QString, Ȼ��ȥ��·���е��ļ���, ������ǰĿ�
    //    �ڮ�ǰĿ�������������ļ��� 
    //-----------------------------------------------------------
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // ���÷��������������
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // ���÷�����ɳ������
    strDll = std::string((const char*)qstrDll.toLocal8Bit());
    strDll += "\\Config.ini";

    //-----------------------------------------------------------
    //    ��ȡ�����ļ���Ϣ
    //-----------------------------------------------------------
    martin->SetPathName(strDll.c_str());
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

void QTServer::startNewGame() {
    //if (martin->CreatProcessInsertDLL("F:\\ty\\bootloader.exe", "\"F:\\ty\\bootloader.exe\"  0", "Q:\\Ty\\TyInject\\Debug\\Inject.dll", "F:\\ty/")) {
    //    // ������سɹ�, ���_�� DLL ע�뾀��
    //}

    //std::list<_Xml> lAllVal;
    //std::vector<std::string> arrFindXmlKeyName;
    //arrFindXmlKeyName.swap(std::vector<std::string>());
    //arrFindXmlKeyName.push_back("VersionDemoStr");
    //CXml::DeadXml(lAllVal, arrFindXmlKeyName, "F:\\��������Online\\TCLS\\mmog_data.xml");
    //for (auto& v : lAllVal) {
    //    martin->Debug((v.KeyName + " -- " + v.Val).c_str());
    //}

    std::string  QxDllpath = "F:\\��������Online\\TCLS\\Tenio.ini";
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

    //CStringW cwDatiPwd, cwacc, cwpsw, cwarea, cwserver, cwDatiAcc;
    USES_CONVERSION;
    //cwacc = A2W(Ltp.Account);
    //cwpsw = A2W(Ltp.Key);
    //cwserver = A2W(Ltp.Server);
    //cwDatiAcc = A2W(m_Verificationcode.Use);
    //cwDatiPwd = A2W(m_Verificationcode.Key);
    //cwarea = A2W(Ltp.Area);

    std::string acc = "2631608094";
    std::string psw = "h0030526h";
    wcscpy_s(pLogMsg->acc, (acc.length() + 1) * 2, A2W(acc.c_str()));
    wcscpy_s(pLogMsg->psw, (psw.length() + 1) * 2, A2W(psw.c_str()));

    std::string area = "�����ڲ���";
    std::string server = "�����ڲ�1��";
    wcscpy_s(pLogMsg->area, (area.length() + 1) * 2, A2W(area.c_str()));
    wcscpy_s(pLogMsg->server, (server.length() + 1) * 2, A2W(server.c_str()));

    //wcscpy_s(pLogMsg->DatiAcc, wcslen(cwDatiAcc) + 1, cwDatiAcc);
    //wcscpy_s(pLogMsg->DatiPwd, wcslen(cwDatiPwd) + 1, cwDatiPwd);
}


