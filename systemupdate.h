#ifndef SYSTEMUPDATE_H
#define SYSTEMUPDATE_H

#include <QDialog>
#include <network.h>
#include <QListWidgetItem>
#include "keyboard.h"
namespace Ui {
class SystemUpdate;
}

class SystemUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit SystemUpdate(QWidget *parent = 0);
    ~SystemUpdate();
   void setTestTime(unsigned int s,bool status);

private slots:
    void on_btn_back_clicked();
    void on_btn_start_clicked();
    void taskInfo(QString task, QString fileName, qint64 fileSize);
    void downloadFinished(QString task);
    void downloadErro_hand(QString err);
    void upTimeout();
    void showDownloadProgress(QString task, qint64 byteTotal, double percent, double speed);



    void on_btn_stop_clicked();

    void on_btn_upsystem_clicked();

    void on_btn_upmcu_clicked();

signals:
    void SendHomeSignal();
    void removeDownloadTask(QString task);
    void stopDownloadTask(QString task);
    void startDownloadTask(QString task);

private:
    Ui::SystemUpdate *ui;
    Network *network=NULL;
    QString downloadPath;
    QTimer *up_wTimer;
    QMovie *Movie;
     unsigned int  time_up;

};

#endif // SYSTEMUPDATE_H
