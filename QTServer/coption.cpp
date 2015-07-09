#include "coption.h"
#include <windows.h>
#include <QFile>
#include <QFileDialog>
#include <libloaderapi.h>
#include "CMartin.h"

COption::COption(QWidget *parent)
    : QDialog(parent) {
    ui.setupUi(this);
    connect(ui.pushButton_path, SIGNAL(clicked()), this, SLOT(PushButton_Path()));
}

COption::COption(QWidget *parent, QString qstrGamePath)
    : COption(parent) {
    ui.lineEdit_path->setText(qstrGamePath);
}

COption::~COption() {

}

void COption::PushButton_Path() {
    QString currentPath = ui.lineEdit_path->text();
    QString fileName = QFileDialog::getExistingDirectory(this, "Open Directory", currentPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!fileName.isEmpty()) {
        ui.lineEdit_path->setText(fileName);

        std::string strPath = martin->GetModulePath(NULL);
        strPath += "\\Config.ini";

        //-----------------------------------------------------------
        //    ���������ļ�
        //-----------------------------------------------------------
        martin->SetPathName(strPath.c_str());
        martin->DeleteSection(TEXT("Path"));
        martin->WriteString("Path", "Game", (const char*)fileName.toLocal8Bit());

        // �������������, ��Ҫ֪ͨ������
        emit SignalNewGamePath(fileName);
    }
}