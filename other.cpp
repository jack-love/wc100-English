#include "other.h"
#include "ui_other.h"
#include "mainbussniessview.h"

Other::Other(QWidget *parent):
    QDialog(parent),ui(new Ui::Other)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。
     ui->label_Thank->setText(tr("Thank you for your use!"));
    ui->label_power->setText(tr("Please wait while shutdown .."));
}

Other::~Other()
{
    delete ui;
}
