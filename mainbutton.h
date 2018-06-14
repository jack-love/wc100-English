#ifndef MAINBUTTON_H
#define MAINBUTTON_H

#include <QDialog>

namespace Ui {
class Mainbutton;
}

class Mainbutton : public QDialog
{
    Q_OBJECT

public:
    explicit Mainbutton(QWidget *parent = 0);
    ~Mainbutton();

signals:
     void SendHomeSignal();
    void on_btn_Testing();
    void on_btn_History();
    void on_btn_Maintancance();
    void on_btn_Calibration();
    void on_btn_System();
    void on_btn_Update();
   void  on_btn_Other();
   void  on_btn_Password();
  // void sendsignal();
private slots:
    void on_btn_Testing_clicked();

    void on_btn_History_clicked();

    void on_btn_Maintancance_clicked();

    void on_btn_Calibration_clicked();

    void on_btn_System_clicked();

    void on_btn_Update_clicked();

    void on_btn_Other_clicked();

    void on_btn_Password_clicked();

    void on_btn_Back_clicked();

private:
    Ui::Mainbutton *ui;
};

#endif // MAINBUTTON_H
