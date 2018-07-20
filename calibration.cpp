#include "calibration.h"
#include "ui_calibration.h"

#include <mainbussniessview.h>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QTableView>
#include <QScrollBar>
#include <QDebug>

Calibration::Calibration(QWidget *parent,MainBussniessView* pMainView) :
    QTabWidget(parent),pMainBussView(pMainView),
    ui(new Ui::Calibration)
{
    ui->setupUi(this);
    pQueryModel = new QSqlQueryModel(this);//
    pMainBussView->GetItemName(pQueryModel);
    ui->btn_options_setup->setModel(pQueryModel);


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

    ui->edt_Calibrate0->installEventFilter(this);
  connect(pMainBussView,SIGNAL(sTime(int )),this,SLOT(sTimeSlot(int)));
       connect(pMainView, SIGNAL(CalibrateObserverveResult(QSqlTableModel*)), this, SLOT(on_CalibrateObserverveResult(QSqlTableModel*)), Qt::AutoConnection);
}

Calibration::~Calibration()
{
    delete ui;
}

void Calibration::on_btn_Back_clicked()
{
      emit SendHomeSignal();
}

//void Calibration::on_btn_Back_2_clicked()
//{
//      emit SendHomeSignal();
//}


void Calibration::on_btn_options_setup_pressed(const QModelIndex &index)
{
    qDebug("bug--->CalibrateDialog.cpp->on_lstView_ItemName_pressed");
    strItemName = index.data(Qt::DisplayRole).toString();
    if(pTableModel == NULL){
        pTableModel = new QSqlQueryModel(this);
    }
    int nItemNo = pMainBussView->GetItemNoByItemName(strItemName);
    pMainBussView->Calibrate_Query(pTableModel, nItemNo);
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

void Calibration::on_btn_save_clicked()
{
    CalibrateModel calibrateModel;
    int nItemNo = pMainBussView->GetItemNoByItemName(strItemName);
    calibrateModel.setItemNo(nItemNo);
    calibrateModel.setCalibrateValue0(ui->edt_Calibrate0->text().toInt());
    calibrateModel.setCalibrateValue1(ui->edt_Calibrate1->text().toInt());
    calibrateModel.setCalibrateValue2(ui->edt_Calibrate2->text().toInt());
    calibrateModel.setCalibrateValue3(ui->edt_Calibrate3->text().toInt());
    calibrateModel.setCalibrateValue4(ui->edt_Calibrate4->text().toInt());
    calibrateModel.setCalibrateValue5(ui->edt_Calibrate5->text().toInt());
    calibrateModel.setCalibrateValue6(ui->edt_Calibrate6->text().toInt());
    calibrateModel.setCalibrateValue7(ui->edt_Calibrate7->text().toInt());

    calibrateModel.setLaderValue0(ui->edt_LaderValue0->text());
    calibrateModel.setLaderValue1(ui->edt_LaderValue1->text());
    calibrateModel.setLaderValue2(ui->edt_LaderValue2->text());
    calibrateModel.setLaderValue3(ui->edt_LaderValue3->text());
    calibrateModel.setLaderValue4(ui->edt_LaderValue4->text());
    calibrateModel.setLaderValue5(ui->edt_LaderValue5->text());
    calibrateModel.setLaderValue6(ui->edt_LaderValue6->text());
    calibrateModel.setLaderValue7(ui->edt_LaderValue7->text());
    pMainBussView->Calibrate_Save(calibrateModel);
    pMainBussView->GetCalibration(nItemNo, strItemName);
     qDebug("bug--->CalibrateDialog.cpp->on_btn_CalibrateSave_clicked");
}

void Calibration::on_CalibrateObserverveResult(QSqlTableModel* calibrateTableModel){
qDebug("bug--->CalibrateDialog.cpp->on_CalibrateObserverveResult");
        ui->calibrateList->setModel(calibrateTableModel);
        ui->calibrateList->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
        ui->calibrateList->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->calibrateList->setSelectionBehavior(QAbstractItemView::SelectRows);
       ui->calibrateList->setRowHeight(0,40);

//        QFont font ;//定义一个字体变量
//        font.setBold(true);  //设置粗体
//         ui->calibrateList->horizontalHeader()->setFont(font);

        ui->calibrateList->verticalHeader()->hide();
}

bool Calibration::eventFilter(QObject *watched, QEvent *event)
{
    if (watched==ui->edt_Calibrate0)
    {
    if (event->type()==QEvent::FocusIn){OpenKeyboard();}
     ui->edt_Calibrate0 ->clearFocus();
    }

    return QWidget::eventFilter(watched,event);
}

void Calibration::OpenKeyboard()
{
    QString mString = ui->edt_Calibrate0->text();

    KeyBoard *v_key = new KeyBoard(this);
    if(ui->edt_Calibrate0 ->hasFocus())
    {
        QString mString = ui->edt_Calibrate0->text();
        v_key->settext(mString);
        v_key->setWindowTitle(QString::fromUtf8("请输入内容"));
        if(v_key->exec()==QDialog::Accepted)
        {
            QString ret = v_key->GetInputBuf(); //返回键盘输入的结果
            if(0==ret.size())
            //如果打开了键盘但是没有输入任何内容
            {
                ret = ui->edt_Calibrate0->text();
            }
            ui->edt_Calibrate0 ->setText(ret);
        }
    }
delete v_key;
}

void Calibration::on_calibrate_start_clicked()
{
    QString strItemName = ui->btn_options_show->currentText();//获取选项名称

        if(!fist_show){
            pMainBussView->Test_DeleteResult(strItemName);//显示一下
            fist_show=true;
        }

bool bResult = false;
ui->calibrateList->setEnabled(false);
ui->calibrate_start->setEnabled(false);
ui->calibrate_stop->setEnabled(true);


       // qDebug("bug--->Calibrate.cpp->on_btn_CalibrateData_clicked start");

       //  qDebug() << "mItemName " <<  strItemName;
        bResult = pMainBussView->sencmd(strItemName);//调用发送接口


        if(bResult){//判断是否完成
        qDebug("bug--->Calibrate.cpp->on_btn_CalibrateData_clicked end 1 ");
        }else{
         qDebug("bug--->Calibrate.cpp->on_btn_CalibrateData_clicked end 2");
        }

        ui->calibrateList->setEnabled(true);
        ui->calibrate_start->setEnabled(true);
        ui->calibrate_stop->setEnabled(false);
}

void Calibration::on_calibrate_stop_clicked()
{

    qDebug("bug--->CalibrateDialog.cpp->on_btn_CalibrateStop_clicked");

    bool bResult = false;
    fist_show=false;

    bResult = pMainBussView->Stop();
    if(bResult){
//        QString strItemName = ui->btn_options_show->currentText();
//        QList<int> lstResult;
//        pMainBussView->WhiteCalendar(strItemName, lstResult);

//        ui->lstResultView->clear();
//        foreach (int nResult, lstResult) {
//            ui->lstResultView->addItem(QString("%1").arg(nResult));
//        }
        //int nTotalCount = pageCount(ui->calibrateList);
        int nTotalCount = pageCount(ui->calibrateList);
        ui->lbTotalCount->setText(QString("%1").arg(nTotalCount));
        ui->calibrate_stop->setEnabled(false);
        ui->calibrate_start->setEnabled(true);
    }
}
void Calibration::sTimeSlot( int st)
{
//printf("[Calibration::sTimeslot] ----->%d\n",st);
    QString s = QString::number(st, 10);
    ui->time_Number->display(s);
}
bool Calibration::pageDown(QTableView *p,bool isLoop)//下翻
{
    qDebug("bug--->CalibrateDialog.cpp->pageDown");
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
}

bool Calibration::pageHome(QTableView *p)//首页
{
     qDebug("bug--->CalibrateDialog.cpp->pageHome");
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxValue = p->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值
    if(maxValue == 0)  return false;
    p->verticalScrollBar()->setSliderPosition(0);
}

bool Calibration::pageEnd(QTableView *p)//末页
{
      qDebug("bug--->CalibrateDialog.cpp->pageEnd");
    if(p == NULL)  return false;
    if(p->rowAt(0) < 0) return false;
    int maxValue = p->verticalScrollBar()->maximum(); // 当前SCROLLER最大显示值
    if(maxValue == 0)  return false;
    p->verticalScrollBar()->setSliderPosition(maxValue);
}

int Calibration::pageCount(QTableView *p)//QTableView 总页数
{
    qDebug("bug--->CalibrateDialog.cpp->pageCount");
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
       qDebug("bug--->CalibrateDialog.cpp->pageTo");
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
}

bool Calibration::pageUp(QTableView *p,bool isLoop)//上翻
{
       qDebug("bug--->CalibrateDialog.cpp->pageUp");
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
}


void Calibration::on_btn_FirstPag_clicked()
{
    qDebug("bug--->CalibrateDialog.cpp->on_btn_FirstPag_clicked");
   pageHome(ui->calibrateList);
}

void Calibration::on_btn_PreviousPage_clicked()
{
    qDebug("bug--->CalibrateDialog.cpp->on_btn_PreviousPage_clicked");
    pageUp(ui->calibrateList,false);
}

void Calibration::on_btn_NextPage_clicked()
{
    qDebug("bug--->CalibrateDialog.cpp->on_btn_NextPage_clicked");
      pageDown(ui->calibrateList, false);

}

void Calibration::on_btn_LastPage_clicked()
{
    qDebug("bug--->CalibrateDialog.cpp->on_btn_PreviousPage_clicked");
        pageEnd(ui->calibrateList);
}
