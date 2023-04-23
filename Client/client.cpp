#include "client.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>

Client::Client(QObject *parent) :
    QObject(parent), socket(nullptr)
{
    connectToServer();
}

void Client::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << "Message received from server: " << data.constData();
}

void Client::connectToServer()
{
    constexpr static int waiting = 3'000;
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress::LocalHost, 12345);

    if (!socket->waitForConnected(waiting)) {
        qDebug() << "Could not connect to server";
        return;
    }
    qDebug() << "Connected to server";

    while (true) {
        QTextStream in(stdin);
        QString message = in.readLine();
        QByteArray data = message.toUtf8();
        socket->write(data);

        if (!socket->waitForBytesWritten(waiting)) {
            qDebug() << "Could not send message to server";
            break;
        }

        if (!socket->waitForReadyRead(waiting)) {
            qDebug() << "Could not receive message from server";
            break;
        }
        readyRead();
    }
}
