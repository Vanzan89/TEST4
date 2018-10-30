#ifndef ClaControl_HPP
#define ClaControl_HPP
#include <QObject>
#include <QString>
#include "ClaNetMan.hpp"

class ClaControl : public QObject
{
    Q_OBJECT

private:
  ClaNetMan requester;
protected:
  QString const token;
public:
    ClaControl();
    goLogin ();
public slots:
    takeToken(const QString replyToken);
signals:
  signalAuth (const QString username, const QString password);


};

#endif
