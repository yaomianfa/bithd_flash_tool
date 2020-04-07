#ifndef BLUETOOTHAPPPROTOCOL_H
#define BLUETOOTHAPPPROTOCOL_H

#include <QWidget>
#include <bluetooth_hwprotocol.h>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include "upload.h"
#define setup_time            0x01
#define setup_balance         0x02
#define setup_timeout         0x03
#define setup_getpower        0x04
#define setup_getversion      0x05
#define setup_turnoff         0x06

/* time bit field */
typedef struct
{
uint32_t seconds  :
    6;
uint32_t minute  :
    6;
uint32_t hours  :
    5;
uint32_t day   :
    5;
uint32_t month  :
    4;
uint32_t year   :
    6;
}
time_bit_field_type_t;



typedef union
{
    uint32_t data;
    time_bit_field_type_t time;
} time_union_t;
/* time bit field */

class UpLoad;
namespace Ui {
class BluetoothAppProtocol;
}

class BluetoothAppProtocol : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothAppProtocol(QWidget *parent = nullptr);
    ~BluetoothAppProtocol();
    void closeOled(int);
    void enterTimeMode(void);
    void BluetoothSetupHW(Bluetooth_HWprotocol* hw);
    void setup_time_f(int);
    void setup_balance_f();
    void setup_timeout_f();
    void setup_getpower_f(int);
    void setup_getversion_f(int);
    void enterDownload(int);
    void exitDownload(int);
    void toUartData(QByteArray qby);
    void Flash_ENTER_STATE_OPEN(int);
    void Flash_PING(int);
    void Flash_SELFTEST(int);
    void FirmwareErase(int);
    void FirmwareUpload1(uint8_t data[]);
    void FirmwareUpload1ACK(int);
    void FirmwareUpload2(uint8_t data[]);
    void getrecivestatus(int);
    void FirmWareUpload();
    void setupload(UpLoad *upload);
    void FLASH_CHECK(int);
    Bluetooth_HWprotocol *hwp;
private slots:
    void on_pushButton_clicked();
    void setProgressbar(int);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void BluetoothWork();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();
    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_openblue_clicked();

    void on_closeblue_clicked();

    void on_linkbithd_clicked();
    void readysucess();
    void unready();
    void UpLoadError(QString Error);
    void setProgresslabel(QString);
    void  onLogicalDotsPerInchChanged(qreal dpi);
public:
    bool statusACK=true;
    void(BluetoothAppProtocol::*AckF)(int)=NULL;
private:
    QTimer *ack_time;
    Ui::BluetoothAppProtocol *ui;
    UpLoad * upload;
    bool needtowACK=false;
};

#endif // BLUETOOTHAPPPROTOCOL_H
