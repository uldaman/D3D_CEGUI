#ifndef CMYTABLEWIDGET_H
#define CMYTABLEWIDGET_H

#include <QTableWidget>

class CMyTableWidget : public QTableWidget {
    Q_OBJECT

public:
    CMyTableWidget(QWidget *parent = 0);
    ~CMyTableWidget();
    QTableWidgetItem* m_itemAcc;
    //QString m_acc;
    //QString m_psw;
    QTableWidgetItem* m_itemArea;
    //QString m_area;
    QTableWidgetItem* m_itemServer;
    //QString m_server;
    QTableWidgetItem* m_itemScript;
    //QString m_script;

protected:
    void CreateActions();
    QMenu* m_popMenu;
    QAction* m_actionAdd;
    QAction* m_actionChange;
    QAction* m_actionStart;
    QAction* m_actionSeparator;
    int m_nRow;
    
    virtual void contextMenuEvent(QContextMenuEvent *event);
    
private slots:
void SlotAddAccount();
void SlotStartGame();
void SlotChangeAccount();
void SlotChangeAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript);
void SlotAddAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript);

signals:
//void SignalStartNewGame(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer);
void SignalStartNewGame(const int &nRow);
void SignalSendAddAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript);
};

#endif // CMYTABLEWIDGET_H
