#include "bluetooth_hwprotocol.h"
#include "ui_bluetooth_hwprotocol.h"

Bluetooth_HWprotocol::Bluetooth_HWprotocol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bluetooth_HWprotocol)
{

    ui->setupUi(this);
    T_Connect=new QTimer(this);
    rec_send=new QTimer(this);
    connect(rec_send,SIGNAL(timeout()),this,SLOT(Bluetooth_ReciveANDSend()));
    connect(T_Connect,SIGNAL(timeout()),this,SLOT(timeoutf()));
    T_Connect->setSingleShot(true);
    localDevice=new QBluetoothLocalDevice();
    discoveryAgent =new QBluetoothDeviceDiscoveryAgent();
    connect(discoveryAgent,
                SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
                this,
                SLOT(addBlueToothDevicesToList(QBluetoothDeviceInfo))
                );
    connect(discoveryAgent,SIGNAL(finished()),this,SLOT(deviceDiscoveredDone()));

    if( localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff )  {
            localDevice->powerOn();
    }
    discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::LimitedInquiry);
    discoveryAgent->setLowEnergyDiscoveryTimeout(7000);
}
void Bluetooth_HWprotocol::TP_START(uint32_t Delaytime)
{
    T_Connect->start(1000);
}


void  Bluetooth_HWprotocol::TP_CLOSE(void)
{
    T_Connect->stop();
    timerout=false;
}


unsigned char  Bluetooth_HWprotocol::CheckTP(void)
{
    if(timerout)
        {
          timerout=false;
          return 0;
        }
    return 1;
}
void Bluetooth_HWprotocol::timeoutf(void){
    timerout=true;
    T_Connect->stop();
}
Bluetooth_HWprotocol::~Bluetooth_HWprotocol()
{
    delete ui;
}
void Bluetooth_HWprotocol::bluetoothConnectedEvent(){
    qDebug()<<"link success!";
    discoveryAgent->stop();
}
void Bluetooth_HWprotocol::bluetoothDisconnectedEvent(){

}
void Bluetooth_HWprotocol::bluetoothErrorEvent(QBluetoothSocket::SocketError error){
    QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketError>();
    QMessageBox::information(NULL, "error", metaEnum.valueToKey(error));
}

void Bluetooth_HWprotocol::BlueServiceDiscovered(QBluetoothUuid gatt){
//    qDebug()<<gatt.toString();

}

void Bluetooth_HWprotocol::BleServiceCharacteristicRead(QLowEnergyCharacteristic,QByteArray){
   //  qDebug()<<"read data succeed";
}
void Bluetooth_HWprotocol::BleServiceCharacteristicWrite(QLowEnergyCharacteristic,QByteArray){
  //  qDebug()<<QString::fromLocal8Bit("send the data succeed");
}
void Bluetooth_HWprotocol::BleServiceServiceStateChanged(QLowEnergyService::ServiceState s){
    if(s == QLowEnergyService::ServiceDiscovered){
            searchCharacteristic();
        }
}


void Bluetooth_HWprotocol::BlueServiceScanDone(){
     qDebug()<<"scan service done";
     m_service=m_control->createServiceObject(QBluetoothUuid(serviceUuid),this);
     if(m_service==NULL){
         qDebug()<<"service create failed";
     }
     connect(m_service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),

                     this, SLOT(BleServiceServiceStateChanged(QLowEnergyService::ServiceState)));

     connect(m_service, SIGNAL(characteristicRead(QLowEnergyCharacteristic,QByteArray)),

                   this, SLOT(BleServiceCharacteristicRead(QLowEnergyCharacteristic,QByteArray)));

     connect(m_service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic,QByteArray)),

                   this, SLOT(BleServiceCharacteristicWrite(QLowEnergyCharacteristic,QByteArray)));

     connect(m_service, static_cast<void(QLowEnergyService::*)(QLowEnergyService::ServiceError)>(&QLowEnergyService::error),

            [=](QLowEnergyService::ServiceError newErrorr)

       {

           QMetaEnum metaEnum = QMetaEnum::fromType<QLowEnergyService::ServiceError>();
           QMessageBox::information(NULL, "error", metaEnum.valueToKey(newErrorr));

       });
     if(m_service->state() == QLowEnergyService::DiscoveryRequired)

      {
          m_service->discoverDetails();

      }else searchCharacteristic();

}

