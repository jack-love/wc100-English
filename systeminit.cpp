#include "systeminit.h"
#include <QTest>
#include <QDebug>
Systeminit::Systeminit(QObject *parent):QThread(parent)
{
    QFont font("ZYSong18030",30);
    progressDialog = new  QProgressDialog();

    progressDialog->setFont(font);
    progressDialog->setWindowModality(Qt::ApplicationModal);

    progressDialog->setMinimumDuration(5);


    progressDialog->setWindowFlags(Qt::FramelessWindowHint);
    progressDialog->setWindowTitle(tr("please wait"));
    progressDialog->setLabelText(tr(" Thanks for using vansful products\n  Initialization..."));
    progressDialog->setCancelButtonText(tr("Canl"));
    progressDialog->setRange(0,100);
    progressDialog->setStyleSheet(QString::fromUtf8("QLabel{\n"
    "color:rgb(255, 255, 255); \n"
    "}\n"
    "\n"
    "QDialog{\n"
    "background:url(://image/backGround.png)\n"
    "}"));
    progressDialog->setFixedSize(480,200);
      progressDialog->setWindowOpacity(0.5);  //设置透明用；
       progressDialog->setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint);

       //取消对话框标题
       //this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);

       //取消对话框标题和边框
       //this->setAutoFillBackground(true);
       progressDialog->setContentsMargins(0,0,0,0);
    //progressDialog->resize(480,200);
    progressDialog->show();

}


Systeminit::~Systeminit()
{
qDebug()<<"~Systeminit()";
    quit();
    wait();
    delete progressDialog;
}

void Systeminit::run()
{
    for (int i=1; i<100+1; i++)
    {
        progressDialog->setValue(i);

        QTest::qSleep(250);
        if (progressDialog->wasCanceled())
            return;
    }
quit();
}
