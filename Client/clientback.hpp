#ifndef CLIENTBACK_HPP
#define CLIENTBACK_HPP

#include <QTcpSocket>

class ClientBack : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientBack(QObject *parent = nullptr);
};

#endif // CLIENTBACK_HPP
