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

}
