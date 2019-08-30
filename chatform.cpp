/****************************************************************************
**
** Copyright (C) 2019 The jpcode.
** Contact: http://jpcode.net/licensing/
**
** --- chatroom
**
****************************************************************************/

#include "chatform.h"
#include "ui_chatform.h"
#include <QDebug>
#include <QDateTime>
#include "message.h"
#include <QJsonDocument>
#include "timeitemview.h"
#include "messageitemview.h"
#include "selfmessageitemview.h"
#include "othermessageitemview.h"
#include <QListWidget>
#include <QFile>
#include <QDomDocument>
#include <QStack>
#include <QDomNode>
#include <QMessageBox>

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);

    m_horSplitter = new QSplitter(Qt::Horizontal, this);

    m_vertSplitter = new QSplitter(Qt::Vertical, m_horSplitter);

    m_msgListWidget = new QListWidget(m_vertSplitter);
    m_msgListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    m_inputView = new ChatInputView(m_vertSplitter);

    m_vertSplitter->setStretchFactor(0, 4);
    m_vertSplitter->setStretchFactor(1, 1);

    m_userListWidget = new QListWidget(m_horSplitter);
    m_userListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    m_horSplitter->setStretchFactor(0, 3);
    m_horSplitter->setStretchFactor(1, 1);

    ui->gridLayout->setMargin(3);
    ui->gridLayout->addWidget(m_horSplitter);

    connect(m_horSplitter, &QSplitter::splitterMoved, this, &ChatForm::horSplitterMoved);
    connect(m_inputView, &ChatInputView::onSend, this, &ChatForm::onSend);

    resize(800, 600);

    //test
    Message msg;
    msg.setContent( "other people." );
    msg.setType( "chat" );
    msg.setFromId( 100001 );
    msg.setFromName( "user1" );
    msg.setTime( QDateTime::currentDateTime().toTime_t() );

    MessageItemView* itemView = new OtherMessageItemView(m_msgListWidget->parentWidget());
    itemView->setMessage(msg);
    QListWidgetItem* item = new QListWidgetItem(m_msgListWidget);
    showMessage(itemView, item);
    m_msgListWidget->setCurrentRow(m_msgListWidget->count()-1);

}

ChatForm::~ChatForm()
{
    delete ui;
}

void ChatForm::onReceive(const QString& message)
{
    qDebug() << "receive: " << message;

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(message.toUtf8(), &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug() << json_error.errorString();
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    Message msg = Message::fromJson(jsonObj);

    QDomDocument doc;
    doc.setContent(message, false);

    QDomElement root = doc.documentElement();

    QStack<QDomElement> *stack = new QStack<QDomElement>();
    stack->push(root);

    while (stack->size() > 0) {
        QDomElement el = stack->pop();

        if ("img" == el.tagName()) {
            // 下载图片
            QString imgUrl = el.attributeNode("src").value();
            QString imgPath = downImage(imgUrl);
            if (imgPath != "") {
                el.attributeNode("src").setValue("file://" + imgPath);
            }
        }

        QDomNodeList nodeList = el.childNodes();
        for (int i=0; i<nodeList.size(); i++) {
            stack->push(nodeList.at(i).toElement());
        }
    }

    msg.setContent( doc.toString() );

    showTimeLabel(msg.time());

    MessageItemView* itemView = new SelfMessageItemView(m_msgListWidget->parentWidget());
    itemView->setMessage(msg);
    QListWidgetItem* item = new QListWidgetItem(m_msgListWidget);
    showMessage(itemView, item);

    m_msgListWidget->setCurrentRow(m_msgListWidget->count()-1);
}

void ChatForm::onSend(const QString& content)
{
    uint time = QDateTime::currentDateTime().toTime_t(); //时间戳
    qDebug()<<"addMessage" << content << time;

    QDomDocument doc;
    doc.setContent(content, false);

    QDomElement root = doc.documentElement();

    QStack<QDomElement> *stack = new QStack<QDomElement>();
    stack->push(root);

    while (stack->size() > 0) {
        QDomElement el = stack->pop();

        if ("img" == el.tagName()) {

            // 上传图片
            QString imgSrc = el.attributeNode("src").value();
            QString imgUrl = uploadImage(imgSrc);
            if (imgUrl != "") {
                el.attributeNode("src").setValue(imgUrl);
            }
        }

        QDomNodeList nodeList = el.childNodes();
        for (int i=0; i<nodeList.size(); i++) {
            stack->push(nodeList.at(i).toElement());
        }
    }

    QString newContent = doc.toString();

    Message msg;
    msg.setFromId( 10002 );
    msg.setFromName( "user2" );
    msg.setContent( newContent );
    msg.setTime( time );

    // send .

    showTimeLabel(time);

    MessageItemView* itemView = new SelfMessageItemView(m_msgListWidget->parentWidget());
    itemView->setMessage(msg);
    QListWidgetItem* item = new QListWidgetItem(m_msgListWidget);
    showMessage(itemView, item);

    m_msgListWidget->setCurrentRow(m_msgListWidget->count()-1);
}

void ChatForm::showMessage(ChatItemView *itemView, QListWidgetItem *item)
{
    itemView->setFixedWidth(m_vertSplitter->width() - 10);
    itemView->updateLayout();
    QSize size(m_vertSplitter->width() - 10, itemView->height());
    item->setSizeHint(size);
    m_msgListWidget->setItemWidget(item, itemView);
}

void ChatForm::showTimeLabel(uint curTime)
{
    bool isShowTime = false;
    if(m_msgListWidget->count() > 0) {
        QListWidgetItem* lastItem = m_msgListWidget->item(m_msgListWidget->count() - 1);
        ChatItemView* itemView = (ChatItemView*)m_msgListWidget->itemWidget(lastItem);
        isShowTime = ((curTime - itemView->time()) > 60); // 两个消息相差一分钟
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        TimeItemView* timeView = new TimeItemView(m_msgListWidget->parentWidget());
        QListWidgetItem* listItem = new QListWidgetItem(m_msgListWidget);

        QSize size = QSize(m_vertSplitter->width() - 10, 40);
        timeView->resize(size);
        listItem->setSizeHint(size);
        timeView->setTime(curTime);
        m_msgListWidget->setItemWidget(listItem, timeView);
    }
}

void ChatForm::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    adjustLayout();
}

void ChatForm::horSplitterMoved(int pos, int index)
{
    Q_UNUSED(pos); Q_UNUSED(index);

    adjustLayout();
}

void ChatForm::adjustLayout()
{
    for(int i = 0; i < m_msgListWidget->count(); i++) {
        ChatItemView* itemView = (ChatItemView*)m_msgListWidget->itemWidget(m_msgListWidget->item(i));
        QListWidgetItem* item = m_msgListWidget->item(i);

        showMessage(itemView, item);
    }
}

QString ChatForm::downImage(const QString& imageUrl)
{
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir;
    if (!dir.exists(dataPath))
        dir.mkpath(dataPath);

    HttpRequest request;
    QByteArray data = request.get(imageUrl);
    if (request.errorCode() == 0 && request.statusCode() == 200) {
       int n = imageUrl.lastIndexOf("/");
       QString filename = dataPath + imageUrl.right(imageUrl.length() - n);
       QFile file(filename);
       file.open(QIODevice::NewOnly | QIODevice::WriteOnly);
       file.write(data);
       file.flush();
       file.close();

       return filename;
    }

    return "";
}

QString ChatForm::uploadImage(const QString& imagePath)
{
    QFile file(QUrl(imagePath).toLocalFile());
    file.open(QIODevice::ReadOnly);

    return "";
}
