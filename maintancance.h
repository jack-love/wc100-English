#ifndef MAINTANCANCE_H
#define MAINTANCANCE_H

#include <QTabWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <signin.h>

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
#define R_WhiteBalance   0xb7 //0xb8
#define  R_STOP          0xbf

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

private:
        Ui::Maintancance *ui;
        QSerialPort *serialPort;
        QTimer *timer;
        QByteArray byteArray;
        WORK_STATE  state;
        ttyThread  * tty_thread;

signals:
        void SendHomeSignal();
        void  receiveTtyData(QString str);
        void  receiveAck(unsigned char state);

private slots:
     void backHomeClicked();
     void clearReceiveClicked();
     void openTttyClicked();
     void closeTttyClicked();
     void sendDataClicked();
    void mechaniceTestClicked();
     void showTtyData(QString str);
     void showTtyAck(unsigned char state);
     void sendMessage(char *message);

};

#endif // MAINTANCANCE_H
