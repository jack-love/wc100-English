#include "testresultmodel.h"

TestResultModel::TestResultModel()
{

}

void TestResultModel::setSampleNo(uint arg){
    this->SampleNo = arg;
}

void TestResultModel::setHatchTime(int arg){
    this->HatchTime = arg;
}

void TestResultModel::setSampleValue(QString arg){
    this->SampleValue = arg;
}

void TestResultModel::setSampleType(QString arg){
    this->SampleType = arg;
}

void TestResultModel::setItemNo(int arg){
    this->ItemNo = arg;
}

void TestResultModel::setItemName(QString arg){
    this->ItemName = arg;
}

void TestResultModel::setUnit(QString arg){
    this->Unit = arg;
}

void TestResultModel::setBarcode(QString arg){
    this->TbType = arg;
}

void TestResultModel::setTestWay(QString arg){
    this->TestWay = arg;
}

void TestResultModel::setSampleDate(QString arg){
    this->SampleDate = arg;
}

void TestResultModel::setIsPrint(bool arg){
    this->IsPrint = arg;
}

void TestResultModel::setFlag(char arg){
    this->Flag = arg;
}


uint TestResultModel::getSampleNo(){
    return SampleNo;
}

int TestResultModel::getHatchTime(){
    return HatchTime;//
}

QString TestResultModel::getSampleValue(){
    return SampleValue;
}

QString TestResultModel::getSampleType(){
    return SampleType;
}

int TestResultModel::getItemNo(){
    return ItemNo;
}

QString TestResultModel::getItemName(){
    return ItemName;
}

QString TestResultModel::getUnit(){
    return Unit;
}

QString TestResultModel::getBarcode(){
    return TbType;
}

QString TestResultModel::getTestWay(){
    return TestWay;
}

QString TestResultModel::getSampleDate(){
    return SampleDate;
}

bool TestResultModel::getIsPrint(){
    return IsPrint;
}

char TestResultModel::getFlag(){
    return Flag;
}
