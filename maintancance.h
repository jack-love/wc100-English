#ifndef MAINTANCANCE_H
#define MAINTANCANCE_H

#include <QTabWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QDebug>

#define  R_VERSION   0xa1
#define  R_SELFEX      0xa2
#define  R_OFW          0xb1
#define R_ETW            0xb2
#define R_SETUP        0xb4
#define R_TEST           0xb3
#define R_ERR_1        0xdc
#define R_ERR_2        0xde
#define R_RESET        0xb6

namespace Ui {
class Maintancance;
}

enum WORK_STATE{
            GETVERSION = 0, //Get a version
            SELFEX   = 1, //Self-examination
            ETW  = 2, //Out of the warehouse
            OFW = 3, //Enter the warehouse
            SETUP = 4,//setup
            TEST = 5,//test
            STOP = 6,//stop
            RDATAACK=7,
            RESET=8,
};

class Maintancance : public QTabWidget
{
    Q_OBJECT

public:
    explicit Maintancance(QWidget *parent = 0);
    ~Maintancance();

private:
    Ui::Maintancance *ui;
    QSerialPort *serialPort;
    QTimer *timer;
    QByteArray byteArray;
    WORK_STATE  state;
  void  ProtocolResolution(unsigned int *cmd,unsigned int length);
signals:
     void SendHomeSignal();
private slots:
     void on_btn_Back_clicked();
     void on_clearReceive_clicked();
     void openTttyClicked();
     void closeTttyClicked();
     void sendDataClicked();


     void slotReadData();
     QString ByteArrayToHexStr(QByteArray data);
     QByteArray QString2Hex(QString str);
     QString ByteArrayToHexString(QByteArray data);
     char ConvertHexChar(char ch);
     void StringToHex(QString str, QByteArray & senddata);



};

#endif // MAINTANCANCE_H
