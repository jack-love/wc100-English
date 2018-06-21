#include "signin.h"
#include "ui_signin.h"
 bool lock;

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

    ui->edit_userName ->installEventFilter(this);
    ui->edit_passWord ->installEventFilter(this);
  lock=false;

}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_PB_OUT_clicked()
{
 emit SendHomeSignal();
}

void SignIn::sendMessage(char *message){

    QMessageBox box;
    box.setText(QString::fromLocal8Bit(message));
    box.setStyleSheet("color:red");
    QFont font;
    font.setPixelSize(30);
    box.setFont(font);
    box.setFixedSize(300, 300);
    int bret = box.exec();

}
void SignIn::on_PB_SignIn_clicked()
{
    if (ui->edit_userName->text() == "jack" && ui->edit_passWord->text() == "123456")
        {

              accept();
            //  QMessageBox::warning(this," username ", "Sign in  System",QMessageBox::Yes);
sendMessage("Sign in  System");
             emit SendHomeSignal();
              lock=true;
              qDebug() << "on_PB_SignIn_clicked"<< lock ;
          }
        else
        {
         //   QMessageBox::warning(this," warning ", "User name and password error !",QMessageBox::Yes);
sendMessage("User name and password error !");
            ui->edit_userName->clear();
            ui->edit_passWord->clear();
            ui->edit_userName->setFocus();
            lock=false;
        }
}

bool SignIn::eventFilter(QObject *watched, QEvent *event)
{
    if (watched==ui->edit_userName)
    {
    if (event->type()==QEvent::FocusIn){OpenKeyboard();}
     ui->edit_userName ->clearFocus();
    }

    if (watched==ui->edit_passWord)
    {
    if (event->type()==QEvent::FocusIn){OpenKeyboard();}
     ui->edit_passWord ->clearFocus();
    }



    return QWidget::eventFilter(watched,event);
}

bool SignIn::getlock()
{
qDebug() << "bool SignIn::getlock()"<< lock ;
return  lock;
}

void SignIn::OpenKeyboard()
{
    KeyBoard *v_key = new KeyBoard(this);
    if(ui->edit_userName ->hasFocus())
    {
        v_key->setWindowTitle(QString::fromUtf8("请输入内容"));
        if(v_key->exec()==QDialog::Accepted)
        {
            QString ret = v_key->GetInputBuf(); //返回键盘输入的结果
            if(0==ret.size())
            //如果打开了键盘但是没有输入任何内容
            {ret = ui->edit_userName->text();}
            ui->edit_userName ->setText(ret);
        }
    }

    if(ui->edit_passWord ->hasFocus())
    {
        v_key->setWindowTitle(QString::fromUtf8("请输入内容"));
        if(v_key->exec()==QDialog::Accepted)
        {
            QString ret = v_key->GetInputBuf(); //返回键盘输入的结果
            if(0==ret.size())
            //如果打开了键盘但是没有输入任何内容
            {ret = ui->edit_passWord->text();}
            ui->edit_passWord ->setText(ret);
        }
    }


delete v_key;
}
