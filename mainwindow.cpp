#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ttythread.h"
#include <QtTest>
#include "messagebox.h"
#include "systeminit.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow){

        ui->setupUi(this);
        QRect rect(0,0,480, 800);
        this->setGeometry(rect);

//调用主要工作接口
        m_MainView = new MainBussniessView(this);
        connect(m_MainView,SIGNAL(Spoweroff()),this,SLOT(MainpowerOff()));
        m_MainView->mcuPopen();
        m_MainView->coverHands();
        m_MainView->setParameters();

//界面切换
        buttonState = MAIN_BTN;
        selectButton(buttonState);
        m_MainButtonDlg->hide();
        buttonState = TESTING;
        selectButton(buttonState);
        App::wifi_connect=false;


//系统WIFI BT
        showWIFI(0);
        showBluetooth();

        QTimer *timer=new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
        timer->start(500);
        connect(m_TestDialog,SIGNAL(sendsignal()),this,SLOT(BackHomeActionSlot()));

//电量温度
        system_Monitor=new systemMonitor(this);
        bool tmp =system_Monitor->rt9428_open();
        if(tmp){
                connect(system_Monitor,SIGNAL(soc_Signal(char)),this,SLOT(socSignalSlot(char)));
                connect(system_Monitor,SIGNAL(charg_Signal(bool)),this,SLOT(chargeSignalSlot(bool)));
                system_Monitor->start();
            }

//开机动画
//            m_system_init=new Systeminit(this);
//            m_system_init->start();
            m_MainView->mcuReset();//必须放在这个位置
            ////  QTest::qWait(1000);
//            delete  m_system_init;

//语言支持
            connect(m_MainView,SIGNAL(languageConversion()),this,SLOT(LanguageConversion()));
            trans =new QTranslator;

            QString curLang=readLanguage_Setting(); //读取语言设置
            //qDebug()<<"[MainWindow]---->"<<curLang;
       if (curLang == "EN")
            trans->load(":/syszux/tr_en.qm");
       else
            trans->load(":/syszux/tr_zh.qm");
            qApp->installTranslator(trans);

            qDebug()<<"system version:"<<App::sys_version;
}

MainWindow::~MainWindow(){
    delete ui;
}

QString MainWindow::readLanguage_Setting(){

    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\Language",
             QSettings::NativeFormat);
    QString Language=reg->value("registered").toString();
    delete reg;

    return  Language;
}

void MainWindow::BackHomeActionSlot(){
selectButton(MAIN_BTN);
}

void MainWindow::TestingActionSlot(){
 selectButton(TESTING);
}

void MainWindow::HistoryActionSlot(){
   selectButton(HISTORY);
}

void MainWindow::MaintancanceActionSlot(){
selectButton(DEBUG);
}

void MainWindow::CalibrationActionSlot(){
selectButton(CALIBRATE);
}

void MainWindow::SystemActionSlot(){
selectButton(SYSTEM);
}

void MainWindow::UpdateActionSlot(){
selectButton(UPDATE);
}

void MainWindow::powerActionSlot(){
selectButton(POWER);
}

void MainWindow::SignInActionSlot(){
selectButton(SIGNIN);
}

void MainWindow::MainpowerOff() {
 selectButton(POWER);
}

void MainWindow::LanguageConversion(){
        if(0==QString::compare(App::Language,"Chinese")) {
        convertTo_Chinese();
        }else if(0==QString::compare(App::Language,"English")){
        convertTo_English();
        }
}

