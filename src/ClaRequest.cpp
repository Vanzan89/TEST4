#include "ClaRequest.hpp"


ClaRequest::ClaRequest(QObject* parent) : QObject(parent)
{
}

//Creating a request for auth
void ClaRequest::makeRequestAuth(const QString username, const QString password)
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
