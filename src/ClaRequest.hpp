#ifndef ClaNetMan_HPP
#define ClaNetMan_HPP
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

class ClaRequest : public QObject
{
            Q_OBJECT

private:
    QNetworkRequest *request;
public:
    ClaRequest(QObject* parent = nullptr);
signals:
     signalTakeToken(const QString tokenReply);
     signalGoPostRequest(const QNetworkRequest request, const QByteArray content);
     signalGoGetRequest(const QNetworkRequest request);
public slots:
     void makeRequestAuth (const QString username, const QString password);
     void makeRequestDoc (const QString *id, const QString token, const QString type);
};

#endif
