#include "mainbussniessview.h"
#include <databasehelper.h>
#include <QMessageBox>
//#include <testingthread.h>
#include <QDateTime>
//#include<QVariant>

#include <QProgressDialog>
#include<QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <qmath.h>
#include <qlibrary.h>
#include"testresultmodel.h"
#include <QTranslator>
#include <QtDebug>
//#include <myhelper.h>
#include<assert.h>
//#include <stopthread.h>
///#include <whitethread.h>
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

    sampleTableModel = NULL;

    whiteTableModel = NULL;
    pTestingThread = NULL;
    stopThread = NULL;
    whiteThread = NULL;
    m_lib = NULL;
    patientTableModel = NULL;
    sampleTypeTableModel = NULL;
    showTabelModel = NULL;
    qcItemTableModel = NULL;
    queryTableModel = NULL;
    calibrateObserveTableModel = NULL;
    itemTableModel = NULL;
    deleteTableModel = NULL;
    showTabelModel = new QSqlTableModel();
    calibrateObserveTableModel = new QSqlTableModel();
    Machine_Inital();
#ifndef TEST_SO
    int nResult = Machine_Reset();
    if(0 == nResult){
        myHelper::ShowMessageBoxError(tr("初始化失败, 重启机器!"));
        system("reboot");
        return;
    }
#endif
    Initalize();
    //lstTestResultModel = new QList<TestResultModel*>();
}
void MainBussniessView::Initalize(){
    // = new QList<ItemModel>();
    int icount = GetItemList(&lstItemModel);
    for(int i = 0;i < icount;i++){
        int itemNO = lstItemModel[i].getItemNo();
        QString strItemName = lstItemModel[i].getItemName();
        GetCalibration(itemNO, strItemName);
        qDebug() << strItemName;
    }
    for(int j = icount-1;j >= 0;j--){
        lstItemModel.removeAt(j);
    }
}

QList<ItemModel> MainBussniessView::getItemModel(){
    return lstItemModel;
}

void MainBussniessView::Machine_Inital(){

    #ifdef TEST_SO
        m_lib = new QLibrary("/lib/libtest.so.1.0.0");//://image/libtest.so.1.0.0
    #else
        m_lib = new QLibrary("/lib/libuart_init.so");
    #endif
    m_lib->load();
    if(m_lib->isLoaded()){
    #ifdef TEST_SO
        _Run = NULL;
        _Run = (RUN)m_lib->resolve("run");
        if(_Run != NULL){
            int ii = _Run(_result);
        }

        qDebug() << "load library successfull!";
    #else
        _Inital = NULL;
        _Inital = (INITAL)m_lib->resolve("uart_init");
        if(_Inital != NULL){
            int ii = _Inital();
        }
    #endif
    }
}
int MainBussniessView::Machine_Power(){
    int nResult = 0;
#ifndef TEST_SO
    _Power = NULL;
    _Power = (POWER)m_lib->resolve("power");
    if(_Power != NULL){
        nResult = _Power();
    }
#endif
    return nResult;
}

int MainBussniessView::Machine_Stop(){
    int nResult = 0;
#ifndef TEST_SO
    _Stop = NULL;
    _Stop = (STOP)m_lib->resolve("stop");
    if(_Stop != NULL){
        nResult = _Stop();
    }
#endif
    return nResult;
}

int MainBussniessView::Machine_Go_on(){
    int nResult = 0;
#ifndef TEST_SO
    _Reset = NULL;
    _Reset = (RESET)m_lib->resolve("go_on");
    if(_Reset != NULL){
        nResult = _Reset();
    }
#endif
    return nResult;
}

int MainBussniessView::Machine_White(struct RESULT buf[]){
    int nResult = 0;
#ifndef TEST_SO
    _White = NULL;
    _White = (WHITE)m_lib->resolve("white");
    if(_White != NULL){
        nResult = _White(buf);
    }
#endif
    return nResult;
}

int MainBussniessView::Machine_Run(struct RESULT buf[]){
    int nResult = 0;
    _Run = NULL;
    _Run = (RUN)m_lib->resolve("run");
    if(_Run != NULL){
        nResult = _Run(buf);
    }
    return nResult;
}

int MainBussniessView::Machine_Sys_Status(){
    int nResult = 0;
    _Sys_status = NULL;
    _Sys_status = (SYS_STATUS)m_lib->resolve("system_state");
    if(_Sys_status != NULL){
        nResult = _Sys_status();
    }
    return nResult;
}

int MainBussniessView:: Machine_Reset(){
    int nResult = 0;
    _Reset = NULL;
    _Reset = (RESET)m_lib->resolve("reset");
    if(_Reset != NULL){
        nResult = _Reset();
    }
    return nResult;
}
int MainBussniessView::GetSampleType(QList<SampleTypeModel>* lstSampleType){
    QString strSQL = "select * from SampleType_tb";
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(strSQL);
    int i = 0;
    while(query.next()){
        SampleTypeModel* sampleTYpeModel = new SampleTypeModel();
        sampleTYpeModel->setSampleTypeNo(query.value(0).toInt());
        sampleTYpeModel->setSampleTypeName(query.value(1).toString());
        lstSampleType->append(*sampleTYpeModel);
        i++;
    }
    return i;
}

QList<TestResultModel*> MainBussniessView::QueryTestResult(QString strWhere){
    QString strSQL = "select * from TestResult_tb" + strWhere;
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(strSQL);
    lstTestResultModel.clear();
    while(query.next()){
        TestResultModel* testResultModel = new TestResultModel();
        testResultModel->setSampleNo(query.value(0).toInt());
        testResultModel->setSampleDate(query.value(1).toString());
        testResultModel->setItemName(query.value(2).toString());
        testResultModel->setSampleValue(query.value(3).toString());
        testResultModel->setUnit(query.value(4).toString());

        lstTestResultModel.push_back(testResultModel);
    }
    return lstTestResultModel;
}

