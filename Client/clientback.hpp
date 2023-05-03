#ifndef CLIENTBACK_HPP
#define CLIENTBACK_HPP

#include <QObject>
#include <QTcpSocket>

class ClientBack : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;

    void readyRead();

public:
    explicit ClientBack(QObject *parent = nullptr);
    void connectToServer();
};

#endif // CLIENTBACK_HPP
