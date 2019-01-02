#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H
#include <QtGui>
#include <QDialog>
#include<QWidget>
class MainBussniessView;
class QSqlTableModel;
class QValidator;
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

    explicit TestingDialog(QWidget *parent = 0, MainBussniessView* pMainBussniessView = NULL);
    ~TestingDialog();



   QVBoxLayout *verticalLayout;
   QHBoxLayout *horizontalLayout_1;
   QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const;

private slots:
        void on_btn_Back_clicked();
        bool on_TestResult(QSqlTableModel*);
        void on_btn_Start_clicked();
        void on_btn_Stop_clicked();
        void sTimeSlot( int st);
        void resetSlot();
signals:
        void SendHomeSignal();
        bool testResult(QSqlTableModel*);
private:
      Ui::TestingDialog *ui;
      MainBussniessView *pMainView=NULL;
};

#endif // TESTINGDIALOG_H
