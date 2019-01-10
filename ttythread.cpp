#include "ttythread.h"
#include <QDebug>
#include <QFile>

#define DEBUG_TTY 1


ttyThread::ttyThread(QObject *parent):QThread(parent){

        command = GETVERSION;

        mcuUart = new QSerialPort(this);
        connect (mcuUart,SIGNAL(readyRead()),this,SLOT(slotReadTty()));
        connect(this,SIGNAL(sendcmd(unsigned char)),this,SLOT(cmdHandle(unsigned char )));
        //connect(this,SIGNAL(receiveAck(unsigned char)),this,SLOT(showTtyAck(unsigned char)));
        listUart = new QSerialPort(this);//list 系统串口
        listUartOpen();

        m_pTimer = new QTimer(this);
        connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
        m_wTimer = new QTimer(this);
        connect(m_wTimer,SIGNAL(timeout()),this,SLOT(testTimeout()));

         working_condition=UN_LOCATION;
         fist_condition=true;
}

ttyThread::~ttyThread()
{
delete m_pTimer;
delete m_wTimer;
delete mcuUart;
delete listUart;
}

void ttyThread::setinitCondition(){
 working_condition=UN_LOCATION;
}

void ttyThread::setWorkTime(unsigned int s,bool status)
{
    if(status){
    time_s = s;
    m_pTimer->start(1*1000);
    }
    else{
           emit sTime(s);
          m_pTimer->stop();
    }
}

void ttyThread::handleTimeout()
{
       if(m_pTimer->isActive()){
           m_pTimer->stop();

           time_s--;
           emit sTime(time_s);
           if(time_s != 0)
           {
              m_pTimer->start(1*1000);
           }
       }
}
//-----------------------------------------------------------------------------
void ttyThread::setTestTime(unsigned int s,bool status)
{
    if(status){
        time_m = s;
        m_wTimer->start(1*1000);
    }
    else{
           m_wTimer->stop();
           time_m=0;
           emit mTime(s);
    }
}

void ttyThread::testTimeout()
{
       if(m_wTimer->isActive()){
           m_wTimer->stop();

           time_m--;
           emit mTime(time_m);
//qDebug()<<"time_m"<<time_m;
           if(time_m != 0){
              m_wTimer->start(1*1000);
           }
       }
}


void ttyThread::setCommand(WORK_STATE cmd){
    command = cmd;
}


void ttyThread::msleep(long s){
    QThread::msleep(s);
}



