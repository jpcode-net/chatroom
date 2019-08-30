/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef CLASSROOMFORM_H
#define CLASSROOMFORM_H

#include <QWidget>
#include "message.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QSplitter>
#include "chatitemview.h"
#include "chatinputview.h"
#include "message.h"

namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();

public:
    void showMessage(ChatItemView *itemView, QListWidgetItem *item);
    void showTimeLabel(uint curTime);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onReceive(const QString& message);
    void onSend(const QString& message);

    void horSplitterMoved(int pos, int index);
    void adjustLayout();

    QString downImage(const QString& imageUrl);
    QString uploadImage(const QString& imagePath);

private:
    Ui::ChatForm *ui;

    QSplitter* m_vertSplitter;
    QSplitter* m_horSplitter;

    QListWidget* m_msgListWidget;
    QListWidget* m_userListWidget;
    ChatInputView* m_inputView;

    QList<Message> m_messageList;
};

#endif // CLASSROOMFORM_H
