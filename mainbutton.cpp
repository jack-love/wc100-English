#include "mainbutton.h"
#include "ui_mainbutton.h"

Mainbutton::Mainbutton(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mainbutton)
{
    ui->setupUi(this);
}

Mainbutton::~Mainbutton()
{
    delete ui;
}
