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
    explicit MainBussniessView(QObject *parent = 0);
    bool Start();
    bool Stop();
    bool White(QString mItemName);
    ~MainBussniessView();
    bool PatientSaveAndUpdate(PatientModel patientModel);

    void PatientDelete(int row);
    void PatientBySampleNo(int nSampleNo);
    void Query_DateBySampleNoAndDate(int sampleNo, QString sBeginDate, QString sEndDate);
    void Query_TestResult(int sampleNo, QString sBeginDate, QString sEndDate);

    void QualityControlItemSave(QC_SubItemModel subItemModel);
    int  GetItemNoByItemName(QString itemName);
    void Qc_Query(int itemNo, QSqlTableModel *tableModel);
    void Qc_MainItemSave(QualityControlModel qcModel, float &cvValue);
    void Item_Save(ItemModel saveModel);
    void Item_Query(QSqlQueryModel *tableModel);
    void ItemParameter_Save(ItemParameterModel parameterModel);
    void Calibrate_Query(QSqlQueryModel *tableModel, int nItemNo);
    void Calibrate_Save(CalibrateModel calibrateModel);
    void Query_SampleResult(int sampleNo, QString sBeginDate, QString sEndDate);
    void SampleTytpeSave(SampleTypeModel model);
    void GetTestResult(RESULT result[]);
    int GetSampleType(QList<SampleTypeModel>* lstSampleType);
    void TestResultSave(TestResultModel* resultModel);
    void ShowTestResult();
    void PrintInformation(PatientModel patientModel);
    void StartProcessing();
    void EndProcessing();
    void Calibrate_Observerve_Query(QString beginDate, QString endDate);
    bool GetSystemStatus();
    void Test_WhiteResult(CalibrateObserverModel* resultModel);
    RESULT _result[MAX_ITEM];
    QList<TestResultModel*> QueryTestResult(QString strWhere);
    void WhiteResultSave(CalibrateObserverModel* resultModel);
    QList<ItemModel> getItemModel();
    QString getItemName();
    void Test_DeleteResult(QString sItemName);
    void WhiteCalendar(QString sItemName, QList<int>& lstResult);
    void SampleType_Query(QSqlTableModel* tableModel);
    void GetItemName(QSqlQueryModel *tableModel);
    void ItemParameter_Query(QSqlQueryModel *tableModel);
    int GetCalibration(int itemNo, QString itemName);
signals:

    bool testResult(QSqlTableModel*);
    void QuerySampleResult(QSqlTableModel*);
    bool positionStatus(uint i);
    void patientInfo(PatientModel);

    void PatientResult(QSqlTableModel*);
    //void SampleResult(QSqlTableModel*);
    void Qc_SubItemResult(QSqlTableModel*);
    void Item_Result(QSqlTableModel*);
    void ItemParameter_Result(QSqlTableModel*);
    void SampleType_Result(QSqlTableModel*);
    void CalibrateObserverveResult(QSqlTableModel*);

    //void Test_WhiteResult(QSqlTableModel*);
public slots:
    //bool on_PositionStatus(int i);
    void updateProgressDialog();
    //void on_testStart();
    //void on_testStop();
private:
    QList<ItemModel> lstItemModel;
    void setItemName(QString);
    void Initalize();
    REPORT _report;
    QList<TestResultModel*> lstTestResultModel;
    double getCalculateCV(QList<double> lstQcValue);
    int GetItemParam(QList<ItemParameterModel>* lstItemParam);
    int  GetItemList(QList<ItemModel>* lstItem);

    uint GetSampleMaxNo();
    databaseHelper* m_DatabaseHelper;
    TestingThread *pTestingThread;
    StopThread *stopThread;
    WhiteThread *whiteThread;
    QProgressDialog *progressDlg;
    int currentValue;
    QObject *p;
    QLibrary *m_lib;
    QTimer *timer;
    QSqlTableModel *sampleTableModel;
    QStringList* lstItemName;
    //QSqlTableModel *calibrateTableModel;
    QSqlTableModel* sampleTypeTableModel;
    QSqlTableModel *whiteTableModel;
    QSqlTableModel *itemTableModel;
    QSqlTableModel *patientTableModel;
    QSqlTableModel *showTabelModel;
    QSqlTableModel *qcItemTableModel;
    QSqlTableModel *queryTableModel;
    QSqlTableModel *calibrateObserveTableModel;
    QSqlTableModel *deleteTableModel;
    QMutex mutex;

    typedef int (*SYS_STATUS)();
    SYS_STATUS _Sys_status;
    typedef int (*INITAL)();
    INITAL _Inital;
    typedef int(*POWER)();
    POWER _Power;
    typedef int(*RESET)();
    RESET _Reset;
    typedef int(*STOP)();
    STOP _Stop;
    typedef int(*WHITE)(RESULT _result[]);
    WHITE _White;
    typedef int(*RUN)(RESULT _result[]);
    RUN _Run;   
    QString _itemName;
    void Machine_Inital();
    void msleep(int sec);
public:
    int Machine_Reset();
    int Machine_Power();
    int Machine_Stop();
    int Machine_Go_on();
    int Machine_White(struct RESULT buf[]);
    int Machine_Run(struct RESULT buf[]);
    int Machine_Sys_Status();

};

#endif // MAINBUSSNIESSVIEW_H
