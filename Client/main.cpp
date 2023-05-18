#include "client.hpp"
#include "registration.hpp"
#include "encryption.hpp"

#include <QJsonDocument>
#include <QJsonObject>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Encryption *obj = Encryption::get_instance();

//    QJsonObject json;
//    json["key"] = "message";
//    json["message"] = "smth text";

//    QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact);
//    qDebug() << data;

//    QByteArray cipher_key = obj->get_n();
//    QJsonObject another;
//    another["key"] = QString::fromUtf8(obj->get_n());
//    qDebug() << "json key\n" << another;

//    QByteArray key = another["key"].toString().toUtf8();
//    qDebug() << "key\n" << key;
//    data = obj->encode(data, key);
//    qDebug() << data;

//    data = obj->decode(data);
//    qDebug() << data;

    Client window;
    if (window.startRegistration() == QDialog::Accepted) {
        window.show();
        return a.exec();
    }
    return 0;
}
