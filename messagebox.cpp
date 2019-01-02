#include "messagebox.h"
#include <QMessageBox>

MessageBox::MessageBox()
{
}


void MessageBox::MessageBox_Info(QString info){
    QMessageBox msg;
    msg.setWindowTitle(QString::fromUtf8("提示"));
    msg.setText(info);
     msg.setFixedSize(480, 600);
     msg.setWindowFlags(Qt::Drawer);
    msg.setStyleSheet("background-color: rgb(188, 188, 188);color:rgb(85, 85, 255);font: 30pt");
    msg.setIcon(QMessageBox::Information);
    msg.addButton((tr("OK")),QMessageBox::ActionRole);
   // msg.addButton(QString::fromUtf8("取消"),QMessageBox::ActionRole);
    msg.exec();
}

void MessageBox::MessageBox_Err(QString info){
    QMessageBox msg;
    msg.setWindowTitle(QString::fromUtf8("提示"));
    msg.setText(info);
     msg.setWindowFlags(Qt::Drawer);
     msg.setFixedSize(300, 300);
    msg.setStyleSheet("color:rgb(220, 0, 0);font: 30pt");
    msg.setIcon(QMessageBox::Critical);
    msg.addButton(tr("OK"),QMessageBox::ActionRole);
  //  msg.addButton(QString::fromUtf8("取消"),QMessageBox::ActionRole);
    msg.exec();

}


int  MessageBox::MessageBox_Ask(QString info)
{
    QMessageBox msg;
   msg.setWindowTitle(QString::fromUtf8("提示"));
    msg.setText(info);
     msg.setWindowFlags(Qt::Drawer);
     msg.setFixedSize(300, 300);
    msg.setStyleSheet("color:rgb(220, 0, 0);font: 30pt");
    msg.setIcon(QMessageBox::NoIcon);
    msg.addButton(tr("OK"),QMessageBox::ActionRole);
    msg.addButton(tr("Cancel"),QMessageBox::ActionRole);
   return  msg.exec();
}
