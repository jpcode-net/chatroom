/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#include "httprequest.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

QByteArray HttpRequest::get(const QString& url)
{
    QNetworkAccessManager *httpMgr = new QNetworkAccessManager();

    QNetworkRequest req;
    req.setUrl(url);

    QNetworkReply *reply = httpMgr->get(req);

    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    m_errorCode = reply->error();
    m_statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (m_errorCode == QNetworkReply::NoError) {
        return reply->readAll();
    } else {
        m_errorMsg = qPrintable(reply->errorString());
        return nullptr;
    }
}

QByteArray HttpRequest::post(const QString& url, const QByteArray& data)
{
    QNetworkAccessManager *httpMgr = new QNetworkAccessManager();

    QNetworkRequest req;
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, data.size());
    req.setUrl(url);

    QNetworkReply *reply = httpMgr->post(req, data);

    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    m_errorCode = reply->error();
    m_statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    if (m_errorCode == QNetworkReply::NoError) {
        return reply->readAll();
    } else {
        m_errorMsg = qPrintable(reply->errorString());
        return nullptr;
    }
}