void Bluetooth_HWprotocol::deviceDiscoveredDone()
{
    qDebug()<<"deviceDiscoveredDone";
    QList<QBluetoothDeviceInfo> qlist=discoveryAgent->discoveredDevices();
    for(int i=0;i<qlist.count();i++){
        QBluetoothDeviceInfo info=qlist[i];
        if( (info.name().indexOf("BITHD")!=-1 || info.name().indexOf("RAZOR")!=-1) && info.rssi()!=0 ){

            if(info.name().indexOf("RAZOR")!=-1) serviceUuid= QLatin1String("00000001-0000-1000-8000-00805f9b34fb");
            else serviceUuid = QLatin1String("6e400001-b5a3-f393-e0a9-e50e24dcca9e");
            if(m_control!=NULL)delete m_control;
            m_control= new QLowEnergyController(info.address(), this);
            if(m_control==0){
                qDebug()<<QString::fromLocal8Bit("create m_control failed");
                return;
            }

            connect(m_control, SIGNAL(serviceDiscovered(QBluetoothUuid)),this, SLOT(BlueServiceDiscovered(QBluetoothUuid)));
            connect(m_control, SIGNAL(discoveryFinished()),this, SLOT(BlueServiceScanDone()));
            connect(m_control, SIGNAL(connected()),this, SLOT(bluetoothConnectedEvent()));
            connect(m_control, SIGNAL(disconnected()),this, SLOT(bluetoothDisconnectedEvent()));
            connect(m_control, static_cast<void(QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
                       [=](QLowEnergyController::Error error){
                        QMetaEnum metaEnum = QMetaEnum::fromType<QLowEnergyController::Error>();
                        QMessageBox::information(NULL, "error", metaEnum.valueToKey(error));
                        emit unready();

                 });

            m_control->connectToDevice();
            m_control->discoverServices();
            return;

        }

    }
    QMessageBox::information(NULL, "error", QString::fromLocal8Bit("未扫描到BITHD 请重新点击连接BITHD"));
    discoveryAgent->stop();
    emit unready();
}

void Bluetooth_HWprotocol::addBlueToothDevicesToList( const QBluetoothDeviceInfo &info )
{

}

void Bluetooth_HWprotocol::searchCharacteristic()

{

    if(m_service){
        QList<QLowEnergyCharacteristic> qlist=m_service->characteristics();
        for(int i=0;i<qlist.count();i++){
             QLowEnergyCharacteristic c=qlist[i];
             if(c.properties() & QLowEnergyCharacteristic::WriteNoResponse || c.properties() & QLowEnergyCharacteristic::Write){
                 tx_c=c;
             }else{
                 rx_c=c;
             }
        }
       if(!tx_c.isValid()){
           qDebug()<<"get tx_c failed";
           return;
       }
       if(!rx_c.isValid()){
           qDebug()<<"get rx_c failed";
           return;
       }
       QLowEnergyDescriptor m_desc= rx_c.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
       if(m_desc.isValid()) m_service->writeDescriptor(m_desc, QByteArray::fromHex("0100")); //enable notify
       else {
           qDebug()<<"enable notify failed";
           return;
       }
       connect(m_service, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
                     this, SLOT(characteristicHasChanged(QLowEnergyCharacteristic,QByteArray)));
       if(tx_c.properties()& QLowEnergyCharacteristic::WriteNoResponse) m_writeMode=QLowEnergyService::WriteWithoutResponse;
       else
           m_writeMode=QLowEnergyService::WriteWithResponse;
       ble_transfer_init();
       rec_send->start(20);
       emit readysuccess();//Notify the APP layer that it can start sending and receiving data
      }

}
void Bluetooth_HWprotocol::characteristicHasChanged(QLowEnergyCharacteristic qlec,QByteArray qby){

    //Received data
    ble_to_phone_data_parse(qby);
    Recivedataflag=1;

}

void Bluetooth_HWprotocol::ble_tx(QByteArray qby){
    if(tx_c.isValid())
        m_service->writeCharacteristic(tx_c,qby,m_writeMode);
    else
        qDebug()<<"no valid tx_c";
}

void Bluetooth_HWprotocol::on_pushButton_clicked() //enter timemode
{

    communicationBluetooth.label[0]=0;
    communicationBluetooth.cmd_id[0]=7;
    communicationBluetooth.data[0]=1;
    communicationBluetooth.data[1]=0;
    Send_bluetoothdata(2);

}

void Bluetooth_HWprotocol::ble_to_phone_data_parse(QByteArray qby)
{
    TP_CLOSE();
    uint16_t buf_len=qby.length();
    uint8_t *buf=(uint8_t *)qby.data();
    ucReTry = 0;
    if((buf[0] == 0xA5) && (buf[1] == 0xA5)) //ACK DATA
    {
        if(SumPackNumber!=0)
          {
            memcpy(ucaPackMsg, buf, buf_len);

            if(0x01 == ucaPackMsg[3])
            {
                ucResend = 1;
            }
            else
            {
                SumPackNumber=0;
                Sendlenth=0;
                lr = 0;
            }

        }

    }
    else
    {

        SumPackNumber=0;
        Sendlenth=0;
        lr = 0;

        if(SumPackNumber!=0) return;
        if(buf[0]!=0&&buf_len<3)return;
        if(buf[0]==0&&buf_len<4)return;


        TP_START(TimeOver);
        ucTotalPack = buf[1];

        if(CheckExist(buf[0],ucaRevPackN)) return;


        memcpy(g_apdu+buf[0]*18, buf+2, buf_len-2);
        MarkPackNum(buf[0],buf[1],ucaRevPackN, ucaPackMsg+2);
        ucExpPackN = NextExpPack(buf[0], ucaPackMsg+2);

        if(Apdufinsh==0){
             Apdufinsh=2;
             g_apdu_length=buf_len-2;
        }else
             g_apdu_length += buf_len-2;

        if((buf[0] == (buf[1]-1)) || (ucaPackMsg[3] == 0))
        {

            tell_ble_missed_packets();
            TP_CLOSE();

            if(ucaPackMsg[3] == 0)
            {
                Apdufinsh=1;
            }
            else
            {
                ucReTry = 1;
            }
        }
    }

}
void Bluetooth_HWprotocol::phone_to_ble_msg(void)
{
    QByteArray buf;
    buf.resize(PackRecive);
    if((lr<17)&&(lr>0))
    {
        buf.resize(lr+4);
        SumPackNumber=1;
        buf[0]=0;
        buf[1]=SumPackNumber;
        buf[2]=0;
        buf[3]=lr;
        memcpy(&buf.data()[4],g_apdu,lr);
        buf.resize(lr+4);
        ble_tx(buf);

        Sendlenth=lr;
        lr = 0;

        TP_START(TimeOver);//wait ack

    }
    if(lr>16)
    {

        SumPackNumber=(lr-(PackRecive-4))/(PackRecive-2)+1;
        if(lr>((PackRecive-4)+(SumPackNumber-1)*18))
        {
            SumPackNumber=SumPackNumber+1;
        }

        if(Sendlenth==0)
        {
            buf[0]=0;
            buf[1]=SumPackNumber;
            buf[2]=(lr>>8)&0x00ff;
            buf[3]=lr&0x00ff;
            memcpy(&buf.data()[4],g_apdu,PackRecive-4);
            ble_tx(buf);

            Sendlenth=PackRecive-4;
        }
        else
        {
            buf[0]=(Sendlenth-(PackRecive-4))/(PackRecive-2)+1;
            buf[1]=SumPackNumber;
            if((SumPackNumber-buf[0])!=1)
                {
                    memcpy(&buf.data()[2],&g_apdu[Sendlenth],PackRecive-2);
                    ble_tx(buf);
                    Sendlenth=Sendlenth+PackRecive-2;
                }
            else
                {
                    memcpy(&buf.data()[2],&g_apdu[Sendlenth],(lr-(PackRecive-4)-(Sendlenth-(PackRecive-4))));
                    buf.resize((lr-(PackRecive-4)-(Sendlenth-(PackRecive-4)))+2);
                    ble_tx(buf);
                    Sendlenth=lr;
                    lr = 0;
                    TP_START(TimeOver);
                }

        }
    }



}
//send data to BITHD
void Bluetooth_HWprotocol::Send_bluetoothdata(unsigned short len)
{
    unsigned short l=len;
    unsigned short crc16;
    //Organize the data according to the protocol
    l=l+3;
    communicationBluetooth.length[0]=l>>8;
    communicationBluetooth.length[1]=0x00ff&l;

    g_apdu_length=l+3;

    communicationBluetooth.crc16=&g_apdu[g_apdu_length-2];  //according send data updata crc data
    crc16=bd_crc16(0,g_apdu,g_apdu_length-2);
    communicationBluetooth.crc16[0]=crc16>>8;
    communicationBluetooth.crc16[1]=crc16&0x00ff;

    blueRecivSendflag=bluetoothSenddata;                    //send enable


}


void Bluetooth_HWprotocol::tell_ble_missed_packets(void)
{

    ucaPackMsg[0] = 0xA5;
    ucaPackMsg[1] = 0xA5;
    QByteArray qby;
    qby.resize(ucaPackMsg[2]+3);
    for(int i=0;i<qby.length();i++)qby[i]=ucaPackMsg[i];
    ble_tx(qby);

}

void Bluetooth_HWprotocol::MarkPackNum(uint8_t curPackN, uint8_t totalNum, uint8_t *RevPackN, uint8_t *MissedPackN)
{
    uint8_t i = 0, n, m, tmp, len;
    n = totalNum/8;
    m = totalNum%8;
    if(m != 0)
    {
        n += 1;
    }
    len = n+1;
    RevPackN[curPackN/8] |= 0x80 >> (curPackN%8);

    for(i=0;i<n;i++)
    {
        MissedPackN[2+i] = ~RevPackN[i];
    }

    if(m != 0)
    {
        tmp = MissedPackN[2+n-1] >> (8-m);
        MissedPackN[2+n-1] = tmp << (8-m);
    }

    for(i=2+n-1;i>1;i--)
    {
        if(MissedPackN[i] == 0x00)
        {
            len--;
        }
        else
        {
            break;
        }
    }
    MissedPackN[0] = len;
    MissedPackN[1] = (len==1 ? 0x00 : 0x01);
}

uint8_t Bluetooth_HWprotocol::CheckExist(uint8_t PackN, uint8_t *Msg)
{
    uint8_t tmp;
    tmp = Msg[PackN/8]<<(PackN%8);
    if(tmp&0x80)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t Bluetooth_HWprotocol::NextExpPack(uint8_t curPackN, const uint8_t *Msg)
{
    uint8_t tmp;

    tmp = Msg[2+curPackN/8]<<(curPackN%8);
    if(tmp&0x80) return (curPackN+1);

    return 0;
}
unsigned char Bluetooth_HWprotocol::SendPackNumber(unsigned char Number)
{
    QByteArray buf;
    buf.resize(PackRecive);
    buf[0]=Number;
    buf[1]=SumPackNumber;
    if(Number==0)
    {
        buf[2]=(Sendlenth>>8)&0x00ff;
        buf[3]=Sendlenth&0x00ff;
        memcpy(&buf.data()[4],g_apdu,PackRecive-4);
        ble_tx(buf);
        return 0;
    }
    else
    {
        if((SumPackNumber-buf[0])!=1)
        {
            memcpy(&buf.data()[2],&g_apdu[(Number-1)*(PackRecive-2)+(PackRecive-4)],PackRecive-2);
            ble_tx(buf);
            return 0;
        }
        else
        {
            memcpy(&buf.data()[2],&g_apdu[(Number-1)*(PackRecive-2)+(PackRecive-4)],(Sendlenth-((Number-1)*(PackRecive-2)+(PackRecive-4))));
            buf.resize((Sendlenth-((Number-1)*(PackRecive-2)+(PackRecive-4))));
            ble_tx(buf);
            return 0;
        }
    }
}

void Bluetooth_HWprotocol::ReSendNotification(uint8_t *PackMsg)
{

    uint8_t ucExpPackN_ = 0;
    uint8_t flag=0;

    if(remberPackn<(PackMsg[0]-1)*8)
    {
        ucExpPackN_ = NextExpPack(remberPackn,PackMsg);
    }


    if(ucExpPackN_!=0)
    {
        if(SendPackNumber(ucExpPackN_-1)==0)
        {

        }
        else
        {
            flag=1;
        }
    }


    if((ucExpPackN_==SumPackNumber&&flag==0)||(((PackMsg[0]-1)*8)==remberPackn))
    {
        ucResend=0;
        remberPackn=0;
        TP_START(TimeOver);
    }
    else
    {
        if(flag==0)
        {remberPackn++;}
    }
}

uint16_t Bluetooth_HWprotocol::crc16_byte(uint16_t crc, const uint8_t data)
{
    return (crc >> 8) ^ crc16_table[(crc ^ data) & 0xff];
}

/**
 * crc16 - compute the CRC-16 for the data buffer
 * @crc: previous CRC value
 * @buffer: data pointer
 * @len: number of bytes in the buffer
 *
 * Returns the updated CRC value.
 */
uint16_t Bluetooth_HWprotocol::bd_crc16(uint16_t crc, uint8_t const *buffer, uint16_t len)
{
    while (len--)
        crc = crc16_byte(crc, *buffer++);
    return crc;
}



void Bluetooth_HWprotocol::ble_transfer_init(void)
{
    memset(ucaRevPackN, 0, 15);
    memset(ucaPackMsg, 0, 20);

    ucExpPackN = 0;
    ucReTry = 0;
    ucTotalPack = 0;
    ucResend = 0;

   // ble_transfer_init();
    SumPackNumber=0;
    Sendlenth=0;
    lr = 0;
}

void Bluetooth_HWprotocol::Bluetooth_ReciveANDSend(void)
{


    if(blueRecivSendflag==bluetoothSenddata)
    {
        lr=g_apdu_length;
        blueRecivSendflag=bluetoothNOdata;
    }

    if(Recivedataflag==1)
    {

        Recivedataflag=0;
        Len_DATA=0;
        if(Apdufinsh==1)
        {
            /*********APDU****************/
            g_apdu_length=g_apdu_length-2;
            memcpy(g_apdu,&g_apdu[2],g_apdu_length);
            blueRecivSendflag=bluetoothRecivedata;
            ble_transfer_init();
            Apdufinsh=0;

        }
    }

    phone_to_ble_msg();

    if(ucResend==1)
    {
        ReSendNotification(&ucaPackMsg[2]);
    }
    if(!CheckTP())
    {

        if(Apdufinsh==2)
        {
            if(ucReTry<(WaitRertyTims))
            {
                tell_ble_missed_packets();
                ucReTry++;
            }
            else
            {
                TP_CLOSE();
                ble_transfer_init();
                Apdufinsh=0;
                g_apdu_length = 0;
                lr = 0;
            }
        }
        if(SumPackNumber!=0)
        {
            if(ucReTry<(WaitRertyTims))
            {
                TP_START(TimeOver);
                ucReTry++;
            }
                else
            {

                QMessageBox::information(this,QString::fromLocal8Bit("提醒"),QString::fromLocal8Bit("指令未得到响应！ "));
                NOACK=true;
                TP_CLOSE();
                ble_transfer_init();
                SumPackNumber=0;
                Sendlenth=0;
                lr = 0;
            }
        }
    }
}


