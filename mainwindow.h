#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainbutton.h>
#include <QMessageBox>
#include <testingdialog.h>
#include <maintancance.h>
#include <signin.h>

#include <systemsetup.h>
#include <QTimer>
#include <QTime>

namespace Ui {
class MainWindow;
}

enum MAIN_BUTTON{
    TESTING = 0,
    HISTORY = 1,
    QUALITY = 2,
    CALIBRATE = 3,
    SIGNIN= 4,
    SYSTEM = 5,
    DEBUG = 6,
    MAIN_BTN = 7,
    MYTEST=8
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLabel *labelWireless;
    QLabel *labelBattery;

private:
    Ui::MainWindow *ui;
    Mainbutton* m_MainButtonDlg;
     void selectButton(MAIN_BUTTON button);
     void hideButton(MAIN_BUTTON button);

    TestingDialog *m_TestDialog;
    Maintancance *m_Maintancance;
     SignIn * m_SignIn;
     SystemSetup *m_SystemSetup; //1

    MAIN_BUTTON buttonState;
    void showBattery();
    void showWIFI();
    void showBluetooth();
private slots:
    void showTime();
    void TestingActionSlot();
    void HistoryActionSlot();
    void MaintancanceActionSlot();
    void CalibrationActionSlot();
    void SystemActionSlot();
    void UpdateActionSlot();
    void OtherActionSlot();
  //  void SystemSetupActionSlot();
  //  void PasswordActionSlot();
    void SignInActionSlot();
    void BackHomeActionSlot();
    void GoTestingActionSlot();
};

#endif // MAINWINDOW_H
