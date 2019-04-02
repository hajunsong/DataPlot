#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sbNum->setValue(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnSearchClicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("텍스트 파일"),"","txt (*.txt)"); //선택한 파일 경로 반환

    qDebug() << fileName;
}

void MainWindow::on_sbNum_valueChanged(int arg1)
{

}
