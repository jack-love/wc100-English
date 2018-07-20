#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QTabWidget>
#include <QModelIndex>
#include <QTabWidget>
#include <QDialog>
#include <QMessageBox>
#include "keyboard.h"
#include <calibrateobservermodel.h>
#include<ttythread.h>
#include<qtableview.h>
namespace Ui {
class Calibration;
}
class MainBussniessView;
class QValidator;
class QSqlQueryModel;
class QSqlTableModel;
class Calibration : public QTabWidget
{
    Q_OBJECT

public:
    explicit Calibration(QWidget *parent = 0,MainBussniessView* pMainView = NULL);
    ~Calibration();
  void OpenKeyboard();
private slots:
        void on_btn_Back_clicked();
        //  void on_btn_Back_2_clicked();

        void on_btn_options_setup_pressed(const QModelIndex &index);

        void on_btn_save_clicked();
        bool eventFilter(QObject *,QEvent *);

        void on_calibrate_start_clicked();

        void on_calibrate_stop_clicked();
        void on_CalibrateObserverveResult(QSqlTableModel*calibrateTableModel);
        void sTimeSlot(int st);

        //void on_btn_Back_2_clicked();

        void on_btn_FirstPag_clicked();

        void on_btn_PreviousPage_clicked();

        void on_btn_NextPage_clicked();

        void on_btn_LastPage_clicked();

signals:
        void SendHomeSignal();
        void   sTime (int s);

private:
        Ui::Calibration *ui;
        QValidator *validator;
        MainBussniessView *pMainBussView;
        QSqlQueryModel *pQueryModel;
        QSqlQueryModel *pTableModel=NULL;
        QString strItemName;
        bool  fist_show=false;
        bool pageHome(QTableView *p);
        bool pageDown(QTableView *p,bool isLoop);
        bool pageEnd(QTableView *p);
        int pageCount(QTableView *p);
        bool pageTo(QTableView *p, int pageNO);
        bool pageUp(QTableView *p,bool isLoop);

};

#endif // CALIBRATION_H
