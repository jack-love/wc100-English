#ifndef MAINTANCANCE_H
#define MAINTANCANCE_H

#include <QTabWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <signin.h>
#include <cac.h>
#include <ttythread.h>

extern  bool lock;

#define  R_VERSION   0xa1
#define  R_SELFEX      0xa2
#define  R_OFW          0xb1
#define R_ETW            0xb2
#define R_SETUP        0xb5
#define R_ONESTEP   0xb3
#define R_ERR_1        0xdc
#define R_ERR_2        0xde
#define R_RESET        0xb6
#define R_WhiteBalance   0xb8 //0xb8
#define  R_STOP          0xbf


enum papertype{
 R10T  =  0,
 R113  =  1,
};
namespace Ui {
class Maintancance;
}


struct resultVal {
    unsigned int calibration[8];
    unsigned int wrgb_value[4];
    unsigned int white_value[4];
};

class Maintancance : public QTabWidget
{
    Q_OBJECT

public:
        explicit Maintancance(QWidget *parent = 0);
        ~Maintancance();

        void  ProtocolResolution(unsigned char *cmd,unsigned int length);
         void uiShowRgb(unsigned int w,unsigned int r,unsigned int g,unsigned int b,unsigned int _result);
         void setPaperType(unsigned char type,unsigned char index);
        resultVal    result[13];
        unsigned int JIEGUO[14];
      Cac  cac;

private:
        Ui::Maintancance *ui;
        QSerialPort *serialPort;
        QTimer *timer;
        QByteArray byteArray;
        WORK_STATE  state;
        ttyThread  * tty_thread;
        unsigned int  receive_count=0;
        unsigned char typeSelection=0;

signals:
        void SendHomeSignal();
        void  receiveTtyData(QString str);
        void  receiveAck(unsigned char state);
        void   sTime (int s);
         void  receiveWb(unsigned int W,unsigned int R,unsigned int G,unsigned int B);
        void  receiveRGB(unsigned int W,unsigned int R,unsigned int G,unsigned int B);
private slots:
     void backHomeClicked();
     void clearReceiveClicked();
     void openTttyClicked();
     void closeTttyClicked();
     void sendDataClicked();
     void mechaniceTestClicked();
     void startDebugClicked();
     void stopDebugClicked();
     void showTtyData(QString str);
     void showTtyAck(unsigned char state);
     void sendMessage(char *message);
    void  typeSelectionClicked(int index);
    void modelSelectionClicked( int index);
    void sTimeSlot(int st);
    void whiteBalance();
    void showWb(unsigned int W,unsigned int R,unsigned int G,unsigned int B);
    void showWrgb(unsigned int W,unsigned int R,unsigned int G,unsigned int B);

};

#endif // MAINTANCANCE_H
