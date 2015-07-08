#include "qtserver.h"
#include "QTableWidget.h"
#include "atlconv.h"
#include "caddaccount.h"
#include "coption.h"
#include "CMartin.h"
#include "Xml.h"

QTServer::QTServer(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    //���ñ�ͷ����С
    QStringList header;
    header << QStringLiteral("�˺�") << QStringLiteral("����") << QStringLiteral("��ɫ") << QStringLiteral("���");
    ui.tableWidget->setColumnCount(header.count());
    ui.tableWidget->setRowCount(10);
    ui.tableWidget->setHorizontalHeaderLabels(header);
    ui.tableWidget->setColumnWidth(0, 150);//���õ�һ�п��
    ui.tableWidget->setColumnWidth(1, 150);//���õڶ��п��
    ui.tableWidget->setColumnWidth(2, 150);//���õ����п��
    ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//�����һ�����쵽�����б�ȫ��

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
    connect (pTcpSocket, SIGNAL(disconnected()), this, SLOT(client_closed()));
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
    a->show();
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

void QTServer::startNewGame() {
    //if (martin->CreatProcessInsertDLL("F:\\ty\\bootloader.exe", "\"F:\\ty\\bootloader.exe\"  0", "Q:\\Ty\\TyInject\\Debug\\Inject.dll", "F:\\ty/")) {
    //    // ������سɹ�, ���_�� DLL ע�뾀��
    //}

    std::list<_Xml> lAllVal;
    std::vector<std::string> arrFindXmlKeyName;
    arrFindXmlKeyName.swap(std::vector<std::string>());
    arrFindXmlKeyName.push_back("VersionDemoStr");
    CXml::DeadXml(lAllVal, arrFindXmlKeyName, "F:\\��������Online\\TCLS\\mmog_data.xml");
    for (auto& v : lAllVal) {
        martin->Debug((v.KeyName + " -- " + v.Val).c_str());
    }
    
    //if (lAllVal.front().Val.Find(Edition) != -1)
    //    return FALSE;
    //return TRUE;
}

