#ifndef TESTRESULTMODEL_H
#define TESTRESULTMODEL_H
#include <qstring.h>
#include <itemparametermodel.h>
#include <testresultmodel.h>
class TestResultModel
{
public:
    TestResultModel();
    //void setUserID(int);
    void setSampleNo(uint);
    void setHatchTime(int);
    void setSampleValue(QString);
    void setSampleType(QString);
    void setItemNo(int);
    void setItemName(QString);
    void setUnit(QString);
    void setBarcode(QString);
    void setTestWay(QString);
    void setSampleDate(QString);
    void setIsPrint(bool);
    void setFlag(char);

    //int getUserID();
    uint getSampleNo();
    int getHatchTime();
    QString getSampleValue();
    QString getSampleType();
    int getItemNo();
    QString getItemName();
    QString getUnit();
    QString getBarcode();
    QString getTestWay();
    QString getSampleDate();
    bool getIsPrint();
    char getFlag();
    ItemParameterModel parameterModel;
private:
    //int UserID;
    uint SampleNo;
    int HatchTime;
    QString SampleValue;
    QString SampleType;
    int ItemNo;
    QString ItemName;
    QString Unit;
    QString Barcode;
    QString TestWay;
    QString SampleDate;
    bool IsPrint;
    char Flag;

};

#endif // TESTRESULTMODEL_H
