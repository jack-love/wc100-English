#include "calibration.h"
#include "ui_calibration.h"

#include "mainbussniessview.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QTableView>
#include <QScrollBar>
#include <QDebug>
#include "messagebox.h"


Calibration::Calibration(QWidget *parent,MainBussniessView* pMainView) :
    QTabWidget(parent),pMainBussView(pMainView),ui(new Ui::Calibration){

    ui->setupUi(this);

    QRegExp regx("[0-9]+$");
    validator = new QRegExpValidator(regx, this);
    ui->edt_Calibrate0->setValidator(validator);
    ui->edt_Calibrate1->setValidator(validator);
    ui->edt_Calibrate2->setValidator(validator);
    ui->edt_Calibrate3->setValidator(validator);
    ui->edt_Calibrate4->setValidator(validator);
    ui->edt_Calibrate5->setValidator(validator);
    ui->edt_Calibrate6->setValidator(validator);
    ui->edt_Calibrate7->setValidator(validator);

//    ui->edt_Calibrate0->installEventFilter(this);
//    ui->edt_Calibrate1->installEventFilter(this);
//    ui->edt_Calibrate2->installEventFilter(this);
//    ui->edt_Calibrate3->installEventFilter(this);
//    ui->edt_Calibrate4->installEventFilter(this);
//    ui->edt_Calibrate5->installEventFilter(this);
//    ui->edt_Calibrate6->installEventFilter(this);
//    ui->edt_Calibrate7->installEventFilter(this);

    connect(pMainBussView,SIGNAL(mTime(int )),this,SLOT(sTimeSlot(int)));
    connect(pMainView, SIGNAL(CalibrateObserverveResult(QSqlTableModel*)), this, SLOT(on_CalibrateObserverveResult(QSqlTableModel*)), Qt::AutoConnection);
    connect(pMainBussView,SIGNAL(system_saveok()),this,SLOT(systemSetup_save()),Qt::AutoConnection);
    connect(ui->btn_Back_2,SIGNAL(clicked()),this,SLOT(on_btn_BackHome_clicked()));
    connect(ui->btn_Back_1,SIGNAL(clicked()),this,SLOT(on_btn_BackHome_clicked()));


    pQueryModel = new QSqlQueryModel(this);
    getItemName();
    ui->btn_options_setup->setModel(pQueryModel);
    ui->edt_TestPapertype->setText(App::TestPapertype);

    pTableModel = new QSqlQueryModel(this);

    ui->calibrate_start->setEnabled(true);
    ui->calibrate_stop->setEnabled(false);

}

Calibration::~Calibration()
{
    delete ui;
    delete validator;
    delete pQueryModel;
    delete pTableModel;
}

void Calibration::on_btn_BackHome_clicked() {
      emit SendHomeSignal();
}


void Calibration::getItemName()
{
    if (0 == QString::compare("11-III",App::TestPapertype)){
         pMainBussView->GetItemName_11_3(pQueryModel);
    }else   if (0 == QString::compare("10T",   App::TestPapertype)){
         pMainBussView->GetItemName_10T(pQueryModel);
    }else if (0 == QString::compare("12MA", App::TestPapertype) ){
         pMainBussView->GetItemName_12MA(pQueryModel);
    }
}

void Calibration::systemSetup_save()
{
   qDebug()<<"[Calibration::saveok()---->]"<<App::TestPapertype;

        getItemName();
        ui->btn_options_setup->setModel(pQueryModel);
        ui->edt_TestPapertype->setText(App::TestPapertype);

         ui->edt_Calibrate0->clear();//校准
         ui->edt_Calibrate1->clear();
         ui->edt_Calibrate2->clear();
         ui->edt_Calibrate3->clear();
         ui->edt_Calibrate4->clear();
         ui->edt_Calibrate5->clear();
         ui->edt_Calibrate6->clear();
         ui->edt_Calibrate7->clear();

         ui->edt_LaderValue0->clear();//梯度值
         ui->edt_LaderValue1->clear();
         ui->edt_LaderValue2->clear();
         ui->edt_LaderValue3->clear();
         ui->edt_LaderValue4->clear();
         ui->edt_LaderValue5->clear();
         ui->edt_LaderValue6->clear();
         ui->edt_LaderValue7->clear();

          pMainBussView-> Initalize();

}

