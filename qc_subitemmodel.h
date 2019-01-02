#ifndef QC_SUBITEMMODEL_H
#define QC_SUBITEMMODEL_H
#include<QString>
class QC_SubItemModel
{
public:
    QC_SubItemModel();
    void setItemNo(int);
    void setQc_Value(QString);
    void setQc_Date(QString);
    int getItemNo();
    QString getQc_Value();
    QString getQc_Date();
private:
   int itemNo;
   QString qc_Value ;
   QString qc_Date;
};

#endif // QC_SUBITEMMODEL_H