void ttyThread::run() {

                 int  count=0;
                receiving_count=0;
                App::test_result = false;
                App::RUN = true;
                state_ack=NULL_ACK;
                oneTime=false;
                oneTime_stop=false;
                App::mutex.lock();


                if (0 == QString::compare("11-III",App::TestPapertype)){
                        count=(11+1);//0x0c
                }else if (0 == QString::compare("10T", App::TestPapertype) ){
                        count =(10+1);
                  }else if (0 == QString::compare("12MA", App::TestPapertype) ){
                        count =(12+1);
                 }


               while(1){
                                                            msleep(500);

                                                            if( command == GETVERSION)
                                                            {
                                                                        emit  sendcmd(GETVERSION);
                                                                #if(DEBUG_TTY)
                                                                        printf(" [tty run]--->get GETVERSION\n");
                                                                #endif
                                                                    if(!oneTime){
                                                                        setWorkTime(3,true);
                                                                        oneTime=true;
                                                                     }
                                                                     if( time_s == 0)
                                                                     {
                                                                        App::RUN=false;
                                                                        App::test_result=false;
                                                                   #if(DEBUG_TTY)
                                                                        printf(" [run]---> Get version time out \n");
                                                                    #endif
                                                                     }
                                                                     else if (state_ack ==  GETVERSION_ACK)
                                                                     {
                                                                           #if(DEBUG_TTY)
                                                                                printf("  [tty run]--->GETVERSION ACK \n");
                                                                            #endif
                                                                        setWorkTime(0,false);
                                                                        App::RUN=false;
                                                                        App::test_result=true;
                                                                        buzzer();
                                                                     }
                                                             }

                                                            else  if((command == SETUP) ) {
                                                                    emit  sendcmd(SETUP);
                                                                #if(DEBUG_TTY)
                                                                    printf(" [tty run]--->SETUP CMD\n");
                                                                #endif
                                                                    if(!oneTime){
                                                                        setWorkTime(3,true);
                                                                        oneTime=true;
                                                                     }

                                                                     if( time_s == 0) {
                                                                        App::RUN=false;
                                                                        App::test_result=false;
                                                               #if(DEBUG_TTY)
                                                                        printf(" [run]--->SETUP time out \n");
                                                                 #endif
                                                                     }

                                                                     else if (state_ack ==  SETUP_ACK){
                                                                 #if(DEBUG_TTY)
                                                                        printf(" [tty run]--->SETUP CMD ACK \n");
                                                                  #endif
                                                                        App::RUN=false;
                                                                        App::test_result=true;
                                                                        setWorkTime(0,false);
                                                                      buzzer();
                                                                        oneTime=false;
                                                                     }

                                                             }


                                                       else  if(command == ONESTEP){
                                                                 if(time_m  == BUZZER )
                                                                  {
                                                                         buzzer();
                                                                  }
                                                              else if((working_condition == UN_LOCATION) ){
                                                                         emit  sendcmd(OFW);
                                                             #if(DEBUG_TTY)
                                                                         printf("  [run]--->OFW CMD\n");
                                                             #endif

                                                                     if(!oneTime){
                                                                            setTestTime(INIT_TIME,true);
                                                                         //setWorkTime(15,true);
                                                                         oneTime=true;
                                                                         fist_condition=true;
                                                                      }

                                                                      if( time_m == 0){
                                                                         App::RUN=false;
                                                                         App::test_result=false;
                                                                        #if(DEBUG_TTY)
                                                                        printf("[run]--->OFW time out \n");
                                                                        #endif
                                                                      }

                                                                      else if (state_ack ==  OFW_ACK){
                                                                         working_condition = OFW_LOCATION;
                                                                         oneTime=false;
                                                             #if(DEBUG_TTY)
                                                                         printf("[run]--->OFW CMD ACK \n");
                                                            #endif
                                                                         //setWorkTime(0,false);
                                                                       //  setTestTime(60,true);
                                                                      }
                                                              }

                                                             else  if((working_condition == OFW_LOCATION) ){

                                                                         if(!oneTime){
                                                                                 if(!fist_condition){
                                                                                    setTestTime(LOOP_TIME ,true);
                                                                                    buzzer();
                                                                                 }
                                                                                fist_condition=false;
                                                                                oneTime=true;
                                                                          }


                                                                       else  if( time_m == TESTSTART  )
                                                                         {
                                                                              #if(DEBUG_TTY)
                                                                                              printf(" [run]---> ONESTEP CMD\n");
                                                                                 #endif
                                                                              emit  sendcmd(ONESTEP);
                                                                         }

                                                                     else  if( time_m == 0) {
                                                                         App::RUN=false;
                                                                         App::test_result=false;
                                                                         printf("[run]--->ONESTEP time out \n");
                                                                      }

                                                                      else if (state_ack ==  ONESTEP_ACK) {
                                                                         working_condition = ETW_LOCATION;
                                                                         oneTime=false;
                                                                         printf("[run]--->ONESTEP CMD ACK \n");


                                                                      }
                                                              }

                                                           else  if((working_condition == ETW_LOCATION) ){

                                                                     if( (time_m == 0)){
                                                                       printf("[run]---> receiving error time out  .count[%d] \n",receiving_count);
                                                                       App::RUN=false;
                                                                       App::test_result=false;
                                                                       working_condition=OFW_LOCATION;
                                                                       setTestTime(0,false);
                                                                    }

                                                                     else if( (receiving_count > count )  ) {
                                                                         App::RUN=false;
                                                                         App::test_result=true;
                                                                         printf("[run]--->receiving ok . count[%d], time[%d]. \n",receiving_count,time_s);
                                                                         working_condition=OFW_LOCATION;
                                                                        setTestTime(0,false);
                                                                      }
                                                       }
                                                }

                                                  else  if(command == STOPR) {
                                                          emit  sendcmd(STOPR);
                                                      #if(DEBUG_TTY)
                                                          printf(" [run]--->STOPR CMD\n");
                                                      #endif
                                                          if(!oneTime_stop){
                                                              working_condition = UN_LOCATION;
                                                              setWorkTime(5,true);
                                                              setTestTime(0,false);
                                                              oneTime_stop=true;
                                                               printf(" [run]--->STOPR CMD1\n");
                                                           }

                                                           if( time_s == 0)
                                                           {
                                                              App::RUN=false;
                                                              App::test_result=false;
                                                                setWorkTime(0,false);
                                                     #if(DEBUG_TTY)
                                                              printf(" [run]--->STOPR time out \n");
                                                       #endif
                                                           }
                                                           else if (state_ack ==  STOP_ACK)
                                                           {
                                                       #if(DEBUG_TTY)
                                                              printf(" [run]--->STOPR CMD ACK \n");
                                                        #endif
                                                              App::RUN=false;
                                                              App::test_result=true;
                                                              setWorkTime(0,false);
                                                             // emit  sendcmd(ETW);
                                                           }
                                                      }

                                                            else  if(command == RESET) {
                                                                #if(DEBUG_TTY)
                                                                    printf(" [run]--->RESET CMD\n");
                                                                #endif
                                                                    if(!oneTime){
                                                                        emit  sendcmd(RESET);
                                                                        setWorkTime(30,true);
                                                                        oneTime=true;
                                                                         working_condition = UN_LOCATION;
                                                                     }

                                                                     if( time_s == 0)
                                                                     {
                                                                        App::RUN=false;
                                                                        App::test_result=false;
                                                                          setWorkTime(0,false);
                                                               #if(DEBUG_TTY)
                                                                        printf(" [run]--->RESET time out \n");
                                                                 #endif
                                                                     }
                                                                     else if (state_ack ==  RESET_ACK)
                                                                     {
                                                                 #if(DEBUG_TTY)
                                                                        printf(" [run]--->RESET CMD ACK \n");
                                                                  #endif
                                                                        App::RUN=false;
                                                                        App::test_result=true;
                                                                        setWorkTime(0,false);
                                                                        buzzer();
                                                                     }
                                                                }

                                                            else  if(command == POWEROFF) {
                                                                #if(DEBUG_TTY)
                                                                    printf(" [run]--->POWEROFF CMD\n");
                                                                #endif
                                                                    if(!oneTime){
                                                                        emit  sendcmd(POWEROFF);
                                                                        setWorkTime(10,true);
                                                                        oneTime=true;
                                                                        working_condition = UN_LOCATION;
                                                                     }

                                                                     if( time_s == 0)
                                                                     {
                                                                        App::RUN=false;
                                                                        App::test_result=false;
                                                                          setWorkTime(0,false);
                                                               #if(DEBUG_TTY)
                                                                        printf(" [run]--->POWEROFF time out \n");
                                                                 #endif
                                                                     }
                                                                     else if (state_ack ==  POWEROF_ACK)
                                                                     {
                                                                 #if(DEBUG_TTY)
                                                                        printf(" [run]--->POWEROF_ACK CMD ACK \n");
                                                                  #endif
                                                                        App::RUN=false;
                                                                        App::test_result=true;
                                                                        setWorkTime(0,false);
                                                                     }
                                                                }


                                                              if(!App::RUN) {
                                                                  #if(DEBUG_TTY)
                                                                   printf("[tty run]--->RUN END\n");
                                                                    #endif
                                                                  break ;
                                                               }

                                }

                App::mutex.unlock();
                App::RUN=false;
                App::test_finished=true;

 }


