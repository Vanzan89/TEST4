#ifndef ClaControl_HPP
#define ClaControl_HPP
#include "ClaRequest.hpp"
#include "ClaParseReply.hpp"
#include <QFile>


class ClaControl : public QObject
{
    Q_OBJECT

private:
    const QString *token;
    QString tokentemp;
    QList<QByteArray> test;
    QString data;
    ClaRequest *requester;
    ClaParseReply *replyer;
    QNetworkAccessManager *manager;
    QString type;
public:
    explicit ClaControl(QObject* parent = nullptr);
    QString *id;
    QString idext;
public slots:
    void takeToken(const QString tokenRepl);
    void goPostRequest(const QNetworkRequest request, const QByteArray content);
    void goGetRequest (const QNetworkRequest request);
    void enterIdDoc();
    void takeDocCard(const QString numberReply, const QString senderReply, const QString documentTypeCodeReply);
    void Chooser ();
    void goLogin ();
    void takePDFReady(const QString info);
signals:
         signalAuth (const QString username, const QString password);
         signalDoc (const QString *id, const QString token, const QString type);
         signalEnterID();
         signalChooser();
};

#endif
