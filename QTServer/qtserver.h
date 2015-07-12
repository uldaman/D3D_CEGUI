#ifndef QTSERVER_H
#define QTSERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_qtserver.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <windows.h>

const std::string g_strVersion = "0.4.19";

class QTServer : public QMainWindow {
    Q_OBJECT

public:
    QTServer(QWidget *parent = 0);
    ~QTServer();

private:
    Ui::QTServerClass ui;
    QTcpServer* m_tcpServer;
    QList<QTcpSocket *> m_tcpSocketList; //连接成功的套接字
    QString m_gamePath;
    BOOL WhetherIsUpdated();

    //std::string GetGetCurentModulePath();

    private slots:
    void SlotMessageRead();
    void SlotClientClosed();
    void SlotNewConnect();
    void SlotAddAccount();
    void SlotOptionSet();
    void SlotExportAcc();
    void SlotImportAcc();
    //void SlotStartNewGame(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer);
    void SlotStartNewGame(const int &nRow);
    void SlotStopScript(const int &nRow);
    void SlotStartScript(const int &nRow);
    void SlotInitGamePath();
    void SlotAddAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript);
    void SlotGuardDog(QTableWidgetItem* pItem);
};

#endif // QTSERVER_H