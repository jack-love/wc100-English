#ifndef ITEMPARAMETER_H
#define ITEMPARAMETER_H

#include <QString>
class ItemParameterModel
{
public:
    ItemParameterModel();
    void setRegeantModel(int);
    void setItemNo(int);
    void setItemName(QString);
    void setItemProperty(QString);
    void setRefMin(float);
    void setRefMax(float);
    void setUnit(QString);
    void setCheckWay(QString);
    void setPostSequence(int);

    int getRegeantModel();
    int getItemNo();
    QString getItemName();
    QString getItemProperty();
    float getRefMin();
    float getRefMax();
    QString getUnit();
    QString getCheckWay();
    int getPostSequence();
private:
    int regeantModel;
    int itemNo;
    QString itemName;
    QString itemProperty;
    float RefMin;
    float RefMax;
    QString unit;
    QString checkWay;
    int postSequence;
};

#endif // ITEMPARAMETER_H
