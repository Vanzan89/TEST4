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
     signalTakeDocCard(const QString numberReply, const QString senderReply, const QString documentTypeCodeReply);
public slots:
    void replyParse(QNetworkReply *reply);
};
#endif
