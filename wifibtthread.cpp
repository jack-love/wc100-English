#include "wifibtthread.h"
#include<QDebug>
#include<QFile>

WifiBtThread::WifiBtThread(QObject *parent):QThread(parent){
}


void WifiBtThread::run(){

       stopped=false;

       while (!stopped){
            msleep(6000*2);
            getWpa_status();
            getSignal_strength();
       }

quit();
}


void WifiBtThread::stop(){
   stopped = true;
}


void WifiBtThread::msleep(long s){
    QThread::msleep(s);
}


bool WifiBtThread::getWpa_status(){
        system("wpa_cli -iwlan0 status |grep  \"wpa_state\" > //opt/wifi/wpa_state" );
        usleep(500);
        system("sync");

        QString fileName ="//opt/wifi/wpa_state";
        QFile  file(fileName);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"open wifi_list file error !";
            emit wifiState("ERROR");
            return false;
        }

        QTextStream in(&file);
        QString line = in.readLine();

        if(line.isNull()) {
                printf("[getWpa_status]------>  Connect  ERROR  \n");
               App::wifi_connect=false;
               emit wifiState("ERROR");
               return false;
        }

         while(!line.isNull()){
                   if(0 ==QString::compare("wpa_state=COMPLETED",line)) {
                      printf("[getWpa_status]------>  Connect COMPLETED   \n");
                       App::wifi_connect=true;
                       emit wifiState("COMPLETED");
                       return true;
                   }else if(0==QString::compare("wpa_state=SCANNING",line)){
                       printf("[getWpa_status]------> Connect SCANNING   \n");
                        App::wifi_connect=false;
                        emit wifiState("SCANNING");
                        return true;
                   }else{
                        printf("[getWpa_status]------>  Connect  BREAK \n");
                       App::wifi_connect=false;
                       emit wifiState("BREAK");
                       return false;
                    }
                  line=in.readLine();
            }

         return false;
}


bool  WifiBtThread::getSignal_strength()
{
    system("wpa_cli scan_results |grep \".\" |awk {'print $3'}  > //opt/wifi/wpa_signalStrength" );

    usleep(500);
    system("sync");

        QString fileName ="//opt/wifi/wpa_signalStrength";
        QFile  file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"open /opt/wifi/wpa_signalStrength file error !";
            return false;
        }

        QTextStream in(&file);
        QString line = in.readLine();

        while(!line.isNull()){
            emit SignalStrength(line);
            break;
            line=in.readLine();
      }
        return true;
}














