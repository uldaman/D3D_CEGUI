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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
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
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QPushButton *pushButton_initializesAttribute;
    QPushButton *pushButton_saveAttribute;

    void setupUi(QDialog *COption)
    {
        if (COption->objectName().isEmpty())
            COption->setObjectName(QStringLiteral("COption"));
        COption->resize(359, 142);
        COption->setMinimumSize(QSize(359, 0));
        COption->setMaximumSize(QSize(359, 146));
        pushButton_path = new QPushButton(COption);
        pushButton_path->setObjectName(QStringLiteral("pushButton_path"));
        pushButton_path->setGeometry(QRect(310, 10, 41, 23));
        layoutWidget = new QWidget(COption);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 291, 22));
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

        groupBox = new QGroupBox(COption);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 60, 201, 71));
        groupBox->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        pushButton_initializesAttribute = new QPushButton(COption);
        pushButton_initializesAttribute->setObjectName(QStringLiteral("pushButton_initializesAttribute"));
        pushButton_initializesAttribute->setGeometry(QRect(240, 60, 75, 31));
        pushButton_saveAttribute = new QPushButton(COption);
        pushButton_saveAttribute->setObjectName(QStringLiteral("pushButton_saveAttribute"));
        pushButton_saveAttribute->setGeometry(QRect(240, 100, 75, 31));

        retranslateUi(COption);
        QObject::connect(pushButton_saveAttribute, SIGNAL(clicked()), COption, SLOT(PushButton_SaveAttribute()));
        QObject::connect(pushButton_initializesAttribute, SIGNAL(clicked()), COption, SLOT(PushButton_InitializesAttribute()));

        QMetaObject::connectSlotsByName(COption);
    } // setupUi

    void retranslateUi(QDialog *COption)
    {
        COption->setWindowTitle(QApplication::translate("COption", "\345\261\254\346\200\247\350\250\255\347\275\256", 0));
        pushButton_path->setText(QApplication::translate("COption", "\347\200\217 \350\246\275", 0));
        label->setText(QApplication::translate("COption", "\351\201\212\346\210\262\350\267\257\345\276\221:", 0));
        lineEdit_path->setText(QApplication::translate("COption", "\350\253\213\351\201\270\346\223\207\351\201\212\346\210\262\344\270\273\347\233\256\351\214\204,\345\246\202\343\200\216F:\\\346\200\252\347\211\251\347\214\216\344\272\272Online\343\200\217...", 0));
        groupBox->setTitle(QApplication::translate("COption", "\346\263\250\346\204\217", 0));
        label_2->setText(QApplication::translate("COption", "\345\210\235\346\254\241\344\275\277\347\224\250\346\234\254\350\275\257\344\273\266, \350\257\267\347\202\271\345\207\273\"\345\210\235\345\247\213\345\214\226\",\n"
"\345\220\246\345\210\231\350\257\267\347\233\264\346\216\245\347\202\271\345\207\273\"\347\241\256\345\256\232.\"", 0));
        pushButton_initializesAttribute->setText(QApplication::translate("COption", "\345\210\235\345\247\213\345\214\226", 0));
        pushButton_saveAttribute->setText(QApplication::translate("COption", "\347\241\256  \345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class COption: public Ui_COption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPTION_H
