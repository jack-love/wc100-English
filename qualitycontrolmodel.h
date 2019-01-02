#ifndef QUALITYCONTROLMODEL_H
#define QUALITYCONTROLMODEL_H
#include <qstring.h>
#include <QList>
class Sub_QC_Model{
public:
    Sub_QC_Model();
    void setItem_sub_No(int);
    void setQC_value(QString);
    void setQC_Date(QString);
    int getItem_sub_No();
    QString getQC_value();
    QString getQC_Date();
private:
    int item_sub_No;
    QString qc_value;
    QString qc_Date;
};

class QualityControlModel
{
public:
    QualityControlModel();

    void setItemNo(int arg);
    void setBatchNo(QString arg);
    void setTargetValue(float arg);
    void setQc_CvValue(float arg);
    int getItemNo();
    QString getBatchNo();
    float getTargetValue();
    float getQc_CvValue();
    QList<double> plstQcModel;
private:
    int itemNo;
    QString batchNo;
    float targetValue;
    float qc_CvValue;
};


#endif // QUALITYCONTROLMODEL_H
