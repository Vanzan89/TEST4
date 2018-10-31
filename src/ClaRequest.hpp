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
public:
    ClaRequest(QObject* parent = nullptr);
signals:
     signalTakeToken(const QString tokenReply);
     signalgoRequestAuth(const QNetworkRequest request, const QByteArray content);
public slots:
     void makeRequestAuth (const QString username, const QString password);
};

#endif
