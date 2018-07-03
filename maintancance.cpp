#include "maintancance.h"
#include "ui_maintancance.h"

unsigned char R_data[6]={0};
//bool  tty_receivingState=false;

Maintancance::Maintancance(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Maintancance)
{
    ui->setupUi(this);
      serialPort = new QSerialPort(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。

    // connect(serialPort,SIGNAL(readyRead()),this,SLOT(slotReadData()));
     connect(ui->openTtty, SIGNAL(clicked()), this, SLOT(openTttyClicked()));
     connect(ui->closeTtty, SIGNAL(clicked()), this, SLOT(closeTttyClicked()));
     connect(ui->sendData,SIGNAL(clicked()),this,  SLOT(sendDataClicked()));
     connect(ui->clearReceive,SIGNAL(clicked()),this,  SLOT(clearReceiveClicked()));

     connect(ui->backHome,SIGNAL(clicked()),this,  SLOT(backHomeClicked()));
     connect(ui->mechaniceTest,SIGNAL(clicked()),this,SLOT(mechaniceTestClicked()));


     ui->openTtty->setEnabled(true);
     ui->closeTtty->setEnabled(false);
     ui->sendData->setEnabled(false);
     ui->functionSelection->setEnabled(false);
     ui->clearReceive->setEnabled(false);


     tty_thread = new ttyThread(this);

       connect(tty_thread,SIGNAL(receiveTtyData(QString)),this,SLOT(showTtyData(QString)));
       connect(tty_thread,SIGNAL(receiveAck(unsigned char)),this,SLOT(showTtyAck(unsigned char)));
}

Maintancance::~Maintancance()
{
    delete ui;
}

void Maintancance::backHomeClicked()
{
    emit SendHomeSignal();
}

void Maintancance::clearReceiveClicked()
{
    ui->dataShow->clear();
}

void Maintancance::mechaniceTestClicked()
{
    openTttyClicked();
    tty_thread->ttyStart();
    tty_thread->start();
    tty_thread->setCommand(RESET);

}

//jack.cc
void Maintancance::openTttyClicked()
{
        //SignIn  signin;
        //bool  lock_tmp = signin.getlock();

        if( 1){
             if(! serialPort->isOpen()){
                 tty_thread->ttyOpen();

                ui->openTtty->setEnabled(false);
                ui->closeTtty->setEnabled(true);
                ui->sendData->setEnabled(true);
                ui->functionSelection->setEnabled(true);
                ui->clearReceive->setEnabled(true);
             }
        }
        else
        {
                //QMessageBox::warning(this," warning ", "Please log in first",QMessageBox::Yes);
                sendMessage("Please log in first.");
        }

}
void Maintancance::sendMessage(char *message){

    QMessageBox box;
    box.setText(QString::fromLocal8Bit(message));
    box.setStyleSheet("color:red");
    QFont font;
    font.setPixelSize(30);
    box.setFont(font);
    box.setFixedSize(300, 300);
    int bret = box.exec();

}

void Maintancance::closeTttyClicked()
{
        if(serialPort->isOpen())
            {

                tty_thread->ttyClose();

                ui->openTtty->setEnabled(true);
                ui->closeTtty->setEnabled(false);
                ui->sendData->setEnabled(false);
                ui->functionSelection->setEditable(false);
                ui->clearReceive->setEnabled(false);
           }
}

void Maintancance::sendDataClicked()
{

        state = (WORK_STATE)ui->functionSelection->currentIndex();
     // tty_thread->setCommand(OFW);
//tty_thread->start();
        tty_thread->commandSend(state);

}

void Maintancance::showTtyData(QString str)
{
     ui->dataShow->append(str);
     ui->dataShow->append("***********************");
     qDebug() << "showTtyData"<< str ;
}

void Maintancance::showTtyAck(unsigned char state)
{


    switch ( state )
    {
            case  R_VERSION:
            ui->cmdShow->setText("ACK Read version information ok!!\n");
            break;

            case R_SELFEX:
            ui->cmdShow->setText("ACK Self test success");
            break;

            case R_OFW:
            ui->cmdShow->setText("Open the Door ACK");
            break;

            case R_ETW:
            ui->cmdShow->setText("Close the Door ACK");
            break;

            case R_SETUP:
            ui->cmdShow->setText("Setup up success ACK");
            break;

            case R_ONESTEP:
            ui->cmdShow->setText("One Step  success ACK");
            break;

            case R_RESET:
            ui->cmdShow->setText("Machine Reset ACK");
            break;

            case R_ERR_1:
            ui->cmdShow->setText("Receive Mechanical error ACK");
            break;

            case R_WhiteBalance:
            ui->cmdShow->setText("White Balance  success ACK");
            break;

            case R_STOP:
            ui->cmdShow->setText("Receive STOP   success ACK");
            break;

            default:
             break;

    }
}


