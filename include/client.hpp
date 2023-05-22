#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "clientback.hpp"

#include <QWidget>
#include <QTextBrowser>

#include <QJsonObject>
#include <QJsonArray>

#include <QListWidget>
#include <QHash>

// Declaring a Registration class that is defined in other file
class ClientBack;
namespace Ui { class Client; }

class Client : public QWidget
{
    Q_OBJECT
    friend class ClientBack;

private:
    Ui::Client *ui;
    ClientBack *m_client_back;

    // Who we are communicating with now will determine the currChatLabel
    // Here is the QString, the username with whom we are communicating
    // We store a pair (index to the widget in the stack)
    // and a pointer to the text browser in this index
    QHash<QString, std::pair<QTextBrowser*, int>> m_chats;

    void showWarning         (const QString& warning);
    void showErrorAndExit    (const QString& error);

    void updateOnlineUsersUi (const QJsonArray& array);
    void processMessage      (const QJsonObject& message);
    void receiveMessageUi    (const QString& fromUser);

    void downloadChats       (const QJsonArray& userArray);
    void updateMyChats       (const QString& username);
    void updateSelectedChat  (const QJsonObject& chat);

    void setStyles();

private slots:
    void on_updateOnlineUsersButton_clicked();

    void on_onlineUsersListWidget_itemClicked (QListWidgetItem *item);
    void on_myChatsListWidget_itemClicked     (QListWidgetItem *item);

    void on_sendMessageButton_clicked();
    void on_sendMessageLineEdit_returnPressed();

public:
    explicit Client(ClientBack *clientBack, QWidget *parent = nullptr);
    ~Client();
};

#endif // CLIENT_HPP
