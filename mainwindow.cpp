#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>
#include <stdio.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_ok_clicked()
{
    QString rtspURL;
    rtspURL=ui->rtspInfo->text();
    const char * info = rtspURL.toStdString().c_str();
    printf("%s",info);
}

void MainWindow::on_btn_cancle_clicked()
{
    exit(1);
}
