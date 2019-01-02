#include "systemsetup.h"
#include "ui_systemsetup.h"
#include "App.h"
#include "mainbussniessview.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QFile>
 #include <unistd.h>
#include <QProcess>
#include "messagebox.h"
#include<QTimer>

SystemSetup::SystemSetup(QWidget *parent,MainBussniessView*pMainBussniessView) :
    QTabWidget(parent),pMainView(pMainBussniessView),
    ui(new Ui::SystemSetup){

    ui->setupUi(this);
    connect(ui->edt_paperType,SIGNAL(activated(int)),this,SLOT(paperTypeSelectionClicked(int)));
    connect(pMainView, SIGNAL(system_Setup(QSqlTableModel*)), this, SLOT(systemShow(QSqlTableModel*)),Qt::AutoConnection);
    connect(pMainView, SIGNAL(system_Species(QSqlTableModel*)), this, SLOT(species(QSqlTableModel*)),Qt::AutoConnection);
    connect(pMainView, SIGNAL(system_Language(QSqlTableModel*)), this, SLOT(language(QSqlTableModel*)),Qt::AutoConnection);
    connect(pMainView, SIGNAL(system_testMode(QSqlTableModel*)), this, SLOT(testMode(QSqlTableModel*)),Qt::AutoConnection);
    connect(pMainView, SIGNAL(system_testPapertype(QSqlTableModel*)), this, SLOT(testPapertype(QSqlTableModel*)),Qt::AutoConnection);
    //connect(pMainView,SIGNAL(system_saveok(int)),this,SLOT(saveok(int)),Qt::AutoConnection);
    connect(&wb_thread, SIGNAL(SignalStrength(QString)),this,SLOT(getSignalStrength(QString)),Qt::AutoConnection);
    connect(&wb_thread, SIGNAL(wifiState(QString)),this,SLOT(getwifiState(QString)),Qt::AutoConnection);

    pMainView->getSystem_status();
    pMainView->getSystem_species();
    pMainView->getSystem_language();
    pMainView->getSystem_testMode();
    pMainView->getSystem_testPapertype();

    ui->btn_openWifi->setEnabled(true);
    ui->btn_closeWifi->setEnabled(false);
    ui->btn_connectWifi->setEnabled(false);
    ui->dt_sysDate->setDate(QDate::currentDate());
    ui->dt_sysTime->setTime(QTime::currentTime());
    ui->edt_password->setEchoMode(QLineEdit::Password);
    runShellProcess =new QProcess(this);
    connect(runShellProcess, SIGNAL(readyRead()), this, SLOT(readProcess()));
    connect(runShellProcess, SIGNAL(finished(int)), this, SLOT(finishedProcess( )));

    ui->btn_closeBt->setEnabled(false);
    ui->btn_scanBt->setEnabled(false);
    ui->btn_connectBt->setEnabled(false);
    ui->edt_language->setEnabled(false);

     btn_openWfi=false;
     bt_Status=0x00;
     lsmodko=false;
     flag_udhcpc=true;

    s_Timer = new QTimer(this);
    connect(s_Timer,SIGNAL(timeout()),this,SLOT(displayUpdate_timeout()));
    QPixmap pixmapBattery(":/image/download1.png");
    ui->label_down->setPixmap(pixmapBattery);
    state=false;
    updateState(state);




}

SystemSetup::~SystemSetup()
{
    delete ui;
    delete runShellProcess;
    delete s_Timer;
}

void SystemSetup::executeShellQProcessq(QString shell){
       shellOutput="";
       runShellProcess->start(shell);
}

//--------------------------------------------------------------------------
void SystemSetup::displayUpdate_timeout(){
    if(s_Timer->isActive()){
        s_Timer->stop();

        time_s--;

        if(time_s != 0)
        {
             state=(!state);
            updateState(state);

           s_Timer->start(1*1000);
        }
    }
}

void SystemSetup::updateState(bool status){
    if(status){
    ui->label_down->show();
    }else{
        ui->label_down->hide();
     }
}

