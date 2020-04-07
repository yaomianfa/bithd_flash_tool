#include "bluetooth_appprotocol.h"
#include "ui_bluetooth_appprotocol.h"
#include <QScreen>
#include <QProcess>
BluetoothAppProtocol::BluetoothAppProtocol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BluetoothAppProtocol)
{

    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    QList<QScreen*> screens = QApplication::screens();
    if (screens.size() > 0) {
            QScreen* screen = screens[0];
            connect(screen, &QScreen::logicalDotsPerInchChanged, this, &BluetoothAppProtocol::onLogicalDotsPerInchChanged);
    }

    ack_time=new QTimer(this);
    connect(ack_time,SIGNAL(timeout()),this,SLOT(BluetoothWork()));
    ack_time->start(20);

}
void BluetoothAppProtocol::onLogicalDotsPerInchChanged(qreal dpi)
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(),QStringList());

}

BluetoothAppProtocol::~BluetoothAppProtocol()
{
    delete ui;
}

void BluetoothAppProtocol::on_pushButton_clicked()
{

    closeOled(0);
}

void BluetoothAppProtocol::BluetoothSetupHW(Bluetooth_HWprotocol* hw){
    hwp=hw;
    connect(hwp,SIGNAL(readysuccess()),this,SLOT(readysucess()));
    connect(hwp,SIGNAL(unready()),this,SLOT(unready()));
    if( hwp->localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff )  {
            ui->openblue->setEnabled(true);
            ui->closeblue->setEnabled(false);
            ui->bluestatus->setText(QString::fromLocal8Bit("蓝牙状态：已关闭"));
    }else {
            ui->openblue->setEnabled(false);
            ui->closeblue->setEnabled(true);
            ui->bluestatus->setText(QString::fromLocal8Bit("蓝牙状态：已开启"));

    }
}



/**************************************************
seting cmd manage function
***************************************************/
void BluetoothAppProtocol::closeOled(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::closeOled;
        hwp->communicationBluetooth.label[0]=0;
        hwp->communicationBluetooth.cmd_id[0]=2; //进入setupf
        hwp->communicationBluetooth.data[0]=setup_turnoff;
        hwp->Send_bluetoothdata(1);
    }else{

        if(hwp->communicationBluetooth.cmd_id[0]==2 && hwp->communicationBluetooth.data[0]==setup_turnoff)
            QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("关闭OLED成功"));
        else
            QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("关闭OLED失败"));
    }

}

void BluetoothAppProtocol::setup_time_f(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::setup_time_f;
        hwp->communicationBluetooth.label[0]=hwp->communicationBluetooth.label[0]++;
        hwp->communicationBluetooth.cmd_id[0]=2; //进入setupf
        hwp->communicationBluetooth.data[0]=setup_time;

        //设置时间
        QTime current_time =QTime::currentTime();
        QDate current_date =QDate::currentDate();
        time_union_t time;
   //     time_union_t *time=(time_union_t *)&(hwp->communicationBluetooth.data[1]);
        time.time.seconds=(uint32_t)current_time.second();
        time.time.minute=(uint32_t)current_time.minute();
        time.time.hours=(uint32_t)current_time.hour();
        time.time.day=(uint32_t)current_date.day();
        time.time.month=(uint32_t)current_date.month();
        time.time.year=(uint32_t)current_date.year()-2000;
        hwp->communicationBluetooth.data[1]=time.data>>24;
        hwp->communicationBluetooth.data[2]=time.data>>16;
        hwp->communicationBluetooth.data[3]=time.data>>8;
        hwp->communicationBluetooth.data[4]=time.data;

       // qDebug()<<current_date.year()<<current_date.month()<<current_date.day();
       // qDebug()<<current_time.hour()<<current_time.minute()<<current_time.second();

        hwp->Send_bluetoothdata(5);
    }else{

        if(hwp->communicationBluetooth.cmd_id[0]==2 && hwp->communicationBluetooth.data[0]==setup_time)
            QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("更新时间成功"));
        else
            QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("更新时间失败"));
    }




}

