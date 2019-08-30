/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- apiclient
**
****************************************************************************/

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>

class HttpRequest : public QObject
{

    Q_OBJECT

public:
    HttpRequest() {}

    QByteArray get(const QString& url);

    QByteArray post(const QString& url, const QByteArray& postData);

public:
    inline int statusCode() const { return m_statusCode; }
    inline int errorCode() const { return m_errorCode; }
    const QString& errorMsg() const { return m_errorMsg; }

    /* member */
public:
    int m_statusCode;
    int m_errorCode;
    QString m_errorMsg;
};

#endif // HTTPREQUEST_H