void Calibration::on_btn_options_setup_pressed(const QModelIndex &index)
{

            strItemName = index.data(Qt::DisplayRole).toString();
 //             qDebug() << " debug--->on_btn_options_setup_pressed"<<strItemName;
//            if(pTableModel == NULL){
//                pTableModel = new QSqlQueryModel(this);
//            }

        if (0 == QString::compare("11-III",App::TestPapertype)){
           int  nItemNo = pMainBussView->GetItemNoByItemName_11_3(strItemName);
            pMainBussView->Calibrate_Query_11_3(pTableModel, nItemNo);
            qDebug()<< "on_btn_options_setup_pressed"<<nItemNo;
        }
        else if (0 == QString::compare("10T", App::TestPapertype) ){
           int  nItemNo = pMainBussView->GetItemNoByItemName_10T(strItemName);
            pMainBussView->Calibrate_Query_10T(pTableModel, nItemNo);
            qDebug()<< "on_btn_options_setup_pressed"<<nItemNo;

        }
        else if(0 == QString::compare("12MA",App::TestPapertype)){
            int nItemNo = pMainBussView->GetItemNoByItemName_12MA(strItemName);
            pMainBussView->Calibrate_Query_12MA(pTableModel, nItemNo);
            qDebug()<< "on_btn_options_setup_pressed"<<nItemNo;

        }

    QSqlRecord record = pTableModel->record(0);
    if(record.count() > 0){
        record.value("ItemName").toString();
        ui->edt_Calibrate0->setText(record.value("CalibrateValue0").toString());//校准
        ui->edt_Calibrate1->setText(record.value("CalibrateValue1").toString());
        ui->edt_Calibrate2->setText(record.value("CalibrateValue2").toString());
        ui->edt_Calibrate3->setText(record.value("CalibrateValue3").toString());
        ui->edt_Calibrate4->setText(record.value("CalibrateValue4").toString());
        ui->edt_Calibrate5->setText(record.value("CalibrateValue5").toString());
        ui->edt_Calibrate6->setText(record.value("CalibrateValue6").toString());
        ui->edt_Calibrate7->setText(record.value("CalibrateValue7").toString());

        ui->edt_LaderValue0->setText(record.value("ResultValue0").toString());//梯度值
        ui->edt_LaderValue1->setText(record.value("ResultValue1").toString());
        ui->edt_LaderValue2->setText(record.value("ResultValue2").toString());
        ui->edt_LaderValue3->setText(record.value("ResultValue3").toString());
        ui->edt_LaderValue4->setText(record.value("ResultValue4").toString());
        ui->edt_LaderValue5->setText(record.value("ResultValue5").toString());
        ui->edt_LaderValue6->setText(record.value("ResultValue6").toString());
        ui->edt_LaderValue7->setText(record.value("ResultValue7").toString());

    }
}


