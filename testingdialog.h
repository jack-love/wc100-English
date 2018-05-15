#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <QDialog>

namespace Ui {
class TestingDialog;
}
enum TestItem{
    URO = 0,
    BIL = 1,
    KET = 2,
    CRE = 3,
    BLD = 4,
    PRO = 5,
    MALB = 6,
    NIT = 7,
    WBC=8,
    GLU=9,
    SG=10,
    PH=11,
    VC=12,
    CA=13,
    ACR=14
};
class TestingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestingDialog(QWidget *parent = 0);
    ~TestingDialog();
   void setItemval_Urs14cc();
   void showItemval_Urs14cc();
private slots:
    void on_btn_Back_clicked();
signals:
     void SendHomeSignal();
private:
    Ui::TestingDialog *ui;
};

#endif // TESTINGDIALOG_H
