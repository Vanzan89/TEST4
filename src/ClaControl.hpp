#ifndef ClaControl_HPP
#define ClaControl_HPP
#include <QObject>
#include <QString>
#include "ClaNetMan.hpp"

class ClaControl : public QObject
{
    Q_OBJECT

private:
    QString token;
    ClaNetMan* requester;
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
