#include "mainbussniessview.h"
#include "databasehelper.h"
#include <QDateTime>
#include <QtCore>
#include <QtGui>
#include <QDesktopWidget>
#include <QProgressDialog>
#include<QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <qmath.h>
#include <qlibrary.h>
#include"testresultmodel.h"
#include <QTranslator>
#include <QtDebug>
#include <QProcess>
#include<assert.h>
#include <QThread>
#include"calibration.h"
#include"App.h"
#include <unistd.h>
#include <QtTest>
#include <QDialog>

MainBussniessView::MainBussniessView(QObject *parent) :
    QObject(parent), p(parent)
{
    assert(p!=NULL);
    memset(_result, 0, sizeof(RESULT));


    m_DatabaseHelper = new databaseHelper(".//autoUrineAnalysis.db");
    try{
        m_DatabaseHelper->createTable();
    }
    catch(...){
        //QMessageBox::information(NULL, "tip", "database conncention error!");
        //myHelper::ShowMessageBoxError(tr("database conncention error!"));
        qDebug()<<" database conncention error";
    }


    for(int i = 0;i < 13; i++)
        {
                for(int j = 0;j < 4; j++)
                {
                    _result[i].wrgb_value[j]=0;
                    _result[i].white_value[j]=0;
                    strcpy(_result[i].item_value[j], "");
                }
                for(int j = 0;j < 8; j++)
                {
                     _result[i].calibration[j]=0;
                }
                strcpy(_result[i].unit,"");
                strcpy(_result[i].name,"");
        }


    showTabelModel = new QSqlTableModel();
    showTabeTest=new QSqlTableModel();
    calibrateObserveTableModel = new QSqlTableModel();
    testdeleteTableModel  = new QSqlTableModel();

    connect(this, SIGNAL(system_Setup(QSqlTableModel*)), this, SLOT(system_setup_show(QSqlTableModel*)),Qt::AutoConnection);
    getSystem_status();
    Initalize();

    tty_thread = new ttyThread(this);
    connect(tty_thread,SIGNAL(receiveTtyData(QString)),this,SLOT(showTtyData(QString)));
    connect(tty_thread,SIGNAL(receiveAck(unsigned char)),this,SLOT(showTtyAck(unsigned char)));
    connect(tty_thread,SIGNAL(mTime(int )),this,SLOT(sTimeSlot(int)));
    connect(tty_thread,SIGNAL(receiveWb(WRGB_DAT )),this,SLOT(showWb(WRGB_DAT)));
    connect(tty_thread,SIGNAL(receiveRGB(WRGB_DAT,unsigned int  )),this,SLOT(showWrgb(WRGB_DAT ,unsigned int )));

}



void MainBussniessView::startProcessing(){
        QFont font("ZYSong18030",25);
        progressDialog->setFont(font);
        progressDialog->setWindowModality(Qt::WindowModal);

        progressDialog->setMinimumDuration(10);
       // progressDialog->setCancelButton(false);
       //progressDialog->setCancelable(true);
        progressDialog->setWindowTitle(tr("稍等....."));
        progressDialog->setLabelText(tr("系统正在初始化."));
        progressDialog->setCancelButtonText(tr("Cancel"));
        progressDialog->setRange(0,100);
        progressDialog->setStyleSheet(QString::fromUtf8("QLabel{\n"
        "color:rgb(255, 255, 255); \n"
        "}\n"
        "\n"
        "QDialog{\n"
        "background:url(://image/backGround.png)\n"
        "}"));
        progressDialog->resize(500,800);
        progressDialog->show();

        for (int i=1; i<100+1; i++)
        {
            progressDialog->setValue(i);

            QTest::qSleep(100);
            if (progressDialog->wasCanceled())
                return;
        }
}

void MainBussniessView::mcuReset()
{

    MessageBox mes;
   bool  get_return  =  mcuCmd(RESET);
   if(!get_return){
         App::errNumber = RESET_ERR;
     //  mes.MessageBox_Err(tr("MCU reset failure!"));
      }

}
void MainBussniessView::coverHands()
{
     MessageBox mes;
    bool  get_return  =  getVersion();
    if(!get_return){
          App::errNumber = VERSION_ERR;
        mes.MessageBox_Err(tr("Read MCU version failed!"));
       }
}

void MainBussniessView::setParameters(){
 bool   get_return = setUp();
    if(!get_return){
          App::errNumber = SETUP_ERR;
          MessageBox mes;
          mes.MessageBox_Err(tr("Set MCU version failed!"));
       }
}

void MainBussniessView::Initalize(){

    int icount = GetItemList(&lstItemModel);//item_tb_11_3
    qDebug()<<"debug--->Initalize()"<< icount;
    for(int i = 0;i < icount;i++){
        int itemNO = lstItemModel[i].getItemNo();
        QString strItemName = lstItemModel[i].getItemName();
        getCalibration(itemNO, strItemName);
        qDebug() << "Initalize()"<<strItemName;
    }

    for(int j = icount-1;j >= 0;j--){
        lstItemModel.removeAt(j);
    }

}

bool MainBussniessView::system_setup_show(QSqlTableModel* model){
    QSqlRecord record = model->record(0);

    App::TestPapertype = record.value("testPapertype").toString();
    qDebug()<< "[system_setup_show]---TestPapertype>"<<App::TestPapertype;


    App::TestMode=record.value("testMode").toString();
    qDebug()<<"[system_setup_show]---testMode"<<App::TestMode;

    App::Language=record.value("language").toString();
     qDebug()<<"[system_setup_show]--->App::Language"<<App::Language;


    return false;
}

int MainBussniessView::getSample_Type(QList<SampleTypeModel>* lstSampleType){
    QString strSQL = "select * from SampleType_tb";
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(strSQL);
    int i = 0;
    while(query.next()){
        SampleTypeModel sampleTYpeModel ;//= new SampleTypeModel();
        sampleTYpeModel.setSampleTypeNo(query.value(0).toInt());
        sampleTYpeModel.setSampleTypeName(query.value(1).toString());
        lstSampleType->append(sampleTYpeModel);
        i++;
    }
    return i;
}



