#include "calibration.h"
#include "ui_calibration.h"

Calibration::Calibration(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Calibration)
{
    ui->setupUi(this);
}

Calibration::~Calibration()
{
    delete ui;
}
