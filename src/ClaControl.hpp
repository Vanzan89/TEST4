#ifndef ClaControl_HPP
#define ClaControl_HPP
#include "ClaRequest.hpp"
#include "ClaParseReply.hpp"


class ClaControl : public QObject
{
    Q_OBJECT

private:
    QString token;
    QList<QByteArray> test;
    QString data;
    QString id;
    ClaRequest *requester;
    ClaParseReply *replyer;
    QNetworkAccessManager *manager;
public:
    ClaControl(QObject* parent = nullptr);
    void goLogin ();
public slots:
    void takeToken(const QString tokenRepl);
    void goRequestAuth(const QNetworkRequest request, const QByteArray content);
    void goRequestDocCard (const QNetworkRequest request);
    void enterIdDoc();
signals:
         signalAuth (const QString username, const QString password);
         signalDocCard (const QString id, const QString token);
         signalEnterID ();
};

#endif
