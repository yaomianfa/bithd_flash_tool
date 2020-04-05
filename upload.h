#ifndef UPLOAD_H
#define UPLOAD_H

#include <QMessageBox>
#include <QThread>
#include <QFileDialog>
#include <QFile>
#include "bluetooth_appprotocol.h"
class BluetoothAppProtocol;
class UpLoad : public QThread
{
    Q_OBJECT
public:
    UpLoad();
    void setupAPP(BluetoothAppProtocol *app);
    int fillprotobufint(uint8_t *,uint32_t len);
protected:
    void virtual run();

public:
    BluetoothAppProtocol *app;
    QString Filename;
    uint32_t lastlen=0;

signals:

    void SendToProgressBar(int);
    void SendToProgresslabel(QString);
    void SendError(QString);
};

#endif // UPLOAD_H
