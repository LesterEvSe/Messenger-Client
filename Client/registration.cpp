#include "registration.hpp"
#include "ui_registration.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QJsonObject>

#include <QDebug>

bool Registration::isConnected = false;

Registration::Registration(Client *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration),
    client(client)
{
    connect(client->m_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(client->m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(connectionError(QAbstractSocket::SocketError)));

    ui->setupUi(this);
    setWindowTitle("Registration");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

Registration::~Registration() {
    delete ui;
}

void Registration::on_showPasswordCheckBox_toggled(bool checked)
{
    if (checked)
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void Registration::on_signUpButton_clicked() {
    client->m_username = ui->usernameLineEdit->text();

    json["type"]     = "registration";
    json["username"] = ui->usernameLineEdit->text();
    json["password"] = ui->passwordLineEdit->text();

    if (isConnected)
        connectedToServer();
    else
        client->m_socket->connectToHost(QHostAddress::LocalHost, 1326);
}

void Registration::on_signInButton_clicked() {
    client->m_username = ui->usernameLineEdit->text();

    json["type"]     = "login";
    json["username"] = ui->usernameLineEdit->text();
    json["password"] = ui->passwordLineEdit->text();

    if (isConnected)
        connectedToServer();
    else
        client->m_socket->connectToHost(QHostAddress::LocalHost, 1326);
}

// The verdict will be rendered, in the Client::slotReadyRead()
void Registration::connectedToServer()
{
    isConnected = true;
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    client->sendToServer(json);
}

void Registration::connectionError(QAbstractSocket::SocketError)
{
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    QMessageBox::critical(this, "Error", "Unable to connect to the server");
}

