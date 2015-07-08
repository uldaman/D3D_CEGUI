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

    //设置表头及大小
    QStringList header;
    header << QStringLiteral("账号") << QStringLiteral("密码") << QStringLiteral("角色") << QStringLiteral("金币");
    ui.tableWidget->setColumnCount(header.count());
    ui.tableWidget->setRowCount(10);
    ui.tableWidget->setHorizontalHeaderLabels(header);
    ui.tableWidget->setColumnWidth(0, 150);//设置第一列宽度
    ui.tableWidget->setColumnWidth(1, 150);//设置第二列宽度
    ui.tableWidget->setColumnWidth(2, 150);//设置第三列宽度
    ui.tableWidget->horizontalHeader()->setStretchLastSection(true);//将最后一列延伸到整个列表全满

    //设置隔一行变一颜色，即：一灰一白
    ui.tableWidget->setAlternatingRowColors(true);

    //控件刚开始的时候左边默认自带序列号，如果想去掉左边的行号，加上下面的代码
    QHeaderView* headerView = ui.tableWidget->verticalHeader();
    headerView->setHidden(true);
    //设置默认行高
    //headerView->setDefaultSectionSize(30);

    //整行选中的方式
    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //不能对表格内容进行修改
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any, 12589); //监听任何连上12589端口的ip
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(new_connect()));

    //菜单栏关联
    connect(ui.actionAddAccount, SIGNAL(triggered()), this, SLOT(AddAccount()));
    connect(ui.actionOption, SIGNAL(triggered()), this, SLOT(OptionSet()));

    // 以下为设置游戏路径
    initGamePath();

    // 列表框關聯
    QObject::connect(ui.tableWidget, &CMyTableWidget::startNewGame, this, &QTServer::startNewGame);
}

QTServer::~QTServer() {

}

void QTServer::new_connect() {
    QTcpSocket* pTcpSocket = m_tcpServer->nextPendingConnection();                     //得到每个连进来的socket
    m_tcpSocketList.append(pTcpSocket);
    connect (pTcpSocket, SIGNAL(disconnected()), this, SLOT(client_closed()));
    connect(pTcpSocket, SIGNAL(disconnected()), pTcpSocket, SLOT(deleteLater()));
    connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(message_read()));
}

void QTServer::message_read() {
    USES_CONVERSION;
    for (int i = 0; i < m_tcpSocketList.length(); i++) {
        if (m_tcpSocketList[i]->bytesAvailable() > 0) {
            QByteArray qba = m_tcpSocketList[i]->readAll();                    //收取m_tcpSocket中的所有数据
            char* data = qba.data();
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromWCharArray(A2W(data)));
            //item->setText(QString::fromWCharArray(A2W(data)));
            item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            item->setData(Qt::UserRole, 6); //关联数据, 类似 MFC 中的 SetItemData
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
    //    獲取當前程序全路徑
    //-----------------------------------------------------------
    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);

    //-----------------------------------------------------------
    //    轉換成 QString, 然後去掉路徑中的文件名, 保留當前目錄
    //    在當前目錄後面加上配置文件名 
    //-----------------------------------------------------------
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
    strDll = std::string((const char*)qstrDll.toLocal8Bit());
    strDll += "\\Config.ini";

    //-----------------------------------------------------------
    //    获取配置文件信息
    //-----------------------------------------------------------
    martin->SetPathName(strDll.c_str());
    m_gamePath = QString::fromLocal8Bit(martin->GetString("Path", "Game").c_str());
}

void QTServer::startNewGame() {
    //if (martin->CreatProcessInsertDLL("F:\\ty\\bootloader.exe", "\"F:\\ty\\bootloader.exe\"  0", "Q:\\Ty\\TyInject\\Debug\\Inject.dll", "F:\\ty/")) {
    //    // 如果返回成功, 就開啟 DLL 注入線程
    //}

    std::list<_Xml> lAllVal;
    std::vector<std::string> arrFindXmlKeyName;
    arrFindXmlKeyName.swap(std::vector<std::string>());
    arrFindXmlKeyName.push_back("VersionDemoStr");
    CXml::DeadXml(lAllVal, arrFindXmlKeyName, "F:\\怪物猎人Online\\TCLS\\mmog_data.xml");
    for (auto& v : lAllVal) {
        martin->Debug((v.KeyName + " -- " + v.Val).c_str());
    }
    
    //if (lAllVal.front().Val.Find(Edition) != -1)
    //    return FALSE;
    //return TRUE;
}

