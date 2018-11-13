#include "ClaRequest.hpp"


ClaRequest::ClaRequest(QObject* parent) : QObject(parent)
{
    request = new QNetworkRequest;
}

//Creating a request for auth
void ClaRequest::makeRequestAuth(const QString username, const QString password)
{
            request->setUrl(QUrl("http://courier-api.esphere.ru/api/auth/logon"));
            request->setRawHeader("Content-Type", "application/json");
            QJsonObject data;
            data["Username"] = QString(username);
            data["Password"] = QString(password);
            QByteArray jsonPost = QJsonDocument(data).toJson();
            emit signalGoPostRequest (*request, jsonPost);
}

//Request for Document
void ClaRequest::makeRequestDoc(const QString *id, const QString token, const QString type)
{

    QNetworkRequest request;
    request.setUrl(QUrl("http://courier-api.esphere.ru/api/document/" + type.toUtf8() + "/" + (*id).toUtf8()));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Auth-Token", token.toUtf8());
    emit signalGoGetRequest (request);

}
