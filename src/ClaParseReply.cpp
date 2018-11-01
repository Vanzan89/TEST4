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
    QJsonDocument jsonResp = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonResp.object();
    if (jsonObj["token"].toString() != 0)
    {
    tokenReply = jsonObj["token"].toString();
    qDebug() << "You are authorized!";
    emit signalTakeToken (tokenReply);
        }
    else {
                                                                                                        // Здесь прописать выборку в зависимости от состояний control
         QString numberReply = jsonObj["number"].toString();
         int senderReplyInt = jsonObj["senderId"].toInt();
         QString senderReply = QString::number(senderReplyInt);
         QString documentTypeCodeReply = jsonObj["documentTypeCode"].toString();
         emit signalTakeDocCard(numberReply, senderReply, documentTypeCodeReply);
        }
}

