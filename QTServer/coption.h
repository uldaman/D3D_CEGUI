#ifndef COPTION_H
#define COPTION_H

#include <QDialog>
#include "ui_coption.h"
#include <windows.h>

class COption : public QDialog {
    Q_OBJECT

public:
    COption(QWidget *parent = 0);
    COption(QWidget *parent, QString qstrGamePath);
    ~COption();

private:
    Ui::COption ui;
    BOOL CopyFolder(const char* lpszFromPath, const char* lpszToPath);
    void installDll();

    private slots:
    void PushButton_Path();
    void PushButton_SaveAttribute();
    void PushButton_InitializesAttribute();

signals:
    void SignalNewGamePath(const QString &name);
};

#endif // COPTION_H
