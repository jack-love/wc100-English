#include "databasehelper.h"
#include <QDebug>

databaseHelper::databaseHelper(const QString &strDatabase) :
    m_strDatabase(strDatabase)
{
    createConnection(m_strDatabase);
}

databaseHelper::~databaseHelper()
{
    m_db.close();
}

bool databaseHelper::createConnection(const QString &database)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");

   /* //与数据库建立连接
    if (QSqlDatabase::contains("my_conn"))
    {
        m_db = QSqlDatabase::database("my_conn");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "my_conn");
    }*/

    //设置数据库名
    m_db.setDatabaseName(database);
    //打开数据库
    if (!m_db.open())
    {
        qDebug() << "Open database failed!";
        return false;
    }
    else
    {
        qDebug() << "Open database successfull!";
        return true;
    }
}

//创建数据库表
bool databaseHelper::createTable()
{
    bool bResult = true;
    bool success = false;

    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);

    success = query.exec("create table PatientInfo_tb(SampleNo int primary key, Name varchar,"
                         "Age int, Sex int, RegisterDate varchar)");
    query.exec(QObject::tr("insert into PatientInfo_tb values (23, 'wang cj', 22, 1, '2017-10-19')"));
    bResult &=success;

    success = query.exec("create table TestResult_tb(SampleNo int, HatchTime int,"
                         "SampleValue int, SampleType varchar, ItemNo int, ItemName varchar, Unit varchar, "
                         "Barcode varchar, TestWay varchar, SampleDate varchar, IsPrint bool, Flag varchar)");
    query.exec(QObject::tr("insert into TestResult_tb values (23, 1, 22, '20.5', 'blood', 1, 'WEB', 'testing', '345', '1', '2017-12-22', 1, 0)"));
    query.exec(QObject::tr("insert into TestResult_tb values (23, 2, 33, '32.5', 'blood', 2, 'KET', 'testing', '345', '2', '2017-10-19', 1, 0)"));
    //query.exec(QObject::tr("insert into TestResult_tb values (23, 3, 33, '54.5', 'blood', 3, 'VC', 'testing', '345', 0, '2017-10-19', 1, 0)"));
    bResult &=success;

    success = query.exec("create table QualityControl_tb(ItemNo int , BatchNo varchar primary key, "
                         "TargetValue float, Qc_CvValue float)");
    query.exec(QObject::tr("insert into QualityControl_tb values (1, '0011', 3, 23.5)"));
    bResult &=success;

    success = query.exec("create table QC_Sub_tb(ItemNo int, QC_Value varchar, QC_Date varchar primary key)");
    query.exec(QObject::tr("insert into QC_Sub_tb values (1, '3.5', '2017-10-10')"));
    query.exec(QObject::tr("insert into QC_Sub_tb values (1, '2.3', '2017-10-11')"));
    bResult &=success;
    success = query.exec("create table item_tb(regeant_model int, ItemNo int, ItemName varchar, flag varchar, primary key (regeant_model,ItemNo))");
    query.exec(QObject::tr("insert into item_tb values (0, 0, 'BIL', '0')"));
    query.exec(QObject::tr("insert into item_tb values (0, 1, 'URO', '1')"));
    query.exec(QObject::tr("insert into item_tb values (0, 2, 'KET', '2')"));
    query.exec(QObject::tr("insert into item_tb values (0, 3, 'BLD', '3')"));
    query.exec(QObject::tr("insert into item_tb values (0, 4, 'PRO', '4')"));
    query.exec(QObject::tr("insert into item_tb values (0, 5, 'NIT', '5')"));
    query.exec(QObject::tr("insert into item_tb values (0, 6, 'WBC', '6')"));
    query.exec(QObject::tr("insert into item_tb values (0, 7, 'GLU', '7')"));
    query.exec(QObject::tr("insert into item_tb values (0, 8, 'SG', '8')"));
    query.exec(QObject::tr("insert into item_tb values (0, 9, 'PH', '9')"));
    query.exec(QObject::tr("insert into item_tb values (0, 10, 'VC', '10')"));
    //query.exec(QObject::tr("insert into item_tb values (10, 'CA', '10')"));
    /*query.exec(QObject::tr("insert into item_tb values (12, 'ACR', '12')"));
    query.exec(QObject::tr("insert into item_tb values (13, 'URO', '13')"));
    query.exec(QObject::tr("insert into item_tb values (14, 'CRE', '14')"));
*/
    bResult &=success;
    success = query.exec("create table ItemParameter_tb(regeant_model int, ItemNo int, ItemName varchar, "
                         "ItemProperty varchar, RefMin float, RefMax float, Unit varchar,"
                         "CheckWay varchar, PostSequence int, primary key (regeant_model,ItemNo))");
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 0, 'BIL', 'P', 0.2, 5.6, 'mol/g', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 1, 'URO', 'P', 0.12, 7.6, 'mg/l', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 2, 'KET', 'P', 0.2, 5.6, 'mol/g', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 3, 'BLD', 'P', 0.12, 7.6, 'mg/l', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 4, 'PRO', 'P', 0.2, 5.6, 'mol/g', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 5, 'NIT', 'P', 0.12, 7.6, 'mg/l', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 6, 'WBC', 'P', 0.2, 5.6, 'mol/g', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 7, 'GLU', 'P', 0.12, 7.6, 'mg/l', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 8, 'SG', 'P', 0.2, 5.6, 'mol/g', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 9, 'PH', 'P', 0.12, 7.6, 'mg/l', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb values (0, 10, 'VC', 'P', 0.2, 5.6, 'mol/g', '00', 1)"));

    bResult &=success;
    success = query.exec("create table Calibrate_tb(ItemNo int primary key, CalibrateValue0 int, CalibrateValue1 int, CalibrateValue2 int, CalibrateValue3 int,"
                         "CalibrateValue4 int, CalibrateValue5 int, CalibrateValue6 int, CalibrateValue7 int, ResultValue0 varchar, ResultValue1 varchar, ResultValue2 varchar, ResultValue3 varchar, ResultValue4 varchar, ResultValue5 varchar,ResultValue6 varchar, ResultValue7 varchar)");
    query.exec(QObject::tr("insert into Calibrate_tb values (0, 123, 123, 147, 666, 123, 456, 789, 258, '- 3.3', '+- 16', '1+ 33', '2+ 66', '3+ 131', '3+ 131', '3+ 131', '3+ 131')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (1, 123, 123, 147, 666, 123, 456, 789, 258, '- Neg', '1+ 17', '2+ 50', '3+ 100', '3+ 100', '3+ 100','3+ 100', '3+ 100')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (2, 123, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.5', '1+ 1.5', '2+ 2.9', '3+ 7.8', '4+ 16', '4+ 16', '4+ 16')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (3, 123, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 10 ca', '1+ 25 ca', '2+ 25 ca', '3+ 25 ca', '3+ 25 ca', '3+ 25 ca', '3+ 25 ca')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (4, 123, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.2', '1+ 0.3', '2+ 1.0', '3+ 3.0', '3+ 3.0','3+ 3.0','3+ 3.0')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (5, 123, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+ Pos', '+ Pos', '+ Pos', '+ Pos', '+ Pos', '+ Pos', '+ Pos')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (6, 123, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+-  15 ca', '1+  70 ca', '2+  125ca', '3+  500ca', '3+  500ca', '3+  500ca', '3+  500ca')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (7, 123, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.2', '1+ 0.3', '2+ 1.0', '3+ 3.0', '3+ 3.0','3+ 3.0','3+ 3.0')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (8, 123, 123, 147, 666, 123, 456, 789, 258, '  1.005', '   1.015', '  1.020', '  1.025', '  1.030', '  1.030', '  1.030', '  1.030')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (9, 123, 123, 147, 666, 123, 456, 789, 258, '  1.005', '   1.015', '  1.020', '  1.025', '  1.030', '  1.030', '  1.030', '  1.030')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (10, 123, 123, 147, 666, 123, 456, 789, 258, ' 1.005', '   1.015', '  1.020', '  1.025', '  1.030', '  1.030', '  1.030', '  1.030')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (11, 123, 123, 147, 666, 123, 456, 789, 258,'  1.005', '   1.015', '  1.020', '  1.025', '  1.030', '  1.030', '  1.030', '  1.030')"));
    /*query.exec(QObject::tr("insert into Calibrate_tb values (12, 123, 123, 147, 666, 123, 456, 789, 258, ' 1.005', '   1.015', '  1.020', '  1.025', '  1.030', '  1.030', '  1.030', '  1.030')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (13, 123, 123, 147, 666, 123, 456, 789, 258, ' 1.005', '   1.015', '  1.020', '  1.025', '  1.030', '  1.030', '  1.030', '  1.030')"));
    query.exec(QObject::tr("insert into Calibrate_tb values (14, 123, 123, 147, 666, 123, 456, 789, 258,'  1.005', '   1.015', '  1.020', '  1.025', '  1.030', '  1.030', '  1.030', '  1.030')"));
*/
    bResult &=success;
    success = query.exec("create table Calibrate_Oberservable_tb(White int, Red int, Green int, Blue int, CalibrateValue int, ResultValue varchar, CalibrateDate varchar, ItemNo int, ItemName varchar)");
    query.exec(QObject::tr("insert into Calibrate_Oberservable_tb values ( 456, 123, 789, 222, 456, '-Neg', '2018-01-11 12:12:00', 1, 'WBC')"));
    query.exec(QObject::tr("insert into Calibrate_Oberservable_tb values ( 258, 369, 147, 666, 789, '-Neg', '2018-01-05 10:14:59', 2, 'KET')"));
    bResult &=success;

    success = query.exec("create table SampleType_tb(SampleTypeNo int primary key, SampleTypeName varchar,SampleFlag varchar)");
    query.exec(QObject::tr("insert into SampleType_tb values (1, '尿常规', 'ncg')"));
    query.exec(QObject::tr("insert into SampleType_tb values (2, '血清', 'xq')"));
    bResult &=success;

    if(bResult)
    {
        qDebug() << QObject::tr("数据库表创建成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

QSqlRecord databaseHelper::ExecuteRecord(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    return query.record();
}

QSqlRecord databaseHelper::ExecuteRecord(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    return query.record();
}

QSqlRecord databaseHelper::ExecuteRecord(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    return query.record();
}

QSqlQuery databaseHelper::ExecuteSqlQuery(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.setForwardOnly(true);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    return query;
}

QSqlQuery databaseHelper::ExecuteSqlQuery(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.setForwardOnly(true);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    return query;
}

QSqlQuery databaseHelper::ExecuteSqlQuery(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.setForwardOnly(true);
    query.prepare(strQuery);
    query.exec();
    return query;
}

int databaseHelper::ExecuteInt(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

int databaseHelper::ExecuteInt(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

int databaseHelper::ExecuteInt(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    query.exec();
    int ID = 0;
    while(query.next())
    {
        ID = query.value(0).toInt();
    }
    return ID;
}

bool databaseHelper::Execute(const QString& strQuery, QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    return query.exec();
}

bool databaseHelper::Execute(const QString& strQuery, QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    return query.exec();
}

QString databaseHelper::ExecuteString(const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.exec();
    QString temp;
    while(query.next())
    {
        temp = query.value(0).toString();
    }
    return temp;
}

void databaseHelper::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    p_queryModel->setQuery(strQuery, m_db);
}

bool databaseHelper::ExecuteTableModel(QSqlTableModel* pTableModel, QString tableName, QString tableFilter){
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    pTableModel->setTable(tableName);

    pTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    pTableModel->setFilter(tableFilter);
    bResult = pTableModel->select(); //选取整个表的所有行
    return bResult;
}


void databaseHelper::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                       QList<QVariant> lstParameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    for(int i = 0; i < lstParameter.count(); i++)
        query.bindValue(i, lstParameter[i]);
    p_queryModel->setQuery(query);
}

void databaseHelper::ExecuteQueryModel(QSqlQueryModel *p_queryModel, const QString& strQuery,
                                   QVariant Parameter)
{
    if(!m_db.isOpen())
    {
        createConnection(m_strDatabase);
    }
    QSqlQuery query(m_db);
    query.prepare(strQuery);
    query.bindValue(0, Parameter);
    p_queryModel->setQuery(query);
 }
/*
databaseHelper::databaseHelper()
{
    nMax = 0;
}


bool databaseHelper::createConnection(QString strConnection)  //创建一个连接".//qtDb.db"
{
    //以后就可以用"sqlite1"与数据库进行连接了
        QSqlDatabase m_database = QSqlDatabase::addDatabase("QSQLITE", "sqlite");
        m_database.setDatabaseName(strConnection);
        if( !m_database.open())
        {
            qDebug() << "无法建立数据库连接";
            return false;
        }
        return true;
}
bool databaseHelper::close(){

    QSqlDatabase m_database = QSqlDatabase::database("sqlite"); //建立数据库连接
    m_database.close();
}

//创建数据库表
bool databaseHelper::createTable()
{
    bool bResult = true;
    QSqlDatabase m_database = QSqlDatabase::database("sqlite"); //建立数据库连接
    QSqlQuery query(m_database);
    bool success = query.exec("create table Item_tb(ItemNo int primary key,ItemName varchar,"
                              "ReferLowValue varchar,ReferHighValue varchar)");
    success &= true;
    success = query.exec("create table PatientInfo_tb(SampleNo int primary key, Name varchar,"
                         "Age int, Sex varchar)");
    bResult &=success;

    success = query.exec("create table TestResult_tb(SampleNo int primary key, HatchTime int,"
                         "SampleIntervalTime int, SampleVol float, SampleNo int, SampleType varchar,"
                         "ItemNo int, CurveNo int, X1 float, X2 float, X3 float, X4 float, X5 float, T float, "
                         "C float, ConcenVol float, CurrentStatus varchar, TestTime int, "
                         "Barcode varchar, TestWay int, IsAutoTest bool, IsPrint bool, IsRingWakeUp bool)");
    bResult &=success;

    success = query.exec("create table CurveData_tb(CurveNo int primary key, FittingWay varchar, "
                         "ReactionValue float, ConcenVol float, CalibrateNum int)");
    bResult &=success;

    success = query.exec("create table MainParam_tb(ItemNo int primary key, ItemName varchar, "
                         "InstrumentType varchar, PointNum int, BeginReadTime int, TestTime int,"
                         "ItemBarcode varchar, BuffLiquidVol float, SampleVol float, Point1 int,"
                         "PointNo1 int, Point2 int, PointNo2 int, BeginPoint int, EndPoint int,"
                         "GetValue float, Calculate float)");
    bResult &=success;

    success = query.exec("create table CompansateRatio_tb(ItemNo int primary key, ItemName varchar, Ratio float)");

    bResult &=success;

    success = query.exec("create table SuItemParam_tb(ItemNo int primary key, ItemName varchar,"
                         "Unit varchar, MinReference float, MaxReference float, P1 int, P2 int,"
                         "WholeBloodRatio int, FecesRatio float, QcLiquidRatio float, UrineLiquidRatio float, "
                         "SeruumRatio float, RatioPoint int, CompensatePoint int)");
    bResult &=success;

    if(success)
    {
        qDebug() << QObject::tr("数据库表创建成功！\n");
        return true;
    }
    else
    {
        qDebug() << QObject::tr("数据库表创建失败！\n");
        return false;
    }
}
bool databaseHelper::insert(QString strSql)            //出入数据
{
       QSqlDatabase m_database = QSqlDatabase::database("sqlite"); //建立数据库连接
       QSqlQuery query(m_database);
       query.prepare(strSql);
       bool success=query.exec();
       if(!success)
       {
           QSqlError lastError = query.lastError();
           qDebug() << lastError.driverText() << QString(QObject::tr("插入失败"));
           return false;
       }
       return true;
}


bool databaseHelper::update(QString strSql)  //更新
{
       QSqlDatabase m_database = QSqlDatabase::database("sqlite"); //建立数据库连接
       QSqlQuery query(m_database);
       query.prepare(strSql);
        bool success=query.exec();
        if(!success)
        {
             QSqlError lastError = query.lastError();
             qDebug() << lastError.driverText() << QString(QObject::tr("更新失败"));
        }
       return true;
}

bool databaseHelper::delete1(QString strSql)  //删除
{

      QSqlDatabase m_database = QSqlDatabase::database("sqlite"); //建立数据库连接
      QSqlQuery query(m_database);
      query.prepare(strSql);
      if(!query.exec())
      {
          qDebug() << "删除记录失败！";
          return false;
      }
      return true;
}
QSqlQuery* databaseHelper::queryAll(QString strSql)         //查询所有信息
{
    QSqlDatabase m_database = QSqlDatabase::database("sqlite"); //建立数据库连接
    QSqlQuery* query = new QSqlQuery(strSql, m_database);
    query->prepare(strSql);
    bool bResult = query->exec(strSql);
    if(bResult){
        qDebug()<<query->value(0).toInt();
    }

    return query;
}
int databaseHelper::getMaxID(QString strSql){
    int nMax = -1;
    QSqlDatabase m_database = QSqlDatabase::database("sqlite"); //建立数据库连接
    QSqlQuery *query = new QSqlQuery(strSql, m_database);
    //query.prepare(strSql);

    int maxID = query->record().indexOf("maxID");
    while(query->next()){
        //nMax = query->value(0).toInt();
        nMax = query->value(maxID).toInt();
    }
    delete query;
    return nMax;
}
*/


