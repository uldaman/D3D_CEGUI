/********************************************************************************
** Form generated from reading UI file 'cqvip.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CQVIP_H
#define UI_CQVIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CQVip
{
public:
    QLineEdit *lineEdit_vip;
    QPushButton *pushButton_vip;

    void setupUi(QWidget *CQVip)
    {
        if (CQVip->objectName().isEmpty())
            CQVip->setObjectName(QStringLiteral("CQVip"));
        CQVip->resize(291, 70);
        CQVip->setMinimumSize(QSize(291, 70));
        CQVip->setMaximumSize(QSize(291, 70));
        lineEdit_vip = new QLineEdit(CQVip);
        lineEdit_vip->setObjectName(QStringLiteral("lineEdit_vip"));
        lineEdit_vip->setGeometry(QRect(10, 10, 271, 20));
        pushButton_vip = new QPushButton(CQVip);
        pushButton_vip->setObjectName(QStringLiteral("pushButton_vip"));
        pushButton_vip->setGeometry(QRect(240, 40, 41, 23));

        retranslateUi(CQVip);
        QObject::connect(pushButton_vip, SIGNAL(clicked()), CQVip, SLOT(SaveVip()));

        QMetaObject::connectSlotsByName(CQVip);
    } // setupUi

    void retranslateUi(QWidget *CQVip)
    {
        CQVip->setWindowTitle(QApplication::translate("CQVip", "\346\263\250\345\206\214", 0));
        pushButton_vip->setText(QApplication::translate("CQVip", "\344\277\235 \345\255\230", 0));
    } // retranslateUi

};

namespace Ui {
    class CQVip: public Ui_CQVip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CQVIP_H
