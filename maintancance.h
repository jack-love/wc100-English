#ifndef MAINTANCANCE_H
#define MAINTANCANCE_H

#include <QTabWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include "signin.h"
#include "cac.h"
#include "ttythread.h"
#include "systemsetup.h"


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
#define R_POWROFF   0xb9


namespace Ui {
class Maintancance;
}




class Maintancance : public QTabWidget
{
    Q_OBJECT

public:
        explicit Maintancance(QWidget *parent = 0);
        ~Maintancance();
         void  ProtocolResolution(unsigned char *cmd,unsigned int length);

        resultVal    result[13];
        unsigned int JIEGUO[14];
        Cac  cac;
      bool  testCmd(WORK_STATE cmd);
private:
        Ui::Maintancance *ui;
        QSerialPort *serialPort;
        QTimer *timer;
        QByteArray byteArray;
        WORK_STATE  state;
        ttyThread  * tty_thread;
        SystemSetup  *systemp;
        bool  tty_open;
        MessageBox msg;

signals:
        void paperChange(int index);
        void SendHomeSignal();
        void  receiveTtyData(QString str);
        void  receiveAck(unsigned char state);
        void   sTime (int s);

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
       // void modelSelectionClicked( int index);
        void sTimeSlot(int st);
        void whiteBalance();
        void showWb(WRGB_DAT wrgb_data);
        void showWrgb(WRGB_DAT wrgb_data,unsigned int count);
        void open_door_clicked();
        void close_door_clicked();
 private:
        void openMcuUart();
};

#endif // MAINTANCANCE_H
