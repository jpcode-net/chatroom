/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef SELFMESSAGEITEMVIEW_H
#define SELFMESSAGEITEMVIEW_H

#include <QWidget>
#include "messageitemview.h"

namespace Ui {
class SelfMessageItemView;
}

class SelfMessageItemView : public MessageItemView
{
    Q_OBJECT

public:
    explicit SelfMessageItemView(QWidget *parent = nullptr);
    ~SelfMessageItemView();

    void updateLayout();

private:
    Ui::SelfMessageItemView *ui;
};

#endif // SELFMESSAGEITEMVIEW_H
