#include "clientback.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientBack window;
    if (window.startRegistration() == QDialog::Accepted) {
        window.gui->show();
        return a.exec();
    }
    return 0;
}
