#include "qtserver.h"
#include <QtWidgets/QApplication>
#include <windows.h>
#include "Xml.h"
#include <string>
#include "QMessageBox"

const std::string strVersion= "0.4.18";

int main(int argc, char *argv[]) {
    HANDLE handle = CreateMutex(NULL, true, "martin_cegui_server");
    if (GetLastError() != ERROR_SUCCESS) {
        ::MessageBox(NULL, "程序已在运行...", "Tatnium Warning", MB_ICONWARNING);
        return 0;
    }

    std::list<_Xml> lAllVal;
    std::vector<std::string> arrFindXmlKeyName;
    arrFindXmlKeyName.swap(std::vector<std::string>());
    arrFindXmlKeyName.push_back("VersionDemoStr");
    CXml::DeadXml(lAllVal, arrFindXmlKeyName, "F:\\怪物猎人Online\\TCLS\\mmog_data.xml");
    if (lAllVal.front().Val != strVersion) {
        MessageBox(NULL, "游戏有更新! 请更新软件!", "提示", MB_OK);
        ExitProcess(0);
    }

    ATOM atInfoID = GlobalFindAtom("shitnow");
    if (atInfoID != 0) {
        GlobalDeleteAtom(atInfoID);
    }

    QApplication a(argc, argv);
    QTServer w;
    w.show();
    return a.exec();
}