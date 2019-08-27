/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#include "timeitemview.h"
#include <QPainter>
#include <QDateTime>

TimeItemView::TimeItemView(QWidget *parent) : ChatItemView(parent)
{

}

void TimeItemView::setTime(const QString& time)
{
    ChatItemView::setTime(time);

    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("hh:mm");

    this->update();
}

void TimeItemView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    QPen penText;
    penText.setColor(QColor(153,153,153));
    painter.setPen(penText);
    QTextOption option(Qt::AlignCenter);
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    QFont te_font = this->font();
    te_font.setFamily("MicrosoftYaHei");
    te_font.setPointSize(10);
    painter.setFont(te_font);
    painter.drawText(this->rect(),m_curTime,option);
}
