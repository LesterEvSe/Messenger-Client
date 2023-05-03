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

private slots:
    void on_showPasswordCheckBox_toggled(bool checked);

    void on_signUpButton_clicked();

    void on_signInButton_clicked();

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();
};

#endif // REGISTRATION_HPP