void SystemSetup::displayUpdate_set(unsigned int s,bool status)//updateBluetoothStatus
{
    if(status){
        time_s = s;
        s_Timer->start(1*1000);
    }
    else{
           s_Timer->stop();
           time_s=0;
         //  emit mTime(s);
    }
}

//-----------------------------------------------------------------------------
void SystemSetup::executeShellCmd(const QString  shell){
            shellOutput="";
           QStringList options;
         //  options << "-c" << " lsmod | grep -E  \"brcmfmac\"";
              options<<"-c"<<shell;
//           QProcess process;
//           process.start("/bin/bash", options);
//           process.waitForFinished();
//           process.waitForReadyRead();
//           process.close();
           runShellProcess->start("/bin/bash", options);
}


void SystemSetup::finishedProcess( ){
 QString tmp="";QStringList list;

          if(bt_Status == bt_scan){
                  list = shellOutput.split("\n");
                  tmp = list.at(0);
                if (0 == QString::compare("Scanning ...", tmp) ){
                for(int i = 1; i< list.size();++i){
                tmp = list.at(i);
                  ui->com_ssidBt->addItem(tmp);
                }
                 ui->btn_connectBt->setEnabled(true);
              }
         }

        if(bt_Status == bt_close){
                QString str= shellOutput.left(5).trimmed();
                QString cmd = QString("kill  -9  %1").arg(str);
                qDebug()<<"[close]-->"<<cmd;
                executeShellQProcessq(cmd);
         }

        if(bt_Status == bt_open){
                int ret = shellOutput.indexOf("brcmutil");
                if( ret > -1) {
                    lsmodko=true;
                }
                 qDebug()<<"finishedProcess 1"<<shellOutput<<ret;
                ret=shellOutput.indexOf("brcmfmac");
                if(ret > -1){
                    lsmodko=true;
                }

                if(lsmodko ==false){
                  insmodko();
                 }
                executeShellQProcessq("bluez_init");
                ui->btn_openBt->setEnabled(false);
                ui->btn_closeBt->setEnabled(true);
                ui->btn_scanBt->setEnabled(true);

                qDebug()<<"finishedProcess 2"<<shellOutput<<ret;
           }

           if(bt_Status==bt_receive){
                     list = shellOutput.split("\n");            
                    if (0 == QString::compare("Disconnect done!", list.at(0)) ){
                         MessageBox msg;
                         msg.MessageBox_Info("Bluetooth received data successfully");
                         updateState(false);
                    }
           }

   bt_Status=0x00;
}


void SystemSetup::readProcess(){
    QString output=runShellProcess->readAll();
        shellOutput+=output;

 qDebug()<<"readpr"<<shellOutput;
}


void SystemSetup::getwifiState(QString state){
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::blue);

        qDebug()<<"[debug->getwifiState]"<<state;

        if(0 ==QString::compare("COMPLETED",state)) {
                     ui->label_wifi->setText(tr("WIFI connected."));
                     if(flag_udhcpc){
                        system("udhcpc -i wlan0");
                        flag_udhcpc=false;
                      }
        }

        else if(0==QString::compare("SCANNING",state)){
                     ui->label_wifi->setText(tr("WIFI unable to connect !"));
        }
/*        else if(0 == QString::compare("ERROR",state)){
                    ui->label_wifi->setText("WIFI密码错误!");
        }*/else{
                    ui->label_wifi->setText(tr("WIFI disconnected!"));
         }

                    ui->label_wifi->setPalette(pa);
}


void SystemSetup::getSignalStrength(QString signal){
   emit SignalStrength(signal);
}
//----------------------------------------------------------------------------------------system steup
void SystemSetup::paperTypeSelectionClicked(int index){
App::paperType=index;
}

void SystemSetup::on_btn_save_clicked()
{
    ui->btn_save->setEnabled(false);
    //App::serialNumber = ui->edt_serialnumber->text().toInt();
    MessageBox msg;
    int ret = msg.MessageBox_Ask(tr("Save data?"));
     if(0 == ret){
            pMainView->systemStatus_Save();
            pMainView->setParameters();
             setSystemTime();
    }
    ui->btn_save->setEnabled(true);
}


