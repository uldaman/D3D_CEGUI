#ifndef CEGUIINJECT_H
#define CEGUIINJECT_H

#include <QtWidgets/QWidget>
#include "ui_ceguiinject.h"


class CeguiInject : public QWidget {
    Q_OBJECT

public:
    CeguiInject(QWidget *parent = 0);
    ~CeguiInject();

private:
    Ui::CeguiInjectClass ui;

    private slots:
    void runGame();
    void selectPath();
};

#endif // CEGUIINJECT_H
