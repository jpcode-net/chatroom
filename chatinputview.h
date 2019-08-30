/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#ifndef CHATINPUTFORM_H
#define CHATINPUTFORM_H

#include <QWidget>
#include "chattextedit.h"

namespace Ui {
class ChatInputView;
}

class ChatInputView : public QWidget
{
    Q_OBJECT

public:
    explicit ChatInputView(QWidget* parent = nullptr);
    ~ChatInputView();

signals:
    void onSend(const QString& list);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_sendButton_clicked();

private:
    Ui::ChatInputView *ui;
    ChatTextEdit *m_textEdit;
};

#endif // CHATINPUTFORM_H
