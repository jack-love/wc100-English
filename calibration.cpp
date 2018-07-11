#include "calibration.h"
#include "ui_calibration.h"

Calibration::Calibration(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Calibration)
{
    ui->setupUi(this);

    QRegExp regx("[0-9]+$");
    validator = new QRegExpValidator(regx, this);
    ui->edt_Calibrate0->setValidator(validator);
    ui->edt_Calibrate1->setValidator(validator);
    ui->edt_Calibrate2->setValidator(validator);
    ui->edt_Calibrate3->setValidator(validator);
    ui->edt_Calibrate4->setValidator(validator);
    ui->edt_Calibrate5->setValidator(validator);
    ui->edt_Calibrate6->setValidator(validator);
    ui->edt_Calibrate7->setValidator(validator);
}

Calibration::~Calibration()
{
    delete ui;
}

void Calibration::on_btn_Back_clicked()
{
      emit SendHomeSignal();
}

void Calibration::on_btn_Back_2_clicked()
{
    emit SendHomeSignal();
}

void Calibration::on_btn_options_setup_pressed(const QModelIndex &index)
{

}
