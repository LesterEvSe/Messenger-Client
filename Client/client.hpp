#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "registration.hpp"

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>

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

    void updateOnlineUsersUi(const QJsonArray& array);
    void sendToServer(const QJsonObject& message);

private slots:
    void on_sendMessageButton_clicked();
    void on_sendMessageLineEdit_returnPressed();

    void on_updateOnlineUsersButton_clicked();

public slots:
    void slotReadyRead();

public:
    explicit Client(QWidget *parent = nullptr);
    int startRegistration();
    ~Client();
};

#endif // CLIENT_HPP
