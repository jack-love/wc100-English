#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QTabWidget>

namespace Ui {
class Calibration;
}

class Calibration : public QTabWidget
{
    Q_OBJECT

public:
    explicit Calibration(QWidget *parent = 0);
    ~Calibration();

private:
    Ui::Calibration *ui;
};

#endif // CALIBRATION_H
