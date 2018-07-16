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
signals:
     void SendHomeSignal();

private:
Ui::Calibration *ui;
QValidator *validator;
MainBussniessView *pMainBussView;
QSqlQueryModel *pQueryModel;
QSqlQueryModel *pTableModel=NULL;
QString strItemName;

};

#endif // CALIBRATION_H