void BluetoothAppProtocol::setup_balance_f(void){
    hwp->communicationBluetooth.label[0]=0;
    hwp->communicationBluetooth.cmd_id[0]=2; //进入setupf
    hwp->communicationBluetooth.data[0]=setup_balance;

    //59字节的BALANCE数据 这里暂时不处理
    hwp->Send_bluetoothdata(60);

}

void BluetoothAppProtocol::setup_timeout_f(void){  //设置超时时间
    hwp->communicationBluetooth.label[0]=0;
    hwp->communicationBluetooth.cmd_id[0]=2; //进入setupf
    hwp->communicationBluetooth.data[0]=setup_timeout;
    hwp->communicationBluetooth.data[1]=(uint8_t)1000; //设置超时时间
    hwp->Send_bluetoothdata(2);

}

void BluetoothAppProtocol::setup_getpower_f(int mode=0){ //获得电源
    if(mode==0){
        AckF=&BluetoothAppProtocol::setup_getpower_f;
        hwp->communicationBluetooth.label[0]=hwp->communicationBluetooth.label[0]++;
        hwp->communicationBluetooth.cmd_id[0]=2; //进入setupf
        hwp->communicationBluetooth.data[0]=setup_getpower;
        hwp->Send_bluetoothdata(1);
    }else{

        QString strvalue;
        int intvalue=hwp->communicationBluetooth.data[1];
        strvalue=tr("%1").arg(intvalue);
        QMessageBox::information(this,QString::fromLocal8Bit("电源信息"),strvalue);

    }

}

void BluetoothAppProtocol::setup_getversion_f(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::setup_getversion_f;
        hwp->communicationBluetooth.label[0]=hwp->communicationBluetooth.label[0]++;
        hwp->communicationBluetooth.cmd_id[0]=2; //进入setupf
        hwp->communicationBluetooth.data[0]=setup_getversion;
        hwp->Send_bluetoothdata(1);
    }else{

        int version_0,version_1,version_2;
        QString strvalue;
        version_0=hwp->communicationBluetooth.data[1];
        version_1=hwp->communicationBluetooth.data[2];
        version_2=hwp->communicationBluetooth.data[3];
        strvalue=tr("BOOT_VERSION:%1.%2.%3").arg(version_0).arg(version_1).arg(version_2);
        QMessageBox::information(this,QString::fromLocal8Bit("版本信息"),strvalue);
    }


}




//Download_cmd_F  cmdid=1
void BluetoothAppProtocol::enterDownload(int mode=0){
    if(mode==0){
        //注意 需要MAIN_STATUS_CLOSEOLED
        AckF=&BluetoothAppProtocol::enterDownload;
        hwp->communicationBluetooth.cmd_id[0]=1;
        hwp->communicationBluetooth.data[0]=1;
        hwp->Send_bluetoothdata(1);
    }
    else{

        if(hwp->communicationBluetooth.data[0]==0x02 && hwp->communicationBluetooth.data[1]==0x01 && hwp->communicationBluetooth.data[2]==0x00)
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("进入下载模式失败"));
        else QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("进入下载模式成功"));
    }


}

void BluetoothAppProtocol::exitDownload(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::exitDownload;
        hwp->communicationBluetooth.cmd_id[0]=1;
        hwp->communicationBluetooth.data[0]=4;
        hwp->Send_bluetoothdata(1);

    }
    else{

        if(hwp->communicationBluetooth.data[0]==0x02 && hwp->communicationBluetooth.data[1]==0x00 && hwp->communicationBluetooth.data[2]==0x00){
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("退出下载模式成功"));
        }else{
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("退出下载模式失败"));
        }
    }


}


