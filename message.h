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
    inline int fromId() const { return m_fromId; }
    inline const QString& fromName() { return m_fromName; }
    inline const QString& type() { return m_type; }
    inline const QString& toUsers() { return m_toUsers; }
    inline const QString& content() { return m_content; }
    inline uint time() const { return m_time; }

    inline void setFromId(int fromId) { m_fromId=fromId; }
    inline void setFromName(const QString& fromName) { m_fromName=fromName; }
    inline void setType(const QString& type) { m_type=type; }
    inline void setToUsers(const QString& toUsers) { m_toUsers=toUsers; }
    inline void setContent(const QString& content) { m_content=content; }
    inline void setTime(uint time) { m_time=time; }

public:
    static Message fromJson(const QJsonObject& jsonObj)
    {
        Message msg;
        msg.setFromId( jsonObj.value("fromId").toInt() );
        msg.setFromName( jsonObj.value("fromName").toString() );
        msg.setType( jsonObj.value("type").toString() );
        msg.setToUsers( jsonObj.value("toUsers").toString() );
        msg.setContent( jsonObj.value("content").toString() );
        msg.setTime( (uint)jsonObj.value("time").toInt() );

        return msg;
    }

    QJsonObject toJson()
    {
        QJsonObject jsonObj;
        jsonObj.insert("fromId", m_fromId);
        jsonObj.insert("type", m_type);
        jsonObj.insert("fromName", m_fromName);
        jsonObj.insert("toUsers", m_toUsers);
        jsonObj.insert("content", m_content);

        return jsonObj;
    }

private:
    int m_fromId;
    QString m_fromName;
    QString m_type;
    QString m_toUsers;
    QString m_content;
    uint m_time;
};

#endif // MESSAGE_H
