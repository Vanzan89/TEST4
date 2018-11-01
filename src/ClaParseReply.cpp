#include "ClaParseReply.hpp"
#include <QFile>
#include <QJsonArray>
#include "ClaControl.hpp"

ClaParseReply::ClaParseReply(QObject* parent) : QObject(parent)
{
}

//Parsing the auth reply
void ClaParseReply::replyParse(QNetworkReply *reply)
{
   QByteArray data = reply->readAll();
    QString response = (QString)data;
    qDebug() << response;
    QJsonDocument jsonResp = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonResp.object();
    if (jsonObj["token"].toString() != 0)
    {
    tokenReply = jsonObj["token"].toString();
    qDebug() << tokenReply;
    qDebug() << "token!";
    emit signalTakeToken (tokenReply);
        }
    else {
         idReply = jsonObj["number"].toString();
         qDebug() <<"Number: " << idReply;
         idReply2 = jsonObj["senderId"].toInt();
         qDebug() << "senderId1" << idReply2;
         qDebug() << "senderId2" << QString::number(idReply2);
        }
    //Need to think how to control type of parse from control
}

