#include "client.hpp"
#include "registration.hpp"

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QTcpSocket *shared_socket = new QTcpSocket();
    QApplication a(argc, argv);

    Registration registration(shared_socket);
    if (registration.exec() == QDialog::Accepted) {
        Client w(shared_socket);
        w.show();
        return a.exec();
    }

    delete shared_socket;
    return 0;
}
