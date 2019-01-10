#include "signin.h"
#include "ui_signin.h"
#include <QtTest>
#include "messagebox.h"
#include"App.h"

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。
   ui->edit_passWord->setEchoMode(QLineEdit::Password);

}


SignIn::~SignIn(){
    delete ui;
}

void SignIn::on_PB_Out_clicked(){
    emit SendHomeSignal();
}


void SignIn::on_PB_SignIn_clicked(){

        if (ui->edit_userName->text() == "jack" && ui->edit_passWord->text() == "123456")
            {
                  accept();
                msg.MessageBox_Info(tr("Login system"));
                 emit SendHomeSignal();
                  App::user_lock=true;
              }
            else {
                msg.MessageBox_Info(tr("Incorrect username or password!"));
                ui->edit_userName->clear();
                ui->edit_passWord->clear();
                ui->edit_userName->setFocus();
                App::user_lock=false;
            }

}



void SignIn::on_PB_contact_clicked(){
    msg.MessageBox_Info(tr("CHANGCHUN WANCHENG\nBIO ELECTRON CO.,LTD\n\nTel:+86-431-84859877\nEmail:yanruzhang@ccwancheng.com\n"));
}

void SignIn::changeEvent(QEvent *e){
//    QWidget::changeEvent(e);
//       switch (e->type()) {
//       case QEvent::LanguageChange:
//           ui->retranslateUi(this);
//           qDebug()<<"[SignIn]---->changeEvent";
//           break;
//       default:
//           break;
//       }

       if(e->type() == QEvent::LanguageChange)
           {
               ui->retranslateUi(this);
               qDebug()<<"[SignIn]---->changeEvent";
           }
           else
               QWidget::changeEvent(e);

}
