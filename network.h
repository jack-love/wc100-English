#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QTime>
#include<QString>
#include <QStringList>
#include <QTextStream>
class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = NULL);
    ~Network();

    QString getFileInfo(QString task);
    void getFileInfo2(QString task);
    void startDownload(QString task, QString path);
    void stopDownload();

signals:
    void process(QString task, qint64 byteTotal, double percent, double speed);
    void taskFinished(QString task);
    void fileInfo(QString task, QString fileName, qint64 fileSize);
    void  downError_signal(QString siganl);

public slots:  
    void stopTask(QString task);


private slots:
    void readyToRead();
    void downloadError(QNetworkReply::NetworkError code);
    void downloadFinished();
    void downloadProgress(qint64 byteReceived, qint64 byteTotal);
    void gotFileInfo();

private:
    QString currentTask;
    QString currentGettingTask;
    QString currentFileName;
    QNetworkAccessManager manager;
    QNetworkReply *reply=NULL;
    QFile file;
    QTime downloadTime;
    QString downloadPath;
    bool isDownloading;
    qint64 bytesTotal;
    qint64 currentFileSize;
    int timeElapsed, timeLast;
};

#endif // NETWORK_H
