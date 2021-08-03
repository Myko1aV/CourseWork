#include "mainwindow4.h"
#include "ui_mainwindow4.h"

MainWindow4::MainWindow4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow4)
{
    ui->setupUi(this);
}

MainWindow4::~MainWindow4()
{
    delete ui;
}

void MainWindow4::on_pushButton_pressed()
{
    window = new MainWindow(this);
    window->show();
    MainWindow4::setHidden(true);
}
