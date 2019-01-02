#ifndef WIFIBTTHREAD_H
#define WIFIBTTHREAD_H

#include <QObject>
#include <QThread>
#include "App.h"
class WifiBtThread : public  QThread
{
    Q_OBJECT
public:
    explicit WifiBtThread(QObject *parent = 0);
     void stop();
     void msleep(long s);
     bool  getWpa_status();
     bool  getSignal_strength();
signals:
    void SignalStrength(QString signal);
    void wifiState(QString state);

public slots:

protected:
    void run();

private:
   volatile bool stopped;
};

#endif // WIFITHREAD_H
