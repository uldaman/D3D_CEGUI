#ifndef CMYTABLEWIDGET_H
#define CMYTABLEWIDGET_H

#include <QTableWidget>

class CMyTableWidget : public QTableWidget {
    Q_OBJECT

public:
    CMyTableWidget(QWidget *parent = 0);
    ~CMyTableWidget();

protected:
    void CreateActions();
    QMenu* m_popMenu;
    QAction* m_actionAdd;
    QAction* m_actionStart;
    virtual void contextMenuEvent(QContextMenuEvent *event);
    
private slots:
void AddAccount();
void StartGame();
void addAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer);

signals:
void startNewGame();
void send_addAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer);
};

#endif // CMYTABLEWIDGET_H
