/********************************************************************************
** Form generated from reading UI file 'caddaccount.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CADDACCOUNT_H
#define UI_CADDACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CAddAccount
{
public:

    void setupUi(QDialog *CAddAccount)
    {
        if (CAddAccount->objectName().isEmpty())
            CAddAccount->setObjectName(QStringLiteral("CAddAccount"));
        CAddAccount->resize(400, 132);

        retranslateUi(CAddAccount);

        QMetaObject::connectSlotsByName(CAddAccount);
    } // setupUi

    void retranslateUi(QDialog *CAddAccount)
    {
        CAddAccount->setWindowTitle(QApplication::translate("CAddAccount", "\346\267\273\345\212\240\350\263\254\350\231\237", 0));
    } // retranslateUi

};

namespace Ui {
    class CAddAccount: public Ui_CAddAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADDACCOUNT_H
