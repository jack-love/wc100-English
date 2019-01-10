#include "systemupdate.h"
#include "ui_systemupdate.h"
#include "App.h"
#include "QDebug"
#include "messagebox.h"
#include <QSplashScreen>
#include <QPixmap>
#include <unistd.h>
#include <QMovie>
#include<QTimer>
SystemUpdate::SystemUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemUpdate) {

    ui->setupUi(this);

    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。

    network    = new Network;
    connect(network, SIGNAL(taskFinished(QString)), this, SLOT(downloadFinished(QString)));
    connect(network, SIGNAL(fileInfo(QString,QString,qint64)), this, SLOT(taskInfo(QString,QString,qint64)));
    connect(network, SIGNAL(process(QString,qint64,double,double)),
        this, SLOT(showDownloadProgress(QString,qint64,double,double)));
    connect(network,SIGNAL(downError_signal(QString)),this,SLOT(downloadErro_hand(QString)));

    up_wTimer = new QTimer(this);
    connect(up_wTimer,SIGNAL(timeout()),this,SLOT(upTimeout()));


    ui->up_progress->setMaximum(100);
    ui->up_progress->setValue(0);
    ui->version_mcu->setText((App::mcu_version));
    ui->version_system->setText((App::sys_version));
    ui->btn_stop->setEnabled(false);

}

void SystemUpdate::upTimeout()
{
       if(up_wTimer->isActive()){
           up_wTimer->stop();

           time_up--;

           if(time_up != 0){
              up_wTimer->start(1*1000);
           }else{
               Movie->stop();
               if(Movie!=NULL){
               delete Movie;
                   qDebug()<<"uptimeout delete movie";
               }
               MessageBox msg;
               msg.MessageBox_Info(tr("update success！"));
               ui->label_state->setText(tr("Success"));
               ui->label_update->clear();
           }
       }
}

void SystemUpdate::setTestTime(unsigned int s,bool status)
{
    if(status){
        time_up = s;
        up_wTimer->start(1*1000);
    }
    else{
           up_wTimer->stop();
           time_up=0;
           Movie->stop();
           if(Movie!=NULL){
            delete Movie;
           }
    }
}


SystemUpdate::~SystemUpdate(){
    delete ui;
    delete network;
    delete up_wTimer;
}

void SystemUpdate::on_btn_back_clicked(){
    emit SendHomeSignal();
}

void SystemUpdate::on_btn_start_clicked(){
    if(App::wifi_connect){
     ui->label_status->setText(tr("loading...."));
     ui->up_progress->setValue(0);
     ui->btn_start->setEnabled(false);
      ui->btn_stop->setEnabled(true);
     network->getFileInfo2("http://fjdx.sc.chinaz.com/Files/DownLoad/font3/bb2247.rar");
  }else{
        MessageBox msg;
        msg.MessageBox_Info(tr("With WIFI ON !"));
    }

}


void SystemUpdate::on_btn_stop_clicked(){
    ui->label_status->setText(tr("Stop download!"));
    ui->btn_start->setEnabled(true);
    ui->btn_stop->setEnabled(false);
    network->stopDownload();
}

//--------------------------------------------------------------------------
void SystemUpdate::showDownloadProgress(QString task, qint64 byteTotal, double percent, double speed)
{
    QString unit;

    if (speed < 1024.0) {
        unit = "B/s";
    } else if (speed < (1024 * 1024)) {
        speed /= 1024.0;
        unit = "kB/s";
    } else {
        speed /= 1024 * 1024;
        unit = "MB/s";
    }

    ui->up_progress->setValue(percent);
}
//----------------------------------------------------------------------------------
void SystemUpdate::taskInfo(QString task, QString fileName, qint64 fileSize){
       // qDebug()<<"network->startDownload"<<task;
        network->startDownload(task, downloadPath);
}
//---------------------------------------------------------------------------------
void SystemUpdate::downloadFinished(QString task){
     ui->up_progress->setValue(100);
     ui->label_status->setText(tr("download completed!"));
     on_btn_stop_clicked();
}
void SystemUpdate::downloadErro_hand(QString err)
{
    qDebug()<<"[systemup_date] download Err!"<<err;
    on_btn_stop_clicked();
}


void SystemUpdate::on_btn_upsystem_clicked()
{

    ui->label_update->setScaledContents(true);
    Movie = new QMovie(":/image/update.gif");
ui->label_update->show();
    ui->label_update->setMovie(Movie);
    Movie->start();
    setTestTime(10,true);
    ui->label_state->setText(tr("Start"));

}

void SystemUpdate::on_btn_upmcu_clicked()
{
    ui->label_update->setScaledContents(true);
    Movie = new QMovie(":/image/update.gif");

    ui->label_update->setMovie(Movie);
    Movie->start();
    setTestTime(10,true);
    ui->label_state->setText(tr("Start"));

}