//下载模式下传输数据 apdu cmd
void BluetoothAppProtocol::toUartData(QByteArray qby){
    //    AckF=&BluetoothAppProtocol::toUartData;
        hwp->communicationBluetooth.label[0]=hwp->communicationBluetooth.label[0]++;
        hwp->communicationBluetooth.cmd_id[0]=1;
        hwp->communicationBluetooth.data[0]=3;
        //apdu length
        hwp->communicationBluetooth.data[1]=qby.length()>>8;
        hwp->communicationBluetooth.data[2]=qby.length()&0xff;
        //apdu msg
        for(int i=0;i<qby.length();i++){
            hwp->communicationBluetooth.data[i+3]=qby[i];
        }
        hwp->Send_bluetoothdata(3+qby.length());

}


//以下函数全是凭借 toUartData 向主控发送数据

//让主控进入 flash_state = STATE_OPEN模式 进行初始化
void BluetoothAppProtocol::Flash_ENTER_STATE_OPEN(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::Flash_ENTER_STATE_OPEN;
        QByteArray qby;
        qby.resize(64);

        qby[0]= '?';
        qby[1]= '#';
        qby[2]= '#';

        //msg_id
        qby[3]=0;
        qby[4]=0;

        //msg.size
        qby[5]=0;
        qby[6]=0;
        qby[7]=0;
        qby[8]=9;

        toUartData(qby);


    }else{

        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("烧写模式初始化成功"));


    }

}

// 在STATE_OPEN模式的前提下 擦除FLASH // FirmwareErase message (id 6) 后进入STATE_FLASHSTART
void BluetoothAppProtocol::FirmwareErase(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::FirmwareErase;
        QByteArray qby;
        qby.resize(64);

        qby[0]= '?';
        qby[1]= '#';
        qby[2]= '#';

        //msg_id
        qby[3]=0;
        qby[4]=6;

        //msg.size
        qby[5]=0;
        qby[6]=0;
        qby[7]=0;
        qby[8]=9;

        toUartData(qby);


    }else{

        if(hwp->communicationBluetooth.length[1]==4)
        {
            needtowACK=true;
            QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("请在机子上操作确认擦除！"));
        }else{
            if(hwp->communicationBluetooth.data[7]==0x02)
            QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("固件擦除成功！"));
            else QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("固件擦除失败！"));

        }

    }

}
void BluetoothAppProtocol::getrecivestatus(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::getrecivestatus;
        hwp->communicationBluetooth.cmd_id[0]=9;
        hwp->communicationBluetooth.data[0]=4;
        hwp->Send_bluetoothdata(1);

    }
    else{

        QString strvalue;
        int oldlabel;
        int cmd0;
        int cmd1;
        oldlabel=hwp->communicationBluetooth.data[0];
        cmd0=hwp->communicationBluetooth.data[1];
        cmd1=hwp->communicationBluetooth.data[2];
        strvalue=QString::fromLocal8Bit("LABEL:%1 CMD_0:%2 CMD_1:%3").arg(oldlabel).arg(cmd0).arg(cmd1);
        QMessageBox::information(this,QString::fromLocal8Bit("接收状态"),strvalue);
    }
}

void BluetoothAppProtocol::FirmwareUpload1(uint8_t data[64]){
        AckF=&BluetoothAppProtocol::FirmwareUpload1ACK;
        QByteArray qby;
        qby.resize(64);

        qby[0]= '?';
        qby[1]= '#';
        qby[2]= '#';

        //msg_id
        qby[3]=0;
        qby[4]=7;

        //msg.size
        qby[5]=0;
        qby[6]=0;
        qby[7]=0;
        qby[8]=64;
        qby[9]=0xa;


        memcpy(&qby.data()[10],data,54);
        toUartData(qby);
}

void BluetoothAppProtocol::FirmwareUpload1ACK(int mode=0){ //这里的ACK供两个状态使用

    if(hwp->communicationBluetooth.length[0]==0 && hwp->communicationBluetooth.length[1]==4){ //ACK回复
        statusACK=true;
    }else{
        if(hwp->communicationBluetooth.data[7]==0x1a)QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("固件烧写完毕！"));
        else if(hwp->communicationBluetooth.data[7]!=0x2)
            QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("固件烧写失败！"));


    }


}

