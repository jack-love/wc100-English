#include "maintancance.h"
#include "ui_maintancance.h"



Maintancance::Maintancance(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Maintancance)
{
    ui->setupUi(this);
      serialPort = new QSerialPort(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。

     connect(serialPort,SIGNAL(readyRead()),this,SLOT(slotReadData()));
     connect(ui->openTtty, SIGNAL(clicked()), this, SLOT(openTttyClicked()));
     connect(ui->closeTtty, SIGNAL(clicked()), this, SLOT(closeTttyClicked()));
    connect(ui->sendData,SIGNAL(clicked()),this,  SLOT(sendDataClicked()));
     ui->openTtty->setEnabled(true);
     ui->closeTtty->setEnabled(false);

     ui->sendData->setEnabled(false);
     ui->functionSelection->setEnabled(false);
     ui->clearReceive->setEnabled(false);
}

Maintancance::~Maintancance()
{
    delete ui;
}

void Maintancance::on_btn_Back_clicked()
{
    emit SendHomeSignal();
}

void Maintancance::on_clearReceive_clicked()
{
 ui->dataShow->clear();
}


void Maintancance::openTttyClicked()
{

    serialPort->setPortName("/dev/ttymxc3");

    serialPort->open(QIODevice::ReadWrite);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    ui->openTtty->setEnabled(false);
    ui->closeTtty->setEnabled(true);

    ui->sendData->setEnabled(true);
    ui->functionSelection->setEnabled(true);

    ui->clearReceive->setEnabled(true);
}
void Maintancance::closeTttyClicked()
{
    if(serialPort->isOpen())
        {
            serialPort->close();
            ui->openTtty->setEnabled(true);
            ui->closeTtty->setEnabled(false);
            ui->sendData->setEnabled(false);
            ui->functionSelection->setEditable(false);
                ui->clearReceive->setEnabled(false);
       }
}

void Maintancance::sendDataClicked()
{
    unsigned int i=0;
    unsigned char data[6]={0};
    //QString str = ui->textEditInfo->toPlainText();
    QByteArray senddata;
    QString str;
   state = (WORK_STATE)ui->functionSelection->currentIndex();
    switch (state) {
        case GETVERSION:
        //获取版本信息  0xcc 0xaa 0xa2 0x00 0xca
           data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xa1;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

        case  SELFEX:
        //自检命令 0xcc 0xaa 0xa2 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xa2;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

       case  ETW:
            //入仓命令 0xcc 0xaa 0xb2 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb2;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
           break;

        case  OFW:
            //出仓命令 0xcc 0xaa 0xb1 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb1;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            break;

        case  SETUP:
        //设置 试纸 命令  0xcc 0xaa 0xb4 0x03 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb4;
            data[3]=0x03;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            break;

        case  TEST:
        //测试 命令  0xcc 0xaa 0xb3 0x00 0xca Checksum
           data[0]=0xcc;
           data[1]=0xaa;
           data[2]=0xb3;
           data[3]=0x00;
           data[4]=0xca;
           data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

        case  STOP:
        //发送停止命令  0xcc 0xaa 0xbf 0x00 0xca Checksum
           data[0]=0xcc;
           data[1]=0xaa;
           data[2]=0xbf;
           data[3]=0x00;
           data[4]=0xca;
           data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

      case RDATAACK:
        //接收数据 Ack 0xcc 0xdd 0x03 0x01 0xcb Checksum
            data[0]=0xcc;
            data[1]=0xdd;
            data[2]=0x03;
            data[3]=0x01;
            data[4]=0xcb;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

        case RESET:
           //发送复位  0xcc 0xdd 0x03 0x01 0xcb Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb6;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

    default:
        break;
    }

    for(i=0;i<6;i++) {
    if(data[i]<16)
            str+='   '+'0'+QString::number(data[i], 16).toUpper();
     else
            str+='   '+QString::number(data[i], 16).toUpper();
    }

    qDebug() << "on_openButton_clicked open"<< str ;


    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serialPort->write(senddata);//发送到串口

}

char ConvertHexChar(char ch)
{
if((ch >= '0') && (ch <= '9'))
return ch-0x30;
else if((ch >= 'A') && (ch <= 'F'))
return ch-'A'+10;
else if((ch >= 'a') && (ch <= 'f'))
return ch-'a'+10;
else return (-1);
}

QByteArray Maintancance::QString2Hex(QString str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
           hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
         i++;
        if(i >= len)
        break;
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if((hexdata == 16) || (lowhexdata == 16))
        break;
        else
            hexdata = hexdata*16+lowhexdata;
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
    }
    senddata.resize(hexdatalen);

                return senddata;

}

