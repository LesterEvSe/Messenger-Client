#ifndef CLIENTBACK_HPP
#define CLIENTBACK_HPP

#include "client.hpp"
#include "registration.hpp"
#include "encryption.hpp"

#include <QTcpSocket>
#include <QJsonObject>

class Client;
class Registration;
class ClientBack : public QTcpSocket
{
    Q_OBJECT
    friend class Client;
    friend class Registration;

private:
    QTcpSocket *m_socket;
    qint64 m_block_size;
    QString m_username;

    Encryption *m_encryption;

    // mutable - this object can be changed in const functions
    mutable std::unique_ptr<QJsonObject> m_message;

    // Must be called after slotReadyRead
    void determineMessage    (const QJsonObject& message);
    void sendToServer        (const QJsonObject& message) const;

public slots:
    void slotReadyRead();

public:
    Client *gui;
    Registration *m_registration;

    int startRegistration();
    explicit ClientBack(QObject *parent = nullptr);
};

#endif // CLIENTBACK_HPP
