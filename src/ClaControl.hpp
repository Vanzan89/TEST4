#ifndef ClaControl_HPP
#define ClaControl_HPP
#include <QObject>
#include <QString>
#include "ClaRequest.hpp"

class ClaControl : public QObject
{
    Q_OBJECT

private:
    QString token;
    ClaRequest *requester;
    ClaParseReply *replyer;
    QNetworkAccessManager *manager;
public:
    ClaControl(QObject* parent = nullptr);
    void goLogin ();
public slots:
    void takeToken(const QString tokenRepl);
    void goRequestAuth(const QNetworkRequest request, const QByteArray content);
signals:
         signalAuth (const QString username, const QString password);
};

#endif
