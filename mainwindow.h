#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mainbutton.h>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Mainbutton* m_MainButtonDlg;
private slots:
    void TestingActionSlot();
    void HistoryActionSlot();
    void MaintancanceActionSlot();
    void CalibrationActionSlot();
    void SystemActionSlot();
    void UpdateActionSlot();
    void OtherActionSlot();
    void PasswordActionSlot();
};

#endif // MAINWINDOW_H
