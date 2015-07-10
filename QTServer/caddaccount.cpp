#include "caddaccount.h"
#include "cmytablewidget.h"
#include <io.h>
#include "CMartin.h"

bool CAddAccount::TransferScript() {
    _finddata_t fileInfo;
    std::string fileName = martin->GetModulePath(NULL);
    fileName += "\\Script\\*.lua";
    long handle = _findfirst(fileName.c_str(), &fileInfo);

    if (handle == -1L) {
        return false;
    }

    QString strScript;
    do {
        //strScript = QString::fromStdString(fileInfo.name); // ÖÐÎÄÂÒÂë
        strScript = QString::fromLocal8Bit(fileInfo.name);
        ui.comboBox_script->addItem(strScript);
    } while (_findnext(handle, &fileInfo) == 0);

    return true;
}

CAddAccount::CAddAccount(QWidget *parent)
    : QDialog(parent) {
    ui.setupUi(this);
    TransferScript();
    if (parent) {
        CMyTableWidget* pTable = (CMyTableWidget*)parent;
        QString strAcc = pTable->m_itemAcc->data(Qt::DisplayRole).toString();
        QString strPsw = pTable->m_itemAcc->data(Qt::UserRole).toString();
        QString strArea = pTable->m_itemArea->data(Qt::DisplayRole).toString();
        QString strServer = pTable->m_itemServer->data(Qt::DisplayRole).toString();
        QString strScript = pTable->m_itemScript->data(Qt::DisplayRole).toString();

        ui.lineEdit_acc->setText(strAcc);
        ui.lineEdit_psw->setText(strPsw);
        ui.comboBox_area->setCurrentIndex(ui.comboBox_area->findText(strArea));
        ui.comboBox_server->setCurrentIndex(ui.comboBox_server->findText(strServer));
        ui.comboBox_script->setCurrentIndex(ui.comboBox_script->findText(strScript));
    }
}

CAddAccount::~CAddAccount() {

}

void CAddAccount::PushButton_Enter_Acc() {
    QString acc = ui.lineEdit_acc->text();
    QString psw = ui.lineEdit_psw->text();
    QString area = ui.comboBox_area->currentText();
    QString server = ui.comboBox_server->currentText();
    QString script = ui.comboBox_script->currentText();
    emit SignalNewAcc(acc, psw, area, server, script);
    this->accept();
}