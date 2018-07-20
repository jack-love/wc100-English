#include"App.h"
#include "qdatetime.h"
QString App::AppFontName = "Ubuntu";
QString App::PYType = "wubi-jidian86";
QString App::AppStyle = "";
QString App::AppPath = "/usr/share/ibus-table/tables";
bool App::test_result = false;
QTranslator App::translator;
bool App::WriteConfig(){
    return false;
}
QString App::language_Chinese = ":/pinyin/chinese.qm";
QString App::language_English = ":/pinyin/english.qm";
QString App::lanStr = "CHINESE";
QMutex App::mutex;
bool App::test_finished = false;
bool App::test_start = false;
int App::current_language = 0;
bool SystemConfig::isPrint = true;
bool SystemConfig::isLISConnect = false;
int SystemConfig::hatchTime = 40;
uint SystemConfig::newold_Model = 0;
uint SystemConfig::regeant_Model = 0;
QString SystemConfig::barcode = "123456";
QString SystemConfig::sampleType = QString::fromUtf8("尿常规");
unsigned int App::Wb_w   ;
unsigned int App::Wb_r    ;
unsigned int App::Wb_g   ;
unsigned int App::Wb_b  ;
unsigned int App::white_value[4];
