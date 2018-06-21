#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_PB_OUT_clicked()
{
 emit SendHomeSignal();
}

void SignIn::on_PB_SignIn_clicked()
{
    if (ui->edit_userName->text() == "username" && ui->edit_passWord->text() == "123456")
            accept();

        else
        {
            QMessageBox::warning(this," warning ", "User name and password error !",QMessageBox::Yes);

            ui->edit_userName->clear();
            ui->edit_passWord->clear();
            ui->edit_userName->setFocus();
        }
}