//在STATE_FLASHING前提下 进行固件升级 // FirmwareUpload message (id 7) 这个后进入STATE_CHECK
void BluetoothAppProtocol::FirmwareUpload2(uint8_t data[64]){
        AckF=&BluetoothAppProtocol::FirmwareUpload1ACK;
        QByteArray qby;
        qby.resize(64);

        qby[0]= '?';
        memcpy(&qby.data()[1],data,63);
        toUartData(qby);
}



//主控下载模式下的自测试模式
void BluetoothAppProtocol::Flash_SELFTEST(int mode=0){

    if(mode==0){
        AckF=&BluetoothAppProtocol::Flash_SELFTEST;
        QByteArray qby;
        qby.resize(64);

        qby[0]= '?';
        qby[1]= '#';
        qby[2]= '#';

        //msg_id
        qby[3]=0;
        qby[4]=0x20;

        //msg.size
        qby[5]=0;
        qby[6]=0;
        qby[7]=0;
        qby[8]=9+2+53;

        //data
        qby[9]=0x0a;
        qby[10]=53;
        char str[54]={
                      "\x00\xFF\x55\xAA\x66\x99\x33\xCC"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!"
                      "\x00\xFF\x55\xAA\x66\x99\x33\xCC"};
        memcpy(&qby.data()[11],&str,53);

        toUartData(qby);


    }else{

        if(hwp->communicationBluetooth.data[7]==0x02)
        QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("主控自测试完全通过！"));
        else QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("主控自测试不完全通过！"));

    }
}



void BluetoothAppProtocol::Flash_PING(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::Flash_PING;
        QByteArray qby;
        qby.resize(64);

        qby[0]= '?';
        qby[1]= '#';
        qby[2]= '#';

        //msg_id
        qby[3]=0;
        qby[4]=1;

        //msg.size
        qby[5]=0;
        qby[6]=0;
        qby[7]=0;
        qby[8]=9;

        toUartData(qby);


    }else{

        QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("主控在下载模式下响应正常"));

    }

}



//handle ack
void BluetoothAppProtocol::BluetoothWork(void){
    if(hwp->blueRecivSendflag==bluetoothRecivedata){

        if(AckF){
            void(BluetoothAppProtocol::*AckF_tmp)(int)=AckF;
            (this->*AckF_tmp)(1);

            if(!needtowACK)
                AckF=NULL;
            else
                needtowACK=false;
        }
       hwp->blueRecivSendflag=bluetoothNOdata;
    }

}


void BluetoothAppProtocol::enterTimeMode(void){
        hwp->communicationBluetooth.label[0]=hwp->communicationBluetooth.label[0]++;
        hwp->communicationBluetooth.cmd_id[0]=7;
        hwp->communicationBluetooth.data[0]=1;
        hwp->communicationBluetooth.data[1]=0;
        hwp->Send_bluetoothdata(2);
}

void BluetoothAppProtocol::on_pushButton_2_clicked()
{
    enterTimeMode();
}

void BluetoothAppProtocol::on_pushButton_3_clicked()
{
    setup_getversion_f();
}

void BluetoothAppProtocol::on_pushButton_4_clicked()
{
    setup_time_f();
}

void BluetoothAppProtocol::on_pushButton_5_clicked()
{
    enterDownload();
}

void BluetoothAppProtocol::on_pushButton_6_clicked()
{
    exitDownload();
}

void BluetoothAppProtocol::on_pushButton_7_clicked()
{
    Flash_PING();
}

void BluetoothAppProtocol::on_pushButton_8_clicked()
{
    setup_getpower_f();
}

void BluetoothAppProtocol::on_pushButton_9_clicked()
{
    Flash_SELFTEST();
}

