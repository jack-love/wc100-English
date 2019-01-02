#include "maintancance.h"
#include "ui_maintancance.h"
#include "App.h"
#include "messagebox.h"


Maintancance::Maintancance(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::Maintancance)
{
    ui->setupUi(this);

    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags); // 设置禁止最大化
    setFixedSize(480,800); // 禁止改变窗口大小。


    connect(ui->openTtty, SIGNAL(clicked()), this, SLOT(openTttyClicked()));
    connect(ui->closeTtty, SIGNAL(clicked()), this, SLOT(closeTttyClicked()));
    connect(ui->sendData,SIGNAL(clicked()),this,  SLOT(sendDataClicked()));
    connect(ui->clearReceive,SIGNAL(clicked()),this,  SLOT(clearReceiveClicked()));
    connect(ui->backHome,SIGNAL(clicked()),this,  SLOT(backHomeClicked()));
    connect(ui->mechaniceTest,SIGNAL(clicked()),this,SLOT(mechaniceTestClicked()));
    connect(ui->open_door,SIGNAL(clicked()),this,SLOT(open_door_clicked()));
    connect(ui->close_door,SIGNAL(clicked()),this,SLOT(close_door_clicked()));
    connect(ui->white_Balance,SIGNAL(clicked()),this,SLOT(whiteBalance()));
    connect(ui->start,SIGNAL(clicked()),this,SLOT(startDebugClicked()));
    connect(ui->stop,SIGNAL(clicked()),this,SLOT(stopDebugClicked()));

    ui->openTtty->setEnabled(true);
    ui->closeTtty->setEnabled(false);
    ui->sendData->setEnabled(false);
    ui->functionSelection->setEnabled(false);
    ui->clearReceive->setEnabled(false);
    ui->start->setEnabled(true);
    ui->backHome->setEnabled(true);
    ui->mechaniceTest->setEnabled(true);
    ui->stop->setEnabled(false);
    ui->edit_green->setEnabled(false);
    ui->edit_read->setEnabled(false);
    ui->eadit_blue->setEnabled(false);
    ui->edit_white->setEnabled(false);
    ui->State_display->setEnabled(false);
    ui->dataShow->setReadOnly(true);
    ui->cmdShow->setReadOnly(true);
     tty_thread = new ttyThread(this);
    connect(tty_thread,SIGNAL(receiveTtyData(QString)),this,SLOT(showTtyData(QString)));
    connect(tty_thread,SIGNAL(receiveAck(unsigned char)),this,SLOT(showTtyAck(unsigned char)));
    connect(tty_thread,SIGNAL(mTime(int )),this,SLOT(sTimeSlot(int)));
    connect(tty_thread,SIGNAL(receiveWb( WRGB_DAT )),this,SLOT(showWb(WRGB_DAT)));
    connect(tty_thread,SIGNAL(receiveRGB(WRGB_DAT,unsigned int)),this,SLOT(showWrgb(WRGB_DAT,unsigned int  )));
    tty_open=false;
}

Maintancance::~Maintancance(){
    delete ui;
    delete tty_thread;
}

void Maintancance::backHomeClicked(){
    closeTttyClicked();
    emit SendHomeSignal();
}

void Maintancance::clearReceiveClicked(){
    ui->dataShow->clear();
}



void Maintancance::mechaniceTestClicked()
{
                 openMcuUart();
                  if(tty_open){

                            ui->mechaniceTest->setEnabled(false);
                        QPalette palette;
                         bool ret = testCmd(RESET);
                              if(ret){
                                 ui->cmdShow->setText("Automatic Check success");
                                  palette.setColor(QPalette::Text,Qt::green);
                                 ui->State_display->setPalette(palette);
                                 ui->State_display->setText("Automatic Check success");
                                 ui->mechaniceTest->setEnabled(true);
                              }
                            else{
                                  ui->cmdShow->setText("Automatic Check fail");
                                  palette.setColor(QPalette::Text,Qt::red);
                                 ui->State_display->setPalette(palette);
                                 ui->State_display->setText("Automatic check fail");
                            }
                        }
                    else{

                        msg.MessageBox_Info(tr("Please open the serial port first !"));
                    }
}

void Maintancance::whiteBalance()
{
     openMcuUart();
      if(tty_open){
        tty_thread->commandSend(WB);
     }else{
          msg.MessageBox_Info(tr("Please open the serial port first!"));
      }
}


void Maintancance::startDebugClicked(){
                openMcuUart();

                 if(tty_open){
                                ui->start->setEnabled(false);
                                ui->stop->setEnabled(true);

                                bool ret = testCmd(ONESTEP);
                                if(!ret){
                                    msg.MessageBox_Info(tr("Single step test fail !"));
                                }

                  }else{
                     msg.MessageBox_Info(tr("Please open the serial port first!"));
                 }
                 ui->start->setEnabled(true);
                 ui->stop->setEnabled(false);
}



void Maintancance::stopDebugClicked()
{

            openMcuUart();
         if(tty_open){
                ui->start->setEnabled(true);
                ui->stop->setEnabled(false);
                bool ret = testCmd(STOPR);
                if(!ret){
                    msg.MessageBox_Info(tr("One step stop fail !"));
                }
       }else{
                   msg.MessageBox_Info(tr("Please open the serial port first!"));
         }

}

void Maintancance::open_door_clicked()
{
    openMcuUart();
      if(tty_open){
     tty_thread->commandSend(OFW);
      }else{
          msg.MessageBox_Info(tr("Please open the serial port first!"));
    }
}

void Maintancance::close_door_clicked()
{
    openMcuUart();
     if(tty_open){
     tty_thread->commandSend(ETW);
     }else{
         msg.MessageBox_Info(tr("Please open the serial port first!"));
    }
}



