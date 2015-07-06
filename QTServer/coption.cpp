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

        // �������O�� ini �����ļ�
        //-----------------------------------------------------------
        //    �@ȡ��ǰ����ȫ·��
        //-----------------------------------------------------------
        char dllname[MAX_PATH];
        GetModuleFileName(NULL, dllname, MAX_PATH);

        //-----------------------------------------------------------
        //    �D�Q�� QString, Ȼ��ȥ��·���е��ļ���, ������ǰĿ�
        //    �ڮ�ǰĿ�������������ļ��� 
        //-----------------------------------------------------------
        std::string strDll = dllname;
        //QString qstrDll = QString::fromStdString(strDll); // ���÷��������������
        QString qstrDll = QString::fromLocal8Bit(strDll.c_str());
        QString strSplit = "\\";
        int index = qstrDll.lastIndexOf(strSplit);
        qstrDll = qstrDll.left(index);
        //strDll = qstrDll.toStdString(); // ���÷�����ɳ������
        strDll = std::string((const char*)qstrDll.toLocal8Bit());
        strDll += "\\Config.ini";

        //-----------------------------------------------------------
        //    ���������ļ�
        //-----------------------------------------------------------
        martin->SetPathName(strDll.c_str());
        martin->DeleteSection(TEXT("Path"));
        martin->WriteString("Path", "Game", (const char*)fileName.toLocal8Bit());

        // �������������, ��Ҫ֪ͨ������
        emit newGamePath(fileName);
    }
}
