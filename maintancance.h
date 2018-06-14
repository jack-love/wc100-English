#ifndef MAINTANCANCE_H
#define MAINTANCANCE_H

#include <QTabWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QDebug>



namespace Ui {
class Maintancance;
}

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

signals:
     void SendHomeSignal();
private slots:
     void on_btn_Back_clicked();
     void on_clearReceive_clicked();
     void openTttyClicked();
     void sendDataClicked();

   //  void slotSendData();
     void slotReadData();
     QString ByteArrayToHexStr(QByteArray data);
     QByteArray QString2Hex(QString str);
     QString ByteArrayToHexString(QByteArray data);

};

#endif // MAINTANCANCE_H
