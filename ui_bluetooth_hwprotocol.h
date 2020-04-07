/********************************************************************************
** Form generated from reading UI file 'bluetooth_hwprotocol.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTH_HWPROTOCOL_H
#define UI_BLUETOOTH_HWPROTOCOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Bluetooth_HWprotocol
{
public:
    QListWidget *list;
    QPushButton *pushButton;

    void setupUi(QWidget *Bluetooth_HWprotocol)
    {
        if (Bluetooth_HWprotocol->objectName().isEmpty())
            Bluetooth_HWprotocol->setObjectName(QString::fromUtf8("Bluetooth_HWprotocol"));
        Bluetooth_HWprotocol->resize(560, 526);
        list = new QListWidget(Bluetooth_HWprotocol);
        list->setObjectName(QString::fromUtf8("list"));
        list->setGeometry(QRect(30, 50, 391, 271));
        pushButton = new QPushButton(Bluetooth_HWprotocol);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 370, 75, 23));

        retranslateUi(Bluetooth_HWprotocol);

        QMetaObject::connectSlotsByName(Bluetooth_HWprotocol);
    } // setupUi

    void retranslateUi(QWidget *Bluetooth_HWprotocol)
    {
        Bluetooth_HWprotocol->setWindowTitle(QCoreApplication::translate("Bluetooth_HWprotocol", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Bluetooth_HWprotocol", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Bluetooth_HWprotocol: public Ui_Bluetooth_HWprotocol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTH_HWPROTOCOL_H
