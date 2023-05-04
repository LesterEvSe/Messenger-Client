#include "client.hpp"
#include "ui_client.h"

#include <QScreen>
#include <QHostAddress>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client),
    socket(new QTcpSocket(this)),
    registration(new Registration(this))
{
    ui->setupUi(this);
    setWindowTitle("Messenger");

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



void Client::sendToServer(QString str)
{
    // Clean it up, because there may be trash in here
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);

    // until we can determine the size of the block, we write 0
    // HERE IS THE MESSAGE OUTPUT
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);

    // The first two bits are separators
    out << quint16(Data.size() - sizeof(quint16));
    socket->write(Data);
    ui->sendMessageLineEdit->clear();
}

void Client::slotReadyRead()
{
    QDataStream in(socket);
    quint16 nextBlockSize(0);

    // Specify the version to avoid errors
    in.setVersion(QDataStream::Qt_5_15);
    if (in.status() != QDataStream::Ok) {
        ui->textBrowser->append("read error");
        return;
    }

    // We do not know if the data will come in full or in parts,
    // so we need an endless loop

    // while(true) gives a warning,
    // so change to the for loop
    for (;;) {
        // Block size unknown (0)
        if (nextBlockSize == 0) {
            if (socket->bytesAvailable() < 2)
                break;
            in >> nextBlockSize;
        }
        // if the data is incomplete
        if (socket->bytesAvailable() < nextBlockSize)
            break;

        QString str;
        QTime time;
        in >> time >> str;

        // To be able to receive new messages
        nextBlockSize = 0;
        ui->textBrowser->append(time.toString() + " " + str);
    }
}


void Client::on_sendMessageButton_clicked() {
    sendToServer(ui->sendMessageLineEdit->text());
}


void Client::on_sendMessageLineEdit_returnPressed() {
    sendToServer(ui->sendMessageLineEdit->text());
}

void Client::on_connectButton_clicked() {
    socket->connectToHost(QHostAddress::LocalHost, 1234);
}

