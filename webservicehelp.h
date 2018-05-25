#ifndef WEBSERVICEHELP_H
#define WEBSERVICEHELP_H

#include <QObject>
#include <QThread>
#include <QtNetwork/QNetworkReply>


class QNetworkReply;
class QNetworkAccessManager;
class QNetworkRequest;
class NetDataListenerThread;
class BmilpWebServiceData;

/**
 * @brief The WebServiceHelp class webservice调用帮助类
 * @author zp
 */



class WebServiceHelp : public QObject
{
    Q_OBJECT    
private:
    class Dispose
    {
    public:
        ~Dispose();
    };
public:
    static WebServiceHelp * getInstance();

public:
    /**
     * @brief sendGetRequest 发送Get请求
     * @param urlStr  url
     * @param ba      返回数据
     * @param timeOutms 超时时间
     * @return  返回错误代码
     */
    QNetworkReply::NetworkError sendGetRequest(QString urlStr, QByteArray & ba, int timeOutms=30000);

    /**
     * @brief sendPostRequest 发送post请求
     * @param website  网址
     * @param methodName 方法名称
     * @param param 参数
     * @param postBa    post数据
     * @param code      返回代码
     * @param message   返回信息
     * @param data      返回数据
     * @param timeOutms 超时时间
     * @return 返回错误代码
     */
    QNetworkReply::NetworkError sendPostRequest(QString website,const QByteArray & postBa, QByteArray& retBa, int timeOutms=30000);


protected slots:
    void slot_error(QNetworkReply::NetworkError code);
private:
    static WebServiceHelp * serverHelp;
    static WebServiceHelp::Dispose disp;
    QNetworkAccessManager *manager;
    QNetworkReply::NetworkError m_errCode;
private:
    WebServiceHelp(QObject *parent=0);
    ~WebServiceHelp();
};

#endif // WEBSERVICEHELP_H
