#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainbutton.h>
#include <QMessageBox>
#include <testingdialog.h>


namespace Ui {
class MainWindow;
}

enum MAIN_BUTTON{
    TESTING = 0,
    HISTORY = 1,
    QUALITY = 2,
    CALIBRATE = 3,
    ITEM = 4,
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

private:
    Ui::MainWindow *ui;
    Mainbutton* m_MainButtonDlg;
     void selectButton(MAIN_BUTTON button);
       void hideButton(MAIN_BUTTON button);
    TestingDialog *m_TestDialog;
    MAIN_BUTTON buttonState;
private slots:
    void TestingActionSlot();
    void HistoryActionSlot();
    void MaintancanceActionSlot();
    void CalibrationActionSlot();
    void SystemActionSlot();
    void UpdateActionSlot();
    void OtherActionSlot();
    void PasswordActionSlot();
    void BackHomeActionSlot();
};

#endif // MAINWINDOW_H