void ttyThread::cmdHandle ( unsigned char state){
    commandSend((WORK_STATE)state);
}




void ttyThread::mcuUartOpen()
{
     if(! mcuUart->isOpen())
     {
    // qDebug()<<"mcuUartOpen----->";
        mcuUart->setPortName("/dev/ttymxc3");
        mcuUart->open(QIODevice::ReadWrite);
        mcuUart->setBaudRate(QSerialPort::Baud115200);
        mcuUart->setDataBits(QSerialPort::Data8);
        mcuUart->setParity(QSerialPort::NoParity);
        mcuUart->setStopBits(QSerialPort::OneStop);
        mcuUart->setFlowControl(QSerialPort::NoFlowControl);
     }
}
void ttyThread::listUartOpen()
{
    if(! listUart->isOpen())
    {
       listUart->setPortName("/dev/ttymxc4");
       listUart->open(QIODevice::ReadWrite);
       listUart->setBaudRate(QSerialPort::Baud9600);
       listUart->setDataBits(QSerialPort::Data8);
       listUart->setParity(QSerialPort::NoParity);
       listUart->setStopBits(QSerialPort::OneStop);
       listUart->setFlowControl(QSerialPort::NoFlowControl);

    }
}

void ttyThread::listUartClose()
{
    if(listUart->isOpen())
    {
        listUart->close();
    }
}


