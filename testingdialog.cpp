#include "testingdialog.h"
#include "ui_testingdialog.h"

TestingDialog::TestingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestingDialog)
{
   TestItem Itemval;
    ui->setupUi(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。
setItemval_Urs14cc();
showItemval_Urs14cc();
}




TestingDialog::~TestingDialog()
{
    delete ui;
}

void TestingDialog::showItemval_Urs14cc()
{
ui->edit_Number->setText("14");
ui->edit_Model->setText("URS4CC");

ui->leftShow_1->setText("10");
ui->rightShow_1->setText("20");


ui->leftShow_2->setText("10");
ui->rightShow_2->setText("20");

ui->leftShow_3->setText("10");
ui->rightShow_3->setText("20");

ui->leftShow_4->setText("10");
ui->rightShow_4->setText("20");

ui->leftShow_5->setText("10");
ui->rightShow_5->setText("20");

ui->leftShow_6->setText("10");
ui->rightShow_6->setText("20");

ui->leftShow_7->setText("10");
ui->rightShow_7->setText("20");

ui->leftShow_8->setText("20");
}

void TestingDialog::setItemval_Urs14cc()
{
ui->leftSelection_1->setCurrentIndex(URO);
ui->rightSelection_1->setCurrentIndex(BIL);
ui->leftShow_1->setText("10");
ui->leftSelection_2->setCurrentIndex(KET);
ui->rightSelection_2->setCurrentIndex(CRE);

ui->leftSelection_3->setCurrentIndex(BLD);
ui->rightSelection_3->setCurrentIndex(PRO);


ui->leftSelection_4->setCurrentIndex(MALB);
ui->rightSelection_4->setCurrentIndex(NIT);

ui->leftSelection_5->setCurrentIndex(WBC);
ui->rightSelection_5->setCurrentIndex(GLU);

ui->leftSelection_6->setCurrentIndex(SG);
ui->rightSelection_6->setCurrentIndex(PH);

ui->leftSelection_7->setCurrentIndex(VC);
ui->rightSelection_7->setCurrentIndex(CA);
ui->leftSelection_8->setCurrentIndex(ACR);
}

void TestingDialog::on_btn_Back_clicked()
{
//qDebug("bug--->mainbuttondialog.cpp---> SendHomeSignal");
 emit SendHomeSignal();
}
