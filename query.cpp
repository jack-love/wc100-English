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

    //connect(pMainView, SIGNAL(PatientResult(QSqlTableModel*)), this, SLOT(on_PatientResult(QSqlTableModel*)));
    connect(pMainView, SIGNAL(SampleResult(QSqlTableModel*)), this, SLOT(on_SampleResult(QSqlTableModel*)));
    //connect(pMainView, SIGNAL(QuerySampleResult(QSqlTableModel*)), this, SLOT(on_QuerySampleResult(QSqlTableModel*)));
      ui->dt_query_End->setDateTime(QDateTime::currentDateTime());
      // printModel = new QSqlQueryModel();
}


Query::~Query()
{
    delete ui;
    delete printModel;
}




//void Query::on_tablevew_Patient_pressed(const QModelIndex &index)
//{
//    nRow = index.row();
//    QSqlRecord record = patientModel->record(nRow);
//    if(record.count() > 0){
//        int nSampleNo = record.value("SampleNo").toInt();
//        QString strDateTime = record.value("RegisterDate").toString();
//        QString tempDate = strDateTime;
//        QString sEndDate = tempDate.replace(10, 9, " 23:59:59");
//        pMainView->Query_SampleResult(nSampleNo, strDateTime, sEndDate);
//    }
//}

//void Query::on_PatientResult(QSqlTableModel*model){
//    patientModel = model;
//    ui->tablevew_Patient->setModel(model);
//    ui->tablevew_Patient->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

//    ui->tablevew_Patient->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tablevew_Patient->setSelectionBehavior(QAbstractItemView::SelectRows);
//    //ui->tablevew_Patient->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//    ui->tablevew_Patient->verticalHeader()->hide();
//}


void Query::on_SampleResult(QSqlTableModel* testModel){

    ui->tableView_TestResult->setModel(testModel);
    ui->tableView_TestResult->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->tableView_TestResult->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_TestResult->setSelectionBehavior(QAbstractItemView::SelectRows);
        //ui->tablevew_Patient->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView_TestResult->verticalHeader()->hide();
    ui->tableView_TestResult->setColumnHidden(1, true);
    ui->tableView_TestResult->setColumnHidden(3, true);
    ui->tableView_TestResult->setColumnHidden(4, true);
    //ui->tableView_TestResult->setColumnHidden(7, true);
    ui->tableView_TestResult->setColumnHidden(8, true);
    //ui->tableView_TestResult->setColumnHidden(9, true);
    ui->tableView_TestResult->setColumnHidden(10, true);
    ui->tableView_TestResult->setColumnHidden(11, true);


    ui->tableView_TestResult->setColumnWidth(0, 80);
    ui->tableView_TestResult->setColumnWidth(2, 100);
    ui->tableView_TestResult->setColumnWidth(5, 80);
    ui->tableView_TestResult->setColumnWidth(6, 120);
    ui->tableView_TestResult->setColumnWidth(7, 80);
    ui->tableView_TestResult->setColumnWidth(9, 300);
    printModel=testModel;

}


//void Query::on_QuerySampleResult(QSqlTableModel* testModel){
//    ui->tbView_SampleResult->setModel(testModel);
//    ui->tbView_SampleResult->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

//    ui->tbView_SampleResult->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tbView_SampleResult->setSelectionBehavior(QAbstractItemView::SelectRows);
//    //ui->tablevew_Patient->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//    ui->tbView_SampleResult->verticalHeader()->hide();
//}


void Query::on_btn_query_clicked()
{
    sBeginDate = ui->dt_query_Start->dateTime().toString("yyyy-MM-dd hh:mm:ss");
       sEndDate = ui->dt_query_End->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    if(ui->edt_query_SampleNo->text().isEmpty()){
             pMainView->Query_SampleResult(1, sBeginDate, sEndDate);
    }else{
             int sampleNo = ui->edt_query_SampleNo->text().toInt();
             pMainView->Query_SampleResult_no(sampleNo, sBeginDate, sEndDate);
             // pMainView->Query_SampleResult(sampleNo, sBeginDate, sEndDate);
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
void Query::on_btn_export_clicked()
{
    QString printStr = "";

    if (printModel->rowCount()==0)
            return;

    QSqlRecord aRec = printModel->record(0);

    printStr.append(trUtf8("Date:")).append(aRec.value("SampleDate").toString()).append("\r\n");
    printStr.append(trUtf8("No:")).append(aRec.value("SampleNo").toString()).append("\r\n");


    for (int i=0;i<printModel->rowCount();i++)
    {
         aRec = printModel->record(i); //获取当前记录
        QString  ItemName=aRec.value("ItemName").toString();
         QString SampleValue=aRec.value("SampleValue").toString();
         QString Unit=aRec.value("Unit").toString();
         printStr.append(ItemName).append("\t").append(SampleValue).append("\t").append(Unit).append("\r\n");
    }

    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QByteArray sendForGBK = codec->fromUnicode(printStr);

    pMainView->PrintInformation(sendForGBK);
}

void Query::on_tableView_TestResult_pressed(const QModelIndex &index)
{
int nRow = index.row();
qDebug()<<"on_tableView_TestResult_pressed"<<nRow;
  //printModel->removeRow(nRow);
}

void Query::on_btn_delete_clicked() {

//        if (printModel->rowCount()==0)
//                return;
    MessageBox msg ;
        int ret = msg.MessageBox_Ask(tr("Delete data?"));

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
msg.MessageBox_Info(tr("Delete completed !"));
        }



}


void Query::on_btn_next_clicked()
{
      MessageBox msg ;
   if(!ui->edt_query_SampleNo->text().isEmpty()){
          SampleNo =ui->edt_query_SampleNo->text().toInt();
        pMainView->Query_SampleResult(SampleNo, sBeginDate, sEndDate);
       SampleNo++;
      QString  tmp = QString("%1").arg(SampleNo);
       ui->edt_query_SampleNo->setText(tmp);
       on_btn_query_clicked();
   }else{
               msg.MessageBox_Info(tr("Please input sample number!"));
   }
}

void Query::on_btn_previous_clicked() {
      MessageBox msg ;
    if(!ui->edt_query_SampleNo->text().isEmpty()){
           SampleNo =ui->edt_query_SampleNo->text().toInt();
         pMainView->Query_SampleResult(SampleNo, sBeginDate, sEndDate);
         if(SampleNo > 0){
            SampleNo--;
         }
       QString  tmp = QString("%1").arg(SampleNo);
        ui->edt_query_SampleNo->setText(tmp);
        on_btn_query_clicked();
    }else{
              msg.MessageBox_Info(tr("Please input sample number!"));
    }
}

void Query::on_btn_back_clicked()
{
   emit SendHomeSignal();
}
