#ifndef  KEYBOARDTHREAD_H
#define KEYBOARDTHREAD_H

#include <QThread>
#include <iostream>
#include <QMultiMap>
#include <QTextCodec>
class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = 0);   //explicit声明后只允许显式调用
    ~Thread();      //程序结束时都会隐式调用析构函数

protected:
    void run(); //新线程,主线程调用start()时,新线程会自动调用run()函数

private:

signals:
    void SendFontMap(QMultiMap<QString,QString>);

};

#endif // THREAD_H
