#include "patientmodel.h"

PatientModel::PatientModel()
{

}
void PatientModel::setName(QString arg){
    name = arg;

}

void PatientModel::setAge(int arg){
    age = arg;

}

void PatientModel::setSex(int arg){
    sex = arg;

}

void PatientModel::setSampleNo(uint arg){
    sampleNo = arg;
}

void PatientModel::setRegisterDateTime(QString arg){
    registerDateTime = arg;
}

QString PatientModel::getName(){
    return name;
}

int PatientModel::getAge(){
    return age;
}

int PatientModel::getSex(){
    return sex;
}

uint PatientModel::getSampleNo(){
    return sampleNo;
}


QString PatientModel::getRegisterDateTime(){
    return registerDateTime;
}
