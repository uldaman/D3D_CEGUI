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
    QString fileName = QFileDialog::getExistingDirectory(this, "Open Directory", NULL, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!fileName.isEmpty()) {
        ui.lineEdit_path->setText(fileName);

        // 以下為了設置 ini 配置文件
        //-----------------------------------------------------------
        //    獲取當前程序全路徑
        //-----------------------------------------------------------
        char dllname[MAX_PATH];
        GetModuleFileName(NULL, dllname, MAX_PATH);

        //-----------------------------------------------------------
        //    轉換成 QString, 然後去掉路徑中的文件名, 保留當前目錄
        //    在當前目錄後面加上配置文件名 
        //-----------------------------------------------------------
        std::string strDll = dllname;
        //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
        QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
        QString strSplit = "\\";
        int index = qstrDll.lastIndexOf(strSplit);
        qstrDll = qstrDll.left(index);
        //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
        strDll = std::string((const char*)qstrDll.toLocal8Bit());
        strDll += "\\Config.ini";

        //-----------------------------------------------------------
        //    保存配置文件
        //-----------------------------------------------------------
        martin->SetPathName(strDll.c_str());
        martin->DeleteSection(TEXT("Path"));
        martin->WriteString("Path", "Game", (const char*)fileName.toLocal8Bit());

        // 本窗口设置完后, 还要通知主窗口
        emit newGamePath(fileName);
    }
}
