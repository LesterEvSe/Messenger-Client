#ifndef CLIENTGUI_HPP
#define CLIENTGUI_HPP

#include <QWidget>

namespace Ui {
class ClientGui;
}

class ClientGui : public QWidget
{
    Q_OBJECT
private:
    Ui::ClientGui *ui;

public:
    explicit ClientGui(QWidget *parent = nullptr);
    ~ClientGui();
};

#endif // CLIENTGUI_HPP
