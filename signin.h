#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QMessageBox>
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
     void on_PB_OUT_clicked();

     void on_PB_SignIn_clicked();

private:
    Ui::SignIn *ui;
};

#endif // SIGNIN_H