void SystemSetup::setSystemTime(){
    QString dateTime="date -s \"";
    dateTime.append(ui->dt_sysDate->date().toString("yyyy-MM-dd"));
    dateTime.append(" ");
    dateTime.append(ui->dt_sysTime->time().toString("HH:mm:ss"));
    dateTime.append("\"");

    QProcess::startDetached(dateTime); // 0312 表示3月12日，1025表示当前时分
    QProcess::startDetached("hwclock -w"); // 同步系统时间
    QProcess::startDetached("sync"); // 保存配置
}


bool SystemSetup::systemShow(QSqlTableModel* model){
    QSqlRecord record = model->record(0);

        App::Species=record.value("species").toString();
        qDebug()<<"species"<<App::Species;
        ui->edt_testtype->addItem(App::Species);
        ui->edt_testtype->setCurrentIndex(0);

        App::TestPapertype=record.value("testPapertype").toString();
        qDebug()<< "debug---TestPapertype>"<<App::TestPapertype;
        ui->edt_paperType->addItem(App::TestPapertype);
        ui->edt_paperType->setCurrentIndex(0);


        App::Language=record.value("language").toString();
        if(0==QString::compare(App::Language,"Chinese"))
        {
          ui->edt_language->addItem("中文");
         }else if(0==QString::compare(App::Language,"English")){
          ui->edt_language->addItem("English");
        }
          ui->edt_language->setCurrentIndex(0);
         qDebug()<<"［systemShow］--->App::Language"<<App::Language;


        App::TestMode=record.value("testMode").toString();
        ui->edt_testmode->addItem(App::TestMode);
        ui->edt_testmode->setCurrentIndex(0);
        qDebug()<<"App::testMode"<<App::TestMode;


//        App::serialNumber=record.value("serialNumber").toInt();
//         ui->edt_serialnumber->setText(record.value("serialNumber").toString());
//         qDebug()<<"App::serialNumber"<<App::serialNumber;

    return false;
}




void  SystemSetup::species(QSqlTableModel *model){

    if (0 == QString::compare( App::Species,model->record(0).value(0).toString()))
    {
        ui->edt_testtype->addItem(model->record(1).value(0).toString());
    }
    else if  (0 == QString::compare( App::Species,model->record(1).value(0).toString()))
    {
        ui->edt_testtype->addItem(model->record(0).value(0).toString());
    }

}


void SystemSetup::language(QSqlTableModel *model)
{
//    qDebug()<<"language"<<model->record(0).value(0).toString()<<model->record(1).value(0).toString();
        if (0 == QString::compare( App::Language,"Chinese"))
        {
            ui->edt_language->addItem("English");
            qDebug()<<"language--->1";
        }
        else if  (0 == QString::compare( App::Language,"English"))
        {
             qDebug()<<"language--->2";
            ui->edt_language->addItem("中文");
        }

}


void SystemSetup::testMode(QSqlTableModel *model)
{
        if (0 == QString::compare( App::TestMode,model->record(0).value(0).toString()))
        {
            ui->edt_testmode->addItem(model->record(1).value(0).toString());
        }
        else if  (0 == QString::compare( App::TestMode,model->record(1).value(0).toString()))
        {
            ui->edt_testmode->addItem(model->record(0).value(0).toString());
        }

}

void SystemSetup::testPapertype(QSqlTableModel *model)
{
    if (0 == QString::compare( App::TestPapertype,model->record(0).value(0).toString()))
    {
        ui->edt_paperType->addItem(model->record(1).value(0).toString());
        ui->edt_paperType->addItem(model->record(2).value(0).toString());
    }
    else if  (0 == QString::compare( App::TestPapertype,model->record(1).value(0).toString()))
    {
        ui->edt_paperType->addItem(model->record(0).value(0).toString());
        ui->edt_paperType->addItem(model->record(2).value(0).toString());
    }else if(0 == QString::compare( App::TestPapertype,model->record(2).value(0).toString()))
    {
        ui->edt_paperType->addItem(model->record(0).value(0).toString());
        ui->edt_paperType->addItem(model->record(1).value(0).toString());
    }
}


