#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ttythread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  m_MainView = new MainBussniessView(this);

    m_MainButtonDlg = NULL;
    m_TestDialog = NULL;
    m_Maintancance = NULL;
    m_SignIn = NULL;
    m_SystemSetup=NULL;//2
    m_Calibration=NULL;

    buttonState = MAIN_BTN;
    selectButton(buttonState);
    m_MainButtonDlg->hide();
    buttonState = TESTING;
    selectButton(buttonState);


QRect rect(0,0,480, 800);
this->setGeometry(rect);


showBattery();
showWIFI();
showBluetooth();

QTimer *timer=new QTimer(this);
connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
timer->start(500);
connect(m_TestDialog,SIGNAL(sendsignal()),this,SLOT(BackHomeActionSlot()));



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::BackHomeActionSlot(){
 qDebug("bug--->mainwindow.cpp->BackHomeActionSlot");
selectButton(MAIN_BTN);
}
void MainWindow::GoTestingActionSlot()
{
selectButton(TESTING);
}
void MainWindow::TestingActionSlot(){
   // qDebug("bug--->mainwindow.cpp->TestingActionSlot");
   // selectButton(TESTING);
  //  QMessageBox::warning(NULL, "warning", "Please input X ", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
 selectButton(TESTING);
}

void MainWindow::HistoryActionSlot(){
     qDebug("bug--->mainwindow.cpp->HistoryActionSlot");
   // selectButton(HISTORY);
}

void MainWindow::MaintancanceActionSlot(){
qDebug("bug--->mainwindow.cpp->MaintancanceActionSlot");
selectButton(DEBUG);
}

void MainWindow::CalibrationActionSlot(){
qDebug("bug--->mainwindow.cpp->CalibrationActionSlot");
selectButton(CALIBRATE);
}

void MainWindow::SystemActionSlot(){
qDebug("bug--->mainwindow.cpp->SystemActionSlot");
selectButton(SYSTEM);
}

void MainWindow::UpdateActionSlot(){
qDebug("bug--->mainwindow.cpp->UpdateActionSlot");
}

void MainWindow::OtherActionSlot(){

qDebug("bug--->mainwindow.cpp->OtherActionSlot");
}

void MainWindow::SignInActionSlot(){
qDebug("bug--->mainwindow.cpp->SignInActionSlot");
selectButton(SIGNIN);
}


