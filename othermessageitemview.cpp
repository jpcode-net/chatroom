/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#include "othermessageitemview.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>
#include <QGridLayout>
#include "ui_othermessageitemview.h"

OtherMessageItemView::OtherMessageItemView(QWidget *parent) :
    MessageItemView(parent),
    ui(new Ui::OtherMessageItemView)
{
    ui->setupUi(this);

    ui->label->setFixedHeight(60);
    ui->label->setFixedWidth(60);
    ui->label->move( 10, 10 );
    ui->textEdit->move( 80, 10 );
}


void OtherMessageItemView::updateLayout()
{
    QPixmap avatarPixmap = QPixmap(":/img/avatar02.png");
    ui->label->setPixmap(avatarPixmap);
    ui->label->setScaledContents(true);

    int maxHeight = 60;  // avatar height;

    ui->textEdit->setHtml( message().content() );

    QTextDocument *doc = ui->textEdit->document();
    doc->adjustSize();
    QSizeF size = ui->textEdit->document()->size();

    ui->textEdit->setFixedWidth((int)size.width() + 20);
    ui->textEdit->setFixedHeight((int)size.height() + 10);

    if (maxHeight < size.height())
        maxHeight = (int)size.height();

    this->setFixedHeight(maxHeight + 20);
}


