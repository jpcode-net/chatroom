/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#include "selfmessageitemview.h"
#include "ui_selfmessageitemview.h"
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>
#include <QStack>
#include <QDebug>

SelfMessageItemView::SelfMessageItemView(QWidget *parent) :
    MessageItemView(parent),
    ui(new Ui::SelfMessageItemView)
{
    ui->setupUi(this);

    ui->label->setFixedHeight(60);
    ui->label->setFixedWidth(60);
}

SelfMessageItemView::~SelfMessageItemView()
{
    delete ui;
}

void SelfMessageItemView::updateLayout()
{
    QPixmap avatarPixmap = QPixmap(":/img/avatar01.png");
    ui->label->setPixmap(avatarPixmap);
    ui->label->setScaledContents(true);
    ui->label->move( this->width() - 70, 10 );

    int maxHeight = 60;  // avatar height;

    ui->textEdit->setHtml( message().content );

    QTextDocument *doc = ui->textEdit->document();
    doc->adjustSize();
    QSizeF size = ui->textEdit->document()->size();

    ui->textEdit->setFixedWidth((int)size.width() + 20);
    ui->textEdit->setFixedHeight((int)size.height() + 10);
    ui->textEdit->move(this->width()-80-size.width()-20, 10);

    if (maxHeight < size.height())
        maxHeight = (int)size.height();

    this->setFixedHeight(maxHeight + 20);
}

