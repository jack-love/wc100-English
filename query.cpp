#include "query.h"
#include "ui_query.h"
#include "mainbussniessview.h"
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQueryModel>
#include<messagebox.h>
 Query::Query (QWidget *parent, MainBussniessView*pMainBussniessView) :QTabWidget(parent),pMainView(pMainBussniessView),ui(new Ui::Query)
{
    ui->setupUi(this);
    connect(pMainView, SIGNAL(SampleResult(QSqlTableModel*)), this, SLOT(on_SampleResult(QSqlTableModel*)));
    ui->dt_query_End->setDateTime(QDateTime::currentDateTime());
}


Query::~Query()
{
    delete ui;
    delete printModel;
}


/*
    ui->tbview_TestResult->setColumnWidth(0, 100);
    ui->tbview_TestResult->setColumnWidth(1, 70);
    ui->tbview_TestResult->setColumnWidth(2, 90);
    ui->tbview_TestResult->setColumnWidth(3, 100);
    ui->tbview_TestResult->setColumnWidth(4, 90);
    ui->tbview_TestResult->setColumnWidth(5, 300);

*/




void Query::on_SampleResult(QSqlTableModel* testModel){

    ui->tableView_TestResult->setModel(testModel);
    ui->tableView_TestResult->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->tableView_TestResult->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_TestResult->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView_TestResult->verticalHeader()->hide();
    ui->tableView_TestResult->setColumnHidden(1, true);
    ui->tableView_TestResult->setColumnHidden(2, true);
    ui->tableView_TestResult->setColumnHidden(3, true);
    ui->tableView_TestResult->setColumnHidden(8, true);
    ui->tableView_TestResult->setColumnHidden(10, true);
    ui->tableView_TestResult->setColumnHidden(11, true);


    ui->tableView_TestResult->setColumnWidth(0, 80);
    ui->tableView_TestResult->setColumnWidth(2, 70);
    ui->tableView_TestResult->setColumnWidth(5, 90);
    ui->tableView_TestResult->setColumnWidth(6, 100);
    ui->tableView_TestResult->setColumnWidth(7, 90);
    ui->tableView_TestResult->setColumnWidth(9, 300);
    printModel=testModel;

}




void Query::on_btn_query_clicked()
{
    if(!ui->edt_query_SampleNo->text().isEmpty()){
      bool ret = queryDate(ui->edt_query_SampleNo->text().toInt());
      if(!ret){
          MessageBox msg ;
          msg.MessageBox_Info(tr("No sample data!"));
      }
    }else{
        queryDate(0);
    }
}

bool Query::queryDate(int sampleNo){
    sBeginDate = ui->dt_query_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss");
       sEndDate = ui->dt_query_End->dateTime().toString("yyyy-MM-dd hh:mm:ss");

   if(ui->edt_query_SampleNo->text().isEmpty()){
             pMainView->Query_SampleResult(1, sBeginDate, sEndDate);
    }else{
             //int sampleNo = ui->edt_query_SampleNo->text().toInt();
             pMainView->Query_SampleResult_No(sampleNo, sBeginDate, sEndDate);
    }


    if (printModel->rowCount()==0){
    return false;
    }
    else{
        qDebug()<<"return ...true";
    return true;
    }
}


/*

Date: 2609-02-04 00:31
No. 000001
 BIL  -  Neg     umol/L
 URO  -  3.3     umol/L
 KET  -  Neg     mmol/L
 BLD  -  Neg   cells/uL
 PRO  -  Neg        g/L
 NIT  -  Neg
 WBC  -  Neg   cells/uL
*GLU 3+  28      mmol/L
 SG      1.005
 PH      5.0
 VC      0       mmol/L

*/
void Query::on_btn_export_clicked(){
 MessageBox msg ;
    int ret = msg.MessageBox_Ask(tr("export data?"));
     if(0 == ret){

    if(!ui->edt_query_SampleNo->text().isEmpty()){
            SampleNo =ui->edt_query_SampleNo->text().toInt();


            QString  tmp = QString("%1").arg(SampleNo);
            ui->edt_query_SampleNo->setText(tmp);
            bool ret = queryDate(SampleNo);
               if(!ret){
                msg.MessageBox_Info(tr("No sample data!"));
               }else{
                dataExport();
                msg.MessageBox_Info(tr("Export success!"));
               }


    }else{


        SampleNo =1;
    while(1){

        QString  tmp = QString("%1").arg(SampleNo);
        ui->edt_query_SampleNo->setText(tmp);

        bool ret = queryDate(SampleNo);
            if(!ret) break;

         dataExport();
         SampleNo++;
        }
         ui->edt_query_SampleNo->clear();
         on_btn_query_clicked();

         msg.MessageBox_Info(tr("Export result %1").arg(SampleNo-1));
       }


 }

}


