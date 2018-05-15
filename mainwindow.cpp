#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_MainButtonDlg = NULL;
    m_TestDialog=NULL;

  //  if(m_MainButtonDlg == NULL){
 //       m_MainButtonDlg = new Mainbutton(ui->main_Frame);
  //  }
 //   m_MainButtonDlg->setModal(true);
  //  m_MainButtonDlg->show();
selectButton(MAIN_BTN);

connect(m_MainButtonDlg, SIGNAL(on_btn_Testing()), this, SLOT(TestingActionSlot()));
connect(m_MainButtonDlg, SIGNAL(on_btn_History()), this, SLOT(HistoryActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Maintancance()),this,SLOT(MaintancanceActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Calibration()),this,SLOT(CalibrationActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_System()),this,SLOT(SystemActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Update()),this,SLOT(UpdateActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Other()),this,SLOT(OtherActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Password()),this,SLOT(PasswordActionSlot()));

//connect(m_TestDialog,SIGNAL(sendsignal()),this,SLOT(BackHomeActionSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::BackHomeActionSlot(){
 qDebug("bug--->mainwindow.cpp->BackHomeActionSlot");
selectButton(MAIN_BTN);
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
}

void MainWindow::CalibrationActionSlot(){
qDebug("bug--->mainwindow.cpp->CalibrationActionSlot");
}

void MainWindow::SystemActionSlot(){
qDebug("bug--->mainwindow.cpp->SystemActionSlot");
}

void MainWindow::UpdateActionSlot(){
qDebug("bug--->mainwindow.cpp->UpdateActionSlot");
}

void MainWindow::OtherActionSlot(){

qDebug("bug--->mainwindow.cpp->OtherActionSlot");
}

void MainWindow::PasswordActionSlot(){
qDebug("bug--->mainwindow.cpp->PasswordActionSlot");
}


void MainWindow::selectButton(MAIN_BUTTON button){

    switch(button){

    case TESTING:
       if(buttonState != button){
            hideButton(buttonState);
        }
        if(m_TestDialog == NULL){
            m_TestDialog = new TestingDialog(ui->main_Frame);
            connect(m_TestDialog,SIGNAL(SendHomeSignal()),this,SLOT(BackHomeActionSlot()));
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
        }
        m_MainButtonDlg->setModal(true);
        m_MainButtonDlg->show();
        buttonState = button;

        break;

    }


}

void MainWindow::hideButton(MAIN_BUTTON button){
    switch(button){
        case TESTING:
        qDebug("bug--->mainwindow.cpp->MainWindow::hideButton case TESTING:");

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
        case CALIBRATE:
            m_calibrateDialog->hide();
        break;
        case ITEM:
            m_ParameterDialog->hide();
        break;
        case SYSTEM:
            m_systemDialog->hide();
        break;
        case DEBUG:
            m_MaintenanceDialog->hide();
        break;
       #endif
        case MAIN_BTN:
            m_MainButtonDlg->hide();
        break;
    }
}
