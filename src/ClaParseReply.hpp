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
      int StateReply;
signals:
     signalTakeToken(const QString tokenReply);
      signalNotToken (const QJsonObject jsonObj);
     signalParseDocCard (const QJsonObject jsonObj);
     signalParsePDF (const QJsonObject jsonObj);
     signalTakeDocCard(const QString numberReply, const QString senderReply, const QString documentTypeCodeReply);
     signalGoLoginAgain();
     signalTakePDFReady(const QString);
public slots:
    void replyParse(QNetworkReply *reply);
    void RouteOptions (const QJsonObject jsonObj);
    void ParseDocCard(const QJsonObject jsonObj);
    void ParsePDF(const QJsonObject jsonObj);
    void setState(int State);
};
#endif
