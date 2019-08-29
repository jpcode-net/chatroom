/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QJsonObject>

class Message
{
public:
    int fromId;
    QString fromName;
    QString type;
    QString toUsers;
    QString content;
    uint time;

public:
    static Message fromJson(const QJsonObject& jsonObj)
    {
        Message msg;
        msg.fromId = jsonObj.value("fromId").toInt();
        msg.fromName = jsonObj.value("fromName").toString();
        msg.type = jsonObj.value("type").toString();
        msg.toUsers = jsonObj.value("toUsers").toString();
        msg.content = jsonObj.value("content").toString();
        msg.time = (uint)jsonObj.value("time").toInt();

        return msg;
    }

    QJsonObject toJson()
    {
        QJsonObject jsonObj;
        jsonObj.insert("fromId", fromId);
        jsonObj.insert("type", type);
        jsonObj.insert("fromName", fromName);
        jsonObj.insert("toUsers", toUsers);
        jsonObj.insert("content", content);

        return jsonObj;
    }

};

#endif // MESSAGE_H
