#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include "client.hpp"

#include <QDialog>
#include <QTcpSocket>
#include <QAbstractSocket>

class Client;
namespace Ui { class Registration; }

class Registration : public QDialog
{
    Q_OBJECT
private:
    Ui::Registration *ui;
    Client *client;

    void successfulConnection();

private slots:
    void on_showPasswordCheckBox_toggled(bool checked);
    void on_signUpButton_clicked();
    void on_signInButton_clicked();

    void connectedToServer();
    void connectionError(QAbstractSocket::SocketError);

public:
    explicit Registration(Client *client, QWidget *parent = nullptr);
    ~Registration();
};

#endif // REGISTRATION_HPP