QString Maintancance::ByteArrayToHexString(QByteArray data){
    QString ret(data.toHex().toUpper());
    int len = ret.length()/2;
   // qDebug()<<len;
    for(int i=1;i<len;i++)
    {
      //  qDebug()<<"ddd" <<i;
        ret.insert(2*i+i-1," ");
    }

    return ret;
}

QString Maintancance::ByteArrayToHexStr(QByteArray data)//字节转十六进制
{
    QString temp="";
    QString hex=data.toHex();
    for (int i=0;i<hex.length();i=i+2)
    {
        temp+=hex.mid(i,2)+" ";
    }
    return temp.trimmed().toUpper();
}

//jack.niu.niu
void Maintancance::slotReadData()
{
             char*  ch;
            unsigned int cont=0;

            //读取串口数据
            QByteArray readComData = serialPort->readAll();
            //QString strq=ByteArrayToHexString(readComData);

            //将读到的数据显示到数据接收区的te中
            if(readComData != NULL)
            {

                QString str=(ByteArrayToHexStr(readComData));
                cont= str.length();
                ui->dataShow->append(str);
                ui->dataShow->append("****************************");


                QByteArray ba = str.toLatin1(); // must
                ch=ba.data();

        //printf("ch:%s\n",ch);
                unsigned int valude[20]={0};
                for(int j=0;j<cont;j++)
                {
                sscanf(ch+(j*3),"%x",&valude[j]);//C7 EB CA E4 C8 EB CA FD BE DD 2C D2 D4 BB D8 B3 B5 BC FC BD E1 CA F8 0A
                }
                ProtocolResolution(valude,cont);
            }

            //清除缓冲区
            readComData.clear();
}
//回应版本信息    0xcc 0xdd 0xa1 0x01 0xca Checksum
//返回自检状态    0xcc 0xdd 0xa2 0x00 0xca Checksum
//ACK                    0xcc 0xdd 0xb1 0x00 0xca Checksum
//发送异常帧        0xcc 0xdd 0xdc 0xde 0xca Checksum
//接收数据            0xcc 0xbb 0x03 0x01  00  00  00  00  00  00  00  00  0xcb Checksum

void Maintancance:: ProtocolResolution(unsigned int *cmd,unsigned int length){ //0xcc 0xaa 0xa1 0x00 0xca Checksum
unsigned int i;
unsigned int status=0;
i=0;
//printf(" start :%x %x %x %x %x %x\n", cmd[0],   cmd[0+1],cmd[0+2],cmd[0+3],cmd[0+4], cmd[0+5]);
  printf(" start 1 :%x %x %x %x %x %x\n", cmd[i],   cmd[i+1],cmd[i+2],cmd[i+3],cmd[i+4], cmd[i+5]);

     while( i < length )
    {
         printf("1.ProtocolResolution %d\n",i);
        if( (cmd[i]==0xcc) && (cmd[i+1]==0xdd ) && (cmd[i+4]==0xca )   )
        {
                printf("2.ProtocolResolution %d\n",i);
                if( (   ((cmd[i]+ cmd[i+1]+cmd[i+2]+cmd[i+3]+cmd[i+4]) %256) ==  cmd[i+5]   ))
               {
                    status=1;
                     printf(" start 2 :%x %x %x %x %x %x\n", cmd[i],   cmd[i+1],cmd[i+2],cmd[i+3],cmd[i+4], cmd[i+5]);

                     switch ( cmd[i+2] )
                     {
                                case  R_VERSION:
                                ui->dataShow_2->setText("Get  Version  ACK OK");
                                break;

                                case R_SELFEX:
                                ui->dataShow_2->setText("Self inspection of machinery ACK ok");
                                break;

                                case R_OFW:
                                ui->dataShow_2->setText("Open the Door ACK ok");
                                break;

                                case R_ETW:
                                ui->dataShow_2->setText("Close the Door ACK ok");
                                break;

                                case R_SETUP:
                                ui->dataShow_2->setText("Mcu Setting ACK ok");
                                break;

                                case R_TEST:
                                ui->dataShow_2->setText("Test  ACK  ok");
                                break;

                                case R_RESET:
                                ui->dataShow_2->setText("Machine Reset ACK ok");
                                break;

                               case R_ERR_1:
                                if(cmd[i+3] == R_ERR_2 )
                                    ui->dataShow_2->setText("Mechanical error ACK ok");
                                break;
                     }
                    break;
                }

        }
       ++i;
     }
}


