#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include <QPixmap>
#include "keyboard.h"
#include "frminput.h"
#include <unistd.h>
/*
VER:1.0 初级版本
VER:1.1 校准测试完成版本
VER:2.0 基本功能完成待测试
VER:2.7 全部功能完毕
VER:2.9.8 解决机器Bug阶段
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QPixmap pixmap(":/image/Initialize_logo.gif");
    QSplashScreen splash(pixmap);

    QMovie *Movie = new QMovie(":/image/Initialize_logo.gif");
    QLabel *Label = new QLabel(&splash);
    Label->setMovie(Movie);
    Movie->start();
    splash.show();



    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
/*
 jack.keyboard
    KeyBoard *v_key = new KeyBoard();
    v_key->SetLineEditEchoMode();
    v_key->hide();
*/
    frmInput::Instance()->hide();
    MainWindow w;
    w.show();
    splash.finish(&w);

    delete Label;
    delete Movie;

    return a.exec();
}
