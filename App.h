#ifndef APP_H
#define APP_H
#include <QString>
#include <QTranslator>
#include <QMutex>
#define MAX_ITEM 12
class App{
public:
    static QString AppFontName;
    static QString PYType;
    static QString AppStyle;
    static QString AppPath;
    static bool WriteConfig();
    static QString language_Chinese;
    static QString language_English;
    static QTranslator translator;
    static QString lanStr;
    static int current_language;
    static QMutex mutex;
    static bool test_finished;
    static bool test_result;
    static bool test_start;
};
class SystemConfig{
public :
    static bool isPrint;
    static bool isLISConnect;
    static int hatchTime;
    static uint newold_Model;
    static uint regeant_Model;
    static QString barcode;
    static QString sampleType;

};
struct RESULT{
    unsigned int calibration[8];                        //input
    unsigned int wrgb_value[4];                         //output
    unsigned int white_value[4];
    unsigned int mode;  //1 = new unit   2 = old unit   //input
    unsigned int paper_model;                           //input
    unsigned int block_num;                             //input
    unsigned int position;                              //output
    unsigned int wrgb_result_value;                     //output
    char unit[10];//- +- 1+ 2+ 3+ ...                   //output
    char name[6];                                       //input
    char item_value[9][10];                             //output
    char flag;
};
struct REPORT{
    char sampleNo[10];
    char userName[15];
    char sex[5];
    char age[5];
    char date[22];
    struct ITEM_RESULT{
        char itemName[8];
        char result[10];
        char unit[10];
        char flag[2];
    }item_result[MAX_ITEM];
};

#endif // APP_H
