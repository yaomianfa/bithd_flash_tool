#include <QApplication>
#include "bluetooth_hwprotocol.h"
#include "bluetooth_appprotocol.h"
#include "upload.h"
#include <QNetworkInterface>
//QT验证功能相关

int main(int argc, char *argv[])
{
#if(QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);
    Bluetooth_HWprotocol *bluetooth_hw=new Bluetooth_HWprotocol();
    BluetoothAppProtocol *bluetooth_app=new BluetoothAppProtocol();
    UpLoad * upload=new UpLoad();
    upload->setupAPP(bluetooth_app);
    bluetooth_app->BluetoothSetupHW(bluetooth_hw);
    bluetooth_app->setupload(upload);
    bluetooth_app->show();



    return a.exec();
}
