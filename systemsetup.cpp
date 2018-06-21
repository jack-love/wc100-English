#include "systemsetup.h"
#include "ui_systemsetup.h"

SystemSetup::SystemSetup(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::SystemSetup)
{
    ui->setupUi(this);
}

SystemSetup::~SystemSetup()
{
    delete ui;
}

void SystemSetup::on_btn_Back_clicked()
{
    emit SendHomeSignal();
}
