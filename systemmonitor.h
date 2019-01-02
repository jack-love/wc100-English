#ifndef SYSTEMMONITOR_H
#define SYSTEMMONITOR_H

#include <QObject>
#include <QThread>
#include<stdio.h>
//----------------------------------------------------------------

#define DEVICE         "/dev/i2c-4"
#define RT9428_ADDR     0x6c

#define SLEEP (0x01<<7)
#define SCEN  (0x01<<6)
#define ALERT (0x01<<5)

#define SL (0x01<<4)
#define SC (0x01<<5)




//----------------------------------------------------------------

class systemMonitor : public QThread
{
    Q_OBJECT
public:
    explicit systemMonitor(QObject *parent = 0);
    void msleep(long s);
    int rt9428_write(int fd, char *tbuf, int len);
    int rt9428_read(int fd,  char *reg,  char *rbuf, int len);
    bool  rt9428_open();
    void  rt9428_Getsoc();
    void rt9428_GetChargstate();
    bool rt9428_QuickSensing();
    bool rt9428_Config();
    QString shellProcess(QString cmd);

signals:
    void soc_Signal(char si);
    void charg_Signal(bool state);
public slots:

protected:
    void run();
};

#endif // SYSTEMMONITOR_H
