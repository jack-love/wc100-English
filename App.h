#ifndef APP_H
#define APP_H
#include <QString>
#include <QTranslator>
#include <QMutex>
#include <QLineEdit>

//#define MAX_ITEM 12
class App{
public:
    static QString language_Chinese;
    static QString language_English;
    static QString Species;
    static QString Language;
    static int Language_count;
    static QString TestMode;
    static QString  mcu_version;
    static QString  sys_version;
    static unsigned int  serialNumber;
    static unsigned int errNumber;
    static char Electric_quantity;
    static QString TestPapertype;
    static unsigned int MAX_ITEM;
    static QMutex mutex;
    static bool test_finished;
    static bool wifi_connect;
    static bool test_result;
    static bool test_start;
    static  volatile bool   RUN;
    static unsigned int workMode   ;
    static bool user_lock;
   static unsigned int white_value[4];
   static unsigned int paperType;
   static QLineEdit* edtSampleNo;
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

struct RESULT{//Result
    unsigned int calibration[8];                        //input
    unsigned int wrgb_value[4];                         //output
    unsigned int white_value[4];
    unsigned int mode;  //1 = new unit   2 = old unit   //input
    unsigned int paper_model;                           //input
    unsigned int block_num;                             //input
    unsigned int position;                              //output
    unsigned int calculation_results;                     //output
    char unit[10];//- +- 1+ 2+ 3+ ...                   //output
    char name[6];                                       //input
    char item_value[9][10];                             //output
    char flag;
};
struct  resultRGB
{
  unsigned int W;
  unsigned int R;
  unsigned int G;
  unsigned int B;
  unsigned int Result;
  char unit[10];
};
struct  gResult{
  unsigned int *W;
  unsigned int *R;
  unsigned int *G;
  unsigned int *B;
  unsigned int *Result;
  char *unit;
};


#endif // APP_H
