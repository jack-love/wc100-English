#ifndef CAC_H
#define CAC_H

#include <QWidget>
#include <QDebug>


class Cac : public QWidget
{
    Q_OBJECT
public:
    explicit Cac(QWidget *parent = 0);


 unsigned char   rgbCalculation  (unsigned char SHZHXH,unsigned char weizhi,unsigned int *CLCORNO, unsigned int *BPH,unsigned int *JSBPH,unsigned int  *JIEGUO);
    void gradientComparison();


signals:

public slots:


private:
    unsigned int JIEGUO[14];
};

#endif // CAC_H
