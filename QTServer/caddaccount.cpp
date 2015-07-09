#include "caddaccount.h"
#include "cmytablewidget.h"

CAddAccount::CAddAccount(QWidget *parent)
    : QDialog(parent) {
    ui.setupUi(this);




    if (parent) {
        CMyTableWidget* pTable = (CMyTableWidget*)parent;
        ui.lineEdit_acc->setText(pTable->m_acc);
        ui.lineEdit_psw->setText(pTable->m_psw);
            //ui.comboBox_area->setText(pTable->m_area);
        ui.comboBox_area->setCurrentIndex(ui.comboBox_area->findText(pTable->m_area));
        ui.comboBox_server->setCurrentIndex(ui.comboBox_server->findText(pTable->m_server));
    }
}

CAddAccount::~CAddAccount() {

}

void CAddAccount::PushButton_Enter_Acc() {
    QString acc = ui.lineEdit_acc->text();
    QString psw = ui.lineEdit_psw->text();
    QString area = ui.comboBox_area->currentText();
    QString server = ui.comboBox_server->currentText();
    emit SignalNewAcc(acc, psw, area, server);
    this->accept();
}