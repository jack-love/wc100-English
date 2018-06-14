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
     connect(ui->openTtty, SIGNAL(clicked()), this, SLOT(openTttyClicked()));
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

}
void Maintancance::sendDataClicked()
{


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

void Maintancance::slotReadData()
{
     char*  ch;


    //读取串口数据
        QByteArray readComData = serialPort->readAll();
//QString strq=ByteArrayToHexString(readComData);
//qDebug()<<"ddd" <<strq;
        //将读到的数据显示到数据接收区的te中
        if(readComData != NULL)
        {

            QString str=(ByteArrayToHexStr(readComData));

               ui->dataShow->append(str);
  ui->dataShow->append("****************************");
//#if 1

               QByteArray ba = str.toLatin1(); // must
               ch=ba.data();

           //   for(int i=0;i<24;i++){
           //       qDebug() <<"SSS" << ch[i];
            //  }
unsigned int valude[24];
for(int j=0;j<24;j++)
{
 sscanf(ch+(j*3),"%x",&valude[j]);//C7 EB CA E4 C8 EB CA FD BE DD 2C D2 D4 BB D8 B3 B5 BC FC BD E1 CA F8 0A
}                                                       //C7 EB CA E4 C8 EB CA FD BE DD 2C D2 D4 BB D8 B3 B5 BC FC BD E1 CA F8 A
for(int k=0;k<24;k++)
    printf("%X ", valude[k]);

printf("\n");
     //           int nValude,val2 = 0;
      //          sscanf(ch, "%x", &nValude);
       //         printf("%x\r\n", nValude);
      //          sscanf(ch+3, "%x", &val2);
      //          printf("%x\r\n", val2);
unsigned int temp=0xc8;
unsigned int tempa=0xf8;
if((valude[4]==temp)&&(tempa==valude[22]))
qDebug() << "0xc8 ok";


        }
#if 0
QString qs = "123";
int d = qs.toInt();
printf("%d ",d);

QString  str="123";
char*  ch;
QByteArray ba = str.toLatin1(); // must
ch=ba.data();

qDebug() << "DDDDD"<<ch;
#endif

        //清除缓冲区
        readComData.clear();
}
