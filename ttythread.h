#ifndef TTYTHREAD_H
#define TTYTHREAD_H

#include <QThread>
#include <iostream>
#include <QMultiMap>
#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include<QTimer>
#include <App.h>
#define  R_VERSION   0xa1
#define  R_SELFEX      0xa2
#define  R_OFW          0xb1
#define  R_ETW            0xb2
#define  R_SETUP        0xb5
#define  R_ONESTEP   0xb3
#define  R_ERR_1        0xdc
#define  R_ERR_2        0xde
#define  R_RESET        0xb6
#define  R_WhiteBalance 0xb8
#define  R_STOP          0xbf
#define RD_ATAACK     0xbb
#define R_POWROFF   0xb9

#define  INIT_TIME    63
#define BUZZER         60
#define TESTSTART       38
enum WORK_STATE{
            GETVERSION = 0, //Get a version
            SELFEX   = 1, //Self-examination
            ETW  = 2, //Out of the warehouse
            OFW = 3, //Enter the warehouse
            SETUP = 4,//setup
            ONESTEP = 5,//test
            STOPR = 6,//stop
            RDATAACK=7,
            RESET=8,
            WB=9,//R_WhiteBalance
           POWEROFF=10,
};
enum err_State{
VERSION_ERR=0x01,
SETUP_ERR=0X02,
RESET_ERR=0X04,
};

enum ACK_STATE{
            GETVERSION_ACK = 0, //Get a version
            SELFEX_ACK   = 1, //Self-examination
            ETW_ACK  = 2, //Out of the warehouse
            OFW_ACK = 3, //Enter the warehouse
            SETUP_ACK = 4,//setup
            ONESTEP_ACK = 5,//test
            STOP_ACK = 6,//stop
            RDATA_ACK=7,
            RESET_ACK=8,
            WB_ACK=9,//R_WhiteBalance
            ERR_ACK=10,
            REC_CONT=11,
            NULL_ACK=12,
            POWEROF_ACK=13,
};

enum current_Location{
        UN_LOCATION=0X00,
        OFW_LOCATION=0X01,
        ETW_LOCATION=0X02,
};


struct resultVal{
    unsigned int calibration[8];                        //input
    unsigned int wrgb_value[4];                         //output
    unsigned int white_value[4];
    unsigned int mode;  //1 = new unit   2 = old unit   //input
    unsigned int paper_model;                           //input
    unsigned int block_num;                             //input
    unsigned int position;                              //output
    unsigned int wrgb_result_value;                     //output
    char unit[10];//- +- 1+ 2+ 3+ ...                   //output
    char name[6];                                       //input
    char item_value[9][10];                             //output
    char flag;
};
struct WRGB_DAT{
    unsigned int W;
    unsigned int R;
    unsigned int G;
    unsigned int B;
};


class ttyThread : public QThread
{
    Q_OBJECT

public:
    explicit ttyThread(QObject *parent = 0);   //explicit声明后只允许显式调用
    ~ttyThread();      //程序结束时都会隐式调用析构函数
    void buzzer();
    void   listWrite(QByteArray cstr );
    void  dataResolution(unsigned char *cmd,unsigned int length);
    void  mcuUartOpen();
    void   listUartOpen();
    void  mcuUartClose();
    void  listUartClose();
    void  commandSend(WORK_STATE  status);
    void setCommand(WORK_STATE  cmd);
    void setWorkTime(unsigned int s,bool status);
    void setTestTime(unsigned int s,bool status);
    QString ByteArrayToHexStr(QByteArray data);
    char ConvertHexChar(char ch);
    void StringToHex(QString str, QByteArray & senddata);
    void msleep(long s);
    WRGB_DAT wrgb_data;

protected:
    void run();

private:
        volatile unsigned char * tty_data=NULL;
        volatile unsigned char tty_len;
        volatile bool   oneTime;
        volatile bool   oneTime_stop;
        WORK_STATE  command;
        QSerialPort *mcuUart=NULL;
        QSerialPort *listUart=NULL;
        unsigned char  state_ack;
        unsigned char  working_condition;
        bool  fist_condition;
        unsigned char  receiving_count;
        QTimer *m_pTimer;
        QTimer  *m_wTimer;
        unsigned int time_s;
        unsigned int  time_m;

 private slots:
        void  slotReadTty();
        void  cmdHandle (unsigned char command);
        void handleTimeout();
        void testTimeout();

signals:
         void  receiveTtyData(QString str);
         void  receiveAck(unsigned char command);
         void  sendcmd(unsigned char command);
         void  sTime (int s);
         void  mTime(int s);
         void  receiveWb(WRGB_DAT wrgb);
         void  receiveRGB(WRGB_DAT wrgb,unsigned int count);
};


#endif // TTYTHREAD_H
