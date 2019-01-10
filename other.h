#ifndef OTHER_H
#define OTHER_H

#include <QDialog>

namespace Ui {
class Other;
}
class MainBussniessView;
class Other : public QDialog
{
    Q_OBJECT

public:
    explicit Other(QWidget *parent = 0);
    ~Other();

private:
    Ui::Other *ui;
      MainBussniessView *pMainBussView=NULL;
      QMovie *Movie;
};

#endif // OTHER_H
