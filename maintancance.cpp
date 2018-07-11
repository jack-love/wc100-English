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

    connect(ui->start,SIGNAL(clicked()),this,SLOT(startDebugClicked()));
    connect(ui->stop,SIGNAL(clicked()),this,SLOT(stopDebugClicked()));
    connect(ui->paperType,SIGNAL(activated(int)),this,SLOT(typeSelectionClicked(int)));
    connect(ui->testItem,SIGNAL(activated(int)),this,SLOT(modelSelectionClicked(int)));

    connect(ui->white_Balance,SIGNAL(clicked()),this,SLOT(whiteBalance()));

     ui->openTtty->setEnabled(true);
     ui->closeTtty->setEnabled(false);
     ui->sendData->setEnabled(false);
     ui->functionSelection->setEnabled(false);
     ui->clearReceive->setEnabled(false);

    ui->start->setEnabled(true);
    ui->backHome->setEnabled(true);
    ui->mechaniceTest->setEnabled(true);
    ui->stop->setEnabled(false);


     tty_thread = new ttyThread(this);
    connect(tty_thread,SIGNAL(receiveTtyData(QString)),this,SLOT(showTtyData(QString)));
    connect(tty_thread,SIGNAL(receiveAck(unsigned char)),this,SLOT(showTtyAck(unsigned char)));
    connect(tty_thread,SIGNAL(sTime(int )),this,SLOT(sTimeSlot(int)));

    connect(tty_thread,SIGNAL(receiveWb(unsigned int,unsigned int ,unsigned int ,unsigned int )),this,SLOT(showWb(unsigned int,unsigned int ,unsigned int,unsigned int )));
    connect(tty_thread,SIGNAL(receiveRGB(unsigned int,unsigned int ,unsigned int ,unsigned int )),this,SLOT(showWrgb(unsigned int,unsigned int ,unsigned int,unsigned int )));

    setPaperType(R113,1);
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
          if(! serialPort->isOpen()){
              openTttyClicked();
          }
    tty_thread->ttyStart();
    tty_thread->start();
    tty_thread->setCommand(RESET);
    tty_thread->setWorkTime(60);


    ui->start->setEnabled(false);
    ui->mechaniceTest->setEnabled(false);
    ui->white_Balance->setEnabled(false);
}


void Maintancance::startDebugClicked()
{
    ui->start->setEnabled(false);
    ui->backHome->setEnabled(false);
    ui->mechaniceTest->setEnabled(false);
    ui->white_Balance->setEnabled(false);
    ui->stop->setEnabled(true);

        if(! serialPort->isOpen()){
            openTttyClicked();
        }

receive_count=0;
    tty_thread->commandSend(SETUP);
    tty_thread->setCommand(ONESTEP);
    tty_thread->ttyStart();
    tty_thread->start();


}



void Maintancance::stopDebugClicked()
{
    ui->start->setEnabled(true);
    ui->backHome->setEnabled(true);
    ui->mechaniceTest->setEnabled(true);
    ui->white_Balance->setEnabled(true);
    ui->stop->setEnabled(false);
 tty_thread->setCommand(STOP);
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
          ui->label_state->setText("machine reset ok");

          ui->start->setEnabled(true);
             ui->white_Balance->setEnabled(true);
          ui->mechaniceTest->setEnabled(true);
            break;

            case R_ERR_1:
            ui->cmdShow->setText("Receive Mechanical error ACK");
            break;

            case R_WhiteBalance:
            ui->cmdShow->setText("White Balance  success ACK");
            ui->label_state->setText("White Balance  success ACK");

            ui->start->setEnabled(true);

            ui->mechaniceTest->setEnabled(true);
            ui->white_Balance->setEnabled(true);
            break;

            case R_STOP:
            ui->cmdShow->setText("Receive STOP   success ACK");
            ui->start->setEnabled(true);
             ui->backHome->setEnabled(true);
            ui->mechaniceTest->setEnabled(true);
            ui->white_Balance->setEnabled(true);
            ui->stop->setEnabled(false);
            break;

            default:
             break;

    }
}

