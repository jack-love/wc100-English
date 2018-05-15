#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_MainButtonDlg = NULL;

    if(m_MainButtonDlg == NULL){
        m_MainButtonDlg = new Mainbutton(ui->main_Frame);
    }
    m_MainButtonDlg->setModal(true);
    m_MainButtonDlg->show();


connect(m_MainButtonDlg, SIGNAL(on_btn_Testing()), this, SLOT(TestingActionSlot()));
connect(m_MainButtonDlg, SIGNAL(on_btn_History()), this, SLOT(HistoryActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Maintancance()),this,SLOT(MaintancanceActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Calibration()),this,SLOT(CalibrationActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_System()),this,SLOT(SystemActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Update()),this,SLOT(UpdateActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Other()),this,SLOT(OtherActionSlot()));
connect(m_MainButtonDlg,SIGNAL(on_btn_Password()),this,SLOT(PasswordActionSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TestingActionSlot(){
    qDebug("bug--->mainwindow.cpp->TestingActionSlot");
   // selectButton(TESTING);
    QMessageBox::warning(NULL, "warning", "Please input X ", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

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
