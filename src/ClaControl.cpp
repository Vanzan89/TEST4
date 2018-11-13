#include <ClaControl.hpp>

ClaControl::ClaControl(QObject* parent) : QObject(parent)
{
       requester = new ClaRequest(this);
       replyer = new ClaParseReply(this);
       manager = new QNetworkAccessManager(this);
       token = new const QString;
       id = new QString;
       list = new QList<QString>;
       connect(this, SIGNAL(signalAuth(const QString,const QString)),requester,SLOT(makeRequestAuth(const QString, const QString)));
       connect(requester,SIGNAL(signalGoPostRequest(const QNetworkRequest,const QByteArray)),this,SLOT(goPostRequest(const QNetworkRequest,const QByteArray)));
       connect(manager,SIGNAL(finished(QNetworkReply*)),replyer,SLOT(replyParse(QNetworkReply*)));
       connect(replyer,SIGNAL(signalTakeToken(const QString)),this,SLOT(takeToken(const QString)));
       connect(this,SIGNAL(signalEnterID()),this,SLOT(enterIdDoc()));
       connect(this,SIGNAL(signalDoc(const QList<QString> *,const QString,const QString)),requester,SLOT(makeRequestDoc(const QList<QString> *,const QString, const QString)));
       connect(requester,SIGNAL(signalGoGetRequest(const QNetworkRequest)),this,SLOT(goGetRequest(const QNetworkRequest)));
       connect(replyer,SIGNAL(signalTakeDocCard(const QString,const QString,const QString)),this,SLOT(takeDocCard(const QString,const QString,const QString)));
       connect(this,SIGNAL(signalChooser()),this,SLOT(Chooser()));
       connect(replyer,SIGNAL(signalGoLoginAgain()),this,SLOT(goLogin()));
       connect(replyer,SIGNAL(signalTakePDFReady(QString)),this,SLOT(takePDFReady(QString)));
       connect(requester,SIGNAL(signalSetId(QString *)),replyer,SLOT(setId(QString *)));
}

//Enter the login and password for auth
void ClaControl::goLogin()
{
   /* qInfo() << "Enter the username";
    QTextStream s1(stdin);
    QString username = s1.readLine();
    qInfo() << "Enter the password";
    QTextStream s2(stdin);
    QString password = s2.readLine();
    */
    QString username = "Vpetrov3";
    QString password = "Password3";

    emit signalAuth  (username,  password);
}

//We got a token now
void ClaControl::takeToken(const QString tokenReply)
{
     tokentemp = tokenReply;
     token =  &tokentemp;
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

    QString filename = "/config.txt";
    QFile idFile(filename);
    if (idFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&idFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
            *list << line;
       }
       idFile.close();
    }
    emit signalChooser();
}

//Choose what to do with document
void ClaControl::Chooser ()
{
    qDebug() << *list;
    qInfo() << "What do you want do to know? \n Type And Number (1) \n Get PDF (2)";
    QTextStream s4(stdin);
    int choose = s4.readLine().toInt();
    switch (choose) {
    case 1:
        replyer->setState(choose);
        type = "card";
        break;
    case 2:
        replyer->setState(choose);
        replyer->setId(id);
        type = "pdf";
        break;
    default: {
        qInfo() << "You have entered the invalid number";
    }
    }
           emit signalDoc (list,*token,type);
   }


//Some info from Document Card
void ClaControl::takeDocCard(const QString numberReply, const QString senderReply, const QString documentTypeCodeReply)
{
    qDebug() << "Number of the document: " << numberReply;
    qDebug() << "Type of the document: " << documentTypeCodeReply;
    qDebug() << "sender ID: " << senderReply;
    delete id;
    emit signalEnterID();
}

//We have downloaded pdf
void ClaControl::takePDFReady(const QString info)
{
    qDebug() << info;
    emit signalChooser();
}