void Calibration::on_btn_save_clicked(){


    CalibrateModel calibrateModel;
 int nItemNo;
    if (0 == QString::compare("11-III",App::TestPapertype)){
       nItemNo = pMainBussView->GetItemNoByItemName_11_3(strItemName);

   }else if (0 == QString::compare("10T", App::TestPapertype) ){
       nItemNo = pMainBussView->GetItemNoByItemName_10T(strItemName);

     }else if (0 == QString::compare("12MA", App::TestPapertype) ){
        nItemNo = pMainBussView->GetItemNoByItemName_12MA(strItemName);
    }

    MessageBox msg;
    int     rets = msg.MessageBox_Ask(tr("Save data ?"));

    if(rets == 0){
    pMainBussView->buzzer();
//--------------------------------------------------------------------------------------------------校准
    calibrateModel.setItemNo(nItemNo);
    calibrateModel.setCalibrateValue0(ui->edt_Calibrate0->text().toInt());
    calibrateModel.setCalibrateValue1(ui->edt_Calibrate1->text().toInt());
    calibrateModel.setCalibrateValue2(ui->edt_Calibrate2->text().toInt());
    calibrateModel.setCalibrateValue3(ui->edt_Calibrate3->text().toInt());
    calibrateModel.setCalibrateValue4(ui->edt_Calibrate4->text().toInt());
    calibrateModel.setCalibrateValue5(ui->edt_Calibrate5->text().toInt());
    calibrateModel.setCalibrateValue6(ui->edt_Calibrate6->text().toInt());
    calibrateModel.setCalibrateValue7(ui->edt_Calibrate7->text().toInt());
//-------------------------------------------------------------------------------------------------梯度
    calibrateModel.setLaderValue0(ui->edt_LaderValue0->text());
    calibrateModel.setLaderValue1(ui->edt_LaderValue1->text());
    calibrateModel.setLaderValue2(ui->edt_LaderValue2->text());
    calibrateModel.setLaderValue3(ui->edt_LaderValue3->text());
    calibrateModel.setLaderValue4(ui->edt_LaderValue4->text());
    calibrateModel.setLaderValue5(ui->edt_LaderValue5->text());
    calibrateModel.setLaderValue6(ui->edt_LaderValue6->text());
    calibrateModel.setLaderValue7(ui->edt_LaderValue7->text());

    pMainBussView->calibrateSave(calibrateModel);
    pMainBussView->getCalibration(nItemNo, strItemName);
    }

}

void Calibration::on_CalibrateObserverveResult(QSqlTableModel* calibrateTableModel){

    ui->calibrateList->setModel(calibrateTableModel);
    ui->calibrateList->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    ui->calibrateList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->calibrateList->setSelectionBehavior(QAbstractItemView::SelectRows);
    //   ui->calibrateList->setRowHeight(0,20);
    ui->calibrateList->setColumnWidth(0, 100);
    ui->calibrateList->setColumnWidth(1, 170);
    ui->calibrateList->setColumnWidth(2, 170);
    ui->calibrateList->setColumnWidth(3, 80);
    ui->calibrateList->setColumnWidth(4, 80);
    ui->calibrateList->setColumnWidth(5, 80);
    ui->calibrateList->setColumnWidth(6, 80);
      ui->calibrateList->setColumnWidth(7, 280);
    //ui->calibrateList->setColumnHidden(6, true);
    //ui->calibrateList->setColumnHidden(7, true);
    ui->calibrateList->verticalHeader()->hide();
    calModel=calibrateTableModel;
}


void Calibration::on_calibrate_start_clicked()
{
    if(App::Electric_quantity > 20){
    QString  strItemName = ui->btn_options_show->currentText();//获取选项名称
    MessageBox msg;

        ItemName=strItemName;
        bool bResult = false;
       // ui->calibrateList->setEnabled(false);
        ui->calibrate_start->setEnabled(false);
        ui->calibrate_stop->setEnabled(true);

        // pMainBussView->buzzer();
        bResult = pMainBussView->calibrationTest(strItemName);//调用发送接口

        if(!bResult){//判断是否完成
            msg.MessageBox_Err(tr("Single step Test failure!"));
        }

     //  ui->calibrateList->setEnabled(true);
        ui->calibrate_start->setEnabled(true);
        ui->calibrate_stop->setEnabled(false);
    }else{
        MessageBox msg;
        msg.MessageBox_Ask(tr("Low power please charge !"));
    }
}

void Calibration::on_calibrate_stop_clicked(){
    MessageBox msg;
    bool bResult = false;


    bResult = pMainBussView->Stop();
    if(!bResult){
     msg.MessageBox_Err(tr("Single stop Test failure!"));
    }
   else{
        int  nTotalCount = pageCount(ui->calibrateList);
        ui->lbTotalCount->setText(QString("%1").arg(nTotalCount));
    }

    ui->calibrate_stop->setEnabled(false);
    ui->calibrate_start->setEnabled(true);
}

void Calibration::sTimeSlot( int st){
    QString s = QString::number(st, 10);
    ui->time_Number->display(s);
}

