#include "upload.h"
UpLoad::UpLoad()
{

}
void UpLoad::setupAPP(BluetoothAppProtocol* app){
    this->app=app;
}
int UpLoad::fillprotobufint(uint8_t *p,uint32_t len){

    int size=0;
    while(len>0x7f){
        p[size++]=(static_cast<uint8_t>(len)&0x7f)|0x80;
        len>>=7;
    }
    p[size++]=static_cast<uint8_t>(len)&0x7f;


    return size;

}
void UpLoad::run(){
    uint8_t data[64];
    QFile file(Filename);
    if (file.open(QIODevice::ReadOnly)){
           int length=file.size();
           char magic[4];
           file.read((char *)&magic,4);
           if(magic[0]!='T' || magic[1]!='R' || magic[2]!='Z' || magic[3]!='R'){
                emit SendError(QString::fromLocal8Bit("固件选择错误，请选择正确的固件！"));
                return;
           }
           file.seek(0);

        //填充protobuf大小
        uint32_t proto_size=fillprotobufint(data,length);
        bool label=0;
        while(length){
            while(!app->statusACK || app->AckF!=NULL )msleep(20);

            app->hwp->communicationBluetooth.label[0]=label?1:0;

            lastlen=length;//记录现在传输的剩余长度
            if(length==file.size()){

                    file.read((char *)&data[proto_size],54-proto_size);

                app->FirmwareUpload1(data);
                length-=(54-proto_size);

            }else{
                if(length>63)
                file.read((char *)&data,63);
                else {
                    file.read((char *)&data,length);
                }
                app->FirmwareUpload2(data);
                length-=63;
            }

            label=!label;
            emit SendToProgressBar((file.size()-length)*100.0/file.size());
            if(length<=0){
                length=0;
                emit SendToProgresslabel(QString::fromLocal8Bit("下载完成！"));
            }
            else
                emit SendToProgresslabel(tr("%1/%2").arg(file.size()-length).arg(file.size()));
        }

    file.close();
    }else{
        emit SendError(QString::fromLocal8Bit("文件打开失败，请重新选择"));
    }
}




