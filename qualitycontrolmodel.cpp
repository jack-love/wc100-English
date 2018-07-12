#include "qualitycontrolmodel.h"

Sub_QC_Model::Sub_QC_Model(){

}

void Sub_QC_Model::setItem_sub_No(int arg){
    item_sub_No = arg;
}
void Sub_QC_Model::setQC_value(QString arg){
    qc_value = arg;
}

void Sub_QC_Model::setQC_Date(QString arg){
    qc_Date = arg;
}

int Sub_QC_Model::getItem_sub_No(){
    return item_sub_No;
}

QString Sub_QC_Model::getQC_value(){
    return qc_value;
}

QString Sub_QC_Model::getQC_Date(){
    return qc_Date;
}

QualityControlModel::QualityControlModel()
{
    //plstQcModel = new QList<double>();
}

void QualityControlModel::setItemNo(int arg){
    itemNo = arg;
}

void QualityControlModel::setBatchNo(QString arg){
    batchNo = arg;
}

void QualityControlModel::setTargetValue(float arg){
    targetValue = arg;
}

void QualityControlModel::setQc_CvValue(float arg){
    qc_CvValue = arg;
}

int QualityControlModel::getItemNo(){
    return itemNo;
}

QString QualityControlModel::getBatchNo(){
    return batchNo;
}

float QualityControlModel::getTargetValue(){
    return targetValue;
}

float QualityControlModel::getQc_CvValue(){
    return qc_CvValue;
}



