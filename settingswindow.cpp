#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "sesion.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_pushButton_clicked()
{
    Sesion *menu;
    menu = new Sesion;
    menu->show();
    this->close();
}