bool Calibration::pageDown(QTableView *p,bool isLoop)//下翻
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;		//每页显示行数
    int canNotViewCount = rowCount-rowCountPerPage;			//看不见的行数
    if(canNotViewCount == 0){
        return false;
    }
    int maxValue = p->verticalScrollBar()->maximum();		// 当前SCROLLER最大显示值
    if(maxValue == 0){
        return false;
    }
    int pageValue = (maxValue*rowCountPerPage)/canNotViewCount;
    int nCurScroller = p->verticalScrollBar()->value();		//获得当前scroller值
    if(nCurScroller<maxValue)
        if(rowCountPerPage > canNotViewCount){
            p->verticalScrollBar()->setSliderPosition(canNotViewCount);
        }else{
            p->verticalScrollBar()->setSliderPosition(nCurScroller+pageValue);
        }

    else
    {
        if(isLoop == TRUE)
            p->verticalScrollBar()->setSliderPosition(0);
    }
    return true;
}

bool Calibration::pageHome(QTableView *p)//首页
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxValue = p->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值
    if(maxValue == 0)  return false;
    p->verticalScrollBar()->setSliderPosition(0);
    return true;
}

bool Calibration::pageEnd(QTableView *p)//末页
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxValue = p->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值
    if(maxValue == 0)  return false;
    p->verticalScrollBar()->setSliderPosition(maxValue);
    return true;
}

int Calibration::pageCount(QTableView *p)//QTableView 总页数
{
    if(p == NULL)  return -1;
    if(p->rowAt(0) < 0) return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;//每页显示行数
    int ret = rowCount/rowCountPerPage;
    int tem = rowCount%rowCountPerPage;
    if (tem != 0) ret++;
    return ret;
}

bool Calibration::pageTo(QTableView *p, int pageNO)//翻到指定页
{
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxPage = pageCount(p);
    if(pageNO > maxPage)  return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;		//每页显示行数
    int canNotViewCount = rowCount-rowCountPerPage;			//看不见的行数
    if(canNotViewCount == 0) return false;
    int maxValue = p->verticalScrollBar()->maximum();		// 当前SCROLLER最大显示值
    if(maxValue == 0) return false;
    int pageValue = (maxValue*rowCountPerPage)/canNotViewCount;
    p->verticalScrollBar()->setSliderPosition(pageValue*(pageNO-1));
    return true;
}

bool Calibration::pageUp(QTableView *p,bool isLoop)//上翻
{

    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int rowCount = p->model()->rowCount();
    int rowHeight = p->rowHeight(0);
    int tableViewHeight = p->height();
    int rowCountPerPage = tableViewHeight/rowHeight-1;		//每页显示行数
    int canNotViewCount = rowCount-rowCountPerPage;			//看不见的行数
    if(canNotViewCount == 0) return false;
    int maxValue = p->verticalScrollBar()->maximum();		// 当前SCROLLER最大显示值
    if(maxValue == 0) return false;
    int pageValue = (maxValue*rowCountPerPage)/canNotViewCount;
    int nCurScroller = p->verticalScrollBar()->value();		//获得当前scroller值
    if(nCurScroller>0){
        p->verticalScrollBar()->setSliderPosition(nCurScroller-pageValue);
    }
    else
    {
        if(isLoop == TRUE){
            p->verticalScrollBar()->setSliderPosition(maxValue);
        }
    }
    return true;
}


void Calibration::on_btn_FirstPag_clicked(){
   pMainBussView->calibrationQuery(ui->btn_options_show->currentText());
   pageHome(ui->calibrateList);
}

void Calibration::on_btn_PreviousPage_clicked(){
    pageUp(ui->calibrateList,false);
}

void Calibration::on_btn_NextPage_clicked(){
      pageDown(ui->calibrateList, false);
}

void Calibration::on_btn_LastPage_clicked(){
        pageEnd(ui->calibrateList);
}

void Calibration::on_btn_delete_clicked()
{
     MessageBox msg ;
     int rets;

    rets = msg.MessageBox_Ask(tr("delete data ?"));
    if(rets == 0){
         pMainBussView->calibrationDelete_Result(ui->btn_options_show->currentText());
    }

}