void Maintancance::setPaperType(unsigned char type,unsigned char index)
{
    int temp;

    ui->paperType->addItem(QWidget::tr("10T"));
    ui->paperType->addItem(QWidget::tr("11-3"));
    ui->paperType-> setCurrentIndex(index);


            temp = ui->testItem->count();
            for(; temp>0; temp--) {
              ui->testItem->removeItem(temp);
              ui->testItem->clear();
            }

    if(type == 0){//URS-10T
        typeSelection=R10T;
        ui->testItem->addItem(QWidget::tr("LEU"));//10
        ui->testItem->addItem(QWidget::tr("NIT"));
        ui->testItem->addItem(QWidget::tr("URO"));
        ui->testItem->addItem(QWidget::tr("PRO"));
        ui->testItem->addItem(QWidget::tr("PH"));
        ui->testItem->addItem(QWidget::tr("BLD"));
        ui->testItem->addItem(QWidget::tr("SG"));
        ui->testItem->addItem(QWidget::tr("KET"));
        ui->testItem->addItem(QWidget::tr("BIL"));
        ui->testItem->addItem(QWidget::tr("GLU"));

        ui->testItem->addItem(QWidget::tr("BPH"));//0
    }

    else if (type == 1){//URS-11-3
        typeSelection=R113;
        ui->testItem->addItem(QWidget::tr("BIL"));  //12
        ui->testItem->addItem(QWidget::tr("URO"));
        ui->testItem->addItem(QWidget::tr("KET"));
        ui->testItem->addItem(QWidget::tr("BLD"));
        ui->testItem->addItem(QWidget::tr("PRO"));
        ui->testItem->addItem(QWidget::tr("NIT"));
        ui->testItem->addItem(QWidget::tr("WBC"));
        ui->testItem->addItem(QWidget::tr("GLU"));
        ui->testItem->addItem(QWidget::tr("SG"));
        ui->testItem->addItem(QWidget::tr("PH"));
        ui->testItem->addItem(QWidget::tr("VC"));

        ui->testItem->addItem(QWidget::tr("CC"));//防伪也叫校准区

        ui->testItem->addItem(QWidget::tr("BPH"));         //0 计时白平衡 取w即可
    }
}


void Maintancance::typeSelectionClicked(int index )
{
            if(index == 0){//URS-10T
                setPaperType(R10T,0);
            }

            else if (index == 1){//URS-11-3
             setPaperType(R113,1);
            }

}
void Maintancance::sTimeSlot( int st)
{

    QString s = QString::number(st, 10);
    ui->timeNumber->display(s);
}

void Maintancance::whiteBalance()
{
    ui->start->setEnabled(false);
    ui->mechaniceTest->setEnabled(false);
    ui->white_Balance->setEnabled(false);


    if(! serialPort->isOpen()){
        openTttyClicked();
    }

    tty_thread->ttyStart();
    tty_thread->start();
    tty_thread->setCommand(WB);
    tty_thread->setWorkTime(60);
    receive_count=0;

}
void Maintancance::uiShowRgb(unsigned int W, unsigned int R, unsigned int G, unsigned int B,unsigned int _result)
{
    QString w,r,g,b,re;


w =  QString::number(W, 10);
r  =   QString::number(R, 10);
g =  QString::number(G, 10);
b =  QString::number(B, 10);
re = QString::number(_result, 10);

ui->edit_white->setText(w);
ui->edit_read->setText(r);
ui->edit_green->setText(g);
ui->eadit_blue->setText(b);
ui->edit_Result->setText(re);
}

void Maintancance::showWrgb(unsigned int W, unsigned int R, unsigned int G,unsigned int B)
{
    QString w,r,g,b;
printf(" ***********  showWrgb ************%d\n",receive_count);

w =  QString::number(W, 10);
r  =   QString::number(R, 10);
g =  QString::number(G, 10);
b =  QString::number(B, 10);

    ui->edit_white->setText(w);
    ui->edit_read->setText(r);
    ui->edit_green->setText(g);
    ui->eadit_blue->setText(b);

    result[receive_count].wrgb_value[0]=W;
    result[receive_count].wrgb_value[1]=R;
    result[receive_count].wrgb_value[2]=G;
    result[receive_count].wrgb_value[3]=B;

    receive_count++;
    if(receive_count >=12)
    {
        stopDebugClicked();
//        for(int i=0;i<13;i++)
//        {

//        printf("count:%d    %d   %d   %d \n",i,result[i].wrgb_value[0],result[i].wrgb_value[1],result[i].wrgb_value[2],result[i].wrgb_value[3]);
//        }
    }
}

