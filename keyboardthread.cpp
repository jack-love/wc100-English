/***********************************************************
************************************************************
************************************************************
*文件名：      Thread.cpp
*
*作者：        jegbrother
*
*日期：        2017-05-25
*
*版本：        V1.0
*
*说明：        加载中文字库的线程
*
*修改记录：
************************************************************
************************************************************
************************************************************/


#include "keyboardthread.h"
#include <QDebug>
#include "keyboard.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QFile>

Thread::Thread(QObject *parent):QThread(parent)
{

}

Thread::~Thread()
{
    quit();
    wait();
}

void Thread::run()
{
    QMultiMap<QString,QString> pinyin_map;  //存放中文字库
    unsigned char ret = 0;      //return value
    QFile font_library(":/syszux/syszuxpinyin");                //设置QFile的名称

    if(!font_library.open(QIODevice::ReadOnly))                    //只读模式，打开文件
    {
        QMessageBox::warning(0,tr("出错啦!"),tr("加载字库失败!"));   //打开失败,则报错
    }

    QRegExp regExp;
    regExp.setCaseSensitivity(Qt::CaseSensitive);           //设置正则表达式的参数,Qt::CaseInsensitive,大小写敏感
    regExp.setPattern(QString("([a-z]+)"));                 //获得正则本身,获取a-z

    while(!font_library.atEnd())
    {
        QByteArray data = font_library.readLine();           //读取一行,存到data中
        //进行匹配,如果成功则返回index,不成功返回-1;
        //data.data()是读取到的一行数据,返回值index应该是正则匹配到的字母位于data的第n个字节,这样就可以区分字库中的字母和汉字
        ret = regExp.indexIn(QString(data.data()),0,QRegExp::CaretAtZero);
        //将mmap对象的成员初始化;key是字母,value是汉字,这样字母和汉字就对应起来
        //regExp.cap(1)就是汉字,data.left(ret)就是字母
/*		
        QByteArray dt = data.left(ret);
         QTextCodec *codec = QTextCodec::codecForName("GBK");
         QString str = codec->toUnicode(dt);
		 pinyin_map.insert(regExp.cap(1), str);
 */       
        pinyin_map.insert(regExp.cap(1),data.left(ret));


    }
    emit SendFontMap(pinyin_map);   //触发信号
    quit();
}


