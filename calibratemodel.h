#ifndef CALIBRATEMODEL_H
#define CALIBRATEMODEL_H
#include <QString>
class CalibrateModel
{
public:
    CalibrateModel();
    void setItemNo(int);
    void setCalibrateValue0(int);
    void setCalibrateValue1(int);
    void setCalibrateValue2(int);
    void setCalibrateValue3(int);
    void setCalibrateValue4(int);
    void setCalibrateValue5(int);
    void setCalibrateValue6(int);
    void setCalibrateValue7(int);

    int getItemNo();
    int getCalibrateValue0();
    int getCalibrateValue1();
    int getCalibrateValue2();
    int getCalibrateValue3();
    int getCalibrateValue4();
    int getCalibrateValue5();
    int getCalibrateValue6();
    int getCalibrateValue7();

    void setLaderValue0(QString);
    void setLaderValue1(QString);
    void setLaderValue2(QString);
    void setLaderValue3(QString);
    void setLaderValue4(QString);
    void setLaderValue5(QString);
    void setLaderValue6(QString);
    void setLaderValue7(QString);

    QString getLaderValue0();
    QString getLaderValue1();
    QString getLaderValue2();
    QString getLaderValue3();
    QString getLaderValue4();
    QString getLaderValue5();
    QString getLaderValue6();
    QString getLaderValue7();
private:
    int itemNo;
    int calibrateValue0;
    int calibrateValue1;
    int calibrateValue2;
    int calibrateValue3;
    int calibrateValue4;
    int calibrateValue5;
    int calibrateValue6;
    int calibrateValue7;

    QString laderValue0;
    QString laderValue1;
    QString laderValue2;
    QString laderValue3;
    QString laderValue4;
    QString laderValue5;
    QString laderValue6;
    QString laderValue7;
};

#endif // CALIBRATEMODEL_H
