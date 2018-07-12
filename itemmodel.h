#ifndef ITEMMODEL_H
#define ITEMMODEL_H
#include <QString>
class ItemModel
{
public:
    ItemModel();
    void setRegeantModel(int);
    void setItemNo(int);
    void setItemName(QString);
    void setFlag(QString);
    int getRegeantModel();
    int getItemNo();
    QString getItemName();
    QString getFlag();
private:
    int regeantmodel;
    int itemNo;
    QString itemName;
    QString flag;
};

#endif // ITEMMODEL_H