void ttyThread::mcuUartClose()
{
    if(mcuUart->isOpen())
    { //qDebug()<<"[mcuUartClose]------->bug";
        mcuUart->close();
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
       QByteArray readComData = mcuUart->readAll();


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

            if (0 == QString::compare("11-III",App::TestPapertype)){
                data[3]=0x03;
           }else   if (0 == QString::compare("10T",   App::TestPapertype)){
                data[3]=0x01;
            }else if (0 == QString::compare("12MA", App::TestPapertype) ){
                data[3]=0x02;
            }

            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
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

        case  STOPR:
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
//cc dd b6 ca 29
        case RESET:
            //发送复位  0xcc 0xaa 0xb6 0x00 0xca Checksum
            data[0]=0xcc;
            data[1]=0xaa;
            data[2]=0xb6;
            data[3]=0x00;
            data[4]=0xca;
            data[5]=(data[0]+data[1]+data[2]+data[3]+data[4])%256;
            cmdok=true;
            break;

    case POWEROFF:
        //发送关机命令
        data[0]=0xcc;
        data[1]=0xaa;
        data[2]=0xb7;
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


            default: break;
    }

        if(cmdok) {

                    for(i=0;i<6;i++) {
                        if(data[i]<16)
                        str+='   '+'0'+QString::number(data[i], 16).toUpper();
                        else
                        str+='   '+QString::number(data[i], 16).toUpper();
                    }


                    StringToHex(str,senddata);//将str字符串转换为16进制的形式
                    mcuUart->write(senddata);//发送到串口
                 //   qDebug()<< "send cmd "<<str;


                    cmdok=false;
              }

}

void ttyThread::listWrite(QByteArray cstr){
    listUart->write(cstr);
}

