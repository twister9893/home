#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertColumn(0);
    ui->tableWidget->insertRow(0);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("first"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
