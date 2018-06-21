#ifndef SYSTEMSETUP_H
#define SYSTEMSETUP_H

#include <QTabWidget>

namespace Ui {
class SystemSetup;
}

class SystemSetup : public QTabWidget
{
    Q_OBJECT

public:
    explicit SystemSetup(QWidget *parent = 0);
    ~SystemSetup();

private slots:
    void on_btn_Back_clicked();
signals:
     void SendHomeSignal();
private:
    Ui::SystemSetup *ui;
};

#endif // SYSTEMSETUP_H
