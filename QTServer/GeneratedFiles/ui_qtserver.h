/********************************************************************************
** Form generated from reading UI file 'qtserver.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSERVER_H
#define UI_QTSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "cmytablewidget.h"

QT_BEGIN_NAMESPACE

class Ui_QTServerClass
{
public:
    QAction *actionOption;
    QAction *actionAddAccount;
    QAction *actionImportAcc;
    QAction *actionExportAcc;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    CMyTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menu_property;
    QMenu *menu_account;

    void setupUi(QMainWindow *QTServerClass)
    {
        if (QTServerClass->objectName().isEmpty())
            QTServerClass->setObjectName(QStringLiteral("QTServerClass"));
        QTServerClass->resize(958, 354);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QTServerClass->sizePolicy().hasHeightForWidth());
        QTServerClass->setSizePolicy(sizePolicy);
        actionOption = new QAction(QTServerClass);
        actionOption->setObjectName(QStringLiteral("actionOption"));
        actionAddAccount = new QAction(QTServerClass);
        actionAddAccount->setObjectName(QStringLiteral("actionAddAccount"));
        actionImportAcc = new QAction(QTServerClass);
        actionImportAcc->setObjectName(QStringLiteral("actionImportAcc"));
        actionExportAcc = new QAction(QTServerClass);
        actionExportAcc->setObjectName(QStringLiteral("actionExportAcc"));
        centralWidget = new QWidget(QTServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new CMyTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setAcceptDrops(false);
        tableWidget->setAutoFillBackground(false);
        tableWidget->setDragEnabled(false);
        tableWidget->setAlternatingRowColors(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setMinimumSectionSize(27);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        tableWidget->verticalHeader()->setMinimumSectionSize(21);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        horizontalLayout->addWidget(tableWidget);

        QTServerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTServerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 958, 23));
        menu_property = new QMenu(menuBar);
        menu_property->setObjectName(QStringLiteral("menu_property"));
        menu_account = new QMenu(menuBar);
        menu_account->setObjectName(QStringLiteral("menu_account"));
        QTServerClass->setMenuBar(menuBar);

        menuBar->addAction(menu_property->menuAction());
        menuBar->addAction(menu_account->menuAction());
        menu_property->addAction(actionOption);
        menu_account->addAction(actionAddAccount);
        menu_account->addAction(actionImportAcc);
        menu_account->addAction(actionExportAcc);

        retranslateUi(QTServerClass);

        QMetaObject::connectSlotsByName(QTServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTServerClass)
    {
        QTServerClass->setWindowTitle(QApplication::translate("QTServerClass", "\346\200\252\347\211\251\347\214\216\344\272\272Online$", 0));
        actionOption->setText(QApplication::translate("QTServerClass", "\345\261\254\346\200\247\350\250\255\347\275\256", 0));
        actionAddAccount->setText(QApplication::translate("QTServerClass", "\346\267\273\345\212\240\350\264\246\345\217\267", 0));
        actionImportAcc->setText(QApplication::translate("QTServerClass", "\345\257\274\345\205\245\350\264\246\345\217\267", 0));
        actionExportAcc->setText(QApplication::translate("QTServerClass", "\345\257\274\345\207\272\350\264\246\345\217\267", 0));
        menu_property->setTitle(QApplication::translate("QTServerClass", "\346\214\202\346\234\272\350\256\276\347\275\256", 0));
        menu_account->setTitle(QApplication::translate("QTServerClass", "\350\264\246\345\217\267\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class QTServerClass: public Ui_QTServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSERVER_H
