#include "widget.h"
#include "client.hpp"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client client;
    return a.exec();
}
