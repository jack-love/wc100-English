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
                         "SampleType varchar, ItemNo int, ItemName varchar,SampleValue varchar,Unit varchar, "
                         "TbType varchar, TestWay varchar, SampleDate varchar, IsPrint bool, Flag varchar)");
    //query.exec(QObject::tr("insert into TestResult_tb values (23, 1, 22, '20.5', 'blood', 1, 'WEB', 'testing', '345', '1', '2017-12-22', 1, 0)"));
    //query.exec(QObject::tr("insert into TestResult_tb values (23, 2, 33, '32.5', 'blood', 2, 'KET', 'testing', '345', '2', '2017-10-19', 1, 0)"));
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

//TbType
    success = query.exec("create table item_tb_11_3(regeant_model int, ItemNo int, ItemName varchar, flag varchar, primary key (regeant_model,ItemNo))");
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 0, 'BIL', '0')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 1, 'URO', '1')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 2, 'KET', '2')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 3, 'BLD', '3')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 4, 'PRO', '4')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 5, 'NIT', '5')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 6, 'WBC', '6')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 7, 'GLU', '7')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 8, 'SG', '8')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 9, 'PH', '9')"));
    query.exec(QObject::tr("insert into item_tb_11_3 values (0, 10, 'VC', '10')"));
     bResult &=success;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    success = query.exec("create table item_tb_10T(regeant_model int, ItemNo int, ItemName varchar, flag varchar, primary key (regeant_model,ItemNo))");
    query.exec(QObject::tr("insert into item_tb_10T values (0, 0, 'LEU', '0')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 1, 'NIT', '1')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 2, 'URO', '2')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 3, 'PRO', '3')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 4, 'PH', '4')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 5, 'BLD', '5')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 6, 'SG', '6')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 7, 'KET', '7')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 8, 'BIL', '8')"));
    query.exec(QObject::tr("insert into item_tb_10T values (0, 9, 'GLU', '9')"));
    bResult &=success;


    success = query.exec("create table item_tb_12MA(regeant_model int, ItemNo int, ItemName varchar, flag varchar, primary key (regeant_model,ItemNo))");
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 0, 'URO', '0')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 1, 'BIL',   '1')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 2, 'KET',   '2')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 3, 'BLD',   '3')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 4, 'PRO',  '4')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 5, 'NIT',   '5')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 6, 'LEU',   '6')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 7, 'GLU',   '7')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 8, 'SG',     '8')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 9, 'PH',     '9')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 10, 'VC',  '10')"));
    query.exec(QObject::tr("insert into item_tb_12MA values (0, 11, 'MALB', '11')"));
    bResult &=success;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------system
success = query.exec("create table system_setup(id int, species varchar, testPapertype varchar, language varchar,  testMode varchar, serialNumber int,primary key (id))");
query.exec(QObject::tr("insert into system_setup values ( 0 , 'human' ,  '10T'     ,  'English'   ,    'manual' , 0)"));
bResult &=success;


success = query.exec("create table system_setup_species(id int, species varchar, primary key (id))");
query.exec(QObject::tr("insert into system_setup_species  values ( 0 , 'human' )"));
query.exec(QObject::tr("insert into system_setup_species  values ( 1 , 'animal' )"));
bResult &=success;

success = query.exec("create table system_setup_testPapertype(id int, testPapertype varchar, primary key (id))");
query.exec(QObject::tr("insert into system_setup_testPapertype  values ( 0 , '10T' )"));
query.exec(QObject::tr("insert into system_setup_testPapertype  values ( 1 , '11-III' )"));
query.exec(QObject::tr("insert into system_setup_testPapertype  values ( 2 , '12MA' )"));
bResult &=success;

success = query.exec("create table system_setup_language(id int, language varchar, primary key (id))");
query.exec(QObject::tr("insert into system_setup_language  values ( 0 , 'English' )"));
query.exec(QObject::tr("insert into system_setup_language  values ( 1 , 'Chinese' )"));
bResult &=success;

