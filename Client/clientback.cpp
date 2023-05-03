#include "clientback.hpp"

#include <QDebug>
#include <QHostAddress>
#include <QByteArray>

ClientBack::ClientBack(QObject *parent) :
    QObject(parent), socket(nullptr)
{
    connectToServer();
}

void ClientBack::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << "Message received from server: " << data;
}

void ClientBack::connectToServer()
{
    constexpr static int waiting = 3'000;
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress::LocalHost, 1234);

    if (!socket->waitForConnected(waiting)) {
        qDebug() << "Could not connect to server";
        return;
    }
    qDebug() << "Connected to server";
}
