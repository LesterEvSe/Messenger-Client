#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include <QDialog>
#include <QTcpSocket>
#include <QAbstractSocket>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT
private:
    Ui::Registration *ui;
    QTcpSocket *socket;

    void successfulConnection();

private slots:
    void on_showPasswordCheckBox_toggled(bool checked);
    void on_signUpButton_clicked();
    void on_signInButton_clicked();

    void connectedToServer();
    void connectionError(QAbstractSocket::SocketError);

public:
    explicit Registration(QTcpSocket *shared_socket, QWidget *parent = nullptr);
    ~Registration();
};

#endif // REGISTRATION_HPP
