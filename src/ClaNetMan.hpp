#ifndef ClaNetMan_HPP
#define ClaNetMan_HPP
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QTextStream>
#include "ClaParseReply.hpp"


class ClaNetMan : public QObject
{
            Q_OBJECT

private:
public:
    ClaNetMan(QObject* parent = nullptr);
signals:
     signalTakeToken(const QString tokenReply);
     signalgoRequestAuth(const QNetworkRequest request, const QByteArray content);
public slots:
     void makeRequestAuth (const QString username, const QString password);
};

#endif