void ttyThread:: dataResolution(unsigned char *cmd,unsigned int length){ //0xcc 0xaa 0xa1 0x00 0xca Checksum
unsigned int i=0;
//unsigned int status=0;
unsigned char R_data[6]={0};

//unsigned int R_DATA=0;
//unsigned int G_DATA=0;
//unsigned int B_DATA=0;
//unsigned int W_DATA=0;

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
                  //  status=1;
                   // printf(" start 2 :%x %x %x %x %x %x\n", cmd[i],   cmd[i+1],cmd[i+2],cmd[i+3],cmd[i+4], cmd[i+5]);
                        state_ack=0;
                     switch ( cmd[i+2] )
                     {
                                case  R_VERSION:
                              //  printf("ACK Read version information ok!!\n");
                                emit receiveAck(R_VERSION);
                                 state_ack= GETVERSION_ACK;
                                break;

                                case R_SELFEX:
                               // printf("ACK Self-test success\n");
                                emit receiveAck(R_SELFEX);
                                state_ack= SELFEX_ACK;
                                break;

                                case R_OFW:
                               //printf("ACK Open the Door\n");
                                emit receiveAck(R_OFW);
                                 state_ack=OFW_ACK;
                                break;

                                case R_ETW:
                               //printf("ACK Close the Door\n");
                               emit receiveAck(R_ETW);
                                   state_ack= ETW_ACK;
                                break;

                                case R_SETUP:
                               // printf("ACK Setup success\n");
                                emit receiveAck(R_SETUP);
                                state_ack=SETUP_ACK;
                                break;

                                case R_ONESTEP:
                              // printf("ACK One Step  success\n");
                                emit receiveAck(R_ONESTEP);
                                  state_ack=ONESTEP_ACK;
                                if(cmd[i+3]==0x01)
                                {
                                  //  commandSend(ONESTEP);
                                    qDebug()<<"[send again ONESTEUP...]";
                                   //  emit  sendcmd(ONESTEP);
                                }
                                break;

                                case R_RESET:
                                printf("ACK Machine Reset \n");
                                emit receiveAck(R_RESET);
                                state_ack= RESET_ACK;
                                break;

                               case R_ERR_1:
                                if(cmd[i+3] == R_ERR_2 )
                                //  printf("Receive Mechanical error \n");
                                emit receiveAck(R_ERR_1);
                                state_ack= ERR_ACK;
                                break;

                              case R_WhiteBalance:
                                //printf("ACK White Balance  success \n");
                                emit receiveAck(R_WhiteBalance);
                                  state_ack= WB_ACK;
                              break;

                             case R_STOP://R_STOP
                               //printf("ACK STOP  success \n");
                               emit receiveAck(R_STOP);
                                    state_ack= STOP_ACK;
                             break;

                            case R_POWROFF:
                                     emit receiveAck(R_POWROFF);
                            break;

                         default:break;

                     }
                    break;
                }

        }
        else    if( (cmd[i]==0xcc) && (cmd[i+1]==0xbb ) &&(cmd[i+12]==0xca )  ) //接收时数据
        {
            if( (   ((cmd[i]+ cmd[i+1]+cmd[i+2]+cmd[i+3]+cmd[i+4]+cmd[i+5]+ cmd[i+6] +cmd[i+7] +cmd[i+8]+cmd[i+9]+cmd[i+10] +cmd[i+11]+cmd[i+12] ) %256) ==  cmd[i+13]   ))
           {


               // printf("[%x] [%x]      W: %x%x   R :%x%x   G:%x%x    B:%x%x \n", cmd[i+2],cmd[i+3],cmd[i+4],cmd[i+5], cmd[i+6] ,cmd[i+7] ,cmd[i+8],cmd[i+9],cmd[i+10] ,cmd[i+11]);

                  wrgb_data. W = (cmd[i+4] *100)+cmd[i+5];
                  wrgb_data. R  = (cmd[i+6] *100)+cmd[i+7];
                  wrgb_data. G  = (cmd[i+8] *100)+cmd[i+9];
                  wrgb_data. B  = (cmd[i+10] *100)+cmd[i+11];
                 receiving_count++;

                 printf("[receive data---->] Count:%d  W:%d  R:%d  G:%d   B:%d\n",cmd[i+3],wrgb_data.W,wrgb_data.R,wrgb_data.G,wrgb_data.B);
                 if(cmd[i+3] == 0xbb)
                   emit receiveWb(wrgb_data);//是单独白平衡发送
               else
                   emit receiveRGB(wrgb_data,cmd[i+3]);

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

                StringToHex(str,senddata);//将str字符串转换为16进制的形式
                mcuUart->write(senddata);//发送到串口
            }
        }


       ++i;
     }
}

void ttyThread::buzzer(){
   system("echo 100  > /sys/class/leds/beeper-pwm/brightness");
   msleep(100*4);//2000
   system("echo 0 > /sys/class/leds/beeper-pwm/brightness");
}
