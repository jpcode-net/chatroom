/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef CHATITEMVIEW_H
#define CHATITEMVIEW_H

#include <QWidget>

enum ChatItemType{
        SystemMessage,//系统
        SelfMessage,    //自己
        TheirMessage,   //用户
        TimeMessage,  //时间
    };

class ChatItemView : public QWidget
{
    Q_OBJECT

public:
    ChatItemView(QWidget *parent=nullptr) : QWidget(parent) { }

public:
    virtual void setTime(uint time) { m_time = time; }
    uint time() const { return m_time; }
    virtual void updateLayout() = 0;

private:
    uint m_time;
};

#endif // CHATITEMVIEW_H
