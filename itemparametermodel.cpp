#include "itemparametermodel.h"

ItemParameterModel::ItemParameterModel()
{

}
void ItemParameterModel::setRegeantModel(int arg){
    regeantModel = arg;
}

void ItemParameterModel::setItemNo(int arg){
    itemNo = arg;
}

void ItemParameterModel::setItemName(QString arg){
    itemName = arg;
}

void ItemParameterModel::setItemProperty(QString arg){
    itemProperty = arg;
}

void ItemParameterModel::setRefMin(float arg){
    RefMin = arg;
}

void ItemParameterModel::setRefMax(float arg){
    RefMax = arg;
}

void ItemParameterModel::setUnit(QString arg){
    unit = arg;
}

void ItemParameterModel::setCheckWay(QString arg){
    checkWay = arg;
}

void ItemParameterModel::setPostSequence(int arg){
    postSequence = arg;
}

int ItemParameterModel::getRegeantModel(){
    return regeantModel;
}

int ItemParameterModel::getItemNo(){
    return itemNo;
}

QString ItemParameterModel::getItemName(){
    return itemName;
}

QString ItemParameterModel::getItemProperty(){
    return itemProperty;
}

float ItemParameterModel::getRefMin(){
    return RefMin;
}

float ItemParameterModel::getRefMax(){
    return RefMax;
}

QString ItemParameterModel::getUnit(){//
    return unit;
}

QString ItemParameterModel::getCheckWay(){
    return checkWay;
}

int ItemParameterModel::getPostSequence(){
    return postSequence;
}

