#include "mainbutton.h"
#include "ui_mainbutton.h"

Mainbutton::Mainbutton(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainbutton)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    //QPoint point(0, 0);
    //this->move(point);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。

}

Mainbutton::~Mainbutton()
{
    delete ui;
}

void Mainbutton::on_btn_History_clicked()
{
    emit on_btn_History();
}

void Mainbutton::on_btn_Maintancance_clicked()
{
    emit on_btn_Maintancance();
}

void Mainbutton::on_btn_Calibration_clicked()
{
    emit on_btn_Calibration();
}

void Mainbutton::on_btn_System_clicked()
{
     emit on_btn_System();
}

void Mainbutton::on_btn_Update_clicked()
{
    emit on_btn_Update();
}


void Mainbutton::on_btn_Help_clicked()
{
    emit SendHomeSignal();
}

void Mainbutton::on_btn_SignIn_clicked()
{
emit on_btn_SignIn();
}

void Mainbutton::on_btn_Test_clicked()
{
emit on_btn_Testing();
}

void Mainbutton::on_btn_Power_clicked()
{
emit on_btn_Other();
}

void Mainbutton::changeEvent(QEvent *e){
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

           }
           else
               QWidget::changeEvent(e);

}
