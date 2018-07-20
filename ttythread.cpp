#include "ttythread.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>



ttyThread::ttyThread(QObject *parent):QThread(parent)
{
RUN = true;
cmdReady = false;
state = GETVERSION;


printf("ttyThread()\n");
serialPort = new QSerialPort(this);
connect (serialPort,SIGNAL(readyRead()),this,SLOT(slotReadTty()));
connect(this,SIGNAL(sendcmd(unsigned char)),this,SLOT(cmdHandle(unsigned char )));

 // connect(this,SIGNAL(receiveAck(unsigned char)),this,SLOT(showTtyAck(unsigned char)));


m_pTimer = new QTimer(this);
connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));


}

ttyThread::~ttyThread()
{

}
void ttyThread::setWorkTime(unsigned int s)
{
    time_s = s;
    m_pTimer->start(1*1000);
}

void ttyThread::handleTimeout()
{

       if(m_pTimer->isActive()){
           m_pTimer->stop();
         // qDebug()<<"Enter timeout processing function\n";
           time_s--;
           emit sTime(time_s);
           if(time_s != 0)
           {
              m_pTimer->start(1*1000);
           }
       }

}

void ttyThread::setCommand(WORK_STATE status)
{
    state = status;
    cmdReady = true;
    oneStepok=0x00;
}


void ttyThread::msleep(long s){
    QThread::msleep(s);
}


void ttyThread::run()
{

                     App::mutex.lock();
                     App::test_result = false;
                    // App::test_finished=false;

                  while(1)
                 {


                                         msleep(500);

                                          if(state == ONESTEP)
                                           {

                                                    if(state_ack != GETVERSION_ACK && oneStepok == 0x00   )
                                                     {
                                                        emit  sendcmd(GETVERSION);
                                                        oneStepok=0X01;

                                                        receivingCount=0;
                                                        setWorkTime(60);
                                                        printf("--[1]-- state_val ----%d\n",state_ack);
                                                     }

//                                                   else if(state_ack != SETUP_ACK && oneStepok == 0x01  )
//                                                     {
//                                                            emit  sendcmd(SETUP);
//                                                            oneStepok=0X02;
//                                                            printf("--[2]-- state_val ----%d\n",state_ack);
//                                                    }
                                                   else  if(state_ack !=OFW_ACK && oneStepok==0x01 )//不在出仓位置时，执行下面的出仓命令
                                                    {
                                                        emit  sendcmd(OFW);
                                                        oneStepok=0x02;
                                                        printf("--[3]-- state_val ----%d\n",state_ack);
                                                    }
                                                    else if ( state_ack == OFW_ACK && oneStepok==0x02  ){//执行进仓后，发送单步命令
                                                         emit  sendcmd(ONESTEP);
                                                         printf("--[4]-- state_val ----%d\n",state_ack);
                                                    }
                                                    else if(receivingCount >12 && time_s > 20 )//接收数据
                                                    {
                                                        RUN=false;
                                                        App::test_result=true;
                                                       printf("receivingCount 12 time %d\n",time_s);
                                                    }
                                                    else if(receivingCount < 12 && time_s ==0 )
                                                   {
                                                        RUN=false;
                                                        App::test_result=false;
                                                    }


                                                //  printf("---- ONESTEP_ACK----\n");
                                            }

                                           else if(cmdReady){//这里命令只执行一次
                                                        emit sendcmd(state);
                                                        cmdReady=false;
                                                         printf("--[6]-- state_val ----%d\n",state_ack);
                                          }

                                          if(!RUN) {
                                                   printf("---- RUN END-1---\n");
                                                  break ;
                                           }


                                            switch(state_ack)
                                            {
                                                    case   RESET_ACK:
                                                    printf("---- RESET_ACK----\n");
                                                    RUN=false;
                                                    break;

                                                    case  WB_ACK:
                                                    printf("---- WB_ACK----\n");
                                                    RUN=false;
                                                    break;

                                                    case  ONESTEP_ACK:
                                                    //printf("---- ONESTEP_ACK----\n");
                                                    break;


                                                    case OFW_ACK:
                                                    printf("---- OFW_ACK----\n");
                                                    break;

                                                    case STOP_ACK:
                                                    printf("---- STOP_ACK----\n");
                                                    RUN=false;
                                                    break;

                                                   default: break;
                                          }


                                }
                        RUN=false;
                        App::test_finished=true;
                        printf("---- RUN END--2--\n");
                        App::mutex.unlock();
 }


void ttyThread::cmdHandle ( unsigned char state)
{
    printf(" cmd Handle %d \n",state);

    commandSend((WORK_STATE)state);
}

void ttyThread::ttyStop()
{
    RUN = false;
    printf(" ttyStop \n");
}


void ttyThread::ttyStart()
{
     RUN = true;
}



void ttyThread::ttyOpen()
{
     if(! serialPort->isOpen())
     {
        serialPort->setPortName("/dev/ttymxc3");
        serialPort->open(QIODevice::ReadWrite);
        serialPort->setBaudRate(QSerialPort::Baud115200);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        tty_open = true;
        printf("ttyOpen \n");
     }

}

