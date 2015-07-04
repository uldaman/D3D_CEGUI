#ifndef CEGUIINJECT_H
#define CEGUIINJECT_H

#include <QtWidgets/QWidget>
#include "ui_ceguiinject.h"
#include <windows.h>


class CeguiInject : public QWidget {
    Q_OBJECT

public:
    CeguiInject(QWidget *parent = 0);
    ~CeguiInject();

private:
    Ui::CeguiInjectClass ui;
    QVBoxLayout* m_layout;
    QMenuBar* m_menuBar;
    QAction* m_actionNew;
    QMenu* m_menu;
    QString m_vipCard;
    void InitReg();
    BOOL RegVip();

    private slots:
    void runGame();
    void selectPath();
    void installDll();
    void OpenVip();
    void receiveVip(const QString & strCard) {
        m_vipCard = strCard;
    }
};

#endif // CEGUIINJECT_H
