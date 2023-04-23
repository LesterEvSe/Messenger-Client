#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;

private slots:
    void readyRead();

public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer();
};

#endif // CLIENT_HPP
