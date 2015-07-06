#ifndef CADDACCOUNT_H
#define CADDACCOUNT_H

#include <QDialog>
#include "ui_caddaccount.h"

class CAddAccount : public QDialog
{
    Q_OBJECT

public:
    CAddAccount(QWidget *parent = 0);
    ~CAddAccount();

private:
    Ui::CAddAccount ui;
};

#endif // CADDACCOUNT_H
