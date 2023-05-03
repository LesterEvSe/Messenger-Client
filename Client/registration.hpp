#ifndef REGISTRATION_HPP
#define REGISTRATION_HPP

#include <QDialog>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT
private:
    Ui::Registration *ui;

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();
private slots:
    void on_showPasswordCheckBox_toggled(bool checked);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // REGISTRATION_HPP
