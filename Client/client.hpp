#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>
#include <QTime>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

private:
    Ui::Client *ui;
    QTcpSocket *socket;
    QByteArray Data;
    quint16 nextBlockSize;

    void sendToServer(QString str);

private slots:
    void on_connectButton_clicked();
    void on_sendMessageButton_clicked();
    void on_sendMessageLineEdit_returnPressed();

public slots:
    void slotReadyRead();

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
};

#endif // CLIENT_HPP