void Maintancance::modelSelectionClicked(int index)
{
        QString w,r,g,b;

        for(int i=0;i<13;i++)
        {

        printf("rgb: count:%d   W: %d  R: %d  G: %d  B: %d\n",i,result[i].wrgb_value[0],result[i].wrgb_value[1],result[i].wrgb_value[2],result[i].wrgb_value[3]);
        }

    printf("wb:   W:%d  R:%d  G:%d B:%d  \n",result[0].white_value[0],
                                                                           result[0].white_value[1],
                                                                           result[0].white_value[2],
                                                                           result[0].white_value[3]
         );

        switch(typeSelection)
        {
            case R10T:
                            switch(index)
                            {
                            case 0:
                                  //  uiShowRgb(result[10].wrgb_value[0],result[10].wrgb_value[1],result[10].wrgb_value[2],result[10].wrgb_value[3]);

                            break;

                            case 1:
                                 //     uiShowRgb(result[9].wrgb_value[0],result[9].wrgb_value[1],result[9].wrgb_value[2],result[9].wrgb_value[3]);
                            break;

                            case 2:
                             //     uiShowRgb(result[8].wrgb_value[0],result[8].wrgb_value[1],result[8].wrgb_value[2],result[8].wrgb_value[3]);
                            break;

                            case 3:
                                //      uiShowRgb(result[7].wrgb_value[0],result[7].wrgb_value[1],result[7].wrgb_value[2],result[7].wrgb_value[3]);
                            break;

                            case 4:
                                 //  uiShowRgb(result[6].wrgb_value[0],result[6].wrgb_value[1],result[6].wrgb_value[2],result[6].wrgb_value[3]);
                            break;

                            case 5:
                                //  uiShowRgb(result[5].wrgb_value[0],result[5].wrgb_value[1],result[5].wrgb_value[2],result[5].wrgb_value[3]);
                            break;

                            case 6:
                               //  uiShowRgb(result[4].wrgb_value[0],result[4].wrgb_value[1],result[4].wrgb_value[2],result[4].wrgb_value[3]);
                            break;

                            case 7:
                                //   uiShowRgb(result[3].wrgb_value[0],result[3].wrgb_value[1],result[3].wrgb_value[2],result[3].wrgb_value[3]);
                            break;

                            case 8:
                              //  uiShowRgb(result[2].wrgb_value[0],result[2].wrgb_value[1],result[2].wrgb_value[2],result[2].wrgb_value[3]);
                            break;

                            case 9:
                                 //    uiShowRgb(result[1].wrgb_value[0],result[1].wrgb_value[1],result[1].wrgb_value[2],result[1].wrgb_value[3]);
                            break;

                            case 10:
                                   // uiShowRgb(result[0].wrgb_value[0],result[0].wrgb_value[1],result[0].wrgb_value[2],result[0].wrgb_value[3]);
                            break;

                            default:break;
                            }
            break;

            case R113:
                            switch(index)
                            {
                            case 0://BIL


                                      cac.rgbCalculation(  2,0,
                                                                               result[12].wrgb_value,
                                                                               result[0].white_value,
                                                                               result[0].wrgb_value,
                                                                               JIEGUO );
                                       uiShowRgb(result[12].wrgb_value[0],result[12].wrgb_value[1],result[12].wrgb_value[2],result[12].wrgb_value[3], JIEGUO[1]);
                            break;

                            case 1://URO

                                       cac.rgbCalculation(  2,1,
                                                                                result[11].wrgb_value,
                                                                                result[0].white_value,
                                                                                result[0].wrgb_value,
                                                                                JIEGUO );
                                        uiShowRgb(result[11].wrgb_value[0],result[11].wrgb_value[1],result[11].wrgb_value[2],result[11].wrgb_value[3],JIEGUO[0]);
                            break;

                            case 2://KET

                                     cac.rgbCalculation(  2,2,
                                                                              result[10].wrgb_value,
                                                                              result[0].white_value,
                                                                              result[0].wrgb_value,
                                                                              JIEGUO );
                                      uiShowRgb(result[10].wrgb_value[0],result[10].wrgb_value[1],result[10].wrgb_value[2],result[10].wrgb_value[3],JIEGUO[2]);
                            break;

                            case 3://BLD

                                     cac.rgbCalculation(  2,3,
                                                                              result[9].wrgb_value,
                                                                              result[0].white_value,
                                                                              result[0].wrgb_value,
                                                                              JIEGUO );
                                      uiShowRgb(result[9].wrgb_value[0],result[9].wrgb_value[1],result[9].wrgb_value[2],result[9].wrgb_value[3],JIEGUO[3]);
                            break;

                            case 4://PRO

                                 cac.rgbCalculation(  2,4,
                                                                          result[8].wrgb_value,
                                                                          result[0].white_value,
                                                                          result[0].wrgb_value,
                                                                          JIEGUO );
                                     uiShowRgb(result[8].wrgb_value[0],result[8].wrgb_value[1],result[8].wrgb_value[2],result[8].wrgb_value[3],JIEGUO[4]);
                            break;

                            case 5://MIT

                                    cac.rgbCalculation(  2,5,
                                                                             result[7].wrgb_value,
                                                                             result[0].white_value,
                                                                             result[0].wrgb_value,
                                                                             JIEGUO );
                                     uiShowRgb(result[7].wrgb_value[0],result[7].wrgb_value[1],result[7].wrgb_value[2],result[7].wrgb_value[3],JIEGUO[5]);
                            break;

                            case 6://WBC

                                     cac.rgbCalculation(  2,6,
                                                                              result[6].wrgb_value,
                                                                              result[0].white_value,
                                                                              result[0].wrgb_value,
                                                                              JIEGUO );
                                     uiShowRgb(result[6].wrgb_value[0],result[6].wrgb_value[1],result[6].wrgb_value[2],result[6].wrgb_value[3],JIEGUO[6]);
                            break;

                            case 7://GLU

                                   cac.rgbCalculation(  2,7,
                                                                            result[5].wrgb_value,
                                                                            result[0].white_value,
                                                                            result[0].wrgb_value,
                                                                            JIEGUO );
                                    uiShowRgb(result[5].wrgb_value[0],result[5].wrgb_value[1],result[5].wrgb_value[2],result[5].wrgb_value[3],JIEGUO[7]);
                            break;

                            case 8://SG

                                cac.rgbCalculation(  2,8,
                                                                         result[4].wrgb_value,
                                                                         result[0].white_value,
                                                                         result[0].wrgb_value,
                                                                         JIEGUO );
                                     uiShowRgb(result[4].wrgb_value[0],result[4].wrgb_value[1],result[4].wrgb_value[2],result[4].wrgb_value[3],JIEGUO[8]);
                            break;

                            case 9://PH

                                cac.rgbCalculation(  2,9,
                                                                         result[3].wrgb_value,
                                                                         result[0].white_value,
                                                                         result[0].wrgb_value,
                                                                         JIEGUO );
                                   uiShowRgb(result[3].wrgb_value[0],result[3].wrgb_value[1],result[3].wrgb_value[2],result[3].wrgb_value[3],JIEGUO[9]);
                            break;

                            case 10://VC

                                cac.rgbCalculation(  2,10,
                                                                         result[2].wrgb_value,
                                                                         result[0].white_value,
                                                                         result[0].wrgb_value,
                                                                         JIEGUO );
                                       uiShowRgb(result[2].wrgb_value[0],result[2].wrgb_value[1],result[2].wrgb_value[2],result[2].wrgb_value[3],JIEGUO[10]);
                            break;

                            case 11://CC

                                 cac.rgbCalculation(  2,11,
                                                                          result[1].wrgb_value,
                                                                          result[0].white_value,
                                                                          result[0].wrgb_value,
                                                                          JIEGUO );
                                  uiShowRgb(result[1].wrgb_value[0],result[1].wrgb_value[1],result[1].wrgb_value[2],result[1].wrgb_value[3],JIEGUO[11]);
                            break;

                            case 12://BPH
                                  uiShowRgb(result[0].wrgb_value[0],result[0].wrgb_value[1],result[0].wrgb_value[2],result[0].wrgb_value[3],result[0].wrgb_value[0]);
                                    printf(" BPH CAC  IS:%d  \n",result[0].wrgb_value[0]);
                            break;

                            default:break;
                            }
             break;
            default:break;
        }
}

void Maintancance::showWb(unsigned int W, unsigned int R, unsigned int G, unsigned int B)
{
    QString w,r,g,b;

printf(" ***********  showWb ************\n");

    w =  QString::number(W, 10);
    r  =   QString::number(R, 10);
    g =  QString::number(G, 10);
    b =  QString::number(B, 10);

    ui->edit_white->setText(w);
    ui->edit_read->setText(r);
    ui->edit_green->setText(g);
    ui->eadit_blue->setText(b);

    result[0].white_value[0]=W;
    result[0].white_value[1]=R;
    result[0].white_value[2]=G;
    result[0].white_value[3]=B;



}
