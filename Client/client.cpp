#include "client.hpp"
#include "ui_widget.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}