success = query.exec("create table system_setup_testMode(id int, testMode varchar, primary key (id))");
query.exec(QObject::tr("insert into system_setup_testMode  values ( 0 , 'automatic' )"));
query.exec(QObject::tr("insert into system_setup_testMode  values ( 1 , 'manual' )"));
bResult &=success;



//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    success = query.exec("create table ItemParameter_tb_11_3(regeant_model int, ItemNo int, ItemName varchar, "
                         "ItemProperty varchar, RefMin float, RefMax float, Unit varchar,"
                         "CheckWay varchar, PostSequence int, primary key (regeant_model,ItemNo))");
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 0, 'BIL',   'P', 0.2,   5.6, 'umol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 1, 'URO', 'P', 0.12, 7.6, 'umol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 2, 'KET', 'P', 0.2, 5.6, 'mmol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 3, 'BLD', 'P', 0.12, 7.6, 'cells/uL', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 4, 'PRO', 'P', 0.2, 5.6, 'g/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 5, 'NIT', 'P', 0.12, 7.6, '    ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 6, 'WBC', 'P', 0.2, 5.6, 'cells/uL', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 7, 'GLU', 'P', 0.12, 7.6, 'mmol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 8, 'SG', 'P', 0.2, 5.6, '   ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 9, 'PH', 'P', 0.12, 7.6, '  ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_11_3 values (0, 10, 'VC', 'P', 0.2, 5.6, 'mmol/L', '00', 1)"));
    bResult &=success;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    success = query.exec("create table ItemParameter_tb_10T(regeant_model int, ItemNo int, ItemName varchar, "
                         "ItemProperty varchar, RefMin float, RefMax float, Unit varchar,"
                         "CheckWay varchar, PostSequence int, primary key (regeant_model,ItemNo))");

    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 0, 'LEU', 'P',  0.2,  5.6, 'cells/uL', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 1, 'NIT',  'P', 0.12, 7.6, '       ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 2, 'URO', 'P', 0.2,   5.6, 'umol/L ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 3, 'PRO', 'P', 0.12, 7.6, 'g/L'        , '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 4, 'PH'  ,  'P',   0.2, 5.6, '   ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 5, 'BLD', 'P', 0.12, 7.6, 'cells/uL', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 6, 'SG',   'P',   0.2, 5.6, '    ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 7, 'KET', 'P',  0.12, 7.6, 'mmol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 8,  'BIL', 'P',  0.12, 7.6,   'umol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_10T values (0, 9, 'GLU', 'P',    0.2, 5.6,   'mmol/L', '00', 1)"));

    bResult &=success;
   //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    success = query.exec("create table ItemParameter_tb_12MA(regeant_model int, ItemNo int, ItemName varchar, "
                         "ItemProperty varchar, RefMin float, RefMax float, Unit varchar,"
                         "CheckWay varchar, PostSequence int, primary key (regeant_model,ItemNo))");
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 0, 'URO', 'P', 0.2, 5.6, 'umol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 1, 'BIL', 'P', 0.12, 7.6, 'umol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 2, 'KET', 'P', 0.2, 5.6, 'mmol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 3, 'BLD', 'P', 0.12, 7.6, 'cells/uL', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 4, 'PRO', 'P', 0.2, 5.6, 'g/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 5, 'NIT', 'P', 0.12, 7.6, '    ', '00', 1)"));

    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 6, 'LEU', 'P', 0.12, 7.6, 'cells/uL', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 7, 'GLU', 'P', 0.2, 5.6, 'mmol/L', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 8, 'SG', 'P', 0.12, 7.6,  '    ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 9, 'PH', 'P', 0.2, 5.6,   '     ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 10, 'VC', 'P', 0.2, 5.6,   'mmol/L ', '00', 1)"));
    query.exec(QObject::tr("insert into ItemParameter_tb_12MA values (0, 11, 'MALB', 'P', 0.12, 7.6, 'g/L', '00', 1)"));

    bResult &=success;
 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
