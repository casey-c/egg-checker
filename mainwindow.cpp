#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "checker.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Checker c1("1A");
    Checker c2("21A1B");
    Checker c3("121A1B");
    Checker c4("21B21BA");

    qDebug() << "c1 is " << c1.isWellFormed();
    qDebug() << "c2 is " << c2.isWellFormed();
    qDebug() << "c3 is " << c3.isWellFormed();
    qDebug() << "c4 is " << c4.isWellFormed();

    c1.printDepths();
    c2.printDepths();
    c3.printDepths();
    c4.printDepths();
    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
