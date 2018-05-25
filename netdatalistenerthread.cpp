#include "netdatalistenerthread.h"


NetDataListenerThread::NetDataListenerThread(QNetworkAccessManager *manager, QNetworkReply *reply, int timeoutms, QObject *parent)
    :QThread(parent),mManager(manager),m_TimeOutms(timeoutms),m_reply(reply)
{
    m_waitTimeOut = false;
    m_isWaitTimeOut = false;
}

NetDataListenerThread::~NetDataListenerThread()
{

}

void NetDataListenerThread::run()
{
    m_isWaitTimeOut = waitForConnect();
}

bool NetDataListenerThread::waitForConnect()
{
    QEventLoop eventLoop;
    QTimer * timer = NULL;
    m_waitTimeOut = false;
    bool bWaitTimeOut = false;
    if (m_TimeOutms > 0)
    {
        timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(slot_waitTimeout()));
        timer->setSingleShot(true);
        timer->start(m_TimeOutms);

        connect(this, SIGNAL(sig_waitTimeout()), &eventLoop, SLOT(quit()));
    }
    connect(mManager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));

    if (m_reply != NULL)
    {
        connect(m_reply, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));
    }
    eventLoop.exec();

    if (timer != NULL)
    {
        timer->stop();
        delete timer;
        timer = NULL;
    }
    bWaitTimeOut = m_waitTimeOut;
    m_waitTimeOut = false;
    return !bWaitTimeOut;
}

void NetDataListenerThread::slot_waitTimeout()
{
    m_waitTimeOut = true;
    emit sig_waitTimeout();
}


bool NetDataListenerThread::getIsWaitTimeOut() const
{
    return m_isWaitTimeOut;
}


