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
QNetworkAccessManager *manager;
ClaParseReply* replyer;
public:
    ClaNetMan(QObject* parent = nullptr);
signals:

public slots:
     void doRequestAuth (const QString username, const QString password);
};

#endif
