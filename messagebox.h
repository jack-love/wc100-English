#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include <QMessageBox>
class MessageBox: public QObject
{
public:
    MessageBox();
    void MessageBox_Info(QString info);
    void MessageBox_Err(QString info);
    int  MessageBox_Ask(QString info);
};

#endif // MESSAGEBOX_H
