#include "calibrateobservermodel.h"



void CalibrateObserverModel::setItemNo(int arg){
    _itemNo = arg;
}

void CalibrateObserverModel::setItemName(QString arg){
    _itemName = arg;
}

void CalibrateObserverModel::setWhite(int arg){
    _white = arg;
}

void CalibrateObserverModel::setRed(int arg){
    _red = arg;
}

void CalibrateObserverModel::setGreen(int arg){
    _green = arg;
}

void CalibrateObserverModel::setBlue(int arg){
    _blue = arg;
}

void CalibrateObserverModel::setCalibrateValue(int arg){
    _calibrateValue = arg;
}

void CalibrateObserverModel::setResultValue(QString arg){
    _resultValue = arg;
}

void CalibrateObserverModel::setCalibrateDate(QString arg){
    _calibrateDate = arg;
}

int CalibrateObserverModel::getItemNo(){
    return _itemNo;
}

QString CalibrateObserverModel::getItemName(){
    return _itemName;
}

int CalibrateObserverModel::getWhite(){
    return _white;
}

int CalibrateObserverModel::getRed(){
    return _red;
}

int CalibrateObserverModel::getGreen(){
    return _green;
}

int CalibrateObserverModel::getBlue(){
    return _blue;
}

int CalibrateObserverModel::getCalibrateValue(){
    return _calibrateValue;
}

QString CalibrateObserverModel::getResultValue(){
    return _resultValue;
}

QString CalibrateObserverModel::getCalibrateDate(){
    return _calibrateDate;
}