void MainBussniessView::GetTestResult(RESULT result[]){
    QList<ItemModel> lstItemModel;// = new QList<ItemModel>();
    int icount = GetItemList(&lstItemModel);
    QList<SampleTypeModel> lstSampleType; //= new QList<SampleTypeModel>();
    int sampeCount = GetSampleType(&lstSampleType);
    uint nSampleMaxNo = GetSampleMaxNo()+1;
    QList<ItemParameterModel> lstItemParams;
    int paramCount = GetItemParam(&lstItemParams);
    for(int j = 0;j < icount;j++) {
        TestResultModel* testResultModel = new TestResultModel();
        int itemNO = ((ItemModel)lstItemModel[j]).getItemNo();
        QString strItemName = ((ItemModel)lstItemModel[j]).getItemName();
        int nRegeantModel = ((ItemModel)lstItemModel[j]).getRegeantModel();
        for(int m = 0;m < paramCount;m++){
            if(lstItemParams[m].getItemName() == strItemName && lstItemParams[m].getRegeantModel() == nRegeantModel){
                testResultModel->parameterModel.setItemProperty(lstItemParams[m].getItemProperty());
                testResultModel->parameterModel.setRefMin(lstItemParams[m].getRefMin());
                testResultModel->parameterModel.setRefMax(lstItemParams[m].getRefMax());
                testResultModel->parameterModel.setUnit(lstItemParams[m].getUnit());
                testResultModel->parameterModel.setCheckWay(lstItemParams[m].getCheckWay());
                testResultModel->parameterModel.setItemName(lstItemParams[m].getItemName());
                testResultModel->parameterModel.setItemNo(lstItemParams[m].getItemNo());
                break;
            }
        }
        testResultModel->setTestWay(testResultModel->parameterModel.getCheckWay());

        testResultModel->setBarcode(SystemConfig::barcode);
        for(int i = 0;i < sampeCount;i++){
            QString strSampleType = lstSampleType[i].getSampleTypeName();
            if(0 == SystemConfig::sampleType.compare(strSampleType)){
                testResultModel->setSampleType(strSampleType);
                break;
            }
        }

        testResultModel->setUnit(testResultModel->parameterModel.getUnit());
        testResultModel->setHatchTime(SystemConfig::hatchTime);

        testResultModel->setIsPrint(SystemConfig::isPrint);
        testResultModel->setFlag(result[j].flag);
        testResultModel->setItemNo(itemNO);

        testResultModel->setItemName(strItemName);
        lstTestResultModel.push_back(testResultModel);

        for(int i = 0;i < MAX_ITEM;i++){
        //recieve item Name
            QString strItemName = lstTestResultModel[j]->getItemName();
            if(QString(result[i].name) == strItemName){
                ((TestResultModel*)lstTestResultModel[j])->setSampleNo(nSampleMaxNo);
                ((TestResultModel*)lstTestResultModel[j])->setItemName(result[i].name);
                ((TestResultModel*)lstTestResultModel[j])->setSampleValue(result[i].unit);
                ((TestResultModel*)lstTestResultModel[j])->setSampleDate(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
                TestResultSave((TestResultModel*)lstTestResultModel[j]);
                //pMainView->lstTestResultModel.removeAt(i);
                //qDebug() << "Accept item :" + QString("%1").arg(result[i].name) + ",  " + QString("%2").arg(result[i].unit);
                break;
            }
        }
        _result[j].block_num = MAX_ITEM;
        _result[j].position = result[j].position;
        _result[j].mode = SystemConfig::newold_Model;
        _result[j].paper_model = SystemConfig::regeant_Model;
    }
    for(int n = icount -1;n >= 0;n--){
        lstItemModel.removeAt(n);
    }
    for(int m = sampeCount-1;m >= 0;m--){
        lstSampleType.removeAt(m);
    }
}

uint MainBussniessView::GetSampleMaxNo(){
    uint nMax = 0;
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(tr("select max(SampleNo) as SampleMaxNo from TestResult_tb where SampleDate like '%1'").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
    if(0 < query.next()){
        nMax = query.value(0).toUInt();
    }
    return nMax;
}

void MainBussniessView:: PrintInformation(PatientModel patientModel){
    if(patientModel.getSampleNo() >= 0){
        strcpy(_report.userName, (char*)patientModel.getName().toLatin1().data());
        strcpy(_report.age, (char*)QString("%1").arg(patientModel.getAge()).toLatin1().data());
        strcpy(_report.sex, (char*)QString("%1").arg(patientModel.getSex()).toLatin1().data());
        strcpy(_report.date, (char*)patientModel.getRegisterDateTime().toLatin1().data());

        for (int i = 0;lstTestResultModel.count();i++) {

            if(lstTestResultModel[i]->getSampleNo() == patientModel.getSampleNo() && (lstTestResultModel[i]->getIsPrint() == true && i < MAX_ITEM)){
                strcpy(_report.sampleNo, (char*)QString("%1").arg(lstTestResultModel[i]->getSampleNo()).toLatin1().data());
                strcpy(_report.item_result[i].itemName, (char*)(lstTestResultModel[i]->getItemName().toLatin1().data()));
                strcpy(_report.item_result[i].result, (char*)QString("%1").arg(lstTestResultModel[i]->getSampleValue()).toLatin1().data());
                //_report.item_result[i].unit = testResult->getUnit();
                //strcpy(_report.item_result[i].flag, testResult->getFlag());
            }
        }
    }
}

int MainBussniessView::GetCalibration(int itemNo, QString itemName){
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from Calibrate_tb where ItemNo = %1").arg(itemNo));
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
   }
    return 0;
}

int MainBussniessView::GetItemParam(QList<ItemParameterModel>* lstItemParam)
{
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(tr("select * from ItemParameter_tb where regeant_model = %1").arg(SystemConfig::regeant_Model));
    int i = 0;
    while(query.next()){
        ItemParameterModel *parameterModel = new ItemParameterModel();
        parameterModel->setRegeantModel(query.value(0).toInt());
        parameterModel->setItemNo(query.value(1).toInt());
        parameterModel->setItemName(query.value(2).toString());
        parameterModel->setItemProperty(query.value(3).toString());
        parameterModel->setRefMin(query.value(4).toFloat());
        parameterModel->setRefMax(query.value(5).toFloat());
        parameterModel->setUnit(query.value(6).toString());
        parameterModel->setCheckWay(query.value(7).toString());
        lstItemParam->append(*parameterModel);
        i++;
    }
    return i;
}


bool MainBussniessView::Start(){
//    App::test_start = true;
//    if(pTestingThread != NULL){
//        delete pTestingThread;
//    }
//    pTestingThread = new TestingThread(this);
///*    if(pTestingThread->isRunning()){
//       return false;
//    }
//*/
//    pTestingThread->start();

//    //执行耗时操作。。。
//    bool bfinished = false;
//    while(!bfinished){
//        emit positionStatus(_result[0].position);
//        //App::mutex.lock();
//        bfinished = App::test_finished;
//        pTestingThread->msleep(100);
//        //App::mutex.unlock();
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
//    }
//    pTestingThread->exit();
//    //wait for result
    return true;
}

bool MainBussniessView::Stop(){
    App::test_start = false;
//    if(stopThread != NULL){
//        delete stopThread;
//    }
//    stopThread = new StopThread(this);
///*    if(stopThread->isRunning()){
//        return false;
//    }
//*/
//    bool bfinished = false;
//    while(!bfinished){
//        if(App::test_result){
//            App::test_finished = true;
//            stopThread->msleep(300);
//            stopThread->start();
//            bfinished = true;
//            break;
//        }
//        stopThread->msleep(10);
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
//    }
//    stopThread->exit();

    return true;
}

void MainBussniessView::setItemName(QString arg){
    _itemName = arg;
}

QString MainBussniessView::getItemName(){
    return _itemName;
}

bool MainBussniessView::White(QString mItemName){
    qDebug()<< "+++++++++++++++begin white+++++++++++"<<mItemName;
    App::test_start = true;

//    if(whiteThread != NULL){
//        delete whiteThread;
//    }

//    this->setItemName(mItemName);
//    whiteThread = new WhiteThread(this);
//    /*if(whiteThread->isRunning()){
//        return false;
//    }
//    */

//    whiteThread->start();
//    bool bfinished = false;
//    while(!bfinished){
//        //App::mutex.lock();
//        bfinished = App::test_finished;
//        //App::mutex.unlock();
//        whiteThread->msleep(100);
//        try{
//            QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
//        }catch(...){
//            qDebug()<< "Exception....";
//        }

//        //msleep(500);
//    }
//    whiteThread->exit();
//    qDebug()<< "+++++++++++++++end white+++++++++++";
//    //}
    return true;
}

void MainBussniessView::msleep(int sec){
//    QTime dieTime = QTime::currentTime().addMSecs(sec);
//    while( QTime::currentTime() < dieTime ){
//        whiteThread->msleep(10);
//        QCoreApplication::processEvents();
//    }
}

void MainBussniessView::ShowTestResult(){

        m_DatabaseHelper->ExecuteQueryModel(showTabelModel, tr("select SampleNo, ItemName, SampleValue, Unit, SampleDate, SampleType, Barcode, HatchTime, IsPrint from TestResult_tb where SampleDate = '%1' order by SampleNo desc").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
        //model->setHeaderData(0,Qt::Horizontal,tr("用户号"));
        showTabelModel->setHeaderData(0,Qt::Horizontal,tr("样本号"));
        showTabelModel->setHeaderData(1,Qt::Horizontal,tr("项目名称"));
        showTabelModel->setHeaderData(2,Qt::Horizontal,tr("样本值"));
        showTabelModel->setHeaderData(3,Qt::Horizontal,tr("单位"));
        showTabelModel->setHeaderData(4,Qt::Horizontal,tr("样本日期"));
        showTabelModel->setHeaderData(5,Qt::Horizontal,tr("样本类型"));
        showTabelModel->setHeaderData(6,Qt::Horizontal,tr("条码"));
        showTabelModel->setHeaderData(7,Qt::Horizontal,tr("孵育时间"));
        showTabelModel->setHeaderData(8,Qt::Horizontal,tr("是否打印"));
        //showTabelModel->setHeaderData(4,Qt::Horizontal,tr("项目编号"));
        //showTabelModel->setHeaderData(8,Qt::Horizontal,tr("测试方法"));
        //showTabelModel->setHeaderData(11,Qt::Horizontal,tr("标志"));
        emit testResult(showTabelModel);
}

MainBussniessView::~MainBussniessView(){
#ifndef TEST_SO
    if(m_lib != NULL){
        m_lib->unload();
        delete m_lib;
        m_lib = NULL;
    }
#endif
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
    if(whiteTableModel != NULL){
        delete whiteTableModel;
        whiteTableModel = NULL;
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
    if(deleteTableModel != NULL){
        delete deleteTableModel;
        deleteTableModel = NULL;
    }
    //delete model;
    if(pTestingThread != NULL){
        delete pTestingThread;
    }

}

bool MainBussniessView::PatientSaveAndUpdate(PatientModel patientModel){
    if(patientTableModel != NULL){
        delete patientTableModel;
        patientTableModel = NULL;
    }
    patientTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(patientTableModel, tr("PatientInfo_tb"), tr("SampleNo = %1").arg(patientModel.getSampleNo()));
    patientTableModel->setHeaderData(0,Qt::Horizontal,tr("样本号"));
    patientTableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
    patientTableModel->setHeaderData(2,Qt::Horizontal,tr("年龄"));
    patientTableModel->setHeaderData(3,Qt::Horizontal,tr("性别"));
    patientTableModel->setHeaderData(4,Qt::Horizontal,tr("注册日期"));
    QSqlRecord record = patientTableModel->record(0);
    if(patientTableModel->rowCount() == 0){
        record.setValue("SampleNo",patientModel.getSampleNo());
        record.setValue("Name",patientModel.getName());
        record.setValue("Age",patientModel.getAge());
        record.setValue("Sex",patientModel.getSex());
        record.setValue("RegisterDate", patientModel.getRegisterDateTime());
        patientTableModel->insertRecord(0,record);
        patientTableModel->submitAll();
    }
    else
    {
        patientTableModel->database().transaction(); //开始事务操作
        record.setValue("SampleNo",patientModel.getSampleNo());
        record.setValue("Name",patientModel.getName());
        record.setValue("Age",patientModel.getAge());
        record.setValue("Sex",patientModel.getSex());
        record.setValue("RegisterDate",patientModel.getRegisterDateTime());
        patientTableModel->setRecord(0,record);
        if (patientTableModel->submitAll()) {
            patientTableModel->database().commit(); //提交
        } else {
            patientTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    emit testResult(patientTableModel);
    return false;
}

void MainBussniessView::PatientDelete(int row){
    if(patientTableModel != NULL){
        patientTableModel->database().transaction();//开始事务操作
        patientTableModel->removeRow(row);
        //int ok = QMessageBox::warning((QWidget*)p, tr("删除当前行!"),tr("你确定”“删除当前行吗？"),QMessageBox::Yes,QMessageBox::No);
        //int nResult = myHelper::ShowMessageBoxQuesion(tr("你确定”“删除当前行吗?"));
int nResult = 0;
        if(nResult == 0){//
            patientTableModel->revertAll();//如果不删除，则撤销
        }else
        {
            if (patientTableModel->submitAll())
            {
                patientTableModel->database().commit();//提交
            }
            else {
                patientTableModel->database().rollback();//回滚
                //QMessageBox::warning(this,tr("tableModel"),tr("数据库错误: %1").arg(model->lastError().text()));
            }
        }
    }
}

void MainBussniessView::PatientBySampleNo(int nSampleNo){
    if(patientTableModel != NULL){
        delete patientTableModel;
    }
    patientTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(patientTableModel, tr("PatientInfo_tb"), QObject::tr("SampleNo = %1").arg(nSampleNo));
    QSqlRecord record = patientTableModel->record(0);
    PatientModel patientModel;
    if(record.count() > 0){
        patientModel.setName(record.value("Name").toString());
        patientModel.setAge(record.value("Age").toInt());
        patientModel.setSex(record.value("Sex").toInt());
        patientModel.setRegisterDateTime("RegisterDate");
        emit patientInfo(patientModel);
    }
    Query_SampleResult(nSampleNo, QDateTime::currentDateTime().toString("yyyy-MM-dd"), QDateTime::currentDateTime().toString("yyyy-MM-dd 23:59:59"));

}
//query 1
void MainBussniessView::Query_DateBySampleNoAndDate(int sampleNo, QString sBeginDate, QString sEndDate){
    QString strSQL = "";
    if(sampleNo > 0){
        strSQL.append(QObject::tr("SampleNo = %1 and ").arg(sampleNo));
    }
    strSQL = strSQL.append("RegisterDate >= '%2' and RegisterDate <= '%3'").arg(sBeginDate).arg(sEndDate);
    if(queryTableModel != NULL){
        delete queryTableModel;
    }
    queryTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(queryTableModel, tr("PatientInfo_tb"), strSQL);
    queryTableModel->setHeaderData(0,Qt::Horizontal,tr("样本号"));
    queryTableModel->setHeaderData(1,Qt::Horizontal,tr("用户名"));
    queryTableModel->setHeaderData(2,Qt::Horizontal,tr("年龄"));
    queryTableModel->setHeaderData(3,Qt::Horizontal,tr("性别"));
    queryTableModel->setHeaderData(4,Qt::Horizontal,tr("注册日期"));
    emit PatientResult(queryTableModel);
}

void MainBussniessView::Query_SampleResult(int sampleNo, QString sBeginDate, QString sEndDate){
    QString strSQL = (QObject::tr("SampleNo = %1 and SampleDate >= '%2' and SampleDate <= '%3'").arg(sampleNo).arg(sBeginDate).arg(sEndDate));

    if(sampleTableModel != NULL){
        delete sampleTableModel;
    }
    sampleTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(sampleTableModel, tr("TestResult_tb"), strSQL);
    //sampleTableModel->setHeaderData(0,Qt::Horizontal,tr("用户号"));
    sampleTableModel->setHeaderData(0,Qt::Horizontal,tr("样本号"));
    sampleTableModel->setHeaderData(1,Qt::Horizontal,tr("孵育时间"));
    sampleTableModel->setHeaderData(2,Qt::Horizontal,tr("样本值"));
    sampleTableModel->setHeaderData(3,Qt::Horizontal,tr("样本类型"));
    sampleTableModel->setHeaderData(4,Qt::Horizontal,tr("项目编号"));
    sampleTableModel->setHeaderData(5,Qt::Horizontal,tr("项目名称"));
    sampleTableModel->setHeaderData(6,Qt::Horizontal,tr("单位"));
    sampleTableModel->setHeaderData(7,Qt::Horizontal,tr("条码"));
    sampleTableModel->setHeaderData(8,Qt::Horizontal,tr("测试方法"));
    sampleTableModel->setHeaderData(9,Qt::Horizontal,tr("样本日期"));
    sampleTableModel->setHeaderData(10,Qt::Horizontal,tr("是否打印"));
    sampleTableModel->setHeaderData(11,Qt::Horizontal,tr("标志"));
    emit testResult(sampleTableModel);

}

int MainBussniessView::GetItemList(QList<ItemModel>* lstItem){
    QString strSQL = QObject::tr("select * from item_tb where regeant_model = %1").arg(SystemConfig::regeant_Model);
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(strSQL);
    int i = 0;
    while(query.next()){
        ItemModel* itemModel = new ItemModel();
        itemModel->setRegeantModel(query.value(0).toInt());
        itemModel->setItemNo(query.value(1).toInt());
        itemModel->setItemName(query.value(2).toString());
        lstItem->append(*itemModel);
        i++;
    }
    return i;
}
int MainBussniessView::GetItemNoByItemName(QString itemName){
    int itemNo = 0;
    QSqlQuery record = m_DatabaseHelper->ExecuteSqlQuery(QObject::tr("select * from item_tb where ItemName = '%1' and regeant_model = %2").arg(itemName).arg(SystemConfig::regeant_Model));
    if(record.next()){
        itemNo = record.value(1).toInt();
    }
    return itemNo;
}

void MainBussniessView::QualityControlItemSave(QC_SubItemModel subItemModel){
    if(qcItemTableModel != NULL){
        delete qcItemTableModel;
    }
    qcItemTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(qcItemTableModel, tr("QC_Sub_tb"), QObject::tr("QC_Date = '%1'").arg(subItemModel.getQc_Date()));
    QSqlRecord record = qcItemTableModel->record();
    if(qcItemTableModel->rowCount() == 0){
        record.setValue("ItemNo",subItemModel.getItemNo());
        record.setValue("QC_Value",subItemModel.getQc_Value());
        record.setValue("QC_Date",subItemModel.getQc_Date());
        qcItemTableModel->insertRecord(0,record);
        qcItemTableModel->submitAll();
    }
    else
    {
        qcItemTableModel->database().transaction(); //开始事务操作
        record.setValue("ItemNo",subItemModel.getItemNo());
        record.setValue("QC_Value",subItemModel.getQc_Value());
        record.setValue("QC_Date",subItemModel.getQc_Date());
        qcItemTableModel->setRecord(0,record);
        if (qcItemTableModel->submitAll()) {
            qcItemTableModel->database().commit(); //提交
        } else {
            qcItemTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    emit Qc_SubItemResult(qcItemTableModel);
}

void MainBussniessView::Qc_Query(int itemNo, QSqlTableModel *tableModel){
    m_DatabaseHelper->ExecuteTableModel(tableModel, tr("QC_Sub_tb"), QObject::tr("itemNo = %1").arg(itemNo));
    return;
}

void MainBussniessView::Qc_MainItemSave(QualityControlModel qcModel, float &cvValue){

    qcItemTableModel = new QSqlTableModel();
    //double cvValue = 0.0f;
    m_DatabaseHelper->ExecuteTableModel(qcItemTableModel, tr("QualityControl_tb"), QObject::tr("ItemNo = %1 and BatchNo = '%2'").arg(qcModel.getItemNo()).arg(qcModel.getBatchNo()));
    QSqlRecord record = qcItemTableModel->record();
    if(qcItemTableModel->rowCount() == 0){
        record.setValue("ItemNo",qcModel.getItemNo());
        record.setValue("BatchNo",qcModel.getBatchNo());
        record.setValue("TargetValue",qcModel.getTargetValue());
        cvValue = getCalculateCV(qcModel.plstQcModel);
        record.setValue("Qc_CvValue", cvValue);
        qcItemTableModel->insertRecord(0,record);
        qcItemTableModel->submitAll();
    }
    else
    {
        qcItemTableModel->database().transaction(); //开始事务操作
        record.setValue("ItemNo",qcModel.getItemNo());
        record.setValue("BatchNo",qcModel.getBatchNo());
        record.setValue("TargetValue",qcModel.getTargetValue());
        cvValue = getCalculateCV(qcModel.plstQcModel);
        record.setValue("Qc_CvValue", cvValue);
        qcItemTableModel->setRecord(0,record);
        if (qcItemTableModel->submitAll()) {
            qcItemTableModel->database().commit(); //提交
        } else {
            qcItemTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    delete qcItemTableModel;
    qcItemTableModel = NULL;
}

double MainBussniessView::getCalculateCV(QList<double> lstQcValue){
    float average = 0.0f;int number = 0;
    for(number = 0;number < lstQcValue.count();number++){
        average += lstQcValue[number];
    }
    if(number > 0){
        average /= number;
    }
    //计算质控量的SD
    double sd = 0;
    for (int i = 0; i < number; i++)
    {
        if (number == 0) break;
           sd += qPow((lstQcValue[i] - average), 2);
    }
    if (number != 0) {
        sd /= number;
    }
    sd = qSqrt(sd);
    //求偏移值CV
    double cv = sd / average * 100;
    return cv;

}
void MainBussniessView::Item_Save(ItemModel saveModel){
    if(itemTableModel != NULL){
        delete itemTableModel;
        itemTableModel = NULL;
    }
    itemTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(itemTableModel, tr("item_tb"), QObject::tr("ItemNo = '%1' and regeant_model = %2").arg(saveModel.getItemNo()).arg(SystemConfig::regeant_Model));
    QSqlRecord record = itemTableModel->record();
    if(itemTableModel->rowCount() == 0){
        record.setValue("regeant_model", saveModel.getRegeantModel());
        record.setValue("ItemNo",saveModel.getItemNo());
        record.setValue("ItemName",saveModel.getItemName());
        record.setValue("flag",saveModel.getFlag());
        itemTableModel->insertRecord(0,record);
        itemTableModel->submitAll();
    }
    else
    {
        itemTableModel->database().transaction(); //开始事务操作
        record.setValue("regeant_model", saveModel.getRegeantModel());
        record.setValue("ItemNo",saveModel.getItemNo());
        record.setValue("ItemName",saveModel.getItemName());
        record.setValue("flag",saveModel.getFlag());
        itemTableModel->setRecord(0,record);
        if (itemTableModel->submitAll()) {
            itemTableModel->database().commit(); //提交
        } else {
            itemTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    emit Item_Result(itemTableModel);
}
void MainBussniessView::Item_Query(QSqlQueryModel *tableModel){
     m_DatabaseHelper->ExecuteQueryModel(tableModel, tr("select ItemNo, ItemName, flag from Item_tb where regeant_model = %1").arg(SystemConfig::regeant_Model));
     return;
}

void MainBussniessView::GetItemName(QSqlQueryModel *tableModel){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, tr("select ItemName from Item_tb where regeant_model = %1").arg(SystemConfig::regeant_Model));
    return;
}

void MainBussniessView::SampleType_Query(QSqlTableModel* tableModel){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, tr("select * from SampleType_tb"));
    return;
}

void MainBussniessView::ItemParameter_Query(QSqlQueryModel *tableModel){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, tr("select ItemNo, ItemName, ItemProperty, RefMin, RefMax, Unit from ItemParameter_tb where regeant_model = %1").arg(SystemConfig::regeant_Model));
    return;
}

void MainBussniessView:: ItemParameter_Save(ItemParameterModel parameterModel){
    if(itemTableModel != NULL){
        delete itemTableModel;
    }
    itemTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(itemTableModel, tr("itemParameter_tb"), QObject::tr("ItemNo = '%1' and regeant_model = %2").arg(parameterModel.getItemNo()).arg(SystemConfig::regeant_Model));
    QSqlRecord record = itemTableModel->record();
    if(itemTableModel->rowCount() == 0){
        record.setValue("regeant_model", parameterModel.getRegeantModel());
        record.setValue("ItemNo",parameterModel.getItemNo());
        record.setValue("ItemName",parameterModel.getItemName());
        record.setValue("ItemProperty",parameterModel.getItemProperty());
        record.setValue("RefMin",parameterModel.getRefMin());
        record.setValue("RefMax",parameterModel.getRefMax());
        record.setValue("Unit",parameterModel.getUnit());
        record.setValue("CheckWay",parameterModel.getCheckWay());
        record.setValue("PostSequence",parameterModel.getPostSequence());
        itemTableModel->insertRecord(0,record);
        itemTableModel->submitAll();
    }
    else
    {
        itemTableModel->database().transaction(); //开始事务操作
        record.setValue("regeant_model", parameterModel.getRegeantModel());
        record.setValue("ItemNo",parameterModel.getItemNo());
        record.setValue("ItemName",parameterModel.getItemName());
        record.setValue("ItemProperty",parameterModel.getItemProperty());
        record.setValue("RefMin",parameterModel.getRefMin());
        record.setValue("RefMax",parameterModel.getRefMax());
        record.setValue("Unit",parameterModel.getUnit());
        record.setValue("CheckWay",parameterModel.getCheckWay());
        record.setValue("PostSequence",parameterModel.getPostSequence());
        itemTableModel->setRecord(0,record);
        if (itemTableModel->submitAll()) {
            itemTableModel->database().commit(); //提交
        } else {
            itemTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    emit ItemParameter_Result(itemTableModel);
}

void MainBussniessView::Calibrate_Query(QSqlQueryModel *tableModel, int nItemNo){
    m_DatabaseHelper->ExecuteQueryModel(tableModel, QObject::tr("select * from Calibrate_tb where ItemNo = %1").arg(nItemNo));
    return;
}

void MainBussniessView::Calibrate_Save(CalibrateModel calibrateModel){
    /*if(calibrateTableModel != NULL){
        delete calibratTableModel;
        calibratTableModel = NULL;
    }*/
    QSqlTableModel *calibrateTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(calibrateTableModel, tr("Calibrate_tb"), QObject::tr("ItemNo = %1").arg(calibrateModel.getItemNo()));
    QSqlRecord record = calibrateTableModel->record();
    if(calibrateTableModel->rowCount() == 0){
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
        calibrateTableModel->insertRecord(0,record);
        calibrateTableModel->submitAll();
    }
    else
    {
        calibrateTableModel->database().transaction(); //开始事务操作
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
        calibrateTableModel->setRecord(0,record);
        if (calibrateTableModel->submitAll()) {
            calibrateTableModel->database().commit(); //提交
        } else {
            calibrateTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    delete calibrateTableModel;

}

void MainBussniessView::Calibrate_Observerve_Query( QString beginDate, QString endDate){

    QString strSQL = (QObject::tr("CalibrateDate >= '%1' and CalibrateDate <= '%2'").arg(beginDate).arg(endDate));

    m_DatabaseHelper->ExecuteTableModel(calibrateObserveTableModel, tr("Calibrate_Oberservable_tb"), strSQL);
    calibrateObserveTableModel->setHeaderData(0,Qt::Horizontal,tr("白"));
    calibrateObserveTableModel->setHeaderData(1,Qt::Horizontal,tr("红"));
    calibrateObserveTableModel->setHeaderData(2,Qt::Horizontal,tr("绿"));
    calibrateObserveTableModel->setHeaderData(3,Qt::Horizontal,tr("蓝"));
    calibrateObserveTableModel->setHeaderData(4,Qt::Horizontal,tr("校准值"));
    calibrateObserveTableModel->setHeaderData(5,Qt::Horizontal,tr("测试值"));
    calibrateObserveTableModel->setHeaderData(6,Qt::Horizontal,tr("校准时间"));
    calibrateObserveTableModel->setHeaderData(7,Qt::Horizontal,tr("项目编号"));
    calibrateObserveTableModel->setHeaderData(8,Qt::Horizontal,tr("项目名称"));
    emit CalibrateObserverveResult(calibrateObserveTableModel);
}

void MainBussniessView::Query_TestResult(int sampleNo, QString sBeginDate, QString sEndDate){

    QString strSQL = (QObject::tr("SampleNo = %1 and SampleDate >= '%2' and SampleDate <= '%3'").arg(sampleNo).arg(sBeginDate).arg(sEndDate));
    if(queryTableModel != NULL)
    {
        delete queryTableModel;
    }
    queryTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(queryTableModel, tr("TestResult_tb"), strSQL);
    //model->setHeaderData(0,Qt::Horizontal,tr("用户号"));
    queryTableModel->setHeaderData(0,Qt::Horizontal,tr("样本号"));
    queryTableModel->setHeaderData(1,Qt::Horizontal,tr("孵育时间"));
    queryTableModel->setHeaderData(2,Qt::Horizontal,tr("样本值"));
    queryTableModel->setHeaderData(3,Qt::Horizontal,tr("样本类型"));
    queryTableModel->setHeaderData(4,Qt::Horizontal,tr("项目编号"));
    queryTableModel->setHeaderData(5,Qt::Horizontal,tr("项目名称"));
    queryTableModel->setHeaderData(6,Qt::Horizontal,tr("单位"));
    queryTableModel->setHeaderData(7,Qt::Horizontal,tr("条码"));
    queryTableModel->setHeaderData(8,Qt::Horizontal,tr("测试方法"));
    queryTableModel->setHeaderData(9,Qt::Horizontal,tr("样本日期"));
    queryTableModel->setHeaderData(10,Qt::Horizontal,tr("是否打印"));
    queryTableModel->setHeaderData(11,Qt::Horizontal,tr("标志"));
    emit QuerySampleResult(queryTableModel);
}

void MainBussniessView::SampleTytpeSave(SampleTypeModel sampleTypeModel){

    if(sampleTypeTableModel != NULL){
        delete sampleTypeTableModel;
        sampleTypeTableModel = NULL;
    }
    sampleTypeTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(sampleTypeTableModel, tr("SampleType_tb"), QObject::tr("SampleTypeNo = %1").arg(sampleTypeModel.getSampleTypeNo()));
    QSqlRecord record = sampleTypeTableModel->record();
    if(sampleTypeTableModel->rowCount() == 0){
        record.setValue("SampleTypeNo",sampleTypeModel.getSampleTypeNo());
        record.setValue("SampleTypeName",sampleTypeModel.getSampleTypeName());
        record.setValue("SampleFlag",sampleTypeModel.getSampleFlag());

        sampleTypeTableModel->insertRecord(0,record);
        sampleTypeTableModel->submitAll();
    }
    else
    {
        sampleTypeTableModel->database().transaction(); //开始事务操作
        record.setValue("SampleTypeNo",sampleTypeModel.getSampleTypeNo());
        record.setValue("SampleTypeName",sampleTypeModel.getSampleTypeName());
        record.setValue("SampleFlag",sampleTypeModel.getSampleFlag());
        sampleTypeTableModel->setRecord(0,record);
        if (sampleTypeTableModel->submitAll()) {
            sampleTypeTableModel->database().commit(); //提交
        } else {
            sampleTypeTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    emit SampleType_Result(sampleTypeTableModel);
}

void MainBussniessView::TestResultSave(TestResultModel* resultModel){

    QSqlTableModel *testTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(testTableModel, tr("TestResult_tb"), QObject::tr("where SampleNo = :SampleNo and ItemName = :ItemName and SampleDate = :SampleDate").arg(resultModel->getSampleNo()).arg(resultModel->getItemName()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd")));
    QSqlRecord record = testTableModel->record();
    if(testTableModel->rowCount() == 0){

        record.setValue("SampleNo", resultModel->getSampleNo());
        record.setValue("HatchTime", resultModel->getHatchTime());
        record.setValue("SampleValue", resultModel->getSampleValue());
        record.setValue("SampleType", resultModel->getSampleType());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        record.setValue("Unit", resultModel->getUnit());
        record.setValue("Barcode", resultModel->getBarcode());
        record.setValue("TestWay", resultModel->getTestWay());
        record.setValue("SampleDate", resultModel->getSampleDate());
        record.setValue("IsPrint", resultModel->getIsPrint());
        record.setValue("Flag", resultModel->getFlag());
        testTableModel->insertRecord(0,record);
        testTableModel->submitAll();
    }
    else
    {
        testTableModel->database().transaction(); //开始事务操作
        record.setValue("SampleNo", resultModel->getSampleNo());
        record.setValue("HatchTime", resultModel->getHatchTime());
        record.setValue("SampleValue", resultModel->getSampleValue());
        record.setValue("SampleType", resultModel->getSampleType());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        record.setValue("Unit", resultModel->getUnit());
        record.setValue("Barcode", resultModel->getBarcode());
        record.setValue("TestWay", resultModel->getTestWay());
        record.setValue("SampleDate", resultModel->getSampleDate());
        record.setValue("IsPrint", resultModel->getIsPrint());
        record.setValue("Flag", resultModel->getFlag());
        testTableModel->setRecord(0,record);
        if (testTableModel->submitAll()) {
            testTableModel->database().commit(); //提交
        } else {
            testTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    delete testTableModel;
}
void MainBussniessView::StartProcessing(){
    assert(p!=NULL);
    progressDlg = new QProgressDialog((QWidget*)p);
    progressDlg->setWindowTitle("Please wait...");
    progressDlg->setFixedWidth(300);
    progressDlg->setRange(0, 100);
    progressDlg->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);//不显示进度条上的“最小化”“最大化”“关闭”| Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint
    progressDlg->setWindowModality(Qt::WindowModal);
    progressDlg->showFullScreen();
    timer = new QTimer(this);
    currentValue = 0;
    progressDlg->setValue(currentValue);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressDialog()));
    timer->start(500);//开启一个没有终点的定时器

}

void MainBussniessView::EndProcessing(){
    //耗时操作完成后，关闭进度对话框
    timer->stop();//停止定时器
    if(currentValue != 100)
       currentValue = 100;
    progressDlg->setValue(currentValue);//进度达到最大值
    delete progressDlg;//关闭进度对话框
}

//借助定时器，不断更新进度条，直到耗时操纵结束
void MainBussniessView::updateProgressDialog()
{
    currentValue++;
    if( currentValue == 100 )
        currentValue = 0;
    progressDlg->setValue(currentValue);
    //QCoreApplication::processEvents();//避免界面冻结
    if(progressDlg->wasCanceled()){
        progressDlg->setHidden(true);//隐藏对话框
    }
}
bool MainBussniessView::GetSystemStatus(){
    return false;
}

void MainBussniessView::WhiteResultSave(CalibrateObserverModel* resultModel){

    QSqlTableModel *whiteTableModel = new QSqlTableModel();
    m_DatabaseHelper->ExecuteTableModel(whiteTableModel, tr("Calibrate_Oberservable_tb"), QObject::tr("where ItemName = :ItemName and CalibrateDate = :CalibrateDate").arg(resultModel->getItemName()).arg(resultModel->getCalibrateDate()));
    QSqlRecord record = whiteTableModel->record();

    if(whiteTableModel->rowCount() == 0){
        record.setValue("White", resultModel->getWhite());
        record.setValue("Red", resultModel->getRed());
        record.setValue("Green", resultModel->getGreen());
        record.setValue("Blue", resultModel->getBlue());
        record.setValue("CalibrateValue", resultModel->getCalibrateValue());
        record.setValue("ResultValue", resultModel->getResultValue());
        record.setValue("CalibrateDate", resultModel->getCalibrateDate());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        whiteTableModel->insertRecord(0,record);
        whiteTableModel->submitAll();
    }
    else
    {
        whiteTableModel->database().transaction(); //开始事务操作
        record.setValue("White", resultModel->getWhite());
        record.setValue("Red", resultModel->getRed());
        record.setValue("Green", resultModel->getGreen());
        record.setValue("Blue", resultModel->getBlue());
        record.setValue("CalibrateValue", resultModel->getCalibrateValue());
        record.setValue("ResultValue", resultModel->getResultValue());
        record.setValue("CalibrateDate", resultModel->getCalibrateDate());
        record.setValue("ItemNo", resultModel->getItemNo());
        record.setValue("ItemName", resultModel->getItemName());
        whiteTableModel->setRecord(0,record);
        if (whiteTableModel->submitAll()) {
            whiteTableModel->database().commit(); //提交
        } else {
            whiteTableModel->database().rollback(); //回滚
        //QMessageBox::warning(this, tr("tableModel") ,tr("数据库错误: %1"));
        }
    }
    delete whiteTableModel;
}
void MainBussniessView::Test_WhiteResult(CalibrateObserverModel* resultModel){
    QString strSQL = (QObject::tr("ItemName = '%1'").arg(resultModel->getItemName()));
    m_DatabaseHelper->ExecuteTableModel(calibrateObserveTableModel, tr("Calibrate_Oberservable_tb"), strSQL);
    calibrateObserveTableModel->setHeaderData(0,Qt::Horizontal,tr("白"));
    calibrateObserveTableModel->setHeaderData(1,Qt::Horizontal,tr("红"));
    calibrateObserveTableModel->setHeaderData(2,Qt::Horizontal,tr("绿"));
    calibrateObserveTableModel->setHeaderData(3,Qt::Horizontal,tr("蓝"));
    calibrateObserveTableModel->setHeaderData(4,Qt::Horizontal,tr("校准值"));
    calibrateObserveTableModel->setHeaderData(5,Qt::Horizontal,tr("测试值"));
    calibrateObserveTableModel->setHeaderData(6,Qt::Horizontal,tr("校准时间"));
    calibrateObserveTableModel->setHeaderData(7,Qt::Horizontal,tr("项目编号"));
    calibrateObserveTableModel->setHeaderData(8,Qt::Horizontal,tr("项目名称"));
    emit CalibrateObserverveResult(calibrateObserveTableModel);

}


void MainBussniessView::Test_DeleteResult(QString sItemName){
    QString strSQL = (QObject::tr("delete from calibrate_oberservable_tb where ItemName = '%1'").arg(sItemName));
    m_DatabaseHelper->ExecuteInt(strSQL);

    strSQL = (QObject::tr("ItemName = '%1'").arg(sItemName));
/*    if(calibrateObserveTableModel != NULL){
        delete calibrateObserveTableModel;
    }
    calibrateObserveTableModel = new QSqlTableModel();
    */
    m_DatabaseHelper->ExecuteTableModel(calibrateObserveTableModel, tr("Calibrate_Oberservable_tb"), strSQL);
    calibrateObserveTableModel->setHeaderData(0,Qt::Horizontal,tr("白"));
    calibrateObserveTableModel->setHeaderData(1,Qt::Horizontal,tr("红"));
    calibrateObserveTableModel->setHeaderData(2,Qt::Horizontal,tr("绿"));
    calibrateObserveTableModel->setHeaderData(3,Qt::Horizontal,tr("蓝"));
    calibrateObserveTableModel->setHeaderData(4,Qt::Horizontal,tr("校准值"));
    calibrateObserveTableModel->setHeaderData(5,Qt::Horizontal,tr("测试值"));
    calibrateObserveTableModel->setHeaderData(6,Qt::Horizontal,tr("校准时间"));
    calibrateObserveTableModel->setHeaderData(7,Qt::Horizontal,tr("项目编号"));
   // calibrateObserveTableModel->setHeaderData(8,Qt::Horizontal,tr("项目名称"));
    emit CalibrateObserverveResult(calibrateObserveTableModel);
}

void MainBussniessView::WhiteCalendar(QString sItemName, QList<int>& lstResult){
    QString strSQL = (QObject::tr("select * from Calibrate_Oberservable_tb where ItemName = '%1' order by CalibrateDate asc").arg(sItemName));
    QSqlQuery query = m_DatabaseHelper->ExecuteSqlQuery(strSQL);
    int nTotal = 0, n = 0, nAva = 0;
    while (query.next()) {
        ++n;
        nTotal += query.value(4).toInt();
        if(n > 0){
            nAva = nTotal/n;
        }
        if(n % 3 == 0){
            lstResult.append(nAva);
        }
    }
    return;
}
