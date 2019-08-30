/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef MESSAGEITEMVIEW_H
#define MESSAGEITEMVIEW_H

#include <QWidget>
#include "chatitemview.h"
#include "message.h"
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include "httprequest.h"

class MessageItemView : public ChatItemView
{
    Q_OBJECT

public:
    MessageItemView(QWidget *parent=nullptr) : ChatItemView(parent) { }

public:
    inline void setMessage(const Message& message)
    {
        m_msg = message;
        setTime(m_msg.time());
    }
    inline Message& message() { return m_msg; }

private:
    Message m_msg;
};

#endif // MESSAGEITEMVIEW_H