void SystemSetup::on_edt_paperType_currentIndexChanged(const QString &arg1){//
    App::TestPapertype = arg1;
}

void SystemSetup::on_edt_language_currentIndexChanged(const QString &arg1){//试纸型号
            if( 0 == QString::compare(arg1,"English")) {
                    App::Language="English";
               }else{
                    App::Language="Chinese";
            }

}


void SystemSetup::on_edt_testmode_currentIndexChanged(const QString &arg1){//语言
    App::TestMode = arg1;
}


void SystemSetup::on_edt_testtype_currentIndexChanged(const QString &arg1){//测试方式
    App::Species = arg1;
}



//--------------------------------------------------------------------------------------------------wifi
void SystemSetup::on_btn_openWifi_clicked(){

        insmodko();
        bool ret =wifiScan();
       if(ret){
            QPalette pa;
            pa.setColor(QPalette::WindowText,Qt::blue);
            ui->label_wifi->setText(tr("WIFI ON !"));
            ui->label_wifi->setPalette(pa);
            ui->btn_openWifi->setEnabled(false);
            ui->btn_closeWifi->setEnabled(true);
       }

}


void SystemSetup::insmodko(){
    system(".  /opt/wifi/insmod_wifiko.sh");
    usleep(1000*2);
}


void SystemSetup::makeWpaConf(QString ssid, QString passWorld){

    QString shellOutput = shellProcess("mount -o remount r+w /");
//    qDebug()<<"makeWpaConf 1"<<shellOutput;

    QFile file("/etc/wpa_supplicant.conf");

        //判断文件是否存在
        if(file.exists()){
            qDebug()<<"文件已存在";
        }else{
            qDebug()<<"文件不存在";
        }

        if(!file.open(QIODevice::ReadWrite)){
            qDebug()<<"打开失败";
        }else{
            qDebug()<<"打开成功";
        }

 char f1[]="ctrl_interface=/var/run/wpa_supplicant\n";
 char f2[]="ap_scan=1\n";
 char f3[]="network={\n";
 char f4[]="}\n";
 //char f5[]="\n";

char *argf[]={
f1,f2,f3,f4
};

  QString content;


        for(int i=0,j=0;i<8;i++){

                if(i==3){
                         content = QString("ssid=\"%1\"").arg(ssid);
                  }
                else if(i==4||i==6) {
                 content = QString("\n");
                }
                else  if (i==5){
                          content = QString("psk=\"%1\"").arg(passWorld);
                }
                else {
                        content = QString(argf[j]);
                         j++;
                }

        //获得文件大小
        qint64 pos;
        pos = file.size();
        //重新定位文件输入位置，这里是定位到文件尾端
        file.seek(pos);

        //写入文件
        qint64 length = -1;
        length = file.write(content.toLatin1(),content.length());

        if(length == -1){
            qDebug()<<"写入文件失败";
        }else{
            qDebug()<<"写入文件成功";
        }
}
file.close();
}

void SystemSetup::openWpatool(){
    int try_run = 2;
        system("wpa_supplicant -Dnl80211 -iwlan0 -c/etc/wpa_supplicant.conf -B &");

      while((try_run)&&(!App::wifi_connect)){
        sleep(1);
         bool ret =wb_thread.getWpa_status();
            if(ret){
                 wb_thread.start();
            }
            try_run--;
      }
}


QString SystemSetup::fileView(QString fileName) {
    QString tmp="";
        //QString fileName ="/opt/wifi/wpa_ps";
        QFile  file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"open wifi_list file error !";
            return tmp;
        }
        QTextStream in(&file);
        QString line = in.readLine();
             while(!line.isNull()){
               qDebug()<< "[systemSetup]--->" << line;
                tmp=line;
                line=in.readLine();
          }
return tmp;
}

