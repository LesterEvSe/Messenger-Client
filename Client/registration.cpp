#include "registration.hpp"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    setWindowTitle("Registration");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_showPasswordCheckBox_toggled(bool checked)
{
    if (checked)
        ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}


void Registration::on_buttonBox_accepted()
{
    accept();
}


void Registration::on_buttonBox_rejected()
{
    reject();
}

