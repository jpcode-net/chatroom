/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#include <QApplication>
#include "chatform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChatForm form;
    form.show();

    return a.exec();

}