bool Query::dataExport(){
    QString printStr = "";

    if (printModel->rowCount()==0){
        //qDebug()<<"return ...";
    return false;
    }


    QSqlRecord aRec = printModel->record(0);
    printStr.append("\n\r\n");
    printStr.append(trUtf8("Date:")).append(aRec.value("SampleDate").toString()).append("\r\n");
    printStr.append(trUtf8("NO:")).append(aRec.value("SampleNo").toString()).append("\t").append(trUtf8("Strips:")).append(aRec.value("TbType").toString()).append("\r\n");


    for (int i=0;i<printModel->rowCount();i++)
    {
         aRec = printModel->record(i); //获取当前记录
        QString  ItemName=aRec.value("ItemName").toString();
         QString SampleValue=aRec.value("SampleValue").toString();
         QString Unit=aRec.value("Unit").toString();
         printStr.append(ItemName).append("\t").append(SampleValue).append("\t").append(Unit).append("\r\n");
    }
    printStr.append("\n\r\n");
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QByteArray sendForGBK = codec->fromUnicode(printStr);

    pMainView->PrintInformation(sendForGBK);
return true;
}

void Query::on_tableView_TestResult_pressed(const QModelIndex &index)
{
int nRow = index.row();
qDebug()<<"on_tableView_TestResult_pressed"<<nRow;

}

void Query::on_btn_delete_clicked() {
    MessageBox msg ;

        if (printModel->rowCount()==0){
                msg.MessageBox_Info(tr("No sample data!"));
              return;
          }


        int ret = msg.MessageBox_Ask(tr("Delete sample data?"));

         if(0 == ret){
             qDebug()<<"start dele!";
            ui->btn_delete->setEnabled(false);
//             int nRowCnt = printModel->rowCount();
//            qDebug()<<"[on_btn_delete_clicked]"<<nRowCnt;
//             while (nRowCnt > 0){
//                 nRowCnt--;
//                 printModel->removeRow(nRowCnt);
//                 printModel->submitAll();

                pMainView->testDelete_Result();

                ui->btn_delete->setEnabled(true);
                msg.MessageBox_Info(tr("Delete successful!"));
        }



}


void Query::on_btn_next_clicked()
{
      MessageBox msg ;
   if(!ui->edt_query_SampleNo->text().isEmpty()){
          SampleNo =ui->edt_query_SampleNo->text().toInt();

       SampleNo++;
      QString  tmp = QString("%1").arg(SampleNo);
       ui->edt_query_SampleNo->setText(tmp);
        bool ret =queryDate(SampleNo);
        if(!ret){
            MessageBox msg ;
            msg.MessageBox_Info(tr("No sample data!"));
        }
   }else{
               msg.MessageBox_Info(tr("Please enter the sample number!"));
   }
}

void Query::on_btn_previous_clicked() {
      MessageBox msg ;
    if(!ui->edt_query_SampleNo->text().isEmpty()){
           SampleNo =ui->edt_query_SampleNo->text().toInt();

         if(SampleNo > 0){
            SampleNo--;
         }
       QString  tmp = QString("%1").arg(SampleNo);
        ui->edt_query_SampleNo->setText(tmp);
        bool ret = queryDate(SampleNo);
        if(!ret){
            MessageBox msg ;
            msg.MessageBox_Info(tr("No sample data!"));
        }
    }else{
              msg.MessageBox_Info(tr("Please enter the sample number!"));
    }
}
void Query::on_btn_back_clicked()
{
   emit SendHomeSignal();
}