bool  Maintancance::testCmd(WORK_STATE cmd)
{
    tty_thread->setCommand(cmd);
    tty_thread->start();
    App::test_finished=false;
    bool bfinished = false;

   while(!bfinished){
                App::workMode= 0x01;
                bfinished = App::test_finished;
                tty_thread->msleep(100);
                try {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 500);
                }catch(...){
                qDebug()<< "Exception....";
                }
     }


   tty_thread->exit();
   return  App::test_result;
}


void Maintancance::openMcuUart(){
    if( !tty_open){
                tty_thread->mcuUartOpen();
                tty_open=true;
     }
}


void Maintancance::openTttyClicked(){
    if(App::user_lock){
                    openMcuUart();
                    ui->openTtty->setEnabled(false);
                    ui->closeTtty->setEnabled(true);
                    ui->sendData->setEnabled(true);
                    ui->functionSelection->setEnabled(true);
                    ui->clearReceive->setEnabled(true);
            }
            else {
                     msg.MessageBox_Info(tr("Please login first.!"));
            }

}


void Maintancance::closeTttyClicked()
{
      if( tty_open ) {
            tty_thread->mcuUartClose();
            ui->openTtty->setEnabled(true);
            ui->closeTtty->setEnabled(false);
            ui->sendData->setEnabled(false);
            ui->functionSelection->setEditable(false);
            ui->clearReceive->setEnabled(false);
            tty_open=false;
      }
}


void Maintancance::sendDataClicked(){
        state = (WORK_STATE)ui->functionSelection->currentIndex();
        tty_thread->commandSend(state);
}

void Maintancance::showTtyData(QString str){
     ui->dataShow->append(str);
     ui->dataShow->append("***********************");
}

void Maintancance::showTtyAck(unsigned char state)
{
    QPalette palette;
    switch ( state )
    {
            case  R_VERSION:
                    ui->cmdShow->setText("Read version information success!\n");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                    ui->State_display->setText("Read version information success!");
            break;

            case R_SELFEX:
                    ui->cmdShow->setText(" Self test success");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                    ui->State_display->setText(" Self test success");
            break;

            case R_OFW:
                    ui->cmdShow->setText("Open  Door success");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                    ui->State_display->setText("Open  Door success!");
            break;

            case R_ETW:
                    ui->cmdShow->setText("Close  Door success.");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                    ui->State_display->setText("Close  Door success.");
            break;

            case R_SETUP:
                    ui->cmdShow->setText("Setup up success.");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                    ui->State_display->setText("Setup up success.");
            break;

            case R_ONESTEP:
                     ui->cmdShow->setText("One Step  success.");
                     palette.setColor(QPalette::Text,Qt::green);
                     ui->State_display->setPalette(palette);
                     ui->State_display->setText("One Step  success.");
            break;

            case R_RESET:
                    ui->cmdShow->setText("Automatic Check success!");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                      ui->State_display->setText("Automatic Check success!");
            break;

            case R_ERR_1:
                    ui->cmdShow->setText("Receive Mechanical error message!");
                    palette.setColor(QPalette::Text,Qt::red);
                    ui->State_display->setPalette(palette);
                     ui->State_display->setText("Receive Mechanical error message!");
            break;

            case R_WhiteBalance:
                    ui->cmdShow->setText("Read White Balance  success.");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                    ui->State_display->setText("Read White Balance  success .");
            break;

            case R_STOP:
                    ui->cmdShow->setText("Receive Stop cmd success.");
                    palette.setColor(QPalette::Text,Qt::green);
                    ui->State_display->setPalette(palette);
                    ui->State_display->setText("Receive Stop  cmd success.");
            break;
           default:break;
    }
}


void Maintancance::sTimeSlot( int st)
{
    QString s = QString::number(st, 10);
    ui->timeNumber->display(s);
}




void Maintancance::showWrgb(WRGB_DAT wrgb_data,unsigned int count)
{
        QString w,r,g,b;
      //  printf(" [showWrgb]---->[count=%d] [W:%d,R:%d,G:%d,B:%d] \n",count,wrgb_data.W,wrgb_data.R,wrgb_data.G,wrgb_data.B);

        w  = QString::number(wrgb_data.W, 10);
        r   =  QString::number(wrgb_data.R, 10);
        g  =  QString::number(wrgb_data.G, 10);
        b  =  QString::number(wrgb_data.B, 10);

        ui->edit_white->setText(w);
        ui->edit_read->setText(r);
        ui->edit_green->setText(g);
        ui->eadit_blue->setText(b);

        result[count].wrgb_value[0]=wrgb_data.W;
        result[count].wrgb_value[1]=wrgb_data.R;
        result[count].wrgb_value[2]=wrgb_data.G;
        result[count].wrgb_value[3]=wrgb_data.B;

}

void Maintancance::showWb(WRGB_DAT wrgb)
{
        QString w,r,g,b;

        w =   QString::number(wrgb.W, 10);
        r  =   QString::number(wrgb.R, 10);
        g =   QString::number(wrgb.G, 10);
        b =   QString::number(wrgb.B, 10);

        ui->edit_white->setText(w);
        ui->edit_read->setText(r);
        ui->edit_green->setText(g);
        ui->eadit_blue->setText(b);

        result[0].white_value[0]=wrgb.W;
        result[0].white_value[1]=wrgb.R;
        result[0].white_value[2]=wrgb.G;
        result[0].white_value[3]=wrgb.B;

        App::white_value[0] = wrgb.W;
        App::white_value[1] = wrgb.R;
        App::white_value[2] = wrgb.G;
        App::white_value[3] = wrgb.B;
 //   printf(" [showWb---->]  W:%d   R:%d   G:%d  B:%d \n",wrgb.W,wrgb.R,wrgb.G,wrgb.B);
}


