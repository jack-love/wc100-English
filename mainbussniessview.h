#ifndef MAINBUSSNIESSVIEW_H
#define MAINBUSSNIESSVIEW_H

#include <QObject>
#include <patientmodel.h>
#include <qtimer.h>
#include <itemmodel.h>
#include <qc_subitemmodel.h>
#include <qualitycontrolmodel.h>
#include <itemparametermodel.h>
#include <calibratemodel.h>
#include <sampletypemodel.h>
#include <qlist.h>
#include <testresultmodel.h>
#include <QMutex>
#include <App.h>
#include <calibrateobservermodel.h>
#include<ttythread.h>
#include<maintancance.h>
#include<QTimer>
#include <QThread>
class QLibrary;
class databaseHelper;
class TestingThread;
class QSqlTableModel;
class QProgressDialog;
class QSqlQueryModel;
class StopThread;
class WhiteThread;

#define TEST_SO
class MainBussniessView : public QObject
{
    Q_OBJECT
public:
     void Initalize();
     bool powerOff();
     bool askUser();
     void coverHands();
     void mcuReset();
     void setParameters();
     bool  mcuCmd(WORK_STATE cmd);
     void  mcuPclose();
     void  mcuPopen();
     void  startProcessing();
    explicit MainBussniessView(QObject *parent = 0);
    bool normalStart();
    bool Stop();
    bool getVersion();
    bool setUp();
    bool calibrationTest(QString mItemName);
    ~MainBussniessView();


    int  GetItemNoByItemName_11_3(QString itemName);
    int  GetItemNoByItemName_10T(QString itemName);
    int  GetItemNoByItemName_12MA(QString itemName);
    void Calibrate_Query_11_3(QSqlQueryModel *tableModel, int nItemNo);
    void Calibrate_Query_10T(QSqlQueryModel *tableModel, int nItemNo);
    void Calibrate_Query_12MA(QSqlQueryModel *tableModel, int nItemNo);
    void  calibrateSave(CalibrateModel calibrateModel);
    void  Query_SampleResult(int sampleNo, QString sBeginDate, QString sEndDate);
    void  Query_SampleResult_no(int sampleNo, QString sBeginDate, QString sEndDate);
    void  getTest_Result(RESULT result[]);
    int    getSample_Type(QList<SampleTypeModel>* lstSampleType);
    void testResult_Save(TestResultModel* resultModel);
    void showTest_Result();
    void PrintInformation(QByteArray arr);
    void  getSystem_status();
    void  getSystem_species();
    void  getSystem_language();
    void  getSystem_testMode();
    void  getSystem_testPapertype();


    void calibrationResult_Show(CalibrateObserverModel* resultModel);

    RESULT _result[13];

    void calibrationResult_Save(CalibrateObserverModel* resultModel);
    void   systemStatus_Save();
    void   realTime_NuSave();
    void calibrationDelete_Result(QString sItemName);
    void testDelete_Result();
    void GetItemName_11_3(QSqlQueryModel *tableModel);
    void GetItemName_10T(QSqlQueryModel *tableModel);
    void GetItemName_12MA(QSqlQueryModel *tableModel);
    void  getCalibration(int itemNo, QString itemName);
    void  calibrationShow(struct RESULT _result[]);
    void  calibrationQuery(QString caliname);
    void  buzzer();

signals:
    bool  testResult(QSqlTableModel*);
    bool  system_Setup(QSqlTableModel*);
    bool  system_Species(QSqlTableModel*);
    bool  system_Language(QSqlTableModel*);
    bool  system_testMode(QSqlTableModel*);
    bool  system_testPapertype(QSqlTableModel*);
    void  reset_signal();
    void Status_signal(QString);
    bool positionStatus(uint i);
    void patientInfo(PatientModel);
    void  system_saveok();

    void SampleResult(QSqlTableModel*);
    void Qc_SubItemResult(QSqlTableModel*);
    void Item_Result(QSqlTableModel*);
    void ItemParameter_Result(QSqlTableModel*);
    void SampleType_Result(QSqlTableModel*);
    void CalibrateObserverveResult(QSqlTableModel*);
    void SignalStrength(QString signal);
    void   Spoweroff();
    void languageConversion();
    void SendHomeSignal();
    void  receiveTtyData(QString str);
    void  receiveAck(unsigned char state);
    void   sTime (int s);
     void  mTime(int s);
    void  receiveWb(WRGB_DAT);
    void  receiveRGB(WRGB_DAT,unsigned int count);


public slots:
    void sTimeSlot(int st);
    void showTtyData(QString str);
    void showTtyAck(unsigned char state);
    void showWb(WRGB_DAT wrgb_data);
    void showWrgb(WRGB_DAT wrgb_data,unsigned int count);
    bool system_setup_show(QSqlTableModel*model);

private:
    QList<ItemModel> lstItemModel;
    QList<TestResultModel*> lstTestResultModel;
    double getCalculateCV(QList<double> lstQcValue);
    int GetItemParam(QList<ItemParameterModel>* lstItemParam);
    int  GetItemList(QList<ItemModel>* lstItem);
    int  MAX_ITEM;
    uint GetSampleMaxNo();
    databaseHelper* m_DatabaseHelper=NULL;
    StopThread *stopThread=NULL;
    WhiteThread *whiteThread=NULL;
    QObject *p=NULL;
    QLibrary *m_lib=NULL;
    QTimer *timer=NULL;
    QSqlTableModel *sampleTableModel=NULL;
    QSqlTableModel *testdeleteTableModel=NULL;
    QStringList* lstItemName=NULL;

    QSqlTableModel* sampleTypeTableModel=NULL;
    QSqlTableModel *itemTableModel=NULL;
    QSqlTableModel *patientTableModel=NULL;
    QSqlTableModel *showTabelModel=NULL;
    QSqlTableModel *showTabeTest=NULL;
    QSqlTableModel *qcItemTableModel=NULL;
    QSqlTableModel *queryTableModel=NULL;
    QSqlTableModel *calibrateObserveTableModel=NULL;


    ttyThread  * tty_thread=NULL;
    resultVal    result[13];
    Cac  cac;
    QString Name_tmp;
    QProgressDialog *progressDialog=NULL;

};

#endif // MAINBUSSNIESSVIEW_H
