#include <ClaControl.hpp>

ClaControl::ClaControl(QObject* parent) : QObject(parent)
{
       requester = new ClaRequest(this);
       replyer = new ClaParseReply(this);
       manager = new QNetworkAccessManager(this);
       connect(this, SIGNAL(signalAuth(const QString,const QString)),requester,SLOT(makeRequestAuth(const QString, const QString)));
       connect(requester,SIGNAL(signalgoRequestAuth(const QNetworkRequest,const QByteArray)),this,SLOT(goRequestAuth(const QNetworkRequest,const QByteArray)));
       connect(manager,SIGNAL(finished(QNetworkReply*)),replyer,SLOT(replyAuthParse(QNetworkReply*)));
       connect(replyer,SIGNAL(signalTakeToken(const QString)),this,SLOT(takeToken(const QString)));
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
    qDebug() << token;
}

//Send the request auth
void ClaControl::goRequestAuth(const QNetworkRequest request, const QByteArray content)
{
            manager->post(request, content);
}