const extern char valueitemsi[14][8][9]={
" -  3.3  ","+-  16   ","1+  33   ","2+  66   ","3+  131  ","3+  131  ","3+  131  ","3+  131  ",//uro  尿胆原
" -  Neg  ","1+  17   ","2+  50   ","3+  100  ","3+  100  ","3+  100  ","3+  100  ","3+  100  ",//bil  胆红素
" -  Neg  ","+-  0.5  ","1+  1.5  ","2+  4.0  ","3+  8.0  ","4+  16   ","4+ 16    ","4+  16   ",//ket  酮体
" -  Neg  ","+-  10 ca","1+  25 ca","2+  80 ca","3+  200ca","3+  200ca","3+  200ca","3+  200ca",//bld  潜血3
" -  Neg  ","+-  0.2  ","1+  0.3  ","2+  1.0  ","3+  3.0  ","3+  3.0  ","3+  3.0  ","3+  3.0  ",//pro  蛋白质
" -  Neg  "," +  Pos  "," +  Pos  "," +  Pos  "," +  Pos  "," +  Pos  "," +  Pos  "," +  Pos  ",//nit  亚硝酸盐5
" -  Neg  ","+-  15 ca","1+  70 ca","2+  125ca","3+  500ca","3+  500ca","3+  500ca","3+  500ca",//leu  白细胞6
" -  Neg  ","1+  5.5  ","2+  14   ","3+  28   ","4+  55   ","4+  55   ","4+  55   ","4+  55   ",//glu  葡萄糖
"    1.005","    1.010","    1.015","    1.020","    1.025","    1.030","    1.030","    1.030",//sg   比重8
"    5.0  ","    6.0  ","    6.5  ","    7.0  ","    7.5  ","    8.0  ","    8.5  ","    9.0  ",//ph   酸碱度9
"    0    ","    0.5  ","    1.5  ","    3.0  ","    6.0  ","    6.0  ","    6.0  ","    6.0  ",//vc   维生素c
" -  Neg  ","    0.15 ","    0.15 ","    0.15 ","    0.15 ","    0.15 ","    0.15 ","    0.15 ",//nc
"         ","         ","         ","         ","         ","         ","         ","         ",//nc
" -  0.9  ","1+  4.4  ","2+  13.2 ","3+  26.5 ","3+  26.5 ","3+  26.5 ","3+  26.5 ","3+  26.5 ",//肌  酐:
};
*/
    success = query.exec("create table Calibrate_tb_11_3(ItemNo int primary key, CalibrateValue0 int, CalibrateValue1 int, CalibrateValue2 int, CalibrateValue3 int,"
                         "CalibrateValue4 int, CalibrateValue5 int, CalibrateValue6 int, CalibrateValue7 int, ResultValue0 varchar, ResultValue1 varchar, ResultValue2 varchar, ResultValue3 varchar, ResultValue4 varchar, ResultValue5 varchar,ResultValue6 varchar, ResultValue7 varchar)");
    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (0, 111, 123, 147, 666, 123, 456, 789, 258, '- Neg', '1+ 17', '2+ 50', '3+ 100', '3+ 100', '3+ 100', '3+ 100', '3+ 100')")); //BIL

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (1, 111, 123, 147, 666, 123, 456, 789, 258, '- 3.3' ,  '+- 16', '1+ 33',  '2+ 66',   '3+ 131', '3+ 131', '3+ 131', '3+ 131')")); //URO

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (2, 111, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.5', '1+ 1.5', '2+ 2.9', '3+ 7.8', '4+ 16', '4+ 16', '4+ 16')"));//KET

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (3, 111, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 10ca', '1+ 25ca', '2+ 80ca', '3+ 200ca', '3+ 200ca', '3+ 200ca', '3+ 200ca')"));//BLD

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (4, 111, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.2', '1+ 0.3', '2+ 1.0', '3+ 3.0', '3+ 3.0','3+ 3.0','3+ 3.0')"));//PRO

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (5, 111, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+Pos', '+Pos', '+ Pos', '+Pos', '+Pos', '+Pos', '+Pos')"));//NIT

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (6, 111, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 15ca', '1+ 70ca', '2+ 125ca', '3+ 500ca', '3+ 500ca', '3+ 500ca', '3+ 500ca')"));//WBC

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (7, 111, 123, 147, 666, 123, 456, 789, 258, '- Neg', '1+ 5.5', '2+ 14', '3+ 28', '4+ 55', '4+ 55','4+ 55','4+ 55')"));//GLU

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (8, 111, 123, 147, 666, 123, 456, 789, 258,  '1.005','1.010','1.015','1.020','1.025','1.030','1.030','1.030')"));//SG

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (9, 111, 123, 147, 666, 123, 456, 789, 258, '5.0', '6.0', '6.5', '7.0', '7.5', '8.0', '8.5  ', '9.0')"));//PH

    query.exec(QObject::tr("insert into Calibrate_tb_11_3 values (10, 111, 123, 147, 666, 123, 456, 789, 258, '0', '0.5', '1.5', '3.0', '6.0', '6.0', '6.0', '6.0')"));//VC
    bResult &=success;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    success = query.exec("create table Calibrate_tb_10T(ItemNo int primary key, CalibrateValue0 int, CalibrateValue1 int, CalibrateValue2 int, CalibrateValue3 int,"
                         "CalibrateValue4 int, CalibrateValue5 int, CalibrateValue6 int, CalibrateValue7 int, ResultValue0 varchar, ResultValue1 varchar, ResultValue2 varchar, ResultValue3 varchar, ResultValue4 varchar, ResultValue5 varchar,ResultValue6 varchar, ResultValue7 varchar)");
    query.exec(QObject::tr("insert into Calibrate_tb_10T values (0, 222, 123, 147, 666, 123, 456, 789, 258, '- Neg','+- 15ca','1+ 70ca','2+ 125ca','3+ 500ca','3+ 500ca','3+ 500ca','3+ 500ca')"));//LEU

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (1, 222, 123, 147, 666, 123, 456, 789, 258, '- Neg','+Pos','+Pos','+Pos','+Pos','+Pos',' +Pos',' +Pos')"));//NIT

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (2, 222, 123, 147, 666, 123, 456, 789, 258, '- 3.3' ,'+- 16','1+ 33' ,'2+ 66','3+ 131','3+ 131','3+ 131','3+ 131')"));//URO

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (3, 222, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.2', '1+ 0.3', '2+ 1.0', '3+ 3.0', '3+ 3.0','3+ 3.0','3+ 3.0')"));//PRO

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (4, 222, 123, 147, 666, 123, 456, 789, 258, '5.0', '6.0', '6.5', '7.0', '7.5', '8.0', '8.5  ', '9.0')"));//PH

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (5, 222, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 10ca', '1+ 25ca', '2+ 80ca', '3+ 200ca', '3+ 200ca', '3+ 200ca', '3+ 200ca')"));//BLD

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (6, 222, 123, 147, 666, 123, 456, 789, 258,'1.005','1.010','1.015','1.020','1.025','1.030','1.030','1.030')"));//SG

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (7, 222, 123, 147, 666, 123, 456, 789, 258, '- Neg','+- 0.5','1+ 1.5','2+ 4.0','3+ 8.0','4+ 16','4+ 16','4+ 16')"));//KET

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (8, 222, 123, 147, 666, 123, 456, 789, 258, '- Neg','1+ 17','2+ 50','3+ 100','3+ 100','3+ 100','3+ 100','3+ 100')"));//BIL

    query.exec(QObject::tr("insert into Calibrate_tb_10T values (9, 222, 123, 147, 666, 123, 456, 789, 258, '- Neg', '1+ 5.5', '2+ 14', '3+ 28', '4+ 55', '4+ 55', '4+ 55', '4+ 55')"));//GLU


    bResult &=success;



    success = query.exec("create table Calibrate_tb_12MA(ItemNo int primary key, CalibrateValue0 int, CalibrateValue1 int, CalibrateValue2 int, CalibrateValue3 int,"
                         "CalibrateValue4 int, CalibrateValue5 int, CalibrateValue6 int, CalibrateValue7 int, ResultValue0 varchar, ResultValue1 varchar, ResultValue2 varchar, ResultValue3 varchar, ResultValue4 varchar, ResultValue5 varchar,ResultValue6 varchar, ResultValue7 varchar)");
    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (0, 333, 123, 147, 666, 123, 456, 789, 258, '- 3.3', '+- 16', '1+ 33', '2+ 66', '3+ 131', '3+ 131', '3+ 131', '3+ 131')"));//URO

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (1, 333, 123, 147, 666, 123, 456, 789, 258, '- Neg', '1+ 17', '2+ 50', '3+ 100', '3+ 100', '3+ 100','3+ 100', '3+ 100')"));//BIL

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (2, 333, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.5', '1+ 1.5', '2+ 2.9', '3+ 7.8', '4+ 16', '4+ 16', '4+ 16')"));//KET

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (3, 333, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 10ca', '1+ 25ca', '2+ 80ca', '3+ 200ca', '3+ 200ca', '3+ 200ca', '3+ 200ca')"));//BLD

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (4, 333, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+- 0.2', '1+ 0.3', '2+ 1.0', '3+ 3.0', '3+ 3.0','3+ 3.0','3+ 3.0')"));//PRO

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (5, 333, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+Pos', '+Pos', '+Pos', '+Pos', '+Pos', '+Pos', '+Pos')"));//NIT

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (6, 333, 123, 147, 666, 123, 456, 789, 258, '- Neg', '+-  15ca', '1+  70ca', '2+  125ca', '3+  500ca', '3+  500ca', '3+  500ca', '3+  500ca')"));//LEU

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (7, 333, 123, 147, 666, 123, 456, 789, 258,'- Neg', '1+ 5.5', '2+ 14', '3+ 28', '4+ 55', '4+ 55', '4+ 55', '4+ 55')"));//GLU

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (8, 333, 123, 147, 666, 123, 456, 789, 258, '1.005','1.010','1.015','1.020','1.025','1.030','1.030','1.030')"));//SG

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (9, 333, 123, 147, 666, 123, 456, 789, 258, '5.0', '6.0', '6.5', '7.0', '7.5', '8.0', '8.5', '8.5')"));//PH

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (10, 333, 123, 147, 666, 123, 456, 789, 258, '0', '0.5 ', '1.5', '3.0', '6.0', '6.0', '6.0', '6.0')"));//VC

    query.exec(QObject::tr("insert into Calibrate_tb_12MA values (11, 333, 123, 147, 666, 123, 456, 789, 258,'-  Neg', '0.15', '  0.15', '0.15', '0.15', '0.15', ' 0.15', ' 0.15')"));//MALB

    bResult &=success;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    success = query.exec("create table Calibrate_Oberservable_tb(White int, Red int, Green int, Blue int, CalibrateValue int, ResultValue varchar, CalibrateDate varchar, ItemNo int, ItemName varchar)");
    //query.exec(QObject::tr("insert into Calibrate_Oberservable_tb values ( 456, 123, 789, 222, 456, '-Neg', '2018-01-11 12:12:00', 1, 'WBC')"));
   // query.exec(QObject::tr("insert into Calibrate_Oberservable_tb values ( 258, 369, 147, 666, 789, '-Neg', '2018-01-05 10:14:59', 2, 'KET')"));
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

    //pTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
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
