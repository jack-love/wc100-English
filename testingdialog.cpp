#include "testingdialog.h"
#include "ui_testingdialog.h"
#include "mainbussniessview.h"
#include <QSqlTableModel>
#include "messagebox.h"

TestingDialog::TestingDialog(QWidget *parent, MainBussniessView*pMainBussniessView) :
    QDialog(parent), pMainView(pMainBussniessView),
    ui(new Ui::TestingDialog)
{

    ui->setupUi(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。

   connect(pMainView, SIGNAL(testResult(QSqlTableModel*)), this, SLOT(on_TestResult(QSqlTableModel*)),Qt::AutoConnection);
   connect(pMainView, SIGNAL(reset_signal()),this,SLOT(resetSlot()),Qt::AutoConnection );
   connect(pMainView, SIGNAL(mTime(int )),this,SLOT(sTimeSlot(int)));
   ui->label_test->setText(tr("Status: Stop"));
   pMainView->showTest_Result();

   ui->btn_Stop->setEnabled(false);

}

TestingDialog::~TestingDialog()
{
    delete ui;
}



bool TestingDialog::on_TestResult(QSqlTableModel* model){
    ui->tbview_TestResult->setModel(model);
   ui->tbview_TestResult->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

//    ui->tbview_TestResult->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tbview_TestResult->setSelectionBehavior(QAbstractItemView::SelectRows);
//   ui->tbview_TestResult->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tbview_TestResult->verticalHeader()->hide();
  //ui->tbview_TestResult->horizontalScrollBar()->setEnabled(false);
 //   ui->tbview_TestResult->setHorizontalScrollBarPolic(Qt::ScrollBarAlwaysOff);
   // ui->tbview_TestResult->setColumnHidden(5, true);

    ui->tbview_TestResult->setColumnWidth(0, 100);
    ui->tbview_TestResult->setColumnWidth(1, 80);
    ui->tbview_TestResult->setColumnWidth(2, 100);
    ui->tbview_TestResult->setColumnWidth(3, 100);
    ui->tbview_TestResult->setColumnWidth(4, 90);
    ui->tbview_TestResult->setColumnWidth(5, 300);
    return false;
}

void TestingDialog::on_btn_Back_clicked(){
 emit SendHomeSignal();
}



void TestingDialog::on_btn_Start_clicked(){

            App::test_start=true;
            while(App::test_start){

                if(App::Electric_quantity > 15){

                                    ui->btn_Start->setEnabled(false);
                                    ui->btn_Stop->setEnabled(true);
                                    ui->btn_Back->setEnabled(false);

                                    ui->label_test->setText(tr("Status: Strip Test"));

                                    bool    bResult = pMainView->normalStart();
                                            if(!bResult){
                                                     qDebug()<<"[start testing  error!]";
                                              }else{
                                                      qDebug()<<"[start testint  ok!]";
                                             }

                                        if( 0 ==QString::compare(App::TestMode,"manual" ) && App::test_start){
                                          App::test_start=false;
                                          ui->label_test->setText(tr("Status: Stop"));
                                                              ui->btn_Start->setEnabled(true);
                                                              ui->btn_Stop->setEnabled(false);
                                                              ui->btn_Back->setEnabled(true);
                                        }

                }else{
                     App::test_start=false;
                    MessageBox msg;
                    msg.MessageBox_Info(tr("Low power please charge!"));
                    ui->btn_Start->setEnabled(true);
                    ui->btn_Stop->setEnabled(false);
                    ui->btn_Back->setEnabled(true);
                 }

           }



}

void TestingDialog::on_btn_Stop_clicked(){

      if(App::test_start){
                App::test_start=false;
                ui->btn_Stop->setEnabled(false);
                ui->btn_Back->setEnabled(false);

               bool   bResult = pMainView->Stop();

                 if(!bResult){
                         qDebug()<<"[start stop error!]";
                }else {
                       qDebug()<<"[start stop ok!]";
                }
                ui->label_test->setText(tr("Status: Reset"));
       }
}


void TestingDialog::resetSlot(){
        ui->btn_Start->setEnabled(true);
        ui->btn_Back->setEnabled(true);
        ui->btn_Stop->setEnabled(false);
        ui->label_test->setText(tr("Status: Stop"));
      //  qDebug()<<"resetSlot";
}


void TestingDialog::sTimeSlot( int st){
        QString s = QString::number(st, 10);
        ui->time_Number->display(s);
}

