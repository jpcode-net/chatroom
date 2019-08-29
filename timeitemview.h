/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef TIMEITEMVIEW_H
#define TIMEITEMVIEW_H

#include <QWidget>
#include "messageitemview.h"

class TimeItemView : public ChatItemView
{
    Q_OBJECT
public:
    explicit TimeItemView(QWidget *parent = nullptr);

signals:

public slots:

public:
    void setTime(uint time);

protected:
    void paintEvent(QPaintEvent *event);
    void updateLayout() { }

private:
    QString m_curTime;

};

#endif // TIMEITEMVIEW_H
