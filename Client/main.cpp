#include "clientgui.hpp"
#include "registration.hpp"

#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Registration registration;
    if (registration.exec() == QDialog::Accepted) {
        ClientGui w;
        w.show();
        return a.exec();
    }

    return 0;
}
