#include "testingdialog.h"
#include "ui_testingdialog.h"
#include "mainbussniessview.h"
#include <QSqlTableModel>
#include "messagebox.h"
#include "myqsqltablemodel.h"
#include "databasehelper.h"
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

    connect(pMainView, SIGNAL(testResult(myQSqlTableModel*)), this, SLOT(on_TestResult(myQSqlTableModel*)),Qt::AutoConnection);
   connect(pMainView, SIGNAL(reset_signal()),this,SLOT(resetSlot()),Qt::AutoConnection );
   connect(pMainView, SIGNAL(mTime(int )),this,SLOT(sTimeSlot(int)));
   ui->label_test->setText(tr("Status: Stop"));
   pMainView->showTest_Result();

   ui->btn_Stop->setEnabled(false);

   // ui->widget_TestResult->setVisible(false);//测试界面QLabel
    ui->tbview_TestResult->setVisible(true);//测试界面QTableView
   // ui->label_No->setText(QApplication::translate("TestingDialog", "TextLabel", 0, QApplication::UnicodeUTF8));

    ui->label_process->setScaledContents(true);
    Movie = new QMovie(":image/test.gif");
    ui->label_process->setMovie(Movie);

}

TestingDialog::~TestingDialog()
{
    delete ui;
    delete Movie;
}


//bool TestingDialog::on_TestResult(QSqlTableModel* model){
//            int rowCount = model->rowCount();

//            for(int i=0; i<rowCount; i++){
//    qDebug()<<"on_TestResult_1:"<<i
//    <<model->record(i).value(0).toString()
//    <<"="
//    <<model->record(i).value(1).toString()
//    <<"="
//    <<model->record(i).value(2).toString()
//    <<"="
//    <<model->record(i).value(3).toString()
//    <<"="
//    <<model->record(i).value(4).toString()
//    <<"="
//    <<model->record(i).value(5).toString()
//    <<"=";

//    }

//QSqlRecord curRec = model->record(0);
//           qDebug()<<"on_TestResult_2"<< curRec.value(0).toString();
//           qDebug()<<"on_TestResult_2"<< curRec.value(1).toString();
//           qDebug()<<"on_TestResult_2"<< curRec.value(2).toString();
//           qDebug()<<"on_TestResult_2"<< curRec.value(3).toString();
//           qDebug()<<"on_TestResult_2"<< curRec.value(4).toString();
//           qDebug()<<"on_TestResult_2"<< curRec.value(5).toString();
//    return false;
//}

bool TestingDialog::on_TestResult(myQSqlTableModel* model){



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
    ui->tbview_TestResult->setColumnWidth(1, 70);
    ui->tbview_TestResult->setColumnWidth(2, 90);
    ui->tbview_TestResult->setColumnWidth(3, 100);
    ui->tbview_TestResult->setColumnWidth(4, 90);
    ui->tbview_TestResult->setColumnWidth(5, 300);
    return false;
}

void TestingDialog::on_btn_Back_clicked(){
 emit SendHomeSignal();
}

void TestingDialog::start_process(bool status){
  if(status){
      ui->label_process->show();
      Movie->start();
      }
  else{
      Movie->stop();
      ui->label_process->hide();
    }
}

void TestingDialog::on_btn_Start_clicked(){

            App::test_start=true;
            while(App::test_start){

                if(App::Electric_quantity > 15){

                                    ui->btn_Start->setEnabled(false);
                                    ui->btn_Stop->setEnabled(true);
                                    ui->btn_Back->setEnabled(false);
                                    start_process(true);
                                    ui->label_test->setText(tr("Status: Strip Test"));

                                    bool    bResult = pMainView->normalStart();
                                            if(!bResult){
                                                     qDebug()<<"[start testing  error!]";
                                              }else{
                                                      qDebug()<<"[start testint  ok!]";
                                             }

                                        if( 0 ==QString::compare(App::TestMode,"manual" ) && App::test_start){
                                          App::test_start=false;
                                            start_process(false);
                                          ui->label_test->setText(tr("Status: Stop"));
                                                              ui->btn_Start->setEnabled(true);
                                                              ui->btn_Stop->setEnabled(false);
                                                              ui->btn_Back->setEnabled(true);
                                               pMainView->setinitCondition();
                                        }

                }else{
                     App::test_start=false;
                    MessageBox msg;
                    msg.MessageBox_Info(tr("Low power please charge!"));
                    ui->btn_Start->setEnabled(true);
                    ui->btn_Stop->setEnabled(false);
                    ui->btn_Back->setEnabled(true);
                    start_process(false);
                 }

           }



}

void TestingDialog::on_btn_Stop_clicked(){

      if(App::test_start){
                App::test_start=false;
                ui->btn_Stop->setEnabled(false);
                ui->btn_Back->setEnabled(false);
                start_process(true);
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
        start_process(false);
}


void TestingDialog::sTimeSlot( int st){
        QString s = QString::number(st, 10);
        ui->time_Number->display(s);
}

