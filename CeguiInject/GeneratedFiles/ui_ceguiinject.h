/********************************************************************************
** Form generated from reading UI file 'ceguiinject.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CEGUIINJECT_H
#define UI_CEGUIINJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CeguiInjectClass
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_d3d9;
    QRadioButton *radioButton_d3d8;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_path;
    QPushButton *pushButton_run;
    QLabel *label_output;
    QPushButton *pushButton_install;

    void setupUi(QWidget *CeguiInjectClass)
    {
        if (CeguiInjectClass->objectName().isEmpty())
            CeguiInjectClass->setObjectName(QStringLiteral("CeguiInjectClass"));
        CeguiInjectClass->resize(355, 180);
        CeguiInjectClass->setMinimumSize(QSize(355, 180));
        CeguiInjectClass->setMaximumSize(QSize(355, 180));
        groupBox = new QGroupBox(CeguiInjectClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 331, 51));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 20, 151, 18));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_d3d9 = new QRadioButton(layoutWidget);
        radioButton_d3d9->setObjectName(QStringLiteral("radioButton_d3d9"));

        gridLayout->addWidget(radioButton_d3d9, 0, 0, 1, 1);

        radioButton_d3d8 = new QRadioButton(layoutWidget);
        radioButton_d3d8->setObjectName(QStringLiteral("radioButton_d3d8"));

        gridLayout->addWidget(radioButton_d3d8, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(CeguiInjectClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 80, 331, 51));
        lineEdit_path = new QLineEdit(groupBox_2);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setGeometry(QRect(11, 22, 261, 20));
        pushButton_path = new QPushButton(groupBox_2);
        pushButton_path->setObjectName(QStringLiteral("pushButton_path"));
        pushButton_path->setGeometry(QRect(279, 21, 41, 23));
        pushButton_run = new QPushButton(CeguiInjectClass);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));
        pushButton_run->setGeometry(QRect(280, 140, 61, 31));
        label_output = new QLabel(CeguiInjectClass);
        label_output->setObjectName(QStringLiteral("label_output"));
        label_output->setGeometry(QRect(20, 139, 191, 31));
        label_output->setAutoFillBackground(false);
        pushButton_install = new QPushButton(CeguiInjectClass);
        pushButton_install->setObjectName(QStringLiteral("pushButton_install"));
        pushButton_install->setGeometry(QRect(210, 140, 61, 31));

        retranslateUi(CeguiInjectClass);
        QObject::connect(pushButton_run, SIGNAL(clicked()), CeguiInjectClass, SLOT(runGame()));
        QObject::connect(pushButton_path, SIGNAL(clicked()), CeguiInjectClass, SLOT(selectPath()));

        QMetaObject::connectSlotsByName(CeguiInjectClass);
    } // setupUi

    void retranslateUi(QWidget *CeguiInjectClass)
    {
        CeguiInjectClass->setWindowTitle(QApplication::translate("CeguiInjectClass", "CeguiInject", 0));
        groupBox->setTitle(QApplication::translate("CeguiInjectClass", "\350\257\267\351\200\211\346\213\251\346\270\262\346\237\223\346\226\271\345\274\217:", 0));
        radioButton_d3d9->setText(QApplication::translate("CeguiInjectClass", "D3D9", 0));
        radioButton_d3d8->setText(QApplication::translate("CeguiInjectClass", "D3D8", 0));
        groupBox_2->setTitle(QApplication::translate("CeguiInjectClass", "\350\257\267\351\200\211\346\213\251\346\270\270\346\210\217\350\267\257\345\276\204:", 0));
        pushButton_path->setText(QApplication::translate("CeguiInjectClass", ". . .", 0));
        pushButton_run->setText(QApplication::translate("CeguiInjectClass", "\345\220\257\345\212\250\346\217\222\344\273\266", 0));
        label_output->setText(QString());
        pushButton_install->setText(QApplication::translate("CeguiInjectClass", "\345\256\211\350\243\205\346\217\222\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class CeguiInjectClass: public Ui_CeguiInjectClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CEGUIINJECT_H
