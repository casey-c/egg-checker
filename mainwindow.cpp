#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "proof.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // DEBUG:
    Proof p("debug/test3.egg");
    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
