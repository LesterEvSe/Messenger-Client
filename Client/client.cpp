#include "client.hpp"
#include "ui_client.h"

// To display the window in the center (QApplication::primaryScreen())
#include <QScreen>
#include <QHostAddress>
#include <QMessageBox>
#include <QDataStream>

#include <QJsonDocument>
#include <QJsonParseError>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client),
    m_socket(new QTcpSocket(this)),

    m_block_size(0),

    m_registration(new Registration(this)),
    m_encryption(Encryption::get_instance())
{
    ui->setupUi(this);
    ui->sendMessageLineEdit->setPlaceholderText("Write a message...");

    connect(m_socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, m_socket, &QTcpSocket::deleteLater);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int w = screenGeometry.width();
    int h = screenGeometry.height();
    move((w - width())/2, (h - height())/2);
}

int Client::startRegistration() { return m_registration->exec(); }
Client::~Client() { delete ui; }

// Frontend
void Client::on_updateOnlineUsersButton_clicked()
{
    QJsonObject json;
    json["type"] = "update online users";
    json["username"] = m_username;
    sendToServer(json);
}

void Client::updateOnlineUsersUi(const QJsonArray& user_array)
{
    ui->onlineUsersListWidget->clear();
    for (int i = 0; i < user_array.size(); ++i)
        ui->onlineUsersListWidget->addItem(user_array[i].toString());
}

void Client::receiveMessageUi(const QString& fromUser)
{
    QTextBrowser *browser = new QTextBrowser(this);
    m_chats[fromUser] = { browser, ui->stackedWidget->count() };

    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->addWidget(browser);

    ui->stackedWidget->addWidget(widget);

    // If we are here, we definitely need to upload the corerspondence
    QJsonObject json;
    json["type"] = "download correspondence";
    json["username"] = m_username;
    json["with"] = fromUser;
    sendToServer(json);
}

void Client::on_onlineUsersListWidget_itemClicked(QListWidgetItem *item)
{
    if (m_chats.find(item->text()) != m_chats.end()) {
        ui->stackedWidget->setCurrentIndex(m_chats[item->text()].second);
        ui->currChatLabel->setText(item->text());
        return;
    }

    // Order is important!
    ui->currChatLabel->setText(item->text());
    receiveMessageUi(ui->currChatLabel->text());
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1);
}

// When we load chats from the database, not all windows may be open,
// so we have to load those that have not been loaded
void Client::on_myChatsListWidget_itemClicked(QListWidgetItem *item) {
    on_onlineUsersListWidget_itemClicked(item);
}

// Next two functions are the same
// Here we describe the JSON for sending messages from user
void Client::on_sendMessageButton_clicked() {
    if (ui->sendMessageLineEdit->text().isEmpty())
        return;

    QJsonObject json;
    QString to      = ui->currChatLabel->text();

    json["type"]    = "message";
    json["from"]    = m_username;
    json["to"]      = to;
    json["message"] = ui->sendMessageLineEdit->text();

    // We send our own part of the message to ourselves.
    // Why strain the server?)
    m_chats[to].first->append( m_username + ": " + ui->sendMessageLineEdit->text());

    // For a more readable conclusion. Empty row
    m_chats[to].first->append("");
    ui->sendMessageLineEdit->clear();

    updateMyChats(to);
    sendToServer(json);
}

void Client::on_sendMessageLineEdit_returnPressed() {
    on_sendMessageButton_clicked();
}

void Client::updateSelectedChat(const QJsonObject& chat)
{
    QJsonArray chat_array = chat["chat array"].toArray();
    QJsonArray mess_num = chat["our messages_id"].toArray();
    QString with = chat["with"].toString();

    for (int coun = 0, our_mess_coun = 0; coun < chat_array.size(); ++coun)
    {
        QString nick;
        if (coun == mess_num[our_mess_coun].toInt()) {
            nick = m_username;
            ++our_mess_coun;
        }
        else
            nick = with;

        m_chats[with].first->append(nick + ": " + chat_array[coun].toString());
        m_chats[with].first->append("");
    }
}

void Client::updateMyChats(const QString& username) {
    for (int i = 0; i < ui->myChatsListWidget->count(); ++i) {
        QListWidgetItem *item = ui->myChatsListWidget->item(i);
        if (item->text() == username)
            return;
    }
    ui->myChatsListWidget->addItem(username);
}





// Backend
void Client::sendToServer(const QJsonObject& message) const
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

void Client::slotReadyRead()
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
        if (error.error != QJsonParseError::NoError) {
            QMessageBox::critical(this, "Error", "Data reading error or key error");
            exit(1);
        }
    }
    QJsonObject jsonData = doc.object();

    // Reset the variable to zero
    // so that we can read the following message
    m_block_size = 0;
    determineMessage(jsonData);
}

void Client::determineMessage(const QJsonObject &message)
{
    if (message["type"] == "message") {
        QString from = message["from"].toString();
        updateMyChats(from);

        if (!m_chats.contains(from)) {
            receiveMessageUi(from);
            return;
        }

        m_chats[from].first->append(
            message["from"].toString() + ": " + message["message"].toString());

        // For a more readable conclusion. Empty row
        m_chats[from].first->append("");
    }

    // This is where we supposedly send the key back.
    // However, in this function we encrypt m_message
    // and send fully encrypted bytes
    else if (message["type"] == "key" ||
             message["type"] == "request a key")
        sendToServer(message);

    else if (message["type"] == "download correspondence")
        updateSelectedChat(message);

    else if (message["type"] == "update online users") {
        QJsonArray arr = message["array of users"].toArray();
        updateOnlineUsersUi(arr);
    }
    else if (message["type"] == "download chats") {
        QJsonArray user_array = message["array of users"].toArray();
        for (int i = 0; i < user_array.size(); ++i)
            ui->myChatsListWidget->addItem(user_array.at(i).toString());

        /// Check Warning in the code block
        /// no successful registration

        // Upon successful registration/login,
        // we send a request to update users on the network
        on_updateOnlineUsersButton_clicked();
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

        setWindowTitle(m_username);
        m_registration->accept();
    }
    else
        QMessageBox::warning(this, "Warning", message["feedback"].toString());
}