void MainBussniessView::getTest_Result(RESULT result[]){
//#define RU11-3       12
//#define RU10T        11
//#define RU12MA    13


      TestResultModel  testResultModel; //new TestResultModel();
    QList<ItemModel> lstItemModel;
    int icount = GetItemList(&lstItemModel);//item_tb_11_3

    QList<SampleTypeModel> lstSampleType;
    int sampeCount = getSample_Type(&lstSampleType);//SampleType_tb

    uint nSampleMaxNo = GetSampleMaxNo()+1;
                qDebug()<<"[getTest_Result]----->2"<<nSampleMaxNo;


    QList<ItemParameterModel> lstItemParams;

    int paramCount = GetItemParam(&lstItemParams);//ItemParameter_tb_11_3

    for(int j = 0;j < icount;j++) {


        int itemNO = ((ItemModel)lstItemModel[j]).getItemNo();
        QString strItemName = ((ItemModel)lstItemModel[j]).getItemName();
        int nRegeantModel = ((ItemModel)lstItemModel[j]).getRegeantModel();
    //qDebug()<<"[GetTestResult]"<<strItemName;
        for(int m = 0;m < paramCount;m++){
            if(lstItemParams[m].getItemName() == strItemName && lstItemParams[m].getRegeantModel() == nRegeantModel){
                testResultModel.parameterModel.setItemProperty(lstItemParams[m].getItemProperty());
                testResultModel.parameterModel.setRefMin(lstItemParams[m].getRefMin());
                testResultModel.parameterModel.setRefMax(lstItemParams[m].getRefMax());
                testResultModel.parameterModel.setUnit(lstItemParams[m].getUnit());
                testResultModel.parameterModel.setCheckWay(lstItemParams[m].getCheckWay());
                testResultModel.parameterModel.setItemName(lstItemParams[m].getItemName());
                testResultModel.parameterModel.setItemNo(lstItemParams[m].getItemNo());
               // qDebug()<<"[GetTestResult]"<<strItemName <<lstItemParams[m].getItemName() ;
                break;
            }
        }
        testResultModel.setTestWay(testResultModel.parameterModel.getCheckWay());


            for(int i = 0;i < sampeCount;i++){
                QString strSampleType = lstSampleType[i].getSampleTypeName();
                if(0 == SystemConfig::sampleType.compare(strSampleType)){
                    testResultModel.setSampleType(strSampleType);
                    break;
                }
            }

        testResultModel.setUnit(testResultModel.parameterModel.getUnit());
        testResultModel.setHatchTime(SystemConfig::hatchTime);

        testResultModel.setIsPrint(SystemConfig::isPrint);
        testResultModel.setFlag(result[j].flag);
        testResultModel.setItemNo(itemNO);

        testResultModel.setItemName(strItemName);
        lstTestResultModel.push_back(&testResultModel);

        if (0 == QString::compare("11-III",App::TestPapertype)){
           MAX_ITEM =12;
         }else   if (0 == QString::compare("10T",   App::TestPapertype)){
           MAX_ITEM = 11;
         }else if (0 == QString::compare("12MA", App::TestPapertype) ){
           MAX_ITEM = 13;
        }


        for(int i = 0;i < MAX_ITEM;i++){

            QString strItemName = lstTestResultModel[j]->getItemName();

            if(QString(result[i].name) == strItemName){
                ((TestResultModel*)lstTestResultModel[j])->setSampleNo(nSampleMaxNo);
                ((TestResultModel*)lstTestResultModel[j])->setItemName(result[i].name);
                ((TestResultModel*)lstTestResultModel[j])->setSampleValue(result[i].unit);
                ((TestResultModel*)lstTestResultModel[j])->setSampleDate(QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss"));//H:mm:ss
                ((TestResultModel*)lstTestResultModel[j])->setBarcode(App::TestPapertype);
                testResult_Save((TestResultModel*)lstTestResultModel[j]);
                //qDebug() << "Accept item :" + QString("%1").arg(result[i].name) + ",  " + QString("%2").arg(result[i].unit);       
                break;
            }
        }
        _result[j].block_num = MAX_ITEM;//MAX_ITEM 需要根据试纸型号进行修改
        _result[j].position = result[j].position;
        _result[j].mode = SystemConfig::newold_Model;
        _result[j].paper_model = SystemConfig::regeant_Model;

    }
        lstTestResultModel.clear();
        for(int n = icount -1;n >= 0;n--){
            lstItemModel.removeAt(n);
        }
        for(int n = paramCount -1;n >= 0;n--){
            lstItemParams.removeAt(n);
        }
        for(int m = sampeCount-1;m >= 0;m--){
            lstSampleType.removeAt(m);
        }
//delete testResultModel;
}


uint MainBussniessView::GetSampleMaxNo(){
    uint nMax = 0;
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(tr("select max(SampleNo) as SampleMaxNo from TestResult_tb"));
    if(0 < query.next()){
        nMax = query.value(0).toUInt();
    }
    return nMax;
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

void MainBussniessView:: PrintInformation(QByteArray arr){
    tty_thread->listWrite(arr);
}

void MainBussniessView::getCalibration(int itemNo, QString itemName){
        QSqlQuery query;

        if (0 == QString::compare("11-III",App::TestPapertype)){
                query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from Calibrate_tb_11_3 where ItemNo = %1").arg(itemNo));
                MAX_ITEM =12;
       }else   if (0 == QString::compare("10T",   App::TestPapertype)){
                query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from Calibrate_tb_10T  where ItemNo = %1").arg(itemNo));
                MAX_ITEM = 11;
        }else if (0 == QString::compare("12MA", App::TestPapertype) ){
                query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from Calibrate_tb_12MA  where ItemNo = %1").arg(itemNo));
                MAX_ITEM = 13;
        }


            if(0 < query.next()){
                _result[itemNo].mode = 1;
                _result[itemNo].paper_model = 1;
                _result[itemNo].block_num = MAX_ITEM;
                strcpy(_result[itemNo].name, (const char*)itemName.toLatin1());
                _result[itemNo].calibration[0] = query.value(1).toUInt();
                _result[itemNo].calibration[1] = query.value(2).toUInt();
                _result[itemNo].calibration[2] = query.value(3).toUInt();
                _result[itemNo].calibration[3] = query.value(4).toUInt();
                _result[itemNo].calibration[4] = query.value(5).toUInt();
                _result[itemNo].calibration[5] = query.value(6).toUInt();
                _result[itemNo].calibration[6] = query.value(7).toUInt();
                _result[itemNo].calibration[7] = query.value(8).toUInt();

                strcpy(_result[itemNo].item_value[0], (const char*)QVariant(query.value(9)).toString().toLatin1());
                strcpy(_result[itemNo].item_value[1], (const char*)QVariant(query.value(10)).toString().toLatin1());
                strcpy(_result[itemNo].item_value[2], (const char*)QVariant(query.value(11)).toString().toLatin1());
                strcpy(_result[itemNo].item_value[3], (const char*)QVariant(query.value(12)).toString().toLatin1());
                strcpy(_result[itemNo].item_value[4], (const char*)QVariant(query.value(13)).toString().toLatin1());
                strcpy(_result[itemNo].item_value[5], (const char*)QVariant(query.value(14)).toString().toLatin1());
                strcpy(_result[itemNo].item_value[6], (const char*)QVariant(query.value(15)).toString().toLatin1());
                strcpy(_result[itemNo].item_value[7], (const char*)QVariant(query.value(16)).toString().toLatin1());

        //    qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[0];
        //    qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[1];
        //    qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[2];
        //    qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[3];
        //    qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[4];
        //    qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[5];
        //   qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[6];
        //    qDebug()<< "GetCalibration---->debug" <<itemNo<<_result[itemNo].item_value[7];
         //qDebug()<< "GetCalibration---->debug"<<_result[itemNo].name;
           }
 }

int MainBussniessView::GetItemParam(QList<ItemParameterModel>* lstItemParam)
{
    QSqlQuery query;
 //qDebug()<<"[GetItemParam]"<<App::TestPapertype;

    if (0 == QString::compare("11-III",App::TestPapertype)){
         query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from ItemParameter_tb_11_3 where regeant_model = %1").arg(SystemConfig::regeant_Model));
    }else   if (0 == QString::compare("10T",   App::TestPapertype)){
        query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from ItemParameter_tb_10T where regeant_model = %1").arg(SystemConfig::regeant_Model));
    }else if (0 == QString::compare("12MA", App::TestPapertype) ){
        query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from ItemParameter_tb_12MA where regeant_model = %1").arg(SystemConfig::regeant_Model));
    }


    int i = 0;
    while(query.next()){
        ItemParameterModel parameterModel;// = new ItemParameterModel();
        parameterModel.setRegeantModel(query.value(0).toInt());
        parameterModel.setItemNo(query.value(1).toInt());
        parameterModel.setItemName(query.value(2).toString());
        parameterModel.setItemProperty(query.value(3).toString());
        parameterModel.setRefMin(query.value(4).toFloat());
        parameterModel.setRefMax(query.value(5).toFloat());
        parameterModel.setUnit(query.value(6).toString());
        parameterModel.setCheckWay(query.value(7).toString());
        lstItemParam->append(parameterModel);
        //qDebug()<<" GetItemParam" <<query.value(2).toString();
        i++;
    }
    return i;
}
void MainBussniessView::mcuPopen() {
     tty_thread->mcuUartOpen();
}
void MainBussniessView::mcuPclose() {
     tty_thread->mcuUartClose();
}


bool MainBussniessView::mcuCmd(WORK_STATE cmd)
{
            tty_thread->setCommand(cmd);
            tty_thread->start();
            App::test_finished=false;
            bool bfinished = false;

               while(!bfinished){
                            bfinished = App::test_finished;
                            tty_thread->msleep(100);
                            try {
                            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
                            }catch(...){
                            qDebug()<< "Exception....";
                            }
                 }


                tty_thread->exit();
 printf("[mcuCmd]--->%d\n",App::test_result);

    return  App::test_result;;
}

bool  MainBussniessView::powerOff()
{     MessageBox msg;
         bool ret ;

        ret = mcuCmd(POWEROFF);
        if(!ret ){
            msg.MessageBox_Info(tr("MCU communication failure!"));
         }

return ret;
}

bool MainBussniessView::askUser(){
    MessageBox msg;
   int rets ;
   rets = msg.MessageBox_Ask(tr("Do you want to turn off the power ?"));
   if(rets == 0)
       return true;
   else
      return false;
}

bool MainBussniessView::normalStart(){

    tty_thread->setCommand(ONESTEP);
    tty_thread->start();

    App::test_finished=false;
    bool bfinished = false;


               while(!bfinished){
                            App::workMode= 0x02;
                            bfinished = App::test_finished;

                            tty_thread->msleep(100);
                            try {
                            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
                            }catch(...){
                            qDebug()<< "Exception....";
                            }
                 }


    tty_thread->exit();

  //  printf("[Start]--->%d\n",App::test_result);
    return  App::test_result;
}

bool MainBussniessView::getVersion(){


    tty_thread->setCommand(GETVERSION);

    tty_thread->start();
    App::test_finished=false;
    bool bfinished = false;


               while(!bfinished){

                            bfinished = App::test_finished;

                            tty_thread->msleep(100);
                            try {
                            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
                            }catch(...){
                            qDebug()<< "Exception....";
                            }
                 }

  //  tty_thread->mcuUartClose();
    tty_thread->exit();
 printf("[getVersion]--->%d\n",App::test_result);

    return  App::test_result;;
}
bool MainBussniessView::setUp(){

    tty_thread->setCommand(SETUP);

    tty_thread->start();
    App::test_finished=false;
    bool bfinished = false;


               while(!bfinished){
                            bfinished = App::test_finished;
                            tty_thread->msleep(100);

                            try {
                            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
                            }catch(...){
                            qDebug()<< "Exception....";
                            }
                 }

//    tty_thread->mcuUartClose();
    tty_thread->exit();
 printf("[ setUp]--->%d\n",App::test_result);

    return  App::test_result;;
}



bool MainBussniessView::Stop(){


  tty_thread->setCommand(STOPR);

  tty_thread->start();
  App::test_finished=false;
  bool bfinished = false;

  while(!bfinished){

               bfinished = App::test_finished;

               tty_thread->msleep(100);
               try {
               QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
               }catch(...){
               qDebug()<< "Exception....";
               }
    }

//tty_thread->mcuUartClose();
tty_thread->exit();
printf("[Stop]--->%d\n",App::test_result);


    return App::test_result;
}




//--------------------------------------------------------------------------------
bool MainBussniessView::calibrationTest(QString mItemName){

                Name_tmp = mItemName;
                tty_thread->setCommand(ONESTEP);
                tty_thread->start();

                App::test_finished=false;
                bool bfinished = false;

               while(!bfinished){
                            App::workMode= 0x01;
                            bfinished = App::test_finished;

                            tty_thread->msleep(100);
                            try {
                            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
                            }catch(...){
                            qDebug()<< "Exception....";
                            }
                 }


    tty_thread->exit();

    printf("[calibrationTest ]--->ret:%d\n",App::test_result);
    return  App::test_result;
}



void MainBussniessView::showTtyData(QString str)
{
     qDebug() << "[showTtyData]-->"<< str ;
}

void MainBussniessView::showTtyAck(unsigned char state)
{
    switch ( state )
    {
//            case  R_VERSION:
//            break;

//            case R_SELFEX:
//            break;

//            case R_OFW:
//            break;

//            case R_ETW:
//            break;

//            case R_SETUP:
//            break;

//            case R_ONESTEP:
//            break;

            case R_RESET:
                emit reset_signal();
            break;

//            case R_ERR_1:
//            break;

//            case R_WhiteBalance:
//            break;

    case R_STOP:
             tty_thread->commandSend(RESET);
           break;


    case R_POWROFF:
                emit Spoweroff();
           break;


          default:break;

    }
}

void MainBussniessView::sTimeSlot( int st){
    emit mTime(st);
}

void MainBussniessView::showWb(WRGB_DAT wrgb_data)// rec wb
{
    QString w,r,g,b;

    w =  QString::number(wrgb_data.W, 10);
    r  =  QString::number(wrgb_data.R, 10);
    g =  QString::number(wrgb_data.G, 10);
    b =  QString::number(wrgb_data.B, 10);

    _result[0].white_value[0]=wrgb_data.W;
    _result[0].white_value[1]=wrgb_data.R;
    _result[0].white_value[2]=wrgb_data.G;
    _result[0].white_value[3]=wrgb_data.B;
}


void MainBussniessView::showWrgb(WRGB_DAT wrgb_data,unsigned int count) {

        _result[count].wrgb_value[0] = wrgb_data.W;
        _result[count].wrgb_value[1] = wrgb_data.R;
        _result[count].wrgb_value[2] = wrgb_data.G;
        _result[count].wrgb_value[3] = wrgb_data.B;


            if(count==0 && App::workMode==0x01) {

                _result[0].white_value[0] =  App::white_value[0];
                _result[0].white_value[1] =  App::white_value[1];
                _result[0].white_value[2] =  App::white_value[2];
                _result[0].white_value[3] =  App::white_value[3];

                calibrationShow(_result);
            }

            else  if  (count==0 && App::workMode==0x02)
            {
                cac.interval_Calculation(_result);
                qDebug() << "Show result:" + QString(_result[0].name) + QString(_result[0].unit) + QString(_result[0].position);
                getTest_Result(_result);
                showTest_Result();
            }

}

void MainBussniessView::calibrationQuery(QString name){

m_DatabaseHelper->ExecuteQueryModel(calibrateObserveTableModel,
tr("select  ItemName,CalibrateValue,ResultValue,White,Red,Green,Blue,CalibrateDate from Calibrate_Oberservable_tb where  ItemName= '%1' order by CalibrateDate>'%2' desc,rowid desc").arg(name).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));

calibrateObserveTableModel->setHeaderData(0,Qt::Horizontal,tr("Item"));
calibrateObserveTableModel->setHeaderData(1,Qt::Horizontal,tr("Calibration"));
calibrateObserveTableModel->setHeaderData(2,Qt::Horizontal,tr("Result"));

calibrateObserveTableModel->setHeaderData(3,Qt::Horizontal,tr("White"));
calibrateObserveTableModel->setHeaderData(4,Qt::Horizontal,tr("Red"));
calibrateObserveTableModel->setHeaderData(5,Qt::Horizontal,tr("Green"));
calibrateObserveTableModel->setHeaderData(6,Qt::Horizontal,tr("Blue"));
calibrateObserveTableModel->setHeaderData(7,Qt::Horizontal,tr("Date"));
emit CalibrateObserverveResult(calibrateObserveTableModel);

}

void MainBussniessView::calibrationShow(struct RESULT _result[]){

    CalibrateObserverModel * resultModel = new CalibrateObserverModel();
    cac.interval_Calculation(_result);

    struct resultRGB  tmp;
    cac.get_CalculationResult(_result,Name_tmp,&tmp);

    printf("[calibrationShow]: W:%d , R:%d , G:%d  , B:%d ,result:%d, unit:%s\n",tmp.W,tmp.R,tmp.G,tmp.B,tmp.Result,tmp.unit);


    resultModel->setWhite(tmp.W);
    resultModel->setRed(tmp.R);
    resultModel->setGreen(tmp.G);
    resultModel->setBlue(tmp.B);
    resultModel->setCalibrateValue(tmp.Result);
    resultModel->setItemNo(App::serialNumber);
    realTime_NuSave();
    resultModel->setItemName(QString(Name_tmp));
    QString ResultValue = QString(QLatin1String(tmp.unit));

    resultModel->setResultValue(QString(ResultValue));
    resultModel->setCalibrateDate(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    calibrationResult_Save(resultModel);
    calibrationResult_Show(resultModel);

    delete resultModel;
}



//-------------------------------------------------------------------------------------------------------------------------------------结果显示
void MainBussniessView::showTest_Result(){


         m_DatabaseHelper->ExecuteQueryModel(showTabeTest, tr("select SampleNo, ItemName, SampleValue, Unit,TbType, SampleDate from TestResult_tb where SampleNo > '0' order by SampleNo desc,rowid asc"));
//else
//         m_DatabaseHelper->ExecuteQueryModel(showTabeTest, tr("select SampleNo, ItemName, SampleValue, Unit,TbType, rowid from TestResult_tb where SampleDate = '%1' order by SampleNo desc,rowid asc"));
//        int rowCount = showTabelModel->rowCount();
//        for(int i=0; i<rowCount; i++){
//            qDebug()
//                      <<showTabelModel->record(i).value(0).toString()
//                      <<"="
//                     <<showTabelModel->record(i).value(1).toString()
//                     <<"="
//                    <<showTabelModel->record(i).value(2).toString()
//                    <<"="
//                   <<showTabelModel->record(i).value(3).toString()
//                   <<"="
//                  <<showTabelModel->record(i).value(4).toString()
//                  <<"="
//                 <<showTabelModel->record(i).value(5).toString()
//                 <<"="
//                   ;
//        }
            showTabeTest->setHeaderData(0,Qt::Horizontal,tr("No"));
            showTabeTest->setHeaderData(1,Qt::Horizontal,tr("Item"));
            showTabeTest->setHeaderData(2,Qt::Horizontal,tr("Result"));
            showTabeTest->setHeaderData(3,Qt::Horizontal,tr("Unit"));
            showTabeTest->setHeaderData(4,Qt::Horizontal,tr("Strip"));
            showTabeTest->setHeaderData(5,Qt::Horizontal,tr("Date"));
            // showTabelModel->setHeaderData(5,Qt::Horizontal,tr("样本类型"));
            // showTabelModel->setHeaderData(6,Qt::Horizontal,tr("条码"));
            // showTabelModel->setHeaderData(7,Qt::Horizontal,tr("孵育时间"));
            //  showTabelModel->setHeaderData(8,Qt::Horizontal,tr("是否打印"));
            //showTabelModel->setHeaderData(4,Qt::Horizontal,tr("项目编号"));
            //showTabelModel->setHeaderData(8,Qt::Horizontal,tr("测试方法"));
            //showTabelModel->setHeaderData(11,Qt::Horizontal,tr("标志"));
        emit testResult(showTabeTest);
}


MainBussniessView::~MainBussniessView(){

    if(m_DatabaseHelper != NULL){
        delete m_DatabaseHelper;
        m_DatabaseHelper = NULL;
    }
    if(sampleTypeTableModel != NULL){
        delete sampleTypeTableModel;
        sampleTypeTableModel = NULL;
    }
    if(sampleTableModel != NULL){
        delete sampleTableModel;
        sampleTableModel = NULL;
    }
    if(itemTableModel != NULL){
        delete itemTableModel;
        itemTableModel = NULL;
    }
    if(patientTableModel != NULL){
        delete patientTableModel;
        patientTableModel = NULL;
    }
    if(showTabelModel != NULL){
        delete showTabelModel;
        showTabelModel = NULL;
    }
    if(qcItemTableModel != NULL){
        delete qcItemTableModel;
        qcItemTableModel = NULL;
    }
    if(queryTableModel != NULL){
        delete queryTableModel;
        queryTableModel = NULL;
    }
    if(calibrateObserveTableModel != NULL){
        delete calibrateObserveTableModel;
        calibrateObserveTableModel = NULL;
    }

    if(testdeleteTableModel != NULL){
        delete testdeleteTableModel;
        testdeleteTableModel = NULL;
    }

}


void MainBussniessView::Query_SampleResult(int sampleNo, QString sBeginDate, QString sEndDate){

    QString strSQL = (tr("SampleNo >= ' %1'   and    SampleDate > '%2' and SampleDate < '%3'").arg(sampleNo).arg(sBeginDate).arg(sEndDate));

    if(sampleTableModel != NULL){
        delete sampleTableModel;
           qDebug()<<" Query_SampleResult delete...";
    }
    sampleTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(sampleTableModel, ("TestResult_tb"), strSQL);
    sampleTableModel->setHeaderData(0,Qt::Horizontal,tr("No"));
    sampleTableModel->setHeaderData(1,Qt::Horizontal,tr("Reaction time"));
    sampleTableModel->setHeaderData(2,Qt::Horizontal,tr("Result"));
    sampleTableModel->setHeaderData(3,Qt::Horizontal,tr("species"));
    sampleTableModel->setHeaderData(4,Qt::Horizontal,tr("No"));
    sampleTableModel->setHeaderData(5,Qt::Horizontal,tr("Item"));
    sampleTableModel->setHeaderData(6,Qt::Horizontal,tr("Unit"));
    sampleTableModel->setHeaderData(7,Qt::Horizontal,tr("Strip"));
    sampleTableModel->setHeaderData(8,Qt::Horizontal,tr("Test mode"));
    sampleTableModel->setHeaderData(9,Qt::Horizontal,tr("Time"));
    sampleTableModel->setHeaderData(10,Qt::Horizontal,tr("printf"));
    sampleTableModel->setHeaderData(11,Qt::Horizontal,tr("flag"));
    emit SampleResult(sampleTableModel);
}



void MainBussniessView::Query_SampleResult_no(int sampleNo, QString sBeginDate, QString sEndDate){
    QString strSQL = (tr("SampleNo = %1 and SampleDate >= '%2' and SampleDate <= '%3'").arg(sampleNo).arg(sBeginDate).arg(sEndDate));

    if(sampleTableModel != NULL){
        qDebug()<<" Query_SampleResult_no delete...";
        delete  sampleTableModel;
    }
    sampleTableModel  = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(sampleTableModel, tr("TestResult_tb"), strSQL);
    sampleTableModel->setHeaderData(0,Qt::Horizontal,tr("No"));
    sampleTableModel->setHeaderData(1,Qt::Horizontal,tr("Reaction time"));
    sampleTableModel->setHeaderData(2,Qt::Horizontal,tr("Result"));
    sampleTableModel->setHeaderData(3,Qt::Horizontal,tr("species"));
    sampleTableModel->setHeaderData(4,Qt::Horizontal,tr("No"));
    sampleTableModel->setHeaderData(5,Qt::Horizontal,tr("Item"));
    sampleTableModel->setHeaderData(6,Qt::Horizontal,tr("Unit"));
    sampleTableModel->setHeaderData(7,Qt::Horizontal,tr("Strips"));
    sampleTableModel->setHeaderData(8,Qt::Horizontal,tr("testing"));
    sampleTableModel->setHeaderData(9,Qt::Horizontal,tr("Time"));
    sampleTableModel->setHeaderData(10,Qt::Horizontal,tr("printf"));
    sampleTableModel->setHeaderData(11,Qt::Horizontal,tr("flag"));
    emit SampleResult(sampleTableModel);
}


int MainBussniessView::GetItemList(QList<ItemModel>* lstItem){
  QString strSQL;
  //qDebug()<<"[GetItemList]"<<App::TestPapertype;
  if (0 == QString::compare("11-III",App::TestPapertype)){
      strSQL = QObject::tr("select * from item_tb_11_3 where regeant_model = %1").arg(SystemConfig::regeant_Model);
  }else if (0 == QString::compare("10T",App::TestPapertype)){
      strSQL = QObject::tr("select * from item_tb_10T where regeant_model = %1").arg(SystemConfig::regeant_Model);
  }else if (0 == QString::compare("12MA",App::TestPapertype)){
      strSQL = QObject::tr("select * from item_tb_12MA where regeant_model = %1").arg(SystemConfig::regeant_Model);
  }

    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(strSQL);
    int i = 0;
    while(query.next()){
        ItemModel itemModel ;//= new ItemModel();
        itemModel.setRegeantModel(query.value(0).toInt());
        itemModel.setItemNo(query.value(1).toInt());
        itemModel.setItemName(query.value(2).toString());
        lstItem->append(itemModel);
        qDebug()<<"debug----->GetItemList"<< query.value(0).toInt() << query.value(1).toInt() <<query.value(2).toString() ;
        i++;
    }
    return i;
}
int MainBussniessView::GetItemNoByItemName_11_3(QString itemName){
    int itemNo = 0;
    QSqlQuery record = m_DatabaseHelper->ExecuteSqlQuery(QObject::tr("select * from item_tb_11_3 where ItemName = '%1' and regeant_model = %2").arg(itemName).arg(SystemConfig::regeant_Model));
    if(record.next()){
        itemNo = record.value(1).toInt();
    }
    return itemNo;
}

int MainBussniessView::GetItemNoByItemName_10T(QString itemName){
    int itemNo = 0;
    QSqlQuery record = m_DatabaseHelper->ExecuteSqlQuery(QObject::tr("select * from item_tb_10T where ItemName = '%1' and regeant_model = %2").arg(itemName).arg(SystemConfig::regeant_Model));
    if(record.next()){
        itemNo = record.value(1).toInt();
    }
    return itemNo;
}

int MainBussniessView::GetItemNoByItemName_12MA(QString itemName){
    int itemNo = 0;
    QSqlQuery record = m_DatabaseHelper->ExecuteSqlQuery(QObject::tr("select * from item_tb_12MA where ItemName = '%1' and regeant_model = %2").arg(itemName).arg(SystemConfig::regeant_Model));
    if(record.next()){
        itemNo = record.value(1).toInt();
    }
    return itemNo;
}


void MainBussniessView::GetItemName_11_3(QSqlQueryModel *tableModel){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, tr("select ItemName from item_tb_11_3 where regeant_model = %1").arg(SystemConfig::regeant_Model));//11-3
    return;
}

void MainBussniessView::GetItemName_10T(QSqlQueryModel *tableModel){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, tr("select ItemName from item_tb_10T where regeant_model = %1").arg(SystemConfig::regeant_Model));
    return;
}
void MainBussniessView::GetItemName_12MA(QSqlQueryModel *tableModel){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, tr("select ItemName from item_tb_12MA where regeant_model = %1").arg(SystemConfig::regeant_Model));
    return;
}




