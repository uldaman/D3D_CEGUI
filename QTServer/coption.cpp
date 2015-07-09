#include "coption.h"
#include <windows.h>
#include <QFile>
#include <QFileDialog>
#include <libloaderapi.h>
#include "CMartin.h"
#include "QMessageBox"

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
    }
}

void COption::PushButton_SaveAttribute() {
    QString strPath = ui.lineEdit_path->text();
    if (!strPath.isEmpty()) {
        std::string strConfig = martin->GetModulePath(NULL);
        strConfig += "\\Config.ini";

        //-----------------------------------------------------------
        //    保存配置文件
        //-----------------------------------------------------------
        martin->SetPathName(strConfig.c_str());
        martin->DeleteSection(TEXT("Path"));
        martin->WriteString("Path", "Game", (const char*)strPath.toLocal8Bit());

        // 通知主窗口
        emit SignalNewGamePath(strPath);
    }
    this->accept();
}

void COption::PushButton_InitializesAttribute() {
    // 复制 DLL
    installDll();
    PushButton_SaveAttribute();
}

void COption::installDll() {
    //if (RegVip() == FALSE) {
    //    return;
    //}
    //ks_exit();

    QString strGame = ui.lineEdit_path->text();
    if (strGame.isEmpty()) {
        QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("没有正确选择游戏路径!"));
        return;
    }

    std::string strDll = martin->GetModulePath(NULL);

    //QString strSplit = "/";
    //int index = strGame.lastIndexOf(strSplit);
    //strGame = strGame.left(index);
    strGame.replace("/", "\\");
    std::string szGame = std::string((const char*)strGame.toLocal8Bit());

    CopyFolder((strDll + "\\CrackCaptchaAPI.dll").c_str(), (szGame + "\\TCLS").c_str());
    Sleep(500);

    CopyFolder((strDll + "\\CrackCaptchaAPI.dll").c_str(), (szGame + "\\TCLS\\tenio").c_str());
    Sleep(500);

    CopyFolder((strDll + "\\IPHLPAPI.dll").c_str(), (szGame + "\\TCLS\\tenprotect").c_str());
    Sleep(500);

    CopyFolder((strDll + "\\qxpatch.dll").c_str(), (szGame + "\\TCLS\\tenio").c_str());
    Sleep(500);

    CopyFolder((strDll + "\\datafiles").c_str(), (szGame + "\\Bin\\Client\\Bin32").c_str());
    Sleep(500);

    CopyFolder((strDll + "\\Bin32").c_str(), (szGame + "\\Bin\\Client").c_str());
    Sleep(500);

    QMessageBox::about(this, QStringLiteral("提示"), QStringLiteral("软件初始化完毕!"));
}

BOOL COption::CopyFolder(const char* lpszFromPath, const char* lpszToPath) {
    int nLengthFrm = strlen(lpszFromPath);
    std::auto_ptr<char> NewPathFrm(new char[nLengthFrm * 2]);
    RtlZeroMemory(NewPathFrm.get(), nLengthFrm * 2);
    strcpy_s(NewPathFrm.get(), nLengthFrm + 1, lpszFromPath);
    NewPathFrm.get()[nLengthFrm] = '\0';
    NewPathFrm.get()[nLengthFrm + 1] = '\0';
    SHFILEOPSTRUCT FileOp;
    RtlZeroMemory((void*)&FileOp, sizeof(SHFILEOPSTRUCT));
    FileOp.fFlags = FOF_NOCONFIRMATION;
    FileOp.hNameMappings = NULL;
    FileOp.hwnd = NULL;
    FileOp.lpszProgressTitle = NULL;
    FileOp.pFrom = NewPathFrm.get();
    FileOp.pTo = lpszToPath;
    FileOp.wFunc = FO_COPY;
    return SHFileOperation(&FileOp) == 0;
}