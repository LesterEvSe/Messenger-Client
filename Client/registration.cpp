#include "registration.hpp"
#include "ui_registration.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>

Registration::Registration(Client *client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration),
    client(client)
{
    connect(client->socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(client->socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(connectionError(QAbstractSocket::SocketError)));

    ui->setupUi(this);
    setWindowTitle("Registration");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

Registration::~Registration()
{
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
    client->socket->connectToHost(QHostAddress::LocalHost, 1234);
}

void Registration::on_signInButton_clicked() {
    client->socket->connectToHost(QHostAddress::LocalHost, 1234);
}

void Registration::connectedToServer()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();

    accept();
}

void Registration::connectionError(QAbstractSocket::SocketError)
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    QMessageBox::critical(this, "Error", "Unable to connect to the server");
}

