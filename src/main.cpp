#include <QCoreApplication>
#include "ClaControl.hpp"
int main(int argc, char *argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    QCoreApplication a(argc, argv);
    ClaControl authTok;
    authTok.goLogin();

    return a.exec();
}
