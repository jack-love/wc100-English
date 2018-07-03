#ifndef TTYTHREAD_H
#define TTYTHREAD_H

#include <QThread>
#include <iostream>
#include <QMultiMap>
#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

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

enum WORK_STATE{
            GETVERSION = 0, //Get a version
            SELFEX   = 1, //Self-examination
            ETW  = 2, //Out of the warehouse
            OFW = 3, //Enter the warehouse
            SETUP = 4,//setup
            ONESTEP = 5,//test
            STOP = 6,//stop
            RDATAACK=7,
            RESET=8,
            WB=9,//R_WhiteBalance
};

class ttyThread : public QThread
{
    Q_OBJECT
public:
    explicit ttyThread(QObject *parent = 0);   //explicit声明后只允许显式调用
    ~ttyThread();      //程序结束时都会隐式调用析构函数


    void  dataResolution(unsigned char *cmd,unsigned int length);
    void  ttyOpen();
    void  ttyClose();
    void  commandSend(WORK_STATE  status);
    void setCommand(WORK_STATE  status);
    void  ttyStop();
    void  ttyStart();


    QString ByteArrayToHexStr(QByteArray data);
    char ConvertHexChar(char ch);
    void StringToHex(QString str, QByteArray & senddata);


protected:
    void run(); //新线程,主线程调用start()时,新线程会自动调用run()函数

private:
    volatile unsigned char * tty_data;
     volatile unsigned char tty_len;
    volatile bool   RUN;
    volatile bool   cmdReady;
    WORK_STATE  state;
    QSerialPort *serialPort;

    unsigned char state_ack;



 private slots:
    void  slotReadTty();
   void   cmdHandle (unsigned char state);
signals:
         void  receiveTtyData(QString str);
         void  receiveAck(unsigned char state);
         void  sendcmd(unsigned char state);

};


#endif // TTYTHREAD_H
