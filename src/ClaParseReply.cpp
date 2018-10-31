#include <ClaParseReply.hpp>

ClaParseReply::ClaParseReply(QObject* parent) : QObject(parent)
{
}

//Parsing the auth reply
void ClaParseReply::replyAuthParse(QNetworkReply *reply)
{
    QJsonDocument jsonResp = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonResp.object();
    tokenReply = jsonObj["token"].toString();
    emit signalTakeToken (tokenReply);
}
