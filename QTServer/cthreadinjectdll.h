#ifndef CTHREADINJECTDLL_H
#define CTHREADINJECTDLL_H

#include <QThread>
#include "QTableWidget.h"

class CThreadInjectDll : public QThread {
    Q_OBJECT

public:
    CThreadInjectDll(QObject *parent);
    ~CThreadInjectDll();
    QTableWidgetItem* pItem;

protected:
    void run();

signals:
    void SignalDone(QTableWidgetItem* pItem);

};

#endif // CTHREADINJECTDLL_H
