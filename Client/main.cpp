#include "widget.h"
#include "client.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    return a.exec();
}
