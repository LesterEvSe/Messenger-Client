#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "registration.hpp"

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>

#include <QListWidget>
#include <QHash>
#include <QTextBrowser>

// Declaring a Registration class that is defined in other file
class Registration;
namespace Ui { class Client; }

class Client : public QWidget
{
    Q_OBJECT
    friend class Registration;

private:
    Ui::Client *ui;
    QTcpSocket *m_socket;
    qint64 m_block_size;

    Registration *m_registration;
    QString m_username;

    // Who we are communicating with now will determine the currChatLabel
    // Here is the QString, the username with whom we are communicating
    // We store a pair (index to the widget in the stack)
    // and a pointer to the text browser in this index
    QHash<QString, std::pair<QTextBrowser*, int>> m_chats;

    void receiveMessageUi    (const QString& username);
    void updateOnlineUsersUi (const QJsonArray& array);
    void sendToServer        (const QJsonObject& message);
    void updateMyChats       (const QString& username);

    // Must be called after slotReadyRead
    void determineMessage    (const QJsonObject& message);

private slots:

    void on_updateOnlineUsersButton_clicked();

    void on_onlineUsersListWidget_itemClicked(QListWidgetItem *item);
    void on_myChatsListWidget_itemClicked    (QListWidgetItem *item);

    void on_sendMessageButton_clicked();
    void on_sendMessageLineEdit_returnPressed();

public slots:
    void slotReadyRead();

public:
    explicit Client(QWidget *parent = nullptr);
    int startRegistration();
    ~Client();
};

#endif // CLIENT_HPP
