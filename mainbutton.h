#ifndef MAINBUTTON_H
#define MAINBUTTON_H

#include <QDialog>

namespace Ui {
class Mainbutton;
}

class Mainbutton : public QDialog
{
    Q_OBJECT

public:
    explicit Mainbutton(QWidget *parent = 0);
    ~Mainbutton();

private:
    Ui::Mainbutton *ui;
};

#endif // MAINBUTTON_H
