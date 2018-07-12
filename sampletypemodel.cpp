#include "sampletypemodel.h"

SampleTypeModel::SampleTypeModel()
{

}
void SampleTypeModel::setSampleTypeNo(int arg){
    SampleTypeNo = arg;
}

void SampleTypeModel::setSampleTypeName(QString arg){
    SampleTypeName = arg;
}

void SampleTypeModel::setSampleFlag(QString arg){
    SampleFlag = arg;
}

int SampleTypeModel::getSampleTypeNo(){
    return SampleTypeNo;
}

QString SampleTypeModel::getSampleTypeName(){
    return SampleTypeName;
}

QString SampleTypeModel::getSampleFlag(){
    return SampleFlag;
}
