#include "ClaNetMan.hpp"


ClaNetMan::ClaNetMan(QObject* parent) : QObject(parent)
{
      //     replyer = new ClaParseReply(this);
       //     manager = new QNetworkAccessManager(this);
      //      connect(manager,SIGNAL(finished(QNetworkReply*)),replyer,SLOT(replyAuthParse(QNetworkReply*)));
        //   connect(replyer,SIGNAL(signalTakeTokenTemp(const QString)),this,SLOT(takeTokenTemp(const QString)));

}

//Делаем запрос на слоте по сигналу от контрола, отправляем запрос в слот реплаера
void ClaNetMan::makeRequestAuth(const QString username, const QString password)
{
            QNetworkRequest request;
            request.setUrl(QUrl("http://courier-api.esphere.ru/api/auth/logon"));
            request.setRawHeader("Content-Type", "application/json");
            QJsonObject data;
            data["Username"] = QString(username);
            data["Password"] = QString(password);
            QByteArray jsonPost = QJsonDocument(data).toJson();
            emit signalgoRequestAuth (request, jsonPost);
}
