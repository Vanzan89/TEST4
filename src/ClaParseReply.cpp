#include "ClaParseReply.hpp"
#include <QFile>
#include <QJsonArray>

ClaParseReply::ClaParseReply(QObject* parent) : QObject(parent)
{
        id = new QString;
        connect(this,SIGNAL(signalNotToken(const QJsonObject)),this,SLOT(RouteOptions(const QJsonObject)));
        connect(this,SIGNAL(signalParseDocCard(const QJsonObject)),this,SLOT(ParseDocCard(const QJsonObject)));
        connect(this,SIGNAL(signalParsePDF(const QJsonObject)),this,SLOT(ParsePDF(const QJsonObject)));
}

//Parsing the auth reply
void ClaParseReply::replyParse(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    //QString response = (QString)data;
    QJsonDocument jsonResp = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonResp.object();
    if (jsonObj["token"].toString() != 0)
    {
    tokenReply = jsonObj["token"].toString();
    qDebug() << "You are authorized!";
    emit signalTakeToken (tokenReply);
        }
    else {
     emit signalNotToken (jsonObj);
      }
}

void ClaParseReply::setState(int StateFromControl)
{
    StateReply = StateFromControl;
}

void ClaParseReply::setId(QString *idext)
{
    id = idext;
}

void ClaParseReply::RouteOptions(const QJsonObject jsonObj)
        {
    switch (StateReply) {
    case 1:
       emit signalParseDocCard (jsonObj);
        break;
    case 2:
       emit signalParsePDF (jsonObj);
        break;
    default: qDebug() << "You have entered something wrong, debil!";
                  qInfo() << "Try one more time";
            emit signalGoLoginAgain();
    }
        }

//Parse elements of Document Card
void ClaParseReply::ParseDocCard(const QJsonObject jsonObj)
{
            QString numberReply = jsonObj["number"].toString();
            int senderReplyInt = jsonObj["senderId"].toInt();
            QString senderReply = QString::number(senderReplyInt);
            QString documentTypeCodeReply = jsonObj["documentTypeCode"].toString();
            emit signalTakeDocCard(numberReply, senderReply, documentTypeCodeReply);
}

//Download PDF
void ClaParseReply::ParsePDF(const QJsonObject jsonObj)
{
            QString pdfBase64 = jsonObj["content"].toString();
            qDebug() << *id;
            QByteArray b64 = QByteArray::fromBase64(pdfBase64.toUtf8());
            QString filename = "/document" + *id + ".pdf";
            QFile f(filename);
            f.open(QIODevice::WriteOnly);
            f.write(b64);
            f.close();
            QString info = "PDF is downloaded to " + filename;
            emit signalTakePDFReady(info);
}




