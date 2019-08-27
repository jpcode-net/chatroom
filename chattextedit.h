/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef CHATTEXTEDIT_H
#define CHATTEXTEDIT_H

#include <QTextEdit>
#include <QMimeData>

class ChatTextEdit : public QTextEdit
{
public:
    ChatTextEdit(QWidget* parent=nullptr);

public:
    bool canInsertFromMimeData(const QMimeData* source) const;
    void insertFromMimeData(const QMimeData* source);

private:
    void dropImage(const QUrl& url, const QImage& image) ;
    void dropTextFile(const QUrl& url);
};

#endif // CHATTEXTEDIT_H
