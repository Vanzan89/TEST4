#ifndef ClaNetMan_HPP
#define ClaNetMan_HPP
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QList>
#include <QFile>

class ClaRequest : public QObject
{
            Q_OBJECT

private:
    QNetworkRequest *request;
public:
    ClaRequest(QObject* parent = nullptr);
    QString *id;
    QString idqs;
signals:
     signalTakeToken(const QString tokenReply);
     signalGoPostRequest(const QNetworkRequest request, const QByteArray content);
     signalGoGetRequest(const QNetworkRequest request);
     signalSetId(QString *id);
public slots:
     void makeRequestAuth (const QString username, const QString password);
     void makeRequestDoc (const QString *id, const QString token, const QString type);
};

#endif
