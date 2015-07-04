#ifndef CQVIP_H
#define CQVIP_H

#include <QDialog>
#include "ui_cqvip.h"

class CQVip : public QDialog {
    Q_OBJECT

public:
    CQVip(QDialog *parent = 0);
    ~CQVip();

private:
    Ui::CQVip ui;

    private slots:
    void SaveVip();

signals:
    void newVip(const QString &strCard);
};

#endif // CQVIP_H
