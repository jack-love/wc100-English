#ifndef QUERY_H
#define QUERY_H
#include <QModelIndex>
#include <QTabWidget>
#include <ttythread.h>
#include "messagebox.h"
class MainBussniessView;
namespace Ui {
class Query;
}
class QSqlTableModel;
class QSqlQueryModel;

class Query : public QTabWidget
{
    Q_OBJECT

public:
     explicit Query(QWidget *parent = 0, MainBussniessView*pMainBussniessView = NULL);
    ~Query();

   ttyThread  * tty_thread=NULL;
private slots:
    void on_SampleResult(QSqlTableModel*);
    void on_btn_export_clicked();
    void on_tableView_TestResult_pressed(const QModelIndex &index);
    void on_btn_delete_clicked();
    void on_btn_query_clicked();
    void on_btn_next_clicked();
    void on_btn_previous_clicked();
    void on_btn_back_clicked();

signals:
     void SendHomeSignal();

private:
    Ui::Query *ui;
    MainBussniessView * pMainView;
    QSqlTableModel* printModel=NULL;

    int SampleNo;
    QString sBeginDate;
    QString sEndDate;

};

#endif // QUERY_H
