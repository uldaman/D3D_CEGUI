/********************************************************************************
** Form generated from reading UI file 'coption.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COPTION_H
#define UI_COPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_COption
{
public:
    QPushButton *pushButton_path;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_path;

    void setupUi(QDialog *COption)
    {
        if (COption->objectName().isEmpty())
            COption->setObjectName(QStringLiteral("COption"));
        COption->resize(359, 146);
        COption->setMinimumSize(QSize(359, 0));
        COption->setMaximumSize(QSize(359, 146));
        pushButton_path = new QPushButton(COption);
        pushButton_path->setObjectName(QStringLiteral("pushButton_path"));
        pushButton_path->setGeometry(QRect(310, 40, 41, 23));
        layoutWidget = new QWidget(COption);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 341, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_path = new QLineEdit(layoutWidget);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));

        horizontalLayout->addWidget(lineEdit_path);


        retranslateUi(COption);

        QMetaObject::connectSlotsByName(COption);
    } // setupUi

    void retranslateUi(QDialog *COption)
    {
        COption->setWindowTitle(QApplication::translate("COption", "\345\261\254\346\200\247\350\250\255\347\275\256", 0));
        pushButton_path->setText(QApplication::translate("COption", "\347\200\217 \350\246\275", 0));
        label->setText(QApplication::translate("COption", "\351\201\212\346\210\262\350\267\257\345\276\221:", 0));
        lineEdit_path->setText(QApplication::translate("COption", "\350\253\213\351\201\270\346\223\207\351\201\212\346\210\262\344\270\273\347\233\256\351\214\204,\345\246\202\343\200\216F:\\ty\343\200\217...", 0));
    } // retranslateUi

};

namespace Ui {
    class COption: public Ui_COption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPTION_H
