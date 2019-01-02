#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainbutton.h>
#include <QMessageBox>
#include <testingdialog.h>
#include <maintancance.h>
#include <signin.h>
#include <ttythread.h>
#include <systemsetup.h>
#include <QTimer>
#include <QTime>
#include<calibration.h>
#include <databasehelper.h>
#include<mainbussniessview.h>
#include<query.h>
#include<systemmonitor.h>
#include<systemupdate.h>
#include<other.h>
#include <systeminit.h>
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
    MYTEST=8,
    UPDATE=9,
    POWER=10,
};

#define     DB0          0
#define     DB_30       -30
#define     DB_50       -50
#define     DB_70       -70
#define     DB_90       -90

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLabel *labelWireless;
    QLabel *labelBattery;

signals:
    void Spoweroff();
    void Signalbt(bool status);

private:
    Ui::MainWindow *ui;
     void selectButton(MAIN_BUTTON button);
     void hideButton(MAIN_BUTTON button);
     unsigned int currentValue;
    QTranslator *trans=NULL;
    Mainbutton* m_MainButtonDlg=NULL;
    TestingDialog *m_TestDialog=NULL;
    Maintancance *m_Maintancance=NULL;
    Calibration *m_Calibration=NULL;
    SignIn * m_SignIn=NULL;
    SystemSetup *m_SystemSetup=NULL;
    MainBussniessView* m_MainView=NULL;
      QProgressDialog * progDlg=NULL;
    Query * m_Query=NULL;
    MAIN_BUTTON buttonState;
    systemMonitor * system_Monitor=NULL;
    SystemUpdate * m_SystemUpdate=NULL;
    Other *m_other=NULL;
   Systeminit *m_system_init=NULL;
   QString readLanguage_Setting();
    void showBattery(char tmp);
    void showWIFI(int signal);
    void showBluetooth();
    void convertTo_Chinese();
    void convertTo_English();
   void language_Saving(QString language);

private slots:
    void showTime();
    void TestingActionSlot();
    void HistoryActionSlot();
    void MaintancanceActionSlot();
    void CalibrationActionSlot();
    void SystemActionSlot();
    void UpdateActionSlot();
    void powerActionSlot();
    void SignInActionSlot();
    void BackHomeActionSlot();
    void MainpowerOff();
    void LanguageConversion();
    void signalStrengthShow(QString signal);
     void signalBtShow(bool status);
    void socSignalSlot(char signal);
    void chargeSignalSlot(bool state);

};

#endif // MAINWINDOW_H