void ttyThread::ttyClose()
{
    if(serialPort->isOpen())
    {
        serialPort->close();
        tty_open=false;
    }
}

//---------------------------------------------------------------------------

char ttyThread::ConvertHexChar(char ch)
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



QString ttyThread::ByteArrayToHexStr(QByteArray data)//字节转十六进制
{
    QString temp="";
    QString hex=data.toHex();
    for (int i=0;i<hex.length();i=i+2)
    {
        temp+=hex.mid(i,2)+" ";
    }
    return temp.trimmed().toUpper();
}



void ttyThread::StringToHex(QString str, QByteArray & senddata)  //字符串转换成16进制数据0-F
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



//---------------------------------------------------------------------------

void ttyThread::slotReadTty()
{
    char*  ch=NULL;
       unsigned char cont=0;

       //读取串口数据
       QByteArray readComData = serialPort->readAll();


       //将读到的数据显示到数据接收区的te中
       if(readComData != NULL)
       {

           QString str=(ByteArrayToHexStr(readComData));
           cont= str.length();

            emit receiveTtyData(str);

           QByteArray ba = str.toLatin1(); // must
           ch=ba.data();

            //printf("ch:%s\n",ch);
           unsigned char valude[50]={0};
           for(int j=0;j<cont;j++)
           {
              sscanf(ch+(j*3),"%x",&valude[j]);//C7 EB CA E4 C8 EB CA FD BE DD 2C D2 D4 BB D8 B3 B5 BC FC BD E1 CA F8 0A
           }
           dataResolution(valude,cont);

       }


       //清除缓冲区
       readComData.clear();
}




void ttyThread::commandSend(WORK_STATE  status)
{
    unsigned int i=0;
    unsigned char data[7]={0};
    bool cmdok=false;

    QByteArray senddata;
    QString str;


    switch (status) {
        case GETVERSION:
            //获取版本信息  0xcc 0xaa 0xa2 0x00 0xca
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xa1;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

        case  SELFEX:
            //自检命令 0xcc 0xaa 0xa2 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xa2;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

       case  ETW:
            //入仓命令 0xcc 0xaa 0xb2 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb2;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

        case  OFW:
            //出仓命令 0xcc 0xaa 0xb1 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb1;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

        case  SETUP:
            //设置 试纸 命令  0xcc 0xaa 0xb5 0x03 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb5;
            data[3]=0x03;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
               printf("---- SETUP----\n");
            break;

        case  ONESTEP:
            //单条命令  0xcc 0xaa 0xb3 0x00 0xca Checksum
           data[0]=0xcc;
           data[1]=0xaa;
           data[2]=0xb3;
           data[3]=0x00;
           data[4]=0xca;
           data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
           cmdok=true;
             break;

        case  STOP:
            //发送停止命令  0xcc 0xaa 0xbf 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xbf;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

      case RDATAACK:
            //接收数据返回 Ack 0xcc 0xdd 0x03 0x01 0xcb Checksum
            //            data[0]=0xcc;
            //            data[1]=0xdd;
            //            data[2]=0x03;
            //            data[3]=0x01;
            //            data[4]=0xcb;
            //            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;

            //data[0]=R_data[0];
            //data[1]=R_data[1];
            //data[2]=R_data[2];
            //data[3]=R_data[3];
            //data[4]=R_data[4];
            //data[5]=R_data[5];
            break;

        case RESET:
            //发送复位  0xcc 0xaa 0xa6 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb6;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

    case WB:
            //发送白平衡  0xcc 0xaa 0xb8 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb8;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

    default:
             break;
    }

        if(cmdok) {

                    for(i=0;i<6;i++) {
                    if(data[i]<16)
                    str+='   '+'0'+QString::number(data[i], 16).toUpper();
                    else
                    str+='   '+QString::number(data[i], 16).toUpper();
                    }


                    StringToHex(str,senddata);//将str字符串转换为16进制的形式
                    serialPort->write(senddata);//发送到串口
printf("send cmd \n");
                    QString ttyname= serialPort->portName();

                    cmdok=false;
              }

}

