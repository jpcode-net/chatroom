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

    horSplitter = new QSplitter(Qt::Horizontal, this);

    vertSplitter = new QSplitter(Qt::Vertical, horSplitter);

    msgListWidget = new QListWidget(vertSplitter);
    msgListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    inputView = new ChatInputView(vertSplitter);

    vertSplitter->setStretchFactor(0, 4);
    vertSplitter->setStretchFactor(1, 1);

    userListWidget = new QListWidget(horSplitter);
    userListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    horSplitter->setStretchFactor(0, 3);
    horSplitter->setStretchFactor(1, 1);

    ui->gridLayout->setMargin(3);
    ui->gridLayout->addWidget(horSplitter);

    connect(horSplitter, &QSplitter::splitterMoved, this, &ChatForm::horSplitterMoved);
    connect(inputView, &ChatInputView::onSend, this, &ChatForm::onSend);

    resize(800, 600);

    //test
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    Message msg;
    msg.content = "other people.";
    msg.type = "chat";
    msg.fromId = 100001;
    msg.fromName = "user1";
    msg.time = time;

    MessageItemView* itemView = new OtherMessageItemView(msgListWidget->parentWidget());
    itemView->setMessage(msg);
    QListWidgetItem* item = new QListWidgetItem(msgListWidget);
    showMessage(itemView, item);
    msgListWidget->setCurrentRow(msgListWidget->count()-1);

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

    QString time = msg.time; //时间戳

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

    msg.content = doc.toString();

    showTimeLabel(time);

    MessageItemView* itemView = new SelfMessageItemView(msgListWidget->parentWidget());
    itemView->setMessage(msg);
    QListWidgetItem* item = new QListWidgetItem(msgListWidget);
    showMessage(itemView, item);

    msgListWidget->setCurrentRow(msgListWidget->count()-1);
}

void ChatForm::onSend(const QString& content)
{
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
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
    msg.fromId = 10002;
    msg.fromName = "user2";
    msg.content = newContent;
    msg.time = time;

    // send .

    showTimeLabel(time);

    MessageItemView* itemView = new SelfMessageItemView(msgListWidget->parentWidget());
    itemView->setMessage(msg);
    QListWidgetItem* item = new QListWidgetItem(msgListWidget);
    showMessage(itemView, item);

    msgListWidget->setCurrentRow(msgListWidget->count()-1);
}

void ChatForm::showMessage(ChatItemView *itemView, QListWidgetItem *item)
{
    itemView->setFixedWidth(vertSplitter->width() - 10);
    QSize size(vertSplitter->width() - 10, itemView->height());
    item->setSizeHint(size);
    msgListWidget->setItemWidget(item, itemView);
    itemView->updateLayout();
}

void ChatForm::showTimeLabel(QString curMsgTime)
{
    bool isShowTime = false;
    if(msgListWidget->count() > 0) {
        QListWidgetItem* lastItem = msgListWidget->item(msgListWidget->count() - 1);
        ChatItemView* itemView = (ChatItemView*)msgListWidget->itemWidget(lastItem);
        int lastTime = itemView->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        TimeItemView* timeView = new TimeItemView(msgListWidget->parentWidget());
        QListWidgetItem* listItem = new QListWidgetItem(msgListWidget);

        QSize size = QSize(vertSplitter->width() - 10, 40);
        timeView->resize(size);
        listItem->setSizeHint(size);
        timeView->setTime(curMsgTime);
        msgListWidget->setItemWidget(listItem, timeView);
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
    for(int i = 0; i < msgListWidget->count(); i++) {
        ChatItemView* itemView = (ChatItemView*)msgListWidget->itemWidget(msgListWidget->item(i));
        QListWidgetItem* item = msgListWidget->item(i);

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
    if (request.errorCode == 0 && request.statusCode == 200) {
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
