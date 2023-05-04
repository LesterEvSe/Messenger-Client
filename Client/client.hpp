#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "registration.hpp"

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>
#include <QTime>

class Registration;
namespace Ui { class Client; }

class Client : public QWidget
{
    Q_OBJECT
    friend class Registration;

private:
    Ui::Client *ui;
    QTcpSocket *socket;
    QByteArray Data;

    Registration *registration;

    void sendToServer(QString str);

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
