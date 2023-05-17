#include "client.hpp"
#include "registration.hpp"
#include "encryption.hpp"

#include <QApplication>
#include <QJsonDocument>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Encryption *obj = Encryption::get();

    QJsonObject json;
    json["type"] = "login";
    json["message"] = "Once upon a time";

    QByteArray bytes = QJsonDocument(json).toJson(QJsonDocument::Compact);
    qDebug() << bytes << "\n";
    qDebug() << bytes.size();
    QByteArray encode = obj->encode_decode(bytes, true);
    qDebug() << encode << "\n";

    QByteArray decode = obj->encode_decode(encode, false);
    qDebug() << decode;

//    Client window;
//    if (window.startRegistration() == QDialog::Accepted) {
//        window.show();
//        return a.exec();
//    }
    return 0;
}
