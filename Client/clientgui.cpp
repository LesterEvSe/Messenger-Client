#include "clientgui.hpp"
#include "ui_clientgui.h"

#include <QScreen>

ClientGui::ClientGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientGui)
{
    ui->setupUi(this);
    setWindowTitle("Messenger");
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    int w = screenGeometry.width();
    int h = screenGeometry.height();
    move((w - width())/2, (h - height())/2);
}

ClientGui::~ClientGui()
{
    delete ui;
}
