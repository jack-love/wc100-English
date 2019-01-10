#include"App.h"
#include "qdatetime.h"
#include <QLineEdit>

QLineEdit* App::edtSampleNo;
QString App::Species="";
QString App::Language="";
int         App::Language_count=0;
QString App::TestMode="";
QString App::TestPapertype="";
QString App::mcu_version="VER: 1.0.5";
QString App::sys_version="VER:2.9.8";//english ok
unsigned int App::serialNumber=1;
bool App::test_result = false;
bool App::user_lock=false;
QString App::language_Chinese = ":/pinyin/chinese.qm";
QString App::language_English = ":/pinyin/english.qm";
QMutex App::mutex;
bool App::test_finished = false;
bool App::test_start = false;
bool App::wifi_connect=false;
char App::Electric_quantity=0;
bool SystemConfig::isPrint = true;
int SystemConfig::hatchTime = 40;
uint SystemConfig::newold_Model = 0;
uint SystemConfig::regeant_Model = 0;
QString SystemConfig::barcode = "11T";
QString SystemConfig::sampleType = QString::fromUtf8("尿常规");
volatile bool   App::RUN=false;
unsigned int  App::workMode   ;
unsigned int  App::white_value[4];
unsigned int  App::paperType;
unsigned int  App:: MAX_ITEM=0;
unsigned int  App::errNumber=0;
