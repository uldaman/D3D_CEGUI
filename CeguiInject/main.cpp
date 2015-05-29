#include "ceguiinject.h"
#include <QtWidgets/QApplication>
#include <windows.h>

int main(int argc, char *argv[]) {
    HANDLE handle = CreateMutex(NULL, true, TEXT("martin_cegui"));
    if (GetLastError() != ERROR_SUCCESS) {
        ::MessageBox(NULL, TEXT("程序已在运行..."), TEXT("Tatnium Warning"), MB_ICONWARNING);
        return 0;
    }

    QApplication a(argc, argv);
    CeguiInject w;
    w.show();
    return a.exec();
}