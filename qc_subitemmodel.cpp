#include "qc_subitemmodel.h"

QC_SubItemModel::QC_SubItemModel()
{

}
void QC_SubItemModel::setItemNo(int arg){
    itemNo = arg;
}

void QC_SubItemModel::setQc_Value(QString arg){
  qc_Value = arg;
}

void QC_SubItemModel::setQc_Date(QString arg){
    qc_Date = arg;
}

int QC_SubItemModel::getItemNo(){
    return itemNo;
}

QString QC_SubItemModel::getQc_Value(){
    return qc_Value;
}

QString QC_SubItemModel::getQc_Date(){
    return qc_Date;
}
