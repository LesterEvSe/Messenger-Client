#include "client.hpp"
#include "ui_client.h"

#include <QScreen>
#include <QHostAddress>
#include <QJsonDocument>
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client),
    socket(new QTcpSocket(this)),
    registration(new Registration(this))
{
    ui->setupUi(this);
    ui->sendMessageLineEdit->setPlaceholderText("Write a message...");

    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int w = screenGeometry.width();
    int h = screenGeometry.height();
    move((w - width())/2, (h - height())/2);
}

int Client::startRegistration() {
    return registration->exec();
}

Client::~Client() {
    delete ui;
}



void Client::sendToServer(const QJsonObject& message)
{
    QJsonDocument doc(message);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    socket->write(data);
}

void Client::slotReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    jsonData = doc.object();

    if (jsonData["message"].toString() == "message") {
        ui->textBrowser->append(jsonData["message"].toString());
        return;
    }

    if (jsonData["isCorrect"].toBool()) {
        setWindowTitle(username);
        registration->accept();
    }
    else
        QMessageBox::warning(this, "Warning", jsonData["feedback"].toString());
}


// Next two functions are the same
// Here we describe the JSON for sending messages from user
void Client::on_sendMessageButton_clicked() {

    // For json["to"] need to make a special button
    // or anything else. THINK ABOUT THIS
    QJsonObject json;
    json["type"]    = "message";
    json["from"]    = username;
    json["to"]      = "unknown"; // Our plug
    json["message"] = ui->sendMessageLineEdit->text();

    ui->textBrowser->append(ui->sendMessageLineEdit->text());
    ui->sendMessageLineEdit->clear();
    sendToServer(json);
}


void Client::on_sendMessageLineEdit_returnPressed() {
    on_sendMessageButton_clicked();
}

