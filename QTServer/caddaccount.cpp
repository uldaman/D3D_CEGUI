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
        strScript = QString::fromStdString(fileInfo.name);
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
        ui.lineEdit_acc->setText(pTable->m_acc);
        ui.lineEdit_psw->setText(pTable->m_psw);
        ui.comboBox_area->setCurrentIndex(ui.comboBox_area->findText(pTable->m_area));
        ui.comboBox_server->setCurrentIndex(ui.comboBox_server->findText(pTable->m_server));
        ui.comboBox_script->setCurrentIndex(ui.comboBox_script->findText(pTable->m_script));
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