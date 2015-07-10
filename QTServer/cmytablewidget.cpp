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

    m_actionChange = new QAction(this);
    m_actionChange->setText(QString(QStringLiteral("修改账号")));

    m_actionStart = new QAction(this);
    m_actionStart->setText(QString(QStringLiteral("開始掛機")));

    m_actionSeparator = new QAction(this);
    m_actionSeparator->setSeparator(true);

    connect(m_actionAdd, SIGNAL(triggered()), this, SLOT(SlotAddAccount()));
    connect(m_actionStart, SIGNAL(triggered()), this, SLOT(SlotStartGame()));
    connect(m_actionChange, SIGNAL(triggered()), this, SLOT(SlotChangeAccount()));
}

void CMyTableWidget::SlotAddAccount() {
    CAddAccount* a = new CAddAccount;
    QObject::connect(a, &CAddAccount::SignalNewAcc, this, &CMyTableWidget::SlotAddAcc);
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
}

void CMyTableWidget::SlotAddAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript) {
    emit SignalSendAddAcc(strAcc, strPsw, strArea, strServer, strScript);
}


void CMyTableWidget::SlotStartGame() {
    // 啟動遊戲
    //emit SignalStartNewGame(m_acc, m_psw, m_area, m_server);
    emit SignalStartNewGame(m_nRow);
}

void CMyTableWidget::contextMenuEvent(QContextMenuEvent* event) {
    m_popMenu->clear(); //清除原有菜单
    QPoint point = event->pos(); //得到窗口坐标
    //QTableWidgetItem* item = this->itemAt(point);
    //QModelIndex modelIndex = this->indexFromItem(item);
    //int i = modelIndex.row();
    QModelIndex modelIndex = this->indexAt(point);
    m_nRow = modelIndex.row();

    m_popMenu->addAction(m_actionAdd);
    m_popMenu->addAction(m_actionSeparator);

    if (m_nRow != 0xFFFFFFFF) {
        m_popMenu->addAction(m_actionChange);
        m_popMenu->addAction(m_actionStart);
        m_itemAcc = this->item(m_nRow, 0);
        //m_acc = m_itemAcc->data(Qt::DisplayRole).toString();
        //m_psw = m_itemAcc->data(Qt::UserRole).toString();

        m_itemArea = this->item(m_nRow, 1);
        //m_area = m_itemArea->data(Qt::DisplayRole).toString();

        m_itemServer = this->item(m_nRow, 2);
        //m_server = m_itemServer->data(Qt::DisplayRole).toString();

        m_itemScript = this->item(m_nRow, 3);
        //m_script = m_itemScript->data(Qt::DisplayRole).toString();
    }

    //菜单出现的位置为当前鼠标的位置
    m_popMenu->exec(QCursor::pos());
    event->accept();
}

void CMyTableWidget::SlotChangeAcc(const QString &strAcc, const QString &strPsw, const QString &strArea, const QString &strServer, const QString &strScript) {
    m_itemAcc->setData(Qt::DisplayRole, strAcc);
    m_itemAcc->setData(Qt::UserRole, strPsw);
    m_itemArea->setData(Qt::DisplayRole, strArea);
    m_itemServer->setData(Qt::DisplayRole, strServer);
    m_itemScript->setData(Qt::DisplayRole, strScript);
}

void CMyTableWidget::SlotChangeAccount() {
    CAddAccount* a = new CAddAccount(this);
    QObject::connect(a, &CAddAccount::SignalNewAcc, this, &CMyTableWidget::SlotChangeAcc);
    a->setAttribute(Qt::WA_DeleteOnClose);
    a->show();
}