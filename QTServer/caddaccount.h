#ifndef CADDACCOUNT_H
#define CADDACCOUNT_H

#include <QDialog>
#include "ui_caddaccount.h"

class CAddAccount : public QDialog {
    Q_OBJECT

public:
    CAddAccount(QWidget *parent = 0);
    ~CAddAccount();
    bool TransferScript();

private:
    Ui::CAddAccount ui;

    private slots:
    void PushButton_Enter_Acc();

signals:
    void SignalNewAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript); // Ìí¼ÓÐÂÕËºÅ
};

#endif // CADDACCOUNT_H