void MainWindow::selectButton(MAIN_BUTTON   button){

    switch(button){

    case TESTING:
       qDebug("bug--->mainwindow.cpp->TESTING 1");
       if(buttonState != button){
            hideButton(buttonState);
            qDebug("bug--->mainwindow.cpp->TESTING 2");
        }
        if(m_TestDialog == NULL){
            m_TestDialog = new TestingDialog(ui->main_Frame);
            connect(m_TestDialog,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
            qDebug("bug--->mainwindow.cpp->TESTING 3");
        }
       m_TestDialog->setModal(true);
        m_TestDialog->show();
        buttonState = button;
        break;

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
            connect(m_MainButtonDlg,SIGNAL(on_btn_SignIn()),this,SLOT(SignInActionSlot()));
            connect(m_MainButtonDlg,SIGNAL(SendHomeSignal()),this,SLOT(GoTestingActionSlot()));
        }
        m_MainButtonDlg->setModal(true);
        m_MainButtonDlg->show();
        buttonState = button;
        break;

  case DEBUG:
        if(buttonState != button){
            hideButton(buttonState);

         }
         if(m_Maintancance == NULL){
         m_Maintancance = new Maintancance(ui->main_Frame);
         connect(m_Maintancance,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
          }

         m_Maintancance->show();
         buttonState = button;
         break;

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

    case SYSTEM:
        qDebug("bug--->mainwindow.cpp->SYSTEM 1");
       if(buttonState !=  button){
            hideButton(buttonState);
            qDebug("bug--->mainwindow.cpp->SYSTEM 2");
        }

       if(m_SystemSetup == NULL){
        m_SystemSetup = new SystemSetup(ui->main_Frame);
          connect(m_SystemSetup,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
            qDebug("bug--->mainwindow.cpp->SYSTEM 3");
        }
        m_SystemSetup->show();
        buttonState = button;
        break;

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

    }


}

void MainWindow::hideButton(MAIN_BUTTON button){
    switch(button){
        case TESTING:
        qDebug("bug--->mainwindow.cpp->MainWindow::hideButton case TESTING ");
            m_TestDialog->hide();
        break;

  #if 0
      case MYTEST:
            m_mytestDialog->hide();
        break;
        case HISTORY:
            m_queryDialog->hide();
        break;
        case QUALITY:
            m_qualityControlDialog->hide();
        break;

        break;
        case ITEM:
            m_ParameterDialog->hide();
        break;
        case SYSTEM:
            m_systemDialog->hide();
        break;
       #endif

      case CALIBRATE:
        m_Calibration->hide();
        break;

        case DEBUG:
        m_Maintancance->hide();
        qDebug("bug--->mainwindow.cpp->MainWindow::hideButton case DEBUG ");

        break;
        case MAIN_BTN:
        m_MainButtonDlg->hide();
        qDebug("bug--->mainwindow.cpp->MainWindow::hideButton case MAIN_BTN ");
        break;

        case  SIGNIN:
        m_SignIn->hide();
        break;

        case SYSTEM:
        m_SystemSetup->hide();
          qDebug("bug--->mainwindow.cpp->MainWindow::hideButton case SYSTEM ");
        break;

    }
}

void MainWindow::showBattery()
{
   // SYSTEM_POWER_STATUS systemPowerSatus;
    //GetSystemPowerStatus(&systemPowerSatus);
   // int remaindPower=(int)systemPowerSatus.BatteryLifePercent;
    int remaindPower=100;
    if(remaindPower>75)
    {
        QPixmap pixmapBattery(":/icons/BatteryIcon.png");
        ui->labelBattery->setPixmap(pixmapBattery);
    }
    else if(remaindPower>50&&remaindPower<=75)
    {
        QPixmap pixmapBattery(":/icons/BatteryIcon1.png");
        ui->labelBattery->setPixmap(pixmapBattery);
    }
    else if(remaindPower>25&&remaindPower<=50)
    {
        QPixmap pixmapBattery(":/icons/BatteryIcon2.png");
        ui->labelBattery->setPixmap(pixmapBattery);
    }
    else if(remaindPower>0&&remaindPower<=25)
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
void MainWindow::showWIFI()
{

//    DWORD dwError = ERROR_SUCCESS;
//    DWORD dwNegotiatedVersion;
//    HANDLE hClientHandle = NULL;

//    dwError = WlanOpenHandle(1, NULL, &dwNegotiatedVersion, &hClientHandle);
//    if (dwError != ERROR_SUCCESS)
//    {
//        WlanCloseHandle(hClientHandle,NULL);
//        return;
//    }

//    PWLAN_INTERFACE_INFO_LIST pInterfaceList = NULL;
//    dwError = WlanEnumInterfaces(hClientHandle, NULL,&pInterfaceList);
//    if ( dwError != ERROR_SUCCESS )
//    {
//        WlanFreeMemory(pInterfaceList);
//        WlanCloseHandle(hClientHandle,NULL);
//        return;
//    }

//    GUID &guid = pInterfaceList->InterfaceInfo[0].InterfaceGuid;
//    PWLAN_AVAILABLE_NETWORK_LIST pWLAN_AVAILABLE_NETWORK_LIST = NULL;

//    dwError = WlanGetAvailableNetworkList(hClientHandle, &guid,
//        2,NULL, &pWLAN_AVAILABLE_NETWORK_LIST);
//    if (dwError != ERROR_SUCCESS)
//    {
//        WlanFreeMemory(pInterfaceList);
//        WlanFreeMemory(pWLAN_AVAILABLE_NETWORK_LIST);
//        WlanCloseHandle(hClientHandle,NULL);
//        return;
//    }

    //WLAN_AVAILABLE_NETWORK wlanAN;
    bool isConnected=false;
  //  int numberOfItems = pWLAN_AVAILABLE_NETWORK_LIST->dwNumberOfItems;
  int   numberOfItems =10;
    if (numberOfItems > 0)
    {
        for(int i = 0; i <numberOfItems; i++)
        {
            //wlanAN = pWLAN_AVAILABLE_NETWORK_LIST->Network[i];
            //if(wlanAN.dwFlags & 1)
            //{
                isConnected=true;
           int wifiQuality =86;
               // int wifiQuality=(int)wlanAN.wlanSignalQuality;

                if(wifiQuality>75)
                {
                    QPixmap pixmapWireless(":/icons/WirelessIcon.png");
                    ui->labelWireless->setPixmap(pixmapWireless);
                }
                else if(wifiQuality>50&&wifiQuality<=75)
                {
                    QPixmap pixmapWireless(":/icons/WirelessIcon1.png");
                    ui->labelWireless->setPixmap(pixmapWireless);
                }
                else if(wifiQuality>25&&wifiQuality<=50)
                {
                    QPixmap pixmapWireless(":/icons/WirelessIcon2.png");
                    ui->labelWireless->setPixmap(pixmapWireless);
                }
                else if(wifiQuality>0&&wifiQuality<=25)
                {
                    QPixmap pixmapWireless(":/icons/WirelessIcon3.png");
                    ui->labelWireless->setPixmap(pixmapWireless);
                }

           // }
        }
    }
    if (!isConnected)
    {
        QPixmap pixmapWireless(":/icons/WirelessIcon4.png");
        ui->labelWireless->setPixmap(pixmapWireless);
    }
    //WlanFreeMemory(pInterfaceList);
   // WlanFreeMemory(pWLAN_AVAILABLE_NETWORK_LIST);
   // WlanCloseHandle(hClientHandle,NULL);
}

void MainWindow::showBluetooth(){

    QPixmap pixmapBattery(":/icons/Bluetooth1.png");
    ui->labelBluetooth->setPixmap(pixmapBattery);
}

void MainWindow::showTime(){
QTime time= QTime::currentTime();
QString txtTime = time.toString("hh:mm:ss");
ui->lcdNumber->display(txtTime);
}


