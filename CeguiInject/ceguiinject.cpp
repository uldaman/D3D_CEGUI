#include <windows.h>
#include <winbase.h>
#include "ceguiinject.h"
#include <minwindef.h>
#include <libloaderapi.h>
#include <QFile>
#include <QFileDialog>
#include <QtDebug>
#include <process.h>
#include <tlhelp32.h>
#include <QMessageBox>
#include "forcelib\ForceLib.h"


CeguiInject::CeguiInject(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);
    QString strOutput = QStringLiteral("说明: 点击 \"启动插件\" 后开始等待游戏启动,\n      等待中按键盘 \"esc\" 键取消等待...");
    ui.label_output->setText(strOutput);
    ui.radioButton_d3d9->setChecked(true);
}

CeguiInject::~CeguiInject() {

}

bool fileExists(const char filename[]) {
    WIN32_FIND_DATA finddata;
    HANDLE handle = FindFirstFile(filename, &finddata);
    return (handle != INVALID_HANDLE_VALUE);
}

bool GetProcessOf(const char exename[], PROCESSENTRY32 *process) {
    HANDLE handle;
    process->dwSize = sizeof(PROCESSENTRY32);
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(handle, process)) {
        do {
            if (lstrcmp(process->szExeFile, exename) == 0) {
                CloseHandle(handle);
                return true;
            }
        } while (Process32Next(handle, process));
    }

    CloseHandle(handle);
    return false;
}

bool GetThreadOf(DWORD ProcessID, THREADENTRY32* thread) {
    HANDLE handle;
    thread->dwSize = sizeof(THREADENTRY32);
    handle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if (Thread32First(handle, thread)) {
        do {
            if (thread->th32OwnerProcessID == ProcessID) {
                CloseHandle(handle);
                return true;
            }
        } while (Thread32Next(handle, thread));
    }

    CloseHandle(handle);
    return false;
}

void CeguiInject::runGame() {
    char dllname[MAX_PATH];
    GetModuleFileName(NULL, dllname, MAX_PATH);
    std::string strDll = dllname;
    QString qstrDll = QString::fromStdString(strDll);
    QString strSplit = "\\";
    int index = qstrDll.lastIndexOf(strSplit);
    qstrDll = qstrDll.left(index);
    strDll = qstrDll.toStdString();
    //dllname[lstrlen(dllname) - 3] = 0;
    //lstrcat(dllname, "dll");

    if (ui.radioButton_d3d9->isChecked()) {
        strDll += "\\D3D9_CEGUI.dll";
    } else if (ui.radioButton_d3d8->isChecked()) {
        strDll += "\\D3D8_CEGUI.dll";
    }

    if (!fileExists(strDll.c_str())) {
        ::MessageBox(NULL, "没有找到 DLL 文件 . . ", "Tatnium Error", MB_ICONERROR);
        return;
    }

    //if (IDCANCEL == ::MessageBox(0, "点击 \"确定\" 后开始等待游戏启动\n\n等待中按键盘 \"esc\" 键取消等待...", "Tatnium Injector", MB_OK)) {
    //    return;
    //}
    
    QString strGame = ui.lineEdit_path->text();
    if (strGame.isEmpty()) {
        return;
    }

    strSplit = "/";
    index = strGame.lastIndexOf(strSplit);
    strGame = strGame.right(strGame.length() - index - 1);
    //QByteArray ba = strGame.toLatin1();
    //char* szGame = ba.data();
    std::string szGame = strGame.toStdString();

    PROCESSENTRY32 pe32;
    while (!GetProcessOf(szGame.c_str(), &pe32)) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return;
        }
        Sleep(10);
    }

    THREADENTRY32 te32;
    while (!GetThreadOf(pe32.th32ProcessID, &te32)) {
        Sleep(2);
    }

    PROCESS_INFORMATION PI;
    PI.dwProcessId = pe32.th32ProcessID;
    PI.dwThreadId = te32.th32ThreadID;
    PI.hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);

    if (!ForceLibrary(strDll.c_str(), &PI)) {
        TerminateProcess(PI.hProcess, 0);
        ::MessageBox(NULL, "无法开启插件...", "Tatnium Error", MB_ICONERROR);
    }

    CloseHandle(PI.hProcess);

    //::CloseHandle((HANDLE)_beginthreadex(NULL, 0, ThreadFun_WaritGame, NULL, 0, NULL));
}

void CeguiInject::selectPath() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", NULL, "file (*.exe)");
    if (!fileName.isEmpty()) {
        ui.lineEdit_path->setText(fileName);
    }
}