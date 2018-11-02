#include <ClaControl.hpp>
#include <QList>

ClaControl::ClaControl(QObject* parent) : QObject(parent)
{
       requester = new ClaRequest(this);
       replyer = new ClaParseReply(this);
       manager = new QNetworkAccessManager(this);
       connect(this, SIGNAL(signalAuth(const QString,const QString)),requester,SLOT(makeRequestAuth(const QString, const QString)));
       connect(requester,SIGNAL(signalgoRequestAuth(const QNetworkRequest,const QByteArray)),this,SLOT(goRequestAuth(const QNetworkRequest,const QByteArray)));
       connect(manager,SIGNAL(finished(QNetworkReply*)),replyer,SLOT(replyParse(QNetworkReply*)));
       connect(replyer,SIGNAL(signalTakeToken(const QString)),this,SLOT(takeToken(const QString)));
       connect(this,SIGNAL(signalEnterID()),this,SLOT(enterIdDoc()));
       connect(this,SIGNAL(signalDocCard(QString,QString)),requester,SLOT(makeRequestDocCard(const QString,const QString)));
       connect(requester,SIGNAL(signalGoGetRequest(const QNetworkRequest)),this,SLOT(goGetRequest(const QNetworkRequest)));
       connect(replyer,SIGNAL(signalTakeDocCard(const QString,const QString,const QString)),this,SLOT(takeDocCard(const QString,const QString,const QString)));
}

//Enter the login and password for auth
void ClaControl::goLogin()
{
    qInfo() << "Enter the username";
    QTextStream s1(stdin);
    QString username = s1.readLine();
    qInfo() << "Enter the password";
    QTextStream s2(stdin);
    QString password = s2.readLine();
    emit signalAuth  (username,  password);
}

//We got a token now
void ClaControl::takeToken(const QString tokenRepl)
{
    token = tokenRepl;
    emit signalEnterID();
}

//Send the request auth
void ClaControl::goRequestAuth(const QNetworkRequest request, const QByteArray content)
{
    manager->post(request, content);
}

// Go for document card
void ClaControl::goGetRequest(const QNetworkRequest request)
{
    manager->get(request);
}

//Test for document card
void ClaControl::enterIdDoc()
{
    qInfo() << "Enter ID of the document: ";
    QTextStream s3(stdin);
    QString id = s3.readLine();
    qInfo() << "What do you want do to know? \n Type And Number (1) \n Route (2)";
    QTextStream s4(stdin);
    QString choose = s4.readLine();
    int chooseint =choose.toInt();

    switch (chooseint) {
    case 1:
        State = 1;
        replyer->setState(State);
       emit signalDocCard (id,token);
        break;
    case 2:
        State = 2;
        replyer->setState(State);
        qInfo() << "Maintance. Plz come later!";
        emit signalDocCard (id,token);
        break;
    default: qInfo() << "You have entered the invalid number";
    }
}

void ClaControl::takeDocCard(const QString numberReply, const QString senderReply, const QString documentTypeCodeReply)
{
    qDebug() << "Number of the document: " << numberReply;
    qDebug() << "Type of the document: " << documentTypeCodeReply;
    qDebug() << "sender ID: " << senderReply;

}