void BluetoothAppProtocol::on_pushButton_10_clicked()
{
    Flash_ENTER_STATE_OPEN();
}


void BluetoothAppProtocol::on_pushButton_12_clicked()
{
    FirmwareErase();


}
void BluetoothAppProtocol::setProgressbar(int value){
    ui->progressBar->setValue(value);
}

void BluetoothAppProtocol::UpLoadError(QString Error){
    QMessageBox::warning(this,QString::fromLocal8Bit("警告"),Error);
}
void BluetoothAppProtocol::setProgresslabel(QString str){
    ui->labelprogress->setText(str);
}
void BluetoothAppProtocol::on_pushButton_11_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL,QString::fromLocal8Bit("选择固件"),"",tr("*"));
    if (fileName.isEmpty())
            return;
    upload->Filename=fileName;
    connect(upload, SIGNAL(SendToProgressBar(int)), this, SLOT(setProgressbar(int)));
    connect(upload, SIGNAL(SendError(QString)), this, SLOT(UpLoadError(QString)));
    connect(upload, SIGNAL(SendToProgresslabel(QString)), this, SLOT(setProgresslabel(QString)));

    this->upload->start();

}
//进行FLASH检查 这里的应答还没处理好
void BluetoothAppProtocol::FLASH_CHECK(int mode=0){
    if(mode==0){
        AckF=&BluetoothAppProtocol::FLASH_CHECK;
        QByteArray qby;
        qby.resize(64);

        qby[0]= '?';
        qby[1]= '#';
        qby[2]= '#';

        //msg_id
        qby[3]=0;
        qby[4]=0x1B;

        //msg.size
        qby[5]=0;
        qby[6]=0;
        qby[7]=0;
        qby[8]=9;

        toUartData(qby);


    }else{
        if(hwp->communicationBluetooth.length[1]==4 && hwp->communicationBluetooth.length[0]==0){
            needtowACK=true;
            return;
        }


        if(hwp->communicationBluetooth.data[7]==0x02)
        QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("固件签名正确！"));
        else QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("固件签名不正确！"));


    }
}
void BluetoothAppProtocol::setupload(UpLoad * upload){
    this->upload=upload;
}

void BluetoothAppProtocol::on_pushButton_13_clicked()
{
    getrecivestatus();
}

void BluetoothAppProtocol::on_pushButton_14_clicked()
{
    FLASH_CHECK();
}




void BluetoothAppProtocol::on_openblue_clicked()
{
    if( hwp->localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff )  {
            hwp->localDevice->powerOn();
    }
    if(hwp->localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff){
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("蓝牙开启失败"));
        return;
    }
    ui->closeblue->setEnabled(true);
    ui->openblue->setEnabled(false);
}

void BluetoothAppProtocol::on_closeblue_clicked()
{
    hwp->localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    if(hwp->localDevice->hostMode()!=QBluetoothLocalDevice::HostPoweredOff){
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("蓝牙关闭失败"));
        return;
    }
    ui->closeblue->setEnabled(false);
    ui->openblue->setEnabled(true);
}

void BluetoothAppProtocol::on_linkbithd_clicked()
{
    if(hwp->m_control!=NULL && hwp->m_control->state()==QLowEnergyController::DiscoveredState){
          QMessageBox::information(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("已连接BITHD 请勿重复点击"));
          return;
    }
    hwp->discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod); //开启扫描
    ui->linkstatus->setText(QString::fromLocal8Bit("连接状态：扫描BITHD中"));

}

void BluetoothAppProtocol::readysucess(){ //槽信号 代表连接成功
    QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("连接成功"));
    ui->linkstatus->setText(QString::fromLocal8Bit("连接状态：已连接"));
}

void BluetoothAppProtocol::unready(){ //HW层的连接失败
    ui->linkstatus->setText(QString::fromLocal8Bit("连接状态：连接失败"));
}
