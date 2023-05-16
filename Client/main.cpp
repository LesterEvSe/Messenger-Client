#include "client.hpp"
#include "registration.hpp"
#include "encryption.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Encryption::get();

//    Client window;
//    if (window.startRegistration() == QDialog::Accepted) {
//        window.show();
//        return a.exec();
//    }
    return 0;
}
