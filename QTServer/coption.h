#ifndef COPTION_H
#define COPTION_H

#include <QDialog>
#include "ui_coption.h"

class COption : public QDialog {
    Q_OBJECT

public:
    COption(QWidget *parent = 0);
    COption(QWidget *parent, QString qstrGamePath);
    ~COption();

private:
    Ui::COption ui;

    private slots:
    void PushButton_Path();

signals:
    void SignalNewGamePath(const QString &name);
};

#endif // COPTION_H
