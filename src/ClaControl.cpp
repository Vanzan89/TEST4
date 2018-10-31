#include <ClaControl.hpp>

ClaControl::ClaControl(QObject* parent) : QObject(parent)
{
       requester = new ClaNetMan(this);
       replyer = new ClaParseReply(this);
       connect(this, SIGNAL(signalAuth(const QString,const QString)),requester,SLOT(doRequestAuth(const QString, const QString)));
       connect(replyer,SIGNAL(signalTakeToken(const QString)),this,SLOT(takeToken(const QString)));
}

//��������� � ��ࠢ�塞 ᨣ��� � ᫮� �� ᮧ����� �����
ClaControl::goLogin()
{
    qInfo() << "Enter the username";
    QTextStream s1(stdin);
    QString username = s1.readLine();
    qInfo() << "Enter the password";
    QTextStream s2(stdin);
    QString password = s2.readLine();
    emit signalAuth  (username,  password);
}

//����砥� � ��࠭塞 ⮪��
ClaControl::takeToken(const QString tokenRepl)
{
    token = tokenRepl;
    qDebug() << "token";
    qDebug() << token;
}
