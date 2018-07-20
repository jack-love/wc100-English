#ifndef CAC_H
#define CAC_H

#include <QWidget>
#include <QDebug>
#include<ttythread.h>

class Cac : public QWidget
{
    Q_OBJECT
public:
    explicit Cac(QWidget *parent = 0);


unsigned char   rgbCalculation  (unsigned char SHZHXH,unsigned char weizhi,unsigned int *CLCORNO, unsigned int *BPH,unsigned int *JSBPH,unsigned int  *JIEGUO);
void gradientComparison();
bool calibrationCalculation( resultVal  *   ttyResult ,QString Name,unsigned char type,unsigned int * W,unsigned int *R,unsigned int *G,unsigned int * B,unsigned int *rgbResult);
bool intervalCalculation();//

signals:

public slots:


private:
    unsigned int JIEGUO[14];
  //     resultVal    result[13];

};

#endif // CAC_H
