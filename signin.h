#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QMessageBox>
#include <messagebox.h>
#include <QDebug>

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = 0);
    ~SignIn();



  
signals:
     void SendHomeSignal();

private slots:
     void on_PB_Out_clicked();
     void on_PB_SignIn_clicked();
     void on_PB_contact_clicked();
    void changeEvent(QEvent *e);
private:
    Ui::SignIn *ui;
       MessageBox  msg;
};

#endif // SIGNIN_H
