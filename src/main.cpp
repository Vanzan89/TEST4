#include <QCoreApplication>
#include "ClaControl.hpp"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ClaControl authTok;
    authTok.goLogin();

    return a.exec();
}
