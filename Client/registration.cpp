#include "registration.hpp"
#include "ui_registration.h"

#include <QHostAddress>
#include <QMessageBox>

bool Registration::isConnected = false;

Registration::Registration(ClientBack *clientBack, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration),
    m_client_back(clientBack)
{
    connect(m_client_back->m_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(m_client_back->m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(connectionError(QAbstractSocket::SocketError)));

    ui->setupUi(this);
    setWindowTitle("Registration");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

Registration::~Registration() { delete ui; }

void Registration::on_showPasswordCheckBox_toggled(bool checked)
{
    if (checked)
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

void Registration::on_signUpButton_clicked() {
    m_client_back->m_username = ui->usernameLineEdit->text();

    m_json["type"]     = "registration";
    m_json["username"] = ui->usernameLineEdit->text();
    m_json["password"] = ui->passwordLineEdit->text();

    if (isConnected)
        connectedToServer();
    else
        m_client_back->m_socket->connectToHost(QHostAddress::LocalHost, 1326);
}

void Registration::on_signInButton_clicked() {
    m_client_back->m_username = ui->usernameLineEdit->text();

    m_json["type"]     = "login";
    m_json["username"] = ui->usernameLineEdit->text();
    m_json["password"] = ui->passwordLineEdit->text();

    if (isConnected)
        connectedToServer();
    else
        m_client_back->m_socket->connectToHost(QHostAddress::LocalHost, 1326);
}

// The verdict will be rendered, in the ClientBack::slotReadyRead()
void Registration::connectedToServer()
{
    isConnected = true;
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    m_client_back->sendToServer(m_json);
}

void Registration::connectionError(QAbstractSocket::SocketError)
{
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();
    QMessageBox::critical(this, "Error", "Unable to connect to the server");
    exit(1);
}
