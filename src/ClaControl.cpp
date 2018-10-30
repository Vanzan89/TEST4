#include <ClaControl.hpp>

ClaControl::ClaControl()
{
       connect(this, SIGNAL(signalAuth(const QString,const QString)),&requester,SLOT(doRequestAuth(const QString, const QString)));
}

ClaControl::goLogin()                           //��������� � ��ࠢ�塞 ᨣ��� � ᫮� �� ᮧ����� �����
{
    qInfo() << "Enter the username";
    QTextStream s1(stdin);
    QString username = s1.readLine();
    qInfo() << "Enter the password";
    QTextStream s2(stdin);
    QString password = s2.readLine();
    emit signalAuth  (username,  password);
}

ClaControl::takeToken(const QString replyToken)
{
  //  token = replyToken;
    qDebug() <<replyToken;
}
