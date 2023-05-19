#include "client.hpp"
#include "ui_clientgui.h"

// To display the window in the center (QApplication::primaryScreen())
#include <QScreen>
#include <QHostAddress>
#include <QMessageBox>
#include <QDataStream>

#include <QJsonDocument>
#include <QJsonParseError>


Client::Client(ClientBack *clientBack, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client),
    m_client_back(clientBack)
{
    ui->setupUi(this);
    ui->sendMessageLineEdit->setPlaceholderText("Write a message...");

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int w = screenGeometry.width();
    int h = screenGeometry.height();
    move((w - width())/2, (h - height())/2);
}

Client::~Client() { delete ui; }

void Client::showWarning(const QString &warning) {
    QMessageBox::warning(this, "Warning", warning);
}

void Client::showErrorAndExit(const QString &error) {
    QMessageBox::critical(this, "Error", error);
    exit(1);
}

// Frontend
void Client::on_updateOnlineUsersButton_clicked()
{
    QJsonObject json;
    json["type"] = "update online users";
    json["username"] = m_client_back->m_username;
    m_client_back->sendToServer(json);
}

void Client::updateOnlineUsersUi(const QJsonArray& user_array)
{
    ui->onlineUsersListWidget->clear();
    for (int i = 0; i < user_array.size(); ++i)
        ui->onlineUsersListWidget->addItem(user_array[i].toString());
}

void Client::processMessage(const QJsonObject& message)
{
    QString from = message["from"].toString();
    updateMyChats(from);

    if (!m_chats.contains(from)) {
        receiveMessageUi(from);
        return;
    }

    m_chats[from].first->append(from + ": " + message["message"].toString());

    // For a more readable conclusion. Empty row
    m_chats[from].first->append("");
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
    json["username"] = m_client_back->m_username;
    json["with"] = fromUser;
    m_client_back->sendToServer(json);
}

void Client::downloadChats(const QJsonArray &userArray)
{
    for (int i = 0; i < userArray.size(); ++i)
        ui->myChatsListWidget->addItem(userArray[i].toString());

    // Upon successful registration/login,
    // we send a request to update users on the network
    on_updateOnlineUsersButton_clicked();
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
void Client::on_sendMessageButton_clicked()
{
    if (ui->sendMessageLineEdit->text().isEmpty())
        return;

    QJsonObject json;
    QString to      = ui->currChatLabel->text();

    json["type"]    = "message";
    json["from"]    = m_client_back->m_username;
    json["to"]      = to;
    json["message"] = ui->sendMessageLineEdit->text();

    // We send our own part of the message to ourselves.
    // Why strain the server?)
    m_chats[to].first->append(m_client_back->m_username + ": " + ui->sendMessageLineEdit->text());

    // For a more readable conclusion. Empty row
    m_chats[to].first->append("");
    ui->sendMessageLineEdit->clear();

    updateMyChats(to);
    m_client_back->sendToServer(json);
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
        if (!mess_num.empty() && coun == mess_num[our_mess_coun].toInt()) {
            nick = m_client_back->m_username;
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