void SystemSetup::killps(QString ps){

    QString kill_wpa=ps;

    std::string str = kill_wpa.toStdString();
    const char* ch = str.c_str();

    system(ch);
    system("sync");
    printf("snd cmd %s\n",ch);
}


void SystemSetup::rmmodko(){
    system("ifconfig wlan0 down");
    system("rmmod brcmfmac");
    system("rmmod brcmutil");
}

void SystemSetup::closeWpatool(){
    QString kill_app;


    system(" ps |grep  \"wpa_supplicant\" |grep -v  \"grep\" |awk '{print $1}'  >  /opt/wifi/wpa_ps");
    system("sync");
    system("ps |grep  \"udhcpc\" |grep -v  \"grep\" |awk '{print $1}'  >  /opt/wifi/udhcpc_ps");
    system("sync");


    QString wpa_ps = fileView("/opt/wifi/wpa_ps");
    kill_app= QString("kill -9 %1").arg(wpa_ps);
    killps(kill_app);
    system("sync");

    QString udhcpc_ps = fileView("/opt/wifi/udhcpc_ps");
    kill_app = QString("kill -9 %1").arg(udhcpc_ps);
    killps(kill_app);

    system("sync");
     App::wifi_connect=false;


    emit(SignalStrength(0));

     wb_thread.stop();
     wb_thread.wait();
    flag_udhcpc=true;
}


//bool SystemSetup::ssidCompare(){

//   // cmd = "grep -E \"ssid=\"  /etc/wpa_supplicant.conf";
//    QString shellOutput = shellProcess("grep -E \"ssid=\"  /etc/wpa_supplicant.conf");

//    wifiScan();

//    for(int i = 0; i< ssidList.size();++i)
//    {
//         QString tmp = ssidList.at(i);

//        qDebug()<<"tmp ="<< tmp;

//         if(  shellOutput.contains(tmp,Qt::CaseSensitive))
//         {
//            qDebug()<<"ok";
//            return true;
//         }
//    }
// return false;
//}

QString SystemSetup::shellProcess(QString cmd){
   QProcess process;
   process.start(cmd);
   process.waitForFinished();
   QByteArray output = process.readAllStandardOutput();
   QString str_output = output;
  return str_output;
}


bool SystemSetup::wifiScan(){
ui->label_wifi->setText(tr("Wifi is scanning...."));
        ui->com_ssidWifi->clear();
        system("iw dev wlan0 scan | grep -E  \"SSID\"  > /opt/wifi/wifi_tmp");
        system("sync");
        usleep(1000);
        system("grep -E  \"SSID|Quality\"  /opt/wifi/wifi_tmp | awk '{print $2}'  > /opt/wifi/wifi_list");
        system("sync");

        QString fileName = "/opt/wifi/wifi_list";
        QFile  file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        qDebug()<<"open wifi_list file error !";
        return false;
        }

        QTextStream in(&file);
        QString ssid = in.readLine();

        while(!ssid.isNull()){
            qDebug()<< "[systemSetup]--->" <<ssid;
            ui->com_ssidWifi->addItem(ssid);
            ssidList << ssid;
            ssid=in.readLine();
        }
ui->btn_connectWifi->setEnabled(true);
   return true;
}


void SystemSetup::on_btn_connectWifi_clicked(){
    QPalette pa;

       if(!btn_openWfi){

                     btn_openWfi=true;
                    qDebug()<<"on_btn_connectWifi_clicked 1";
                     ui->label_wifi->setText(tr("Wifi is connecting...."));
                     QString  passWorld = ui->edt_password->text();
                     QString  ssid = ui->com_ssidWifi->currentText();

                     if(!(passWorld.isEmpty())&&(!ssid.isEmpty())){
                        rmWpaConfi();
                      qDebug()<<"[Connect---->passWorld  ssid]"<<passWorld<<ssid;
                      makeWpaConf(ssid,passWorld);
                      openWpatool();


                      ui->btn_connectWifi->setText("Disconnects");

                     }else{

                         ui->label_wifi->setText(tr("Please enter WIFI password!"));
                         pa.setColor(QPalette::WindowText,Qt::blue);
                         ui->label_wifi->setPalette(pa);

                     }

       }else if(btn_openWfi) {
                      qDebug()<<"on_btn_Connect_clicked close!";
                     btn_openWfi=false;

                     closeWpatool();

                     pa.setColor(QPalette::WindowText,Qt::blue);
                     ui->label_wifi->setPalette(pa);
                     ui->label_wifi->setText(tr("WIFI disconnected!"));
                    ui->btn_connectWifi->setText(tr("Connect"));
       }

}




