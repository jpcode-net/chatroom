/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef OTHERMESSAGEITEMVIEW_H
#define OTHERMESSAGEITEMVIEW_H

#include <QWidget>
#include <QLabel>
#include "messageitemview.h"
#include "message.h"
#include <QTextEdit>

namespace Ui {
class OtherMessageItemView;
}

class OtherMessageItemView : public MessageItemView
{
    Q_OBJECT

public:
    OtherMessageItemView(QWidget *parent=nullptr);

    void updateLayout();

private:
    Ui::OtherMessageItemView* ui;
};

#endif // OTHERMESSAGEITEMVIEW_H
