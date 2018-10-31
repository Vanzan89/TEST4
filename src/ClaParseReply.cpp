#include <ClaParseReply.hpp>

ClaParseReply::ClaParseReply(QObject* parent) : QObject(parent)
{

}

//���ᨬ �⢥� � ��ࠢ�塞 � ����஫
void ClaParseReply::replyAuthParse(QNetworkReply *reply)
{
    QJsonDocument jsonResp = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonResp.object();
    tokenReply = jsonObj["token"].toString();
    emit signalTakeToken (tokenReply);
}
