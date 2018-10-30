#include <ClaParseReply.hpp>

ClaParseReply::ClaParseReply()
{
    connect(this, SIGNAL(signalTakeToken(const QString)),&controller,SLOT(takeToken(const QString)));
}

void ClaParseReply::replyAuthParse(QNetworkReply *reply)
{

    QJsonDocument jsonResp = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonResp.object();
    tokenReply = jsonObj["token"].toString();
    qDebug() << tokenReply;
 //   emit signalTakeToken (tokenReply);
}