void SystemSetup::on_btn_clean_clicked(){
    ui->edt_password->clear();
    ui->label_wifi->setText(tr("Please re-enter WIFI password!"));
    rmWpaConfi();
}

void SystemSetup::rmWpaConfi(){
        QString shellOutput;

        shellOutput = shellProcess("mount -o remount r+w /");
        qDebug()<<"rmWpaConfi 1"<<shellOutput;
        shellOutput = shellProcess("rm  /etc/wpa_supplicant.conf");
        qDebug()<<"rmWpaConfi 2"<<shellOutput;
}

void SystemSetup::on_btn_scanWifi_clicked(){
    wifiScan();
}


void SystemSetup::on_com_ssid_currentIndexChanged(const QString &arg1){
    qDebug()<<"[on_com_ssid_currentIndexChanged]--> " <<arg1;
ssidName=arg1;
}


void SystemSetup::on_btn_closeWifi_clicked(){
  QPalette pa;
        if(App::wifi_connect){
                closeWpatool();
          }
        rmmodko();

        pa.setColor(QPalette::WindowText,Qt::blue);
        ui->label_wifi->setText(tr("WIFI OFF !"));
        ui->label_wifi->setPalette(pa);

        ui->btn_openWifi->setEnabled(true);
        ui->btn_closeWifi->setEnabled(false);

}



//------------------------------------------------------------------------BT

//void SystemSetup::shellCmd(unsigned int cmd){
//    int count=2;

//    switch(cmd){
//             case 0x03:
//                      executeShellCmd("lsmod|grep -E  \"brcmfmac\"");
//                      while(cont--){
//                         if(lsmodko){
//                          printf("lsmod ko insmod ok\n");
//                        }
//                    }
//                break;

//            default: break;
//        }
//}


void SystemSetup::on_btn_openBt_clicked(){
        bt_Status = bt_open;
        executeShellCmd("lsmod|grep -E  \"brcmfmac\"");
        ui->btn_closeBt->setEnabled(true);
}


void SystemSetup::on_btn_scanBt_clicked(){
    bt_Status=bt_scan;
    executeShellQProcessq("hcitool scan");
}


void SystemSetup::on_btn_closeBt_clicked(){
    ui->btn_openBt->setEnabled(true);


}

void SystemSetup::on_btn_connectBt_clicked(){
    QString  ssidName = ui->com_ssidBt->currentText();
    QString tmp  = ssidName.left(18).trimmed();
    QString cmd  = QString("agent -a hci0 0000 %1").arg(tmp);

    executeShellQProcessq(cmd);
    emit Signalbt(true);
    executeShellCmd("sync");
    executeShellCmd("sdptool add OPUSH");

}


void SystemSetup::on_btn_receiveFiles_clicked()
{  MessageBox msg;
    int     rets = msg.MessageBox_Ask(tr("Bluetooth Receive data ?"));
    if(rets == 0){
        qDebug()<<"[Debug] receive data ..";
        bt_Status = bt_receive;
displayUpdate_set(60,true);
        //system("cd /opt/BT/ && ./bt_update.sh");
        executeShellCmd("obex_test_wc -b local 9 |grep -E  \"Disconnect done!\"");
    }
}







void SystemSetup::on_btn_back_clicked()
{
emit SendHomeSignal();
}

void SystemSetup::on_btn_back_2_clicked()
{
emit SendHomeSignal();
}

void SystemSetup::on_btn_back_3_clicked()
{
  emit SendHomeSignal();
}
