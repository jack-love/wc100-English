#include "testingdialog.h"
#include "ui_testingdialog.h"

TestingDialog::TestingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestingDialog)
{
    ui->setupUi(this);
}

TestingDialog::~TestingDialog()
{
    delete ui;
}
