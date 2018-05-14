#include "mainbutton.h"
#include "ui_mainbutton.h"

Mainbutton::Mainbutton(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainbutton)
{
   // qDebug("bug--->mainbuttondialog.cpp---> MainButtonDialog()");
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    QPoint point(0, 0);
    this->move(point);
}

Mainbutton::~Mainbutton()
{
    delete ui;
}

void Mainbutton::on_btn_Testing_clicked()
{
 emit on_btn_Testing();
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

void Mainbutton::on_btn_Other_clicked()
{
emit on_btn_Other();
}

void Mainbutton::on_btn_Password_clicked()
{
emit on_btn_Password();
}
