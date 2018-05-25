#ifndef NETDATALISTENERTHREAD_H
#define NETDATALISTENERTHREAD_H


#include <QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTimer>
#include <QThread>
#include <QEventLoop>

//namespace Ui {
//class NetDataListenerThread;
//}


class NetDataListenerThread : public QThread
{
    Q_OBJECT
public:
    NetDataListenerThread(QNetworkAccessManager *manager,QNetworkReply * reply,int timeoutms,QObject *parent = 0);
    ~NetDataListenerThread();
    QByteArray getBa() const;
    bool getIsWaitTimeOut() const;
protected:
    virtual void run();
private:
    bool waitForConnect();
protected slots:
    void slot_waitTimeout();

signals:
    void sig_waitTimeout();
private:
    QNetworkAccessManager *mManager;
    int m_TimeOutms;
    bool m_waitTimeOut;
    bool m_isWaitTimeOut;
    QNetworkReply * m_reply;
};

#endif // NETDATALISTENERTHREAD_H
