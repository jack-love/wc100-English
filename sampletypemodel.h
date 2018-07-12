#ifndef SAMPLETYPEMODEL_H
#define SAMPLETYPEMODEL_H
#include <QString>
class SampleTypeModel
{
public:
    SampleTypeModel();

    void setSampleTypeNo(int);
    void setSampleTypeName(QString);
    void setSampleFlag(QString);
    int getSampleTypeNo();
    QString getSampleTypeName();
    QString getSampleFlag();
private:
    int SampleTypeNo;
    QString SampleTypeName;
    QString SampleFlag;
};

#endif // SAMPLETYPEMODEL_H
