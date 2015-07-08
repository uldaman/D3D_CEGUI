#include "qtserver.h"
#include <QtWidgets/QApplication>
#include <windows.h>

int main(int argc, char *argv[]) {
    HANDLE handle = CreateMutex(NULL, true, "martin_cegui_server");
    if (GetLastError() != ERROR_SUCCESS) {
        ::MessageBox(NULL, "程序已在运行...", "Tatnium Warning", MB_ICONWARNING);
        return 0;
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