#include "ClaParseReply.hpp"
#include <QFile>

ClaParseReply::ClaParseReply(QObject* parent) : QObject(parent)
{
}

//Parsing the auth reply
void ClaParseReply::replyParse(QNetworkReply *reply)
{
    QJsonDocument jsonResp = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonResp.object();
    if (jsonObj["token"].toString() != 0)
    {
    tokenReply = jsonObj["token"].toString();
    qDebug() << "token!";
    emit signalTakeToken (tokenReply);
        }
    else {
        QString strJson(jsonResp.toJson(QJsonDocument::Compact));
        qDebug() << strJson;
        qDebug() << "Pidor";
        }
}

