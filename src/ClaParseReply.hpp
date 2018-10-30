#ifndef ClaParseReply_HPP
#define ClaParseReply_HPP
#include <QObject>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include "ClaControl.hpp"


class ClaParseReply : public  QObject
{
    Q_OBJECT
private:
    QString tokenReply;
    ClaControl controller;
public:
    ClaParseReply();
signals:
    signalTakeToken(const QString tokenReply);
public slots:
    void replyAuthParse(QNetworkReply *reply);
};
#endif
