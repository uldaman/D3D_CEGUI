#ifndef QTSERVER_H
#define QTSERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_qtserver.h"
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class QTServer : public QMainWindow
{
    Q_OBJECT

public:
    QTServer(QWidget *parent = 0);
    ~QTServer();

private:
    Ui::QTServerClass ui;
    QTcpServer* m_tcpServer;
    QList<QTcpSocket *> m_tcpSocketList; //连接成功的套接字
    QString m_gamePath;
    
private slots:
    void message_read();
    void client_closed();
    void new_connect();
    void AddAccount();
    void OptionSet();
    void startNewGame();
    void initGamePath();
};

#endif // QTSERVER_H
