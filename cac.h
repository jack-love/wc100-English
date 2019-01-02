#ifndef CAC_H
#define CAC_H

#include <QWidget>
#include <QDebug>
#include "ttythread.h"

class Cac : public QWidget
{
    Q_OBJECT
public:
    explicit Cac(QWidget *parent = 0);

    void    interval_Calculation(struct RESULT buf[]);
    unsigned int       wc100_algorithm(struct RESULT buf[15],unsigned int i, unsigned int position);
    void    get_CalculationResult(struct RESULT buf[], QString Name,struct resultRGB*  tmp);

signals:

public slots:


private:


};

#endif // CAC_H
