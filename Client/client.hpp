#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Client : public QWidget
{
    Q_OBJECT
private:
    Ui::Widget *ui;

public:
    Client(QWidget *parent = nullptr);
    ~Client();
};
#endif // CLIENT_H
