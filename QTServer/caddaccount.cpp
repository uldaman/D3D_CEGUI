#include "caddaccount.h"

CAddAccount::CAddAccount(QWidget *parent)
    : QDialog(parent) {
    ui.setupUi(this);
}

CAddAccount::~CAddAccount() {

}

void CAddAccount::PushButton_Enter_Acc() {
    QString acc = ui.lineEdit_acc->text();
    QString psw = ui.lineEdit_psw->text();
    QString area = ui.comboBox_area->itemText(0);
    QString server = ui.comboBox_server->itemText(0);
    emit newAcc(acc, psw, area, server);
    this->accept();
}