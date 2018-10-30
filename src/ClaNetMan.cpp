#include "ClaNetMan.hpp"


ClaNetMan::ClaNetMan()
{

           manager = new QNetworkAccessManager(this);
           connect(manager,SIGNAL(finished(QNetworkReply*)),&replyer,SLOT(replyAuthParse(QNetworkReply*)));
}

//������ ����� �� ᫮� �� ᨣ���� �� ����஫���, ��ࠢ�塞 ����� � ᫮� ९����
void ClaNetMan::doRequestAuth(const QString username, const QString password)
{
            QNetworkRequest request;
            request.setUrl(QUrl("http://courier-api.esphere.ru/api/auth/logon"));
            request.setRawHeader("Content-Type", "application/json");
            QJsonObject data;
            data["Username"] = QString(username);
            data["Password"] = QString(password);
            QByteArray jsonPost = QJsonDocument(data).toJson();
            manager->post(request, jsonPost);
}
