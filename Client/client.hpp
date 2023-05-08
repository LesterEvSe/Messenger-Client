#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "registration.hpp"

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonObject>

// Declaring a Registration class that is defined in other file
class Registration;
namespace Ui { class Client; }

class Client : public QWidget
{
    Q_OBJECT
    friend class Registration;

private:
    Ui::Client *ui;
    QTcpSocket *socket;
    QJsonObject jsonData;

    Registration *registration;
    QString username;

    void sendToServer(const QJsonObject& message);

private slots:
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
