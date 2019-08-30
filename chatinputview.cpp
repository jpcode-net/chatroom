/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#include "chatinputview.h"
#include "ui_chatinputview.h"
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>

ChatInputView::ChatInputView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatInputView)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout(ui->widget);
    m_textEdit = new ChatTextEdit(ui->widget);
    layout->addWidget(m_textEdit);
    layout->setMargin(0);

}

ChatInputView::~ChatInputView()
{
    delete ui;
}

void ChatInputView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    ui->widget->resize(this->width(), this->height());
    ui->widget->move(0, 0);

    ui->sendButton->move(this->width() - ui->sendButton->width() - 10,
                         this->height() - ui->sendButton->height() - 10);

}

void ChatInputView::on_sendButton_clicked()
{
    QString content = m_textEdit->toPlainText();
    if (content == "") {
        QMessageBox::warning(this, "提示", "请输入内容。");
        return ;
    }

    emit onSend(m_textEdit->toHtml());

    m_textEdit->setText("");
}
