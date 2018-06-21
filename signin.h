#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QMessageBox>
#include "keyboard.h"
#include <QDebug>
extern  bool lock;
namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = 0);
    ~SignIn();


   bool getlock (void);
 void sendMessage(char *message);
   void OpenKeyboard();
signals:
     void SendHomeSignal();

private slots:
     void on_PB_OUT_clicked();

     void on_PB_SignIn_clicked();
    bool eventFilter(QObject *,QEvent *);
private:
    Ui::SignIn *ui;
    //bool lock;
};

#endif // SIGNIN_H
