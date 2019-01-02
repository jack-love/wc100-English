#ifndef SYSTEMINIT_H
#define SYSTEMINIT_H
#include <QProgressDialog>
#include <QThread>
class Systeminit: public QThread
{
public:
    explicit Systeminit(QObject *parent = 0);
~Systeminit();

    QProgressDialog *progressDialog=NULL;

protected:
    void run();

};

#endif // SYSTEMINIT_H
