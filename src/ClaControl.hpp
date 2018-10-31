#ifndef ClaControl_HPP
#define ClaControl_HPP
#include <QObject>
#include <QString>
#include "ClaNetMan.hpp"

class ClaControl : public QObject
{
    Q_OBJECT

private:
    ClaNetMan* requester;
    ClaParseReply* replyer;
   QString token;
public:
    ClaControl(QObject* parent = nullptr);
    goLogin ();
public slots:
    takeToken(const QString tokenRepl);
signals:
    signalAuth (const QString username, const QString password);
};

#endif
