#include "webservicehelp.h"
#include "netdatalistenerthread.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>
#include <QThread>
#include <QEventLoop>
#include <QVariantMap>
#include <iterator>
#include <QJsonParseError>
#include <QJsonDocument>

WebServiceHelp * WebServiceHelp::serverHelp = NULL;
WebServiceHelp::Dispose WebServiceHelp::disp;

WebServiceHelp::WebServiceHelp(QObject *parent):QObject(parent)
{
    manager = new QNetworkAccessManager();
    m_errCode= QNetworkReply::NoError;
}

WebServiceHelp::~WebServiceHelp()
{
    manager->deleteLater();

}

WebServiceHelp *WebServiceHelp::getInstance()
{
    if(serverHelp==NULL)
    {
        serverHelp = new WebServiceHelp();
    }
    return serverHelp;
}

QNetworkReply::NetworkError WebServiceHelp::sendGetRequest(QString urlStr, QByteArray & ba,int timeOutms)
{
    QNetworkReply::NetworkError retError = QNetworkReply::NoError;
    m_errCode= QNetworkReply::NoError;
    QNetworkRequest request;
    QUrl url(urlStr);
    request.setUrl(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),this,&WebServiceHelp::slot_error);


    QEventLoop eventLoop;
    NetDataListenerThread * thread = new NetDataListenerThread(manager,reply,timeOutms);
    connect(thread, &NetDataListenerThread::finished,&eventLoop,&QEventLoop::quit);
    thread->start();
    eventLoop.exec();
    if(thread->getIsWaitTimeOut())
    {
        ba = reply->readAll();
    }
    else
    {
        m_errCode=QNetworkReply::TimeoutError;
    }
    thread->deleteLater();
    delete reply;
    delete thread;
    thread = NULL;
    retError = m_errCode;
    m_errCode= QNetworkReply::NoError;
    return retError;
}

QNetworkReply::NetworkError WebServiceHelp::sendPostRequest(QString website, const QByteArray &postBa, QByteArray &retBa, int timeOutms)
{
    QString urlStr =website;

    QNetworkReply::NetworkError retError = QNetworkReply::NoError;
    m_errCode= QNetworkReply::NoError;
    QNetworkRequest request;
    QUrl url(urlStr);
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,postBa.length());
    QNetworkReply *reply = manager->post(request,postBa);

    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),this,&WebServiceHelp::slot_error);


    QEventLoop eventLoop;
    NetDataListenerThread * thread = new NetDataListenerThread(manager,reply,timeOutms);
    connect(thread, &NetDataListenerThread::finished,&eventLoop,&QEventLoop::quit);
    thread->start();
    eventLoop.exec();

    if(thread->getIsWaitTimeOut())
    {
        retBa = reply->readAll();
    }
    else
    {
        m_errCode=QNetworkReply::TimeoutError;
    }
    thread->deleteLater();
    delete reply;
    delete thread;
    thread = NULL;
    retError = m_errCode;
    m_errCode= QNetworkReply::NoError;
    return retError;


}

void WebServiceHelp::slot_error(QNetworkReply::NetworkError code)
{
    m_errCode = code;
}

WebServiceHelp::Dispose::~Dispose()
{
    if(WebServiceHelp::serverHelp!=NULL)
    {
        delete WebServiceHelp::serverHelp;
        WebServiceHelp::serverHelp=NULL;
    }
}

//QNetworkReply::NetworkError WebServiceHelp::stop(QString website, const QByteArray &postBa, QByteArray &retBa, int timeOutms)
//{
//    if(!httpRequestAbort)
//    {
//        reply->abort();//响应终止
//        httpRequestAbort=true;
//        stop_Btn->setText("start");
//    }
//    else
//    {   httpDownload();
//        httpRequestAbort=false;
//        stop_Btn->setText("stop");
//     }
//}










//void WebServiceHelp::updateProgram()
//{
//    //QFile file("123");
//    if(netfile != NULL)
//    {
//        if(!netfile->open(QIODevice::WriteOnly))
//        {
//            return;
//        }
//        netfile->seek(downsize);
//        qDebug()<<"file exit "<<downsize;
//    }
//    else
//    {
//        netfile =  new QFile("123");
//        if(!netfile->open(QIODevice::WriteOnly))
//        {
//            return;
//        }
//        qDebug()<<"file not exit "<<downsize;
//    }
//    bar->show();
//    httpRequestAborted = false;
//    update_status == Text::stop;
//    QUrl  u("http://192.168.1.101/123.zip");
//    qDebug()<<"downsize"<<downsize;
//    QNetworkRequest qheader;
//    qheader.setUrl(u);
//    qheader.setRawHeader("Range",tr("bytes=%1-").arg(downsize).toUtf8());
//    reply = m_netwManager->get(QNetworkRequest(qheader));
//    connect(reply,SIGNAL(finished()),this,SLOT(FinishLoad()));
//    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(UpdateBar(qint64,qint64)));
//    connect(reply,SIGNAL(readyRead()),this,SLOT(ReadyFile()));
//    updatebtn->disconnect();
//    connect(updatebtn,SIGNAL(clicked()),this,SLOT(cancelDownload()));
//}

//void WebServiceHelp::ReadyFile()
//{
//     if (netfile)
//    netfile->write(reply->readAll());
//}

//void WebServiceHelp::FinishLoad()
//{
//    qDebug()<<"finished";
//    if (httpRequestAborted) {//httpRequestAborted暂停的标志
//        if (netfile) {
//            netfile->close();
//        }
//        reply->deleteLater();
//        return;
//    }
//      netfile->close();
//      bar->hide();
//      reply->deleteLater();
//}

////更新进度条
//void Text::UpdateBar(qint64 x,qint64 size)
//{
//    qDebug()<<"x"<<x<<"size"<<size;
//    bar->setMaximum(size);
//    bar->setValue(datasize+x);
//}
