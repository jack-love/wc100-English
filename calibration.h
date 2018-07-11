#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QTabWidget>
#include <QModelIndex>
namespace Ui {
class Calibration;
}
class QValidator;
class Calibration : public QTabWidget
{
    Q_OBJECT

public:
    explicit Calibration(QWidget *parent = 0);
    ~Calibration();

private slots:
    void on_btn_Back_clicked();
    void on_btn_Back_2_clicked();

signals:
     void SendHomeSignal();

private:
    Ui::Calibration *ui;
        QValidator *validator;
};

#endif // CALIBRATION_H
