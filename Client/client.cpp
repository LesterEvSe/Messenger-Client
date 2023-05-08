#include "client.hpp"
#include "ui_client.h"

#include <QScreen>
#include <QHostAddress>
#include <QJsonDocument>
#include <QMessageBox>
#include <QDataStream>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client),
    m_socket(new QTcpSocket(this)),
    m_block_size(0),
    m_registration(new Registration(this))
{
    ui->setupUi(this);
    ui->sendMessageLineEdit->setPlaceholderText("Write a message...");

    connect(m_socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, m_socket, &QTcpSocket::deleteLater);

    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int w = screenGeometry.width();
    int h = screenGeometry.height();
    move((w - width())/2, (h - height())/2);
}

int Client::startRegistration() {
    return m_registration->exec();
}

Client::~Client() {
    delete ui;
}



void Client::sendToServer(const QJsonObject& message)
{
    QByteArray data = QJsonDocument(message).toJson(QJsonDocument::Compact);
    QDataStream out(m_socket);
    out.setVersion(QDataStream::Qt_5_15);

    out << quint16(data.size());
    out.writeRawData(data.constData(), data.size());

    // Forcing all data to be sent at once
    // to avoid multithreading problems when data accumulate in the buffer
    m_socket->flush();
}

void Client::slotReadyRead()
{
    // First of all we read the size of the message to be transmitted
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_5_15);

    if (m_block_size == 0) {
        if (m_socket->bytesAvailable() < static_cast<qint64>(sizeof(m_block_size)))
            return;
        in >> m_block_size;
    }

    // if the data came in less than agreed
    if (m_socket->bytesAvailable() < m_block_size)
        return;

    // when we got the size, then we get our data
    QByteArray data = m_socket->read(m_block_size);
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject jsonData = doc.object();

    // Reset the variable to zero
    // so that we can read the following message
    m_block_size = 0;


    if (jsonData["message"].toString() == "message") {
        ui->textBrowser->append(jsonData["message"].toString());
        return;
    }

    if (jsonData["isCorrect"].toBool()) {
        setWindowTitle(m_username);
        m_registration->accept();
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
    json["from"]    = m_username;
    json["to"]      = "unknown"; // Our plug
    json["message"] = ui->sendMessageLineEdit->text();

    ui->textBrowser->append(ui->sendMessageLineEdit->text());
    ui->sendMessageLineEdit->clear();
    sendToServer(json);
}


void Client::on_sendMessageLineEdit_returnPressed() {
    on_sendMessageButton_clicked();
}