//start 2 :cc dd a1 1 ca 15 start 1 :cc dd a1 1 ca 15ProtocolResolution 0
//void Maintancance::on_sendData_clicked()
//{
//   // QString sendData = ui->textEditInfo->toPlainText();
//QString sendData =   "0xcc  0xdd  0xa1  0x01 0xca ";

// QByteArray sendData_cmd=QString2Hex(sendData);
//  serialPort->write(sendData_cmd);
//}

char Maintancance::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
//        else return (-1);
        else return ch-ch;//不在0-f范围内的会发送成0
}

void Maintancance::StringToHex(QString str, QByteArray & senddata)  //字符串转换成16进制数据0-F
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

#if 0
void Maintancance::on_sendData_clicked()
{
    unsigned int i=0;
    unsigned char data[6]={0};
    //QString str = ui->textEditInfo->toPlainText();
    QByteArray senddata;
    QString str;
   state = (WORK_STATE)ui->functionSelection->currentIndex();
    switch (state) {
        case GETVERSION:
        //获取版本信息  0xcc 0xaa 0xa2 0x00 0xca
           data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xa1;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

        case  SELFEX:
        //自检命令 0xcc 0xaa 0xa2 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xa2;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

       case  ETW:
            //入仓命令 0xcc 0xaa 0xb2 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb2;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
           break;

        case  OFW:
            //出仓命令 0xcc 0xaa 0xb1 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb1;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            break;

        case  SETUP:
        //设置 试纸 命令  0xcc 0xaa 0xb4 0x03 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb4;
            data[3]=0x03;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            break;

        case  TEST:
        //测试 命令  0xcc 0xaa 0xb3 0x00 0xca Checksum
           data[0]=0xcc;
           data[1]=0xaa;
           data[2]=0xb3;
           data[3]=0x00;
           data[4]=0xca;
           data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

        case  STOP:
        //发送停止命令  0xcc 0xaa 0xbf 0x00 0xca Checksum
           data[0]=0xcc;
           data[1]=0xaa;
           data[2]=0xbf;
           data[3]=0x00;
           data[4]=0xca;
           data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

      case RDATAACK:
        //接收数据 Ack 0xcc 0xdd 0x03 0x01 0xcb Checksum
            data[0]=0xcc;
            data[1]=0xdd;
            data[2]=0x03;
            data[3]=0x01;
            data[4]=0xcb;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

        case RESET:
           //发送复位  0xcc 0xdd 0x03 0x01 0xcb Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb6;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
        break;

    default:
        break;
    }

    for(i=0;i<6;i++) {
    if(data[i]<16)
            str+='   '+'0'+QString::number(data[i], 16).toUpper();
     else
            str+='   '+QString::number(data[i], 16).toUpper();
    }

    qDebug() << "on_openButton_clicked open"<< str ;


    StringToHex(str,senddata);//将str字符串转换为16进制的形式
    serialPort->write(senddata);//发送到串口
}

#endif


