#include "ClaParseReply.hpp"
#include <QFile>
#include <QJsonArray>
#include "ClaControl.hpp"

ClaParseReply::ClaParseReply(QObject* parent) : QObject(parent)
{
        connect(this,SIGNAL(signalNotToken(const QJsonObject)),this,SLOT(RouteOptions(const QJsonObject)));
        connect(this,SIGNAL(signalParseDocCard(const QJsonObject)),this,SLOT(ParseDocCard(const QJsonObject)));
        connect(this,SIGNAL(signalSomethingElse(const QJsonObject)),this,SLOT(SomethingElse(const QJsonObject)));
}

//Parsing the auth reply
void ClaParseReply::replyParse(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QString response = (QString)data;
    QJsonDocument jsonResp = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonResp.object();
    if (jsonObj["token"].toString() != 0)
    {
    tokenReply = jsonObj["token"].toString();
    qDebug() << "You are authorized!";
    emit signalTakeToken (tokenReply);
        }
    else {
       emit signalNotToken (jsonObj);
      }
}

void ClaParseReply::setState(int State)
{
    StateReply = State;
}

void ClaParseReply::RouteOptions(const QJsonObject jsonObj)
        {
    switch (StateReply) {
    case 1:
       emit signalParseDocCard (jsonObj);
        break;
    case 2:
       emit signalSomethingElse (jsonObj);
        break;
    default: qDebug() << "You have entered something wrong, debil!";
    }
        }

void ClaParseReply::ParseDocCard(const QJsonObject jsonObj)
{
         QString numberReply = jsonObj["number"].toString();
         int senderReplyInt = jsonObj["senderId"].toInt();
         QString senderReply = QString::number(senderReplyInt);
         QString documentTypeCodeReply = jsonObj["documentTypeCode"].toString();
         emit signalTakeDocCard(numberReply, senderReply, documentTypeCodeReply);
}

void ClaParseReply::SomethingElse(const QJsonObject jsonObj)
{
    qInfo() << "Smth Else!!";
}




