#include "itemmodel.h"

ItemModel::ItemModel()
{

}
void ItemModel::setRegeantModel(int arg){
    regeantmodel = arg;
}
void ItemModel::setItemNo(int arg){
    itemNo = arg;
}

void ItemModel::setItemName(QString arg){
    itemName = arg;
}

void ItemModel::setFlag(QString arg){
    flag = arg;
}

int ItemModel::getRegeantModel(){
    return regeantmodel;
}

int ItemModel::getItemNo(){
    return itemNo;
}

QString ItemModel::getItemName(){
    return itemName;
}

QString ItemModel::getFlag(){
    return flag;
}

