#ifndef SYSTEMSETUP_H
#define SYSTEMSETUP_H
#include <QTabWidget>
#include <QProcess>
#include "wifibtthread.h"
#include "keyboard.h"
class MainBussniessView;
class QSqlTableModel;
class QValidator;
namespace Ui {
class SystemSetup;
}

#define  bt_open  0x03
#define  bt_close  0x02
#define  bt_scan   0x01
#define  bt_mate  0x04
#define  bt_receive 0x05
class SystemSetup : public QTabWidget
{
    Q_OBJECT

public:
       explicit SystemSetup(QWidget *parent = 0,MainBussniessView* pMainView = NULL);
      ~SystemSetup();

       void makeWpaConf(QString ssid,QString passWorld);
       void rmWpaConfi();
       QString fileView(QString fileName);
       QString shellProcess(QString cmd);
       void openWpatool();
       void closeWpatool();
       bool wifiScan();
       void rmmodko();
       void insmodko();
       void killps(QString ps);
       void  displayUpdate_set(unsigned int s,bool status);
        void updateState(bool status);
        void setSystemTime();
  QString getIPAddr();
private slots:
        void finishedProcess();
        void readProcess();
        void executeShellQProcessq(QString shell);
        void executeShellCmd(const QString shell);
        void paperTypeSelectionClicked( int index);
        void on_btn_save_clicked();
        bool systemShow(QSqlTableModel*model);
        void species(QSqlTableModel*model);
        void language(QSqlTableModel*model);
        void testMode(QSqlTableModel*model);
        void testPapertype(QSqlTableModel*model);
        void  getSignalStrength(QString signal);
        void  getwifiState(QString state);
        void on_edt_testtype_currentIndexChanged(const QString &arg1);
        void on_edt_paperType_currentIndexChanged(const QString &arg1);
        void on_edt_language_currentIndexChanged(const QString &arg1);
        void on_edt_testmode_currentIndexChanged(const QString &arg1);
        void on_btn_openWifi_clicked();
        void on_btn_clean_clicked();
        void on_btn_scanWifi_clicked();
        void on_com_ssid_currentIndexChanged(const QString &arg1);
        void on_btn_closeWifi_clicked();
        void on_btn_connectWifi_clicked();
        void on_btn_openBt_clicked();
        void on_btn_scanBt_clicked();
        void on_btn_closeBt_clicked();
        void on_btn_connectBt_clicked();
        void on_btn_receiveFiles_clicked();
        void on_btn_back_clicked();
        void on_btn_back_2_clicked();
        void on_btn_back_3_clicked();
        void displayUpdate_timeout();

signals:
         void SendHomeSignal();
         void paperChange(int index);
         void SignalStrength(QString signal);
         void Signalbt(bool status);

private:
            Ui::SystemSetup *ui;
            MainBussniessView *pMainView;
            QString ssidName;
            WifiBtThread  wb_thread;
            QStringList   ssidList;    
            QString pword;
            QProcess *runShellProcess=NULL;
            QString shellOutput;
            bool btn_openWfi;
            unsigned int     bt_Status;
            bool lsmodko;
            bool flag_udhcpc;
            QTimer  *s_Timer;
             unsigned int time_s;
             bool state;
};

#endif // SYSTEMSETUP_H
