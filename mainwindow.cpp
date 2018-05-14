#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_MainButtonDlg = NULL;

    if(m_MainButtonDlg == NULL){
        m_MainButtonDlg = new Mainbutton(ui->main_Frame);
    }


    m_MainButtonDlg->setModal(true);
    m_MainButtonDlg->show();



}

MainWindow::~MainWindow()
{
    delete ui;
}
