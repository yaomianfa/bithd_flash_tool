/********************************************************************************
** Form generated from reading UI file 'bluetooth_appprotocol.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BLUETOOTH_APPPROTOCOL_H
#define UI_BLUETOOTH_APPPROTOCOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BluetoothAppProtocol
{
public:
    QPushButton *linkbithd;
    QPushButton *openblue;
    QPushButton *closeblue;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_10;
    QPushButton *pushButton_12;
    QPushButton *pushButton_11;
    QPushButton *pushButton_14;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QLabel *labelprogress;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QProgressBar *progressBar;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_13;
    QPushButton *pushButton_8;
    QPushButton *pushButton_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *linkstatus;
    QLabel *bluestatus;
    QTextEdit *textEdit;

    void setupUi(QWidget *BluetoothAppProtocol)
    {
        if (BluetoothAppProtocol->objectName().isEmpty())
            BluetoothAppProtocol->setObjectName(QString::fromUtf8("BluetoothAppProtocol"));
        BluetoothAppProtocol->resize(789, 398);
        linkbithd = new QPushButton(BluetoothAppProtocol);
        linkbithd->setObjectName(QString::fromUtf8("linkbithd"));
        linkbithd->setGeometry(QRect(80, 40, 75, 23));
        openblue = new QPushButton(BluetoothAppProtocol);
        openblue->setObjectName(QString::fromUtf8("openblue"));
        openblue->setGeometry(QRect(520, 50, 75, 23));
        closeblue = new QPushButton(BluetoothAppProtocol);
        closeblue->setObjectName(QString::fromUtf8("closeblue"));
        closeblue->setGeometry(QRect(610, 50, 75, 23));
        groupBox = new QGroupBox(BluetoothAppProtocol);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(230, 30, 221, 301));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 20, 121, 23));
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(50, 50, 121, 23));
        pushButton_10 = new QPushButton(groupBox);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(20, 80, 131, 23));
        pushButton_12 = new QPushButton(groupBox);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(20, 110, 75, 23));
        pushButton_11 = new QPushButton(groupBox);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(20, 140, 75, 23));
        pushButton_14 = new QPushButton(groupBox);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(20, 170, 75, 23));
        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(50, 200, 121, 23));
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(130, 140, 81, 23));
        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(130, 110, 81, 23));
        labelprogress = new QLabel(groupBox);
        labelprogress->setObjectName(QString::fromUtf8("labelprogress"));
        labelprogress->setGeometry(QRect(20, 270, 181, 20));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 240, 164, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);

        horizontalLayout->addWidget(progressBar);

        groupBox_2 = new QGroupBox(BluetoothAppProtocol);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 80, 151, 201));
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 30, 111, 23));
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(20, 60, 111, 23));
        pushButton_13 = new QPushButton(groupBox_2);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(20, 90, 111, 23));
        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(20, 120, 111, 23));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(true);
        pushButton_2->setGeometry(QRect(20, 150, 111, 23));
        layoutWidget1 = new QWidget(BluetoothAppProtocol);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 350, 421, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        linkstatus = new QLabel(layoutWidget1);
        linkstatus->setObjectName(QString::fromUtf8("linkstatus"));

        horizontalLayout_2->addWidget(linkstatus);

        bluestatus = new QLabel(BluetoothAppProtocol);
        bluestatus->setObjectName(QString::fromUtf8("bluestatus"));
        bluestatus->setEnabled(false);
        bluestatus->setGeometry(QRect(520, 130, 207, 29));
        textEdit = new QTextEdit(BluetoothAppProtocol);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(480, 40, 281, 341));

        retranslateUi(BluetoothAppProtocol);

        QMetaObject::connectSlotsByName(BluetoothAppProtocol);
    } // setupUi

    void retranslateUi(QWidget *BluetoothAppProtocol)
    {
        BluetoothAppProtocol->setWindowTitle(QCoreApplication::translate("BluetoothAppProtocol", "BITHD\345\210\267\346\234\272\345\267\245\345\205\267", nullptr));
        linkbithd->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\277\236\346\216\245BITHD", nullptr));
        openblue->setText(QCoreApplication::translate("BluetoothAppProtocol", "\346\211\223\345\274\200\350\223\235\347\211\231", nullptr));
        closeblue->setText(QCoreApplication::translate("BluetoothAppProtocol", "\345\205\263\351\227\255\350\223\235\347\211\231", nullptr));
        groupBox->setTitle(QCoreApplication::translate("BluetoothAppProtocol", "\344\270\213\350\275\275\345\212\237\350\203\275\345\214\272", nullptr));
        pushButton->setText(QCoreApplication::translate("BluetoothAppProtocol", "Close OLED", nullptr));
        pushButton_5->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\277\233\345\205\245\344\270\213\350\275\275\346\250\241\345\274\217", nullptr));
        pushButton_10->setText(QCoreApplication::translate("BluetoothAppProtocol", "\347\203\247\345\206\231\346\250\241\345\274\217\345\210\235\345\247\213\345\214\226", nullptr));
        pushButton_12->setText(QCoreApplication::translate("BluetoothAppProtocol", "\346\223\246\351\231\244\345\233\272\344\273\266", nullptr));
        pushButton_11->setText(QCoreApplication::translate("BluetoothAppProtocol", "\347\203\247\345\206\231\345\233\272\344\273\266", nullptr));
        pushButton_14->setText(QCoreApplication::translate("BluetoothAppProtocol", "\346\243\200\346\237\245\345\233\272\344\273\266", nullptr));
        pushButton_6->setText(QCoreApplication::translate("BluetoothAppProtocol", "\351\200\200\345\207\272\344\270\213\350\275\275\346\250\241\345\274\217", nullptr));
        pushButton_7->setText(QCoreApplication::translate("BluetoothAppProtocol", "PING\346\265\213\350\257\225", nullptr));
        pushButton_9->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\207\252\346\265\213\350\257\225\346\250\241\345\274\217", nullptr));
        labelprogress->setText(QString());
        label->setText(QCoreApplication::translate("BluetoothAppProtocol", "\344\270\213\350\275\275\350\277\233\345\272\246", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("BluetoothAppProtocol", "\346\231\256\351\200\232\345\212\237\350\203\275", nullptr));
        pushButton_3->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\216\267\345\217\226\345\274\225\345\257\274\347\211\210\346\234\254", nullptr));
        pushButton_4->setText(QCoreApplication::translate("BluetoothAppProtocol", "\346\233\264\346\226\260\346\227\266\351\227\264", nullptr));
        pushButton_13->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\216\267\345\217\226\346\216\245\346\224\266\347\212\266\346\200\201", nullptr));
        pushButton_8->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\216\267\345\217\226\347\224\265\351\207\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\277\233\345\205\245\346\227\266\351\227\264\346\250\241\345\274\217", nullptr));
        linkstatus->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\277\236\346\216\245\347\212\266\346\200\201\357\274\232\346\234\252\350\277\236\346\216\245", nullptr));
        bluestatus->setText(QCoreApplication::translate("BluetoothAppProtocol", "\350\223\235\347\211\231\347\212\266\346\200\201:\345\267\262\345\205\263\351\227\255", nullptr));
        textEdit->setHtml(QCoreApplication::translate("BluetoothAppProtocol", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\344\275\277\347\224\250\350\257\264\346\230\216</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\347\241\256\344\277\235\346\234\272\345\255\220\345\274\200\345\220\257\350\223\235\347\211\231\345\220\216 \345\205\210\345\234\250WIN10\351\207\214\345\260\206\350\223\235\347\211\231\351\205\215\345\257\271\344\270\212 \345\206\215\345\233\236\346\235\245\344\275\277\347\224\250\350\275\257\344\273\266<"
                        "/span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">-------\344\270\213\350\275\275\345\212\237\350\203\275\345\214\272\350\257\264\346\230\216-------</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\347\203\247\345\206\231\345\233\272\344\273\266\350\257\264\346\230\216\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-ind"
                        "ent:0px;\"><span style=\" font-family:'SimSun';\">1.\347\202\271\345\207\273CLOSE OLED \347\241\256\344\277\235\346\234\272\345\255\220\345\261\217\345\271\225\345\267\262\350\242\253\345\205\263\351\227\255</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">2.\347\202\271\345\207\273\350\277\233\345\205\245\344\270\213\350\275\275\346\250\241\345\274\217</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">3.\347\202\271\345\207\273\347\203\247\345\206\231\346\250\241\345\274\217\345\210\235\345\247\213\345\214\226</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">4.\347\202\271\345\207\273\346\223\246\351\231\244\345\233\272\344\273\266</span><"
                        "/p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">5.\347\202\271\345\207\273\347\203\247\345\206\231\345\233\272\344\273\266 \351\200\211\346\213\251\346\255\243\347\241\256\345\233\272\344\273\266\347\203\247\345\206\231</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">6.\351\200\211\346\213\251\346\243\200\346\237\245\345\233\272\344\273\266</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">7.\347\202\271\345\207\273\351\200\200\345\207\272\344\270\213\350\275\275\346\250\241\345\274\217</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-famil"
                        "y:'SimSun';\">\346\263\250\346\204\217 \344\273\245\344\270\212\344\273\273\344\275\225\344\270\200\346\255\245\345\244\261\350\264\245\350\257\267\350\277\224\345\233\236\347\254\254\344\270\200\346\255\245\351\207\215\346\226\260\345\274\200\345\247\213</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\350\277\233\345\205\245\344\270\213\350\275\275\350\277\207\347\250\213\345\220\216\350\257\267\345\213\277\347\202\271\345\207\273\344\273\273\344\275\225\346\223\215\344\275\234 \350\200\220\345\277\203\347\255\211\345\276\205</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\344\270\213\350\275\275\350\277\207\347\250\213\345\276\210\351\225\277 \345\217\257\350\203\275\351\234\200\350\246\20120\345\207\240\345\210\206\351\222\237</span></p>\n"
"<p style=\" ma"
                        "rgin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\350\257\267\345\260\206\346\234\272\345\255\220\346\217\222\344\270\212\345\205\205\347\224\265 \344\277\235\346\214\201\347\224\265\351\207\217\344\276\233\345\272\224</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\350\207\252\346\265\213\350\257\225\346\250\241\345\274\217\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px"
                        "; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\345\234\250\344\270\213\350\275\275\346\250\241\345\274\217\344\270\213 \345\217\257\344\273\245\347\202\271\345\207\273\350\207\252\346\265\213\350\257\225\346\250\241\345\274\217\346\265\213\350\257\225\346\234\272\345\255\220\347\241\254\344\273\266\346\255\243\345\270\270</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">PING\346\265\213\350\257\225\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\345\234\250\344\270\213\350\275\275\346\250\241\345\274\217\344\270\213 \345\217\257\344\273"
                        "\245\347\202\271\345\207\273\346\265\213\350\257\225\346\234\272\345\255\220\345\234\250\344\270\213\350\275\275\346\250\241\345\274\217\344\270\213\345\223\215\345\272\224\346\230\257\345\220\246\346\255\243\345\270\270</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BluetoothAppProtocol: public Ui_BluetoothAppProtocol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BLUETOOTH_APPPROTOCOL_H
