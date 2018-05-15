#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <QDialog>

namespace Ui {
class TestingDialog;
}

class TestingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestingDialog(QWidget *parent = 0);
    ~TestingDialog();

private:
    Ui::TestingDialog *ui;
};

#endif // TESTINGDIALOG_H
