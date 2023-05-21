#include "clientback.hpp"

#include <QDataStream>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

ClientBack::ClientBack(QObject *parent) :
    QTcpSocket(parent),
    m_socket(new QTcpSocket(this)),
    m_block_size(0),

    m_encryption(Encryption::get_instance()),
    gui(new Client(this)),
    m_registration(new Registration(this))
{
    connect(m_socket, &QTcpSocket::readyRead,    this,     &ClientBack::slotReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, m_socket, &QTcpSocket::deleteLater);
}

int ClientBack::startRegistration() { return m_registration->exec(); }

void ClientBack::sendToServer(const QJsonObject& message) const
{
    QByteArray data;
    if (message["type"] == "request a key") {
        QJsonObject answer;
        answer["type"] = "key";
        answer["key"]  = QString::fromUtf8(m_encryption->get_n());
        data = QJsonDocument(answer).toJson(QJsonDocument::Compact);
    }
    else if (message["type"] == "key") {
        QByteArray cipher_key = message["key"].toString().toUtf8();
        data = QJsonDocument(*m_message).toJson(QJsonDocument::Compact);

        data = m_encryption->encode(data, cipher_key);
        m_message = nullptr;
    }

    // Executed when m_message is empty
    else {
        m_message = std::make_unique<QJsonObject>(message);
        QJsonObject request;
        request["type"] = "request a key";
        data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    }
    // There is no fourth. Because if the message is NOT empty,
    // then we have an encryption key (second block)

    QDataStream out(m_socket);

    // To avoid errors, as it is constantly updated
    out.setVersion(QDataStream::Qt_5_15);

    // Write the size of transferred data in the SAME TYPE AS m_block_size,
    // otherwise data will not be transferred correct!!!
    out << decltype(m_block_size)(data.size());

    // Writing data as "raw bytes" with size 'data.size()'
    out.writeRawData(data.constData(), data.size());

    // Forcing all data to be sent at once
    // to avoid multithreading problems when data accumulate in the buffer
    m_socket->flush();
}

void ClientBack::slotReadyRead()
{
    // First of all we read the size of the message to be transmitted
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_5_15);

    if (m_block_size == 0) {
        if (m_socket->bytesAvailable() < static_cast<qint64>(sizeof(m_block_size)))
            return;
        in >> m_block_size;
    }

    // if the data came in less than agreed
    if (m_socket->bytesAvailable() < m_block_size)
        return;

    // when we got the size, then we get our data
    QByteArray data = m_socket->read(m_block_size);

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    // If we caught the first error, then our data came in encrypted form
    // Otherwise we get the key
    if (error.error != QJsonParseError::NoError) {
        data = m_encryption->decode(data);
        doc = QJsonDocument::fromJson(data, &error);

        // If after decryption we get an error
        if (error.error != QJsonParseError::NoError)
            gui->showErrorAndExit("Data reading error or key error");
    }
    QJsonObject jsonData = doc.object();

    // Reset the variable to zero
    // so that we can read the following message
    m_block_size = 0;
    determineMessage(jsonData);
}

void ClientBack::determineMessage(const QJsonObject &message)
{
    if (message["type"] == "message")
        gui->processMessage(message);

    // This is where we supposedly send the key back.
    // However, in this function we encrypt m_message
    // and send fully encrypted bytes
    else if (message["type"] == "key" ||
             message["type"] == "request a key")
        sendToServer(message);

    else if (message["type"] == "download correspondence")
        gui->updateSelectedChat(message);

    else if (message["type"] == "update online users") {
        QJsonArray arr = message["array of users"].toArray();
        gui->updateOnlineUsersUi(arr);
    }
    else if (message["type"] == "download chats") {
        QJsonArray arr = message["array of users"].toArray();
        gui->downloadChats(arr);
    }

    // Here jsonData["type"] is 'registration' or 'login'
    else if (message["isCorrect"].toBool()) {
        // First request
        // Also, we request a one-time update of all our available chats
        QJsonObject json;
        json["type"] = "download chats";
        json["username"] = m_username;
        sendToServer(json);

        // Second request (update online users)
        /// WARNING!!!
        /// Do not send two requests at once, with successful registration,
        /// otherwise KABOOM happens!

        // In future. Use two pointers to appropriate class
        // to do this
        gui->setWindowTitle(m_username);
        m_registration->accept();
    }
    else
        gui->showWarning(message["feedback"].toString());
}
