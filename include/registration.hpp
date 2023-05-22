#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include "clientback.hpp"

#include <QDialog>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QJsonObject>

// Declaring a Client class that is defined in other file
class ClientBack;
namespace Ui { class Registration; }

class Registration : public QDialog
{
    Q_OBJECT
private:
    Ui::Registration *ui;
    ClientBack *m_client_back;

    QJsonObject m_json;
    static bool isConnected;

    void successfulConnection();
    void setStyles();

private slots:
    void on_showPasswordCheckBox_toggled(bool checked);
    void on_signUpButton_clicked();
    void on_signInButton_clicked();

    void connectedToServer();
    void connectionError(QAbstractSocket::SocketError);

public:
    explicit Registration(ClientBack *clientBack, QWidget *parent = nullptr);
    virtual ~Registration();
};

#endif // REGISTRATION_HPP
