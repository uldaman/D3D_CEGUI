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
        ::MessageBox(NULL, "������������...", "Tatnium Warning", MB_ICONWARNING);
        return 0;
    }

    std::list<_Xml> lAllVal;
    std::vector<std::string> arrFindXmlKeyName;
    arrFindXmlKeyName.swap(std::vector<std::string>());
    arrFindXmlKeyName.push_back("VersionDemoStr");
    CXml::DeadXml(lAllVal, arrFindXmlKeyName, "F:\\��������Online\\TCLS\\mmog_data.xml");
    if (lAllVal.front().Val != strVersion) {
        MessageBox(NULL, "��Ϸ�и���! ��������!", "��ʾ", MB_OK);
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