void MainBussniessView::Calibrate_Query_11_3(QSqlQueryModel *tableModel, int nItemNo){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, QObject::tr("select * from Calibrate_tb_11_3 where ItemNo = %1").arg(nItemNo));
    return;
}
void MainBussniessView::Calibrate_Query_10T(QSqlQueryModel *tableModel, int nItemNo){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, QObject::tr("select * from Calibrate_tb_10T where ItemNo = %1").arg(nItemNo));
    return;
}
void MainBussniessView::Calibrate_Query_12MA(QSqlQueryModel *tableModel, int nItemNo){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, QObject::tr("select * from Calibrate_tb_12MA where ItemNo = %1").arg(nItemNo));
    return;
}





void MainBussniessView::calibrateSave(CalibrateModel calibrateModel){

        QSqlTableModel calibrateTableModel;// = new QSqlTableModel();

     if (0 == QString::compare("11-III",App::TestPapertype)){
        m_DatabaseHelper->ExecuteTableModel(&calibrateTableModel, tr("Calibrate_tb_11_3"), QObject::tr("ItemNo = %1").arg(calibrateModel.getItemNo()));
    }else   if (0 == QString::compare("10T",   App::TestPapertype)){
        m_DatabaseHelper->ExecuteTableModel(&calibrateTableModel, tr("Calibrate_tb_10T"), QObject::tr("ItemNo = %1").arg(calibrateModel.getItemNo()));
     }else if (0 == QString::compare("12MA", App::TestPapertype) ){
        m_DatabaseHelper->ExecuteTableModel(&calibrateTableModel, tr("Calibrate_tb_12MA"), QObject::tr("ItemNo = %1").arg(calibrateModel.getItemNo()));
     }

    QSqlRecord record = calibrateTableModel.record();
    if(calibrateTableModel.rowCount() == 0){
        record.setValue("ItemNo",calibrateModel.getItemNo());
        record.setValue("CalibrateValue0",calibrateModel.getCalibrateValue0());
        record.setValue("CalibrateValue1",calibrateModel.getCalibrateValue1());
        record.setValue("CalibrateValue2",calibrateModel.getCalibrateValue2());
        record.setValue("CalibrateValue3",calibrateModel.getCalibrateValue3());
        record.setValue("CalibrateValue4",calibrateModel.getCalibrateValue4());
        record.setValue("CalibrateValue5",calibrateModel.getCalibrateValue5());
        record.setValue("CalibrateValue6",calibrateModel.getCalibrateValue6());
        record.setValue("CalibrateValue7",calibrateModel.getCalibrateValue7());

        record.setValue("ResultValue0",calibrateModel.getLaderValue0());
        record.setValue("ResultValue1",calibrateModel.getLaderValue1());
        record.setValue("ResultValue2",calibrateModel.getLaderValue2());
        record.setValue("ResultValue3",calibrateModel.getLaderValue3());
        record.setValue("ResultValue4",calibrateModel.getLaderValue4());
        record.setValue("ResultValue5",calibrateModel.getLaderValue5());
        record.setValue("ResultValue6",calibrateModel.getLaderValue6());
        record.setValue("ResultValue7",calibrateModel.getLaderValue7());
        calibrateTableModel.insertRecord(0,record);
        calibrateTableModel.submitAll();
    }
    else
    {
        calibrateTableModel.database().transaction(); //开始事务操作
        record.setValue("ItemNo",calibrateModel.getItemNo());
        record.setValue("CalibrateValue0",calibrateModel.getCalibrateValue0());
        record.setValue("CalibrateValue1",calibrateModel.getCalibrateValue1());
        record.setValue("CalibrateValue2",calibrateModel.getCalibrateValue2());
        record.setValue("CalibrateValue3",calibrateModel.getCalibrateValue3());
        record.setValue("CalibrateValue4",calibrateModel.getCalibrateValue4());
        record.setValue("CalibrateValue5",calibrateModel.getCalibrateValue5());
        record.setValue("CalibrateValue6",calibrateModel.getCalibrateValue6());
        record.setValue("CalibrateValue7",calibrateModel.getCalibrateValue7());

        record.setValue("ResultValue0",calibrateModel.getLaderValue0());
        record.setValue("ResultValue1",calibrateModel.getLaderValue1());
        record.setValue("ResultValue2",calibrateModel.getLaderValue2());
        record.setValue("ResultValue3",calibrateModel.getLaderValue3());
        record.setValue("ResultValue4",calibrateModel.getLaderValue4());
        record.setValue("ResultValue5",calibrateModel.getLaderValue5());
        record.setValue("ResultValue6",calibrateModel.getLaderValue6());
        record.setValue("ResultValue7",calibrateModel.getLaderValue7());
        calibrateTableModel.setRecord(0,record);
        if (calibrateTableModel.submitAll()) {
            calibrateTableModel.database().commit(); //提交
        } else {
            calibrateTableModel.database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    //delete calibrateTableModel;

}


void MainBussniessView::testResult_Save(TestResultModel* resultModel){

    QSqlTableModel testTableModel;
    m_DatabaseHelper->ExecuteTableModel(&testTableModel, tr("TestResult_tb"), QObject::tr("where SampleNo = :SampleNo and ItemName = :ItemName and SampleDate = :SampleDate").arg(resultModel->getSampleNo()).arg(resultModel->getItemName()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));

    QSqlRecord record = testTableModel.record();
    if(testTableModel.rowCount() == 0){

        record.setValue("SampleNo", resultModel->getSampleNo());
        record.setValue("HatchTime", resultModel->getHatchTime());
        record.setValue("SampleValue", resultModel->getSampleValue());
        record.setValue("SampleType", resultModel->getSampleType());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        record.setValue("Unit", resultModel->getUnit());
        record.setValue("TbType", resultModel->getBarcode());
        record.setValue("TestWay", resultModel->getTestWay());
        record.setValue("SampleDate", resultModel->getSampleDate());
        record.setValue("IsPrint", resultModel->getIsPrint());
        record.setValue("Flag", resultModel->getFlag());
        testTableModel.insertRecord(0,record);
        testTableModel.submitAll();
    }
    else
    {
        testTableModel.database().transaction(); //开始事务操作
        record.setValue("SampleNo", resultModel->getSampleNo());
        record.setValue("HatchTime", resultModel->getHatchTime());
        record.setValue("SampleValue", resultModel->getSampleValue());
        record.setValue("SampleType", resultModel->getSampleType());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        record.setValue("Unit", resultModel->getUnit());
        record.setValue("TbType", resultModel->getBarcode());
        record.setValue("TestWay", resultModel->getTestWay());
        record.setValue("SampleDate", resultModel->getSampleDate());
        record.setValue("IsPrint", resultModel->getIsPrint());
        record.setValue("Flag", resultModel->getFlag());
        testTableModel.setRecord(0,record);
        if (testTableModel.submitAll()) {
            qDebug() <<"debug---->TestResultSave-->3";
            testTableModel.database().commit(); //提交
        } else {
            testTableModel.database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
 //   delete testTableModel;
}

void  MainBussniessView::getSystem_species(){
    m_DatabaseHelper->ExecuteQueryModel(showTabelModel, tr("select  species from  system_setup_species"));
    emit system_Species(showTabelModel);
}

void MainBussniessView::getSystem_language(){
    m_DatabaseHelper->ExecuteQueryModel(showTabelModel, tr("select  language from  system_setup_language"));
    emit system_Language(showTabelModel);
}

void MainBussniessView::getSystem_testMode(){
    m_DatabaseHelper->ExecuteQueryModel(showTabelModel, tr("select  testMode from  system_setup_testMode"));
    emit system_testMode(showTabelModel);
}

void MainBussniessView::getSystem_testPapertype(){
    m_DatabaseHelper->ExecuteQueryModel(showTabelModel, tr("select  testPapertype from  system_setup_testPapertype"));
    emit system_testPapertype(showTabelModel);
}


void MainBussniessView::getSystem_status(){
    m_DatabaseHelper->ExecuteQueryModel(showTabelModel, tr("select id , species ,testPapertype, language , testMode , serialNumber from  system_setup"));
    emit system_Setup(showTabelModel);
}

void MainBussniessView::realTime_NuSave(){
    QSqlTableModel systemTableModel ;
    m_DatabaseHelper->ExecuteTableModel(&systemTableModel, tr("system_setup"),QObject::tr(""));
   systemTableModel.setData(systemTableModel.index(0,5),App::serialNumber);
   systemTableModel.submitAll();
}

void MainBussniessView::systemStatus_Save()
{
    QSqlTableModel systemTableModel ;//= new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(&systemTableModel, tr("system_setup"),QObject::tr(""));

   emit  system_saveok();

systemTableModel.setData(systemTableModel.index(0,1),App::Species);
systemTableModel.setData(systemTableModel.index(0,2),App::TestPapertype);
systemTableModel.setData(systemTableModel.index(0,3),App::Language);
systemTableModel.setData(systemTableModel.index(0,4),App::TestMode);
systemTableModel.setData(systemTableModel.index(0,5),App::serialNumber);

    emit languageConversion();
    if(!(systemTableModel.submitAll()))  {
         qDebug()<<"submit all fail";
      }

}

void MainBussniessView::calibrationResult_Save(CalibrateObserverModel* resultModel){

    QSqlTableModel whiteTableModel ;//= new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(&whiteTableModel, tr("Calibrate_Oberservable_tb"), QObject::tr("where ItemName = :ItemName and CalibrateDate = :CalibrateDate").arg(resultModel->getItemName()).arg(resultModel->getCalibrateDate()));
    QSqlRecord record = whiteTableModel.record();

    if(whiteTableModel.rowCount() == 0){
        record.setValue("White", resultModel->getWhite());
        record.setValue("Red", resultModel->getRed());
        record.setValue("Green", resultModel->getGreen());
        record.setValue("Blue", resultModel->getBlue());
        record.setValue("CalibrateValue", resultModel->getCalibrateValue());
        record.setValue("ResultValue", resultModel->getResultValue());
        record.setValue("CalibrateDate", resultModel->getCalibrateDate());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        whiteTableModel.insertRecord(0,record);
        whiteTableModel.submitAll();
    }
    else
    {
        whiteTableModel.database().transaction(); //开始事务操作
        record.setValue("White", resultModel->getWhite());
        record.setValue("Red", resultModel->getRed());
        record.setValue("Green", resultModel->getGreen());
        record.setValue("Blue", resultModel->getBlue());
        record.setValue("CalibrateValue", resultModel->getCalibrateValue());
        record.setValue("ResultValue", resultModel->getResultValue());
        record.setValue("CalibrateDate", resultModel->getCalibrateDate());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        whiteTableModel.setRecord(0,record);
        if (whiteTableModel.submitAll()) {
            whiteTableModel.database().commit(); //提交
        } else {
            whiteTableModel.database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
  //  delete whiteTableModel;
}


void MainBussniessView::calibrationResult_Show(CalibrateObserverModel* resultModel){

 m_DatabaseHelper->ExecuteQueryModel(calibrateObserveTableModel,
 tr("select  ItemName,CalibrateValue,ResultValue,White,Red,Green,Blue,CalibrateDate from Calibrate_Oberservable_tb where  ItemName= '%1' order by CalibrateDate>'%2' desc,rowid desc").arg(resultModel->getItemName()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));

        calibrateObserveTableModel->setHeaderData(0,Qt::Horizontal, tr("Item"));
        calibrateObserveTableModel->setHeaderData(1,Qt::Horizontal, tr("Calibration"));
        calibrateObserveTableModel->setHeaderData(2,Qt::Horizontal, tr("Result"));
        calibrateObserveTableModel->setHeaderData(3,Qt::Horizontal, tr("White"));
        calibrateObserveTableModel->setHeaderData(4,Qt::Horizontal, tr("Red"));
        calibrateObserveTableModel->setHeaderData(5,Qt::Horizontal, tr("Green"));
        calibrateObserveTableModel->setHeaderData(6,Qt::Horizontal, tr("Blue"));
        calibrateObserveTableModel->setHeaderData(7,Qt::Horizontal, tr("Time"));
        calibrateObserveTableModel->setHeaderData(8,Qt::Horizontal,tr("No"));
        emit CalibrateObserverveResult(calibrateObserveTableModel);
}


void MainBussniessView::calibrationDelete_Result(QString sItemName){//delete from calibrate_oberservable_tb where ItemName = 'BIL' and CalibrateDate='2018-10-24 11:31:08'
    QString strSQL = (QObject::tr("delete from calibrate_oberservable_tb where ItemName = '%1'").arg(sItemName));
    m_DatabaseHelper->ExecuteInt(strSQL);

    strSQL = (QObject::tr("ItemName = '%1'").arg(sItemName));

    m_DatabaseHelper->ExecuteTableModel(calibrateObserveTableModel, ("Calibrate_Oberservable_tb"), strSQL);


    calibrateObserveTableModel->setHeaderData(0,Qt::Horizontal,tr("Item"));
    calibrateObserveTableModel->setHeaderData(1,Qt::Horizontal,tr("calibration"));
    calibrateObserveTableModel->setHeaderData(2,Qt::Horizontal,tr("Result"));
    calibrateObserveTableModel->setHeaderData(3,Qt::Horizontal,tr("White"));
    calibrateObserveTableModel->setHeaderData(4,Qt::Horizontal,tr("Red"));
    calibrateObserveTableModel->setHeaderData(5,Qt::Horizontal,tr("Green"));
    calibrateObserveTableModel->setHeaderData(6,Qt::Horizontal,tr("Blue"));
    calibrateObserveTableModel->setHeaderData(7,Qt::Horizontal,tr("Time"));
    calibrateObserveTableModel->setHeaderData(8,Qt::Horizontal,tr("No"));

    emit CalibrateObserverveResult(calibrateObserveTableModel);
}

void MainBussniessView::testDelete_Result(){
    QString strSQL = (QObject::tr("delete from TestResult_tb where SampleNo >= '%1'").arg(0));
  m_DatabaseHelper->ExecuteInt(strSQL);
   strSQL = (QObject::tr("SampleNo  >= '%1'").arg(1));

    m_DatabaseHelper->ExecuteTableModel(testdeleteTableModel, tr("TestResult_tb"), strSQL);

    testdeleteTableModel->setHeaderData(0,Qt::Horizontal, tr("No"));

    testdeleteTableModel->setHeaderData(1,Qt::Horizontal, tr("Reaction time"));

    testdeleteTableModel->setHeaderData(2,Qt::Horizontal, tr("Result"));

    testdeleteTableModel->setHeaderData(3,Qt::Horizontal, tr("类型"));

    testdeleteTableModel->setHeaderData(4,Qt::Horizontal, tr("项目编号"));

    testdeleteTableModel->setHeaderData(5,Qt::Horizontal, tr("Item"));

    testdeleteTableModel->setHeaderData(6,Qt::Horizontal, tr("Unit"));

    testdeleteTableModel->setHeaderData(7,Qt::Horizontal, tr("Strip"));

    testdeleteTableModel->setHeaderData(8,Qt::Horizontal, tr("测试方法"));

    testdeleteTableModel->setHeaderData(9,Qt::Horizontal, tr("Time"));

    testdeleteTableModel->setHeaderData(10,Qt::Horizontal, tr("是否打印"));

    testdeleteTableModel->setHeaderData(11,Qt::Horizontal, tr("标志"));

    emit SampleResult(testdeleteTableModel);
    showTest_Result();
}


void MainBussniessView::buzzer(){
   system("echo 100  > /sys/class/leds/beeper-pwm/brightness");
   usleep(500*4);
   system("echo 0 > /sys/class/leds/beeper-pwm/brightness");
}