void ttyThread:: dataResolution(unsigned char *cmd,unsigned int length){ //0xcc 0xaa 0xa1 0x00 0xca Checksum
unsigned int i=0;
unsigned int status=0;
unsigned char R_data[6]={0};

unsigned int R_DATA=0;
unsigned int G_DATA=0;
unsigned int B_DATA=0;
unsigned int W_DATA=0;

QByteArray senddata;
QString str;

//printf(" main :%x %x %x %x %x %x\n", cmd[0],   cmd[0+1],cmd[0+2],cmd[0+3],cmd[0+4], cmd[0+5]);
  //printf(" start 1 :%x %x %x %x %x %x\n", cmd[i],   cmd[i+1],cmd[i+2],cmd[i+3],cmd[i+4], cmd[i+5]);

     while( i < length )
    {

        if( (cmd[i]==0xcc) && (cmd[i+1]==0xdd ) && (cmd[i+4]==0xca )   ) //接收是命令
        {

                if( (   ((cmd[i]+ cmd[i+1]+cmd[i+2]+cmd[i+3]+cmd[i+4]) %256) ==  cmd[i+5]   ))
               {
                    status=1;
                   // printf(" start 2 :%x %x %x %x %x %x\n", cmd[i],   cmd[i+1],cmd[i+2],cmd[i+3],cmd[i+4], cmd[i+5]);
                        state_ack=0;
                     switch ( cmd[i+2] )
                     {
                                case  R_VERSION:
                                printf("ACK Read version information ok!!\n");
                                emit receiveAck(R_VERSION);
                                 state_ack= GETVERSION_ACK;
                                break;

                                case R_SELFEX:
                                printf("ACK Self-test success\n");
                                emit receiveAck(R_SELFEX);
                                state_ack= SELFEX_ACK;
                                break;

                                case R_OFW:
                               printf("ACK Open the Door\n");
                                emit receiveAck(R_OFW);
                                 state_ack=OFW_ACK;
                                break;

                                case R_ETW:
                               printf("ACK Close the Door\n");
                               emit receiveAck(R_ETW);
                                   state_ack= ETW_ACK;
                                break;

                                case R_SETUP:
                                printf("ACK Setup success\n");
                                emit receiveAck(R_SETUP);
                                state_ack=SETUP_ACK;
                                break;

                                case R_ONESTEP:
                               printf("ACK One Step  success\n");
                                emit receiveAck(R_ONESTEP);
                                  state_ack=ONESTEP_ACK;
                                break;

                                case R_RESET:
                                printf("ACK Machine Reset \n");
                                emit receiveAck(R_RESET);
                                state_ack= RESET_ACK;
                                break;

                               case R_ERR_1:
                                if(cmd[i+3] == R_ERR_2 )
                                  printf("Receive Mechanical error \n");
                                emit receiveAck(R_ERR_1);
                                state_ack= ERR_ACK;
                                break;

                              case R_WhiteBalance://R_STOP
                                printf("ACK White Balance  success \n");
                                emit receiveAck(R_WhiteBalance);
                                  state_ack= WB_ACK;
                              break;

                             case R_STOP://R_STOP
                               printf("ACK STOP  success \n");
                               emit receiveAck(R_STOP);
                                    state_ack= STOP_ACK;
                             break;

                     }
                    break;
                }

        }
        else    if( (cmd[i]==0xcc) && (cmd[i+1]==0xbb ) &&(cmd[i+12]==0xca )  ) //接收时数据
        {
            if( (   ((cmd[i]+ cmd[i+1]+cmd[i+2]+cmd[i+3]+cmd[i+4]+cmd[i+5]+ cmd[i+6] +cmd[i+7] +cmd[i+8]+cmd[i+9]+cmd[i+10] +cmd[i+11]+cmd[i+12] ) %256) ==  cmd[i+13]   ))
           {


                printf("[%x] [%x]      W: %x%x   R :%x%x   G:%x%x    B:%x%x \n", cmd[i+2],cmd[i+3],cmd[i+4],cmd[i+5], cmd[i+6] ,cmd[i+7] ,cmd[i+8],cmd[i+9],cmd[i+10] ,cmd[i+11]);

                 W_DATA = (cmd[i+4] *100)+cmd[i+5];
                 R_DATA  = (cmd[i+6] *100)+cmd[i+7];
                 G_DATA  = (cmd[i+8] *100)+cmd[i+9];
                 B_DATA  = (cmd[i+10] *100)+cmd[i+11];
                 receivingCount+=1;
//                 printf(" %x %x %x %x \n",W_DATA,R_DATA,G_DATA,B_DATA);
                 printf("W:%d  R:%d  G:%d   B:%d\n",W_DATA,R_DATA,G_DATA,B_DATA);
                 if(cmd[i+3] == 0xbb)
                   emit receiveWb(W_DATA,R_DATA,G_DATA,B_DATA);//是单独白平衡发送
               else
                   emit receiveRGB(W_DATA,R_DATA,G_DATA,B_DATA);

                R_data[0]=0xcc;
                R_data[1]=0xdd;
                R_data[2]=cmd[i+2];;
                R_data[3]=cmd[i+3];
                R_data[4]=0xca;
                R_data[5]=(R_data[0]+R_data[1]+R_data[2]+R_data[3]+R_data[4])%256;

                for(i=0;i<6;i++) {
                if(R_data[i]<16)
                        str+='   '+'0'+QString::number(R_data[i], 16).toUpper();
                 else
                        str+='   '+QString::number(R_data[i], 16).toUpper();
                }

                emit receiveAck(RD_ATAACK);


                StringToHex(str,senddata);//将str字符串转换为16进制的形式
                serialPort->write(senddata);//发送到串口

            }
        }


       ++i;
     }
}
//W:9945  R:3356  G:2933   B:3619
