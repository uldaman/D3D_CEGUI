#include "cmytablewidget.h"
#include "QMenu"
#include "QContextMenuEvent"
#include "caddaccount.h"
#include "coption.h"

CMyTableWidget::CMyTableWidget(QWidget *parent)
    : QTableWidget(parent) {
    CreateActions();
}

CMyTableWidget::~CMyTableWidget() {

}

void CMyTableWidget::CreateActions() {
    m_popMenu = new QMenu();

    m_actionAdd = new QAction(this);
    m_actionAdd->setText(QString(QStringLiteral("添加賬號")));

    m_actionStart = new QAction(this);
    m_actionStart->setText(QString(QStringLiteral("開始掛機")));

    connect(m_actionAdd, SIGNAL(triggered()), this, SLOT(AddAccount()));
    connect(m_actionStart, SIGNAL(triggered()), this, SLOT(StartGame()));
}

void CMyTableWidget::AddAccount() {
    CAddAccount* a = new CAddAccount;
    QObject::connect(a, &CAddAccount::newAcc, this, &CMyTableWidget::addAcc);
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
}

void CMyTableWidget::addAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer) {
    emit send_addAcc(strAcc, strPsw, strArea, strServer);
}


void CMyTableWidget::StartGame() {
    // 啟動遊戲
    emit startNewGame();
}

void CMyTableWidget::contextMenuEvent(QContextMenuEvent* event) {
    m_popMenu->clear(); //清除原有菜单
    QPoint point = event->pos(); //得到窗口坐标

    QTableWidgetItem* item = this->itemAt(point);
    //if(item != NULL) {
    m_popMenu->addAction(m_actionAdd);
    m_popMenu->addAction(m_actionStart);

    //菜单出现的位置为当前鼠标的位置
    m_popMenu->exec(QCursor::pos());
    event->accept();
    //} 
}