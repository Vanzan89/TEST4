#ifndef ClaParseReply_HPP
#define ClaParseReply_HPP
#include <QObject>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>


class ClaParseReply : public  QObject
{
    Q_OBJECT
private:
      QString tokenReply;
public:
      ClaParseReply(QObject* parent = nullptr);
signals:
     signalTakeToken(const QString tokenReply);
public slots:
    void replyParse(QNetworkReply *reply);
};
#endif
