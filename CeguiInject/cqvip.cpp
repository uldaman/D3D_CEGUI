#include "cqvip.h"
#include "..\D3D9_CEGUI\My_Ini.h"
#include "QMessageBox"

CQVip::CQVip(QDialog *parent)
    : QDialog(parent) {
    ui.setupUi(this);

    ///////////////////////////////////////////////////////////////////////////////

    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
    strDll = std::string((const char*)qstrDll.toLocal8Bit());
    strDll += "\\Config.ini";
    CMy_Ini obj_ini(strDll.c_str());
    QString strVip = QString::fromLocal8Bit(obj_ini.GetString("Vip", "Card").c_str());
    ui.lineEdit_vip->setText(strVip);

    ///////////////////////////////////////////////////////////////////////////////
}

CQVip::~CQVip() {

}

void CQVip::SaveVip() {
    QString strVip = ui.lineEdit_vip->text();
    if (strVip.isEmpty()) {
        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("请先填写注册码!"));
        return;
    }

    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);
    std::string strDll = dllname;
    //QString qstrDll = QString::fromStdString(strDll); // 此用法会造成中文乱码
    QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    //strDll = qstrDll.toStdString(); // 此用法会造成程序崩溃
    strDll = std::string((const char*)qstrDll.toLocal8Bit());
    strDll += "\\Config.ini";
    CMy_Ini obj_ini(strDll.c_str());
    obj_ini.DeleteSection(TEXT("Vip"));
    obj_ini.WriteString("Vip", "Card", (const char*)strVip.toLocal8Bit());
    emit newVip(strVip);
    this->accept();
}