void MainWindow::selectButton(MAIN_BUTTON   button){

    switch(button){
//-------------------------------------------------------------------
      case MAIN_BTN:
                if(buttonState != button){
                    hideButton(buttonState);
               }
            if (m_MainButtonDlg == NULL){
                m_MainButtonDlg = new Mainbutton(ui->main_Frame);
                connect(m_MainButtonDlg, SIGNAL(on_btn_Testing()), this, SLOT(TestingActionSlot()));
                connect(m_MainButtonDlg, SIGNAL(on_btn_History()), this, SLOT(HistoryActionSlot()));
                connect(m_MainButtonDlg,SIGNAL(on_btn_Maintancance()),this,SLOT(MaintancanceActionSlot()));
                connect(m_MainButtonDlg,SIGNAL(on_btn_Calibration()),this,SLOT(CalibrationActionSlot()));
                connect(m_MainButtonDlg,SIGNAL(on_btn_System()),this,SLOT(SystemActionSlot()));
                connect(m_MainButtonDlg,SIGNAL(on_btn_Update()),this,SLOT(UpdateActionSlot()));
                connect(m_MainButtonDlg,SIGNAL(on_btn_Other()),this,SLOT(powerActionSlot()));
                connect(m_MainButtonDlg,SIGNAL(on_btn_SignIn()),this,SLOT(SignInActionSlot()));
                connect(m_MainButtonDlg,SIGNAL(SendHomeSignal()),this,SLOT(TestingActionSlot()));
            }
            m_MainButtonDlg->setModal(true);
            m_MainButtonDlg->show();
            buttonState = button;
            break;
//---------------------------------------------------------------------
    case TESTING:
            if(buttonState != button){
                hideButton(buttonState);
            }
            if(m_TestDialog == NULL){
                m_TestDialog = new TestingDialog(ui->main_Frame,m_MainView);
                connect(m_TestDialog,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
            }
            m_TestDialog->setModal(true);
            m_TestDialog->show();
            buttonState = button;
            break;
//-----------------------------------------------------------------
   case DEBUG:
            if(buttonState != button){
                hideButton(buttonState);
             }

             if(m_Maintancance == NULL){
                 m_Maintancance = new Maintancance(ui->main_Frame);
                 connect(m_Maintancance,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
              }
             m_MainView->mcuPclose();
             m_Maintancance->show();
             buttonState = button;
            break;
//-----------------------------------------------------------------------
    case SIGNIN:
                  if(buttonState != button){
                      hideButton(buttonState);
                 }
                 if(m_SignIn == NULL) {
                     m_SignIn = new SignIn(ui->main_Frame);
                     connect(m_SignIn,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
                 }
                m_SignIn->setModal(true);
                m_SignIn->show();
                buttonState=button;
          break;
//-----------------------------------------------------------------------------
    case SYSTEM:
       if(buttonState !=  button){
            hideButton(buttonState);  
        }
       if(m_SystemSetup == NULL){
        m_SystemSetup = new SystemSetup(ui->main_Frame,m_MainView);
          connect(m_SystemSetup,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
          connect(m_SystemSetup, SIGNAL(SignalStrength(QString)),this,SLOT(signalStrengthShow(QString)),Qt::AutoConnection);
          connect(m_SystemSetup, SIGNAL(Signalbt(bool)),this,SLOT(signalBtShow(bool)),Qt::AutoConnection);
        }
        m_SystemSetup->show();
        buttonState = button;
        break;
//-------------------------------------------------------------------------------
    case CALIBRATE:
                if(buttonState != button){
                hideButton(buttonState);
                }

                if(m_Calibration == NULL){
                m_Calibration = new Calibration(ui->main_Frame,m_MainView);
                connect(m_Calibration,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
                }

                m_Calibration->show();
                buttonState = button;
           break;
//-----------------------------------------------------------------------
         case HISTORY:
                if(buttonState != button){
                    hideButton(buttonState);
                 }
                if(m_Query ==NULL){
                    m_Query=new Query(ui->main_Frame,m_MainView);
                    connect(m_Query,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
                }
                 m_Query->show();
                    buttonState = button;
         break;
//-----------------------------------------------------------------------
           case UPDATE:
                if(buttonState != button){
                    hideButton(buttonState);
                }
                if( m_SystemUpdate == NULL){
                    m_SystemUpdate=new SystemUpdate( ui->main_Frame);
                    connect(m_SystemUpdate,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
                }
                    m_SystemUpdate->show();
                    buttonState = button;
            break;
//---------------------------------------------------------------------------
             case POWER:
                  bool  retb;
                            retb=m_MainView->askUser();

                  if(retb) {

                                if(buttonState != button){
                                    hideButton(buttonState);
                                 }

                                if( m_other == NULL){
                                    m_other=new Other( ui->main_Frame);
                                }

                                m_other->show();
                                buttonState = button;
                                m_MainView->mcuReset();
                                m_MainView->powerOff();
                         }
               break;
//-----------------------------------------------------------------------
             default:break;

    }
}


void MainWindow::hideButton(MAIN_BUTTON button){
    switch(button){
        case TESTING:
             m_TestDialog->hide();
        break;

        case CALIBRATE:
              m_Calibration->hide();
        break;

        case DEBUG:
             m_Maintancance->hide();
             m_MainView->mcuPopen();
        break;

        case MAIN_BTN:
              m_MainButtonDlg->hide();
        break;

        case  SIGNIN:
                m_SignIn->hide();
        break;

        case SYSTEM:
             m_SystemSetup->hide();
        break;

        case HISTORY:
                m_Query->hide();
        break;

        case UPDATE:
             m_SystemUpdate->hide();
        break;

        case POWER:
             m_other->hide();
        break;

        default: break;
    }
}

void MainWindow::socSignalSlot(char signal){
    showBattery(signal);
}

void MainWindow::chargeSignalSlot(bool state){
        if( true == state){
                QPixmap pixmapBattery(":/icons/BatteryIcon5.png");
                ui->labelCharging->setPixmap(pixmapBattery);
                ui->labelCharging->show();
            }else{
                ui->labelCharging->hide();
            }
}

void MainWindow::showBattery(char tmp) {
        char  remaindPower=tmp;
        if(remaindPower >100)
        {
            QPixmap pixmapBattery(":/icons/BatteryIcon.png");
            ui->labelBattery->setPixmap(pixmapBattery);
        }
       else  if(remaindPower>90 && remaindPower <=100)
        {
            QPixmap pixmapBattery(":/icons/BatteryIcon.png");
            ui->labelBattery->setPixmap(pixmapBattery);
        }
        else if(remaindPower>70&&remaindPower<=90)
        {
            QPixmap pixmapBattery(":/icons/BatteryIcon1.png");
            ui->labelBattery->setPixmap(pixmapBattery);
        }
        else if(remaindPower>35&&remaindPower<=70)
        {
            QPixmap pixmapBattery(":/icons/BatteryIcon2.png");
            ui->labelBattery->setPixmap(pixmapBattery);
        }
        else if(remaindPower>0&&remaindPower<=35)
        {
            QPixmap pixmapBattery(":/icons/BatteryIcon3.png");
            ui->labelBattery->setPixmap(pixmapBattery);
        }
        else
        {
            QPixmap pixmapBattery(":/icons/BatteryIcon4.png");
            ui->labelBattery->setPixmap(pixmapBattery);
        }

}
void MainWindow::signalBtShow(bool status){
    qDebug()<<"signalBtShow"<<status;
    if(status){
            QPixmap pixmapBattery(":/icons/Bluetooth1.png");
            ui->labelBluetooth->setPixmap(pixmapBattery);
    }else{
            QPixmap pixmapBattery(":/icons/Bluetooth2.png");
            ui->labelBluetooth->setPixmap(pixmapBattery);
    }
}

void MainWindow::signalStrengthShow(QString signal) {
        int  tmp = signal.toInt();
        showWIFI(tmp);
}

void MainWindow::showWIFI(int signal)
{

       if(App::wifi_connect){

                     int wifiQuality = signal;

                    if(wifiQuality > DB_30)
                    {
                        QPixmap pixmapWireless(":/icons/WirelessIcon.png");
                        ui->labelWireless->setPixmap(pixmapWireless);
                    }
                    else if(wifiQuality>DB_50&&wifiQuality<=DB_30)
                    {
                        QPixmap pixmapWireless(":/icons/WirelessIcon1.png");
                        ui->labelWireless->setPixmap(pixmapWireless);
                    }
                    else if(wifiQuality>DB_70&&wifiQuality<=DB_50)
                    {
                        QPixmap pixmapWireless(":/icons/WirelessIcon2.png");
                        ui->labelWireless->setPixmap(pixmapWireless);
                    }
                    else if(wifiQuality>DB_90&&wifiQuality<=DB_70)
                    {
                        QPixmap pixmapWireless(":/icons/WirelessIcon3.png");
                        ui->labelWireless->setPixmap(pixmapWireless);
                    }

    }   else  if (!(App::wifi_connect))
        {
            QPixmap pixmapWireless(":/icons/WirelessIcon4.png");
            ui->labelWireless->setPixmap(pixmapWireless);
        }

}

void MainWindow::showBluetooth(){
    QPixmap pixmapBattery(":/icons/Bluetooth2.png");
    ui->labelBluetooth->setPixmap(pixmapBattery);
}

void MainWindow::showTime(){
    QString str_time = QDateTime::currentDateTime().toString("yyyy-MM-dd H:mm:ss");
     ui->lbl_sysTime->setText(str_time);
     QPalette pa;
     pa.setColor(QPalette::WindowText,Qt::blue);
     ui->lbl_sysTime->setPalette(pa);
}

void MainWindow::convertTo_Chinese()
{//中文界面
    qApp->removeTranslator(trans);
    trans->load(":/syszux/tr_zh.qm");
    qApp->installTranslator(trans);

    ui->retranslateUi(this);

    language_Saving("CN");
    QString Language=readLanguage_Setting();
    qDebug()<<"convertTo_Chinese"<<Language;
}

void MainWindow::convertTo_English()
{//英文界面
     qApp->removeTranslator(trans);
     trans->load(":/syszux/tr_en.qm");
    qApp->installTranslator(trans);

     ui->retranslateUi(this);

    language_Saving("EN");
    QString Language=readLanguage_Setting();
    qDebug()<<"convertTo_English"<<Language;
}

void MainWindow::language_Saving(QString language){
    QSettings *reg =new QSettings("HKEY_CURRENT_USER\\Software\\Language",QSettings::NativeFormat);
    reg->setValue("registered",language);
    delete reg;
}
