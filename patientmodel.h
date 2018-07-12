#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H
#include <qstring.h>
class PatientModel
{
public:
    PatientModel();

    void setName(QString);
    void setAge(int);
    void setSex(int);
    void setSampleNo(uint);
    void setRegisterDateTime(QString);

    QString getName();
    int getAge();
    int getSex();
    uint getSampleNo();
    QString getRegisterDateTime();

private:
    QString name;
    int age;
    int sex;
    int sampleNo;
    QString registerDateTime;

};

#endif // PATIENTMODEL_H
