#include <ClaControl.hpp>
#include <QList>

ClaControl::ClaControl(QObject* parent) : QObject(parent)
{
       requester = new ClaRequest(this);
       replyer = new ClaParseReply(this);
       manager = new QNetworkAccessManager(this);
       const QString *token = new const QString;
       connect(this, SIGNAL(signalAuth(const QString,const QString)),requester,SLOT(makeRequestAuth(const QString, const QString)));
       connect(requester,SIGNAL(signalGoPostRequest(const QNetworkRequest,const QByteArray)),this,SLOT(goPostRequest(const QNetworkRequest,const QByteArray)));
       connect(manager,SIGNAL(finished(QNetworkReply*)),replyer,SLOT(replyParse(QNetworkReply*)));
       connect(replyer,SIGNAL(signalTakeToken(const QString)),this,SLOT(takeToken(const QString)));
       connect(this,SIGNAL(signalEnterID()),this,SLOT(enterIdDoc()));
       connect(this,SIGNAL(signalDoc(QString,QString,QString)),requester,SLOT(makeRequestDoc(const QString,const QString, const QString)));
       connect(requester,SIGNAL(signalGoGetRequest(const QNetworkRequest)),this,SLOT(goGetRequest(const QNetworkRequest)));
       connect(replyer,SIGNAL(signalTakeDocCard(const QString,const QString,const QString)),this,SLOT(takeDocCard(const QString,const QString,const QString)));
       connect(this,SIGNAL(signalChooser(const QString)),this,SLOT(Chooser(const QString)));
       connect(replyer,SIGNAL(signalGoLoginAgain()),this,SLOT(goLogin()));
       connect(replyer,SIGNAL(signalTakePDFReady(QString)),this,SLOT(takePDFReady(QString)));
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
     token =  &tokenRepl;
    emit signalEnterID();
}

//Send post request
void ClaControl::goPostRequest(const QNetworkRequest request, const QByteArray content)
{
    manager->post(request, content);
}

// Send get request
void ClaControl::goGetRequest(const QNetworkRequest request)
{
    manager->get(request);
}

//Need to rebuild for reading the config list
void ClaControl::enterIdDoc()
{
    qInfo() << "Enter ID of the document: ";
    QTextStream s3(stdin);
    QString id = s3.readLine();    
    emit signalChooser(id);
}

//Choose what to do with document
void ClaControl::Chooser (const QString id)
{
    qInfo() << "What do you want do to know? \n Type And Number (1) \n Get PDF (2)";
    QTextStream s4(stdin);
    QString choose = s4.readLine();
    int chooseint =choose.toInt();
    switch (chooseint) {
    case 1:
        replyer->setState(chooseint);
        type = "card";
        break;
    case 2:
        replyer->setState(chooseint);
        type = "pdf";
        break;
    default: {
        qInfo() << "You have entered the invalid number";
    }
    }
           emit signalDoc (id,*token,type);
}

//Some info from Document Card
void ClaControl::takeDocCard(const QString numberReply, const QString senderReply, const QString documentTypeCodeReply)
{
    qDebug() << "Number of the document: " << numberReply;
    qDebug() << "Type of the document: " << documentTypeCodeReply;
    qDebug() << "sender ID: " << senderReply;
    emit signalEnterID();
}

//We have downloaded pdf
void ClaControl::takePDFReady(const QString info)
{
    qDebug() << info;
    emit signalEnterID();
}


