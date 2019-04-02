#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sbNum->setValue(1);

    Group *group = new Group();
    group->gb = new QGroupBox();
    group->gb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    group->gb->setObjectName("gb_1");
    group->gb->setTitle(QApplication::translate("MainWindow", "Group 1", nullptr));
    addGroupBox(&gVector);
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

void MainWindow::addGroupBox(QVector<Group*> *gVector)
{
    QGridLayout *gridLayout = new QGridLayout(gVector->back()->gb);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    QCheckBox *checkBox = new QCheckBox(gVector->back()->gb);
    checkBox->setObjectName("cb_1");
    gridLayout->addWidget(checkBox, 0, 2, 1, 1);
    QPushButton *pushButton = new QPushButton(gVector->back()->gb);
    pushButton->setObjectName("btn_1");
    pushButton->setText("...");
    gridLayout->addWidget(pushButton, 0, 1, 1, 1);
    QLineEdit *lineEdit = new QLineEdit(gVector->back()->gb);
    lineEdit->setObjectName("le_1");
    gridLayout->addWidget(lineEdit, 0, 0, 1, 1);
    QSpinBox *spinBox = new QSpinBox(gVector->back()->gb);
    spinBox->setObjectName("sb_1");
    spinBox->setValue(1);
    gridLayout->addWidget(spinBox, 0, 3, 1, 1);
    QCustomPlot *plot= new QCustomPlot(gVector->back()->gb);
    plot->setObjectName("plot_1");
    gridLayout->addWidget(plot, 1, 0, 1, 4);
    ui->gridLayout->addWidget(gVector->back()->gb);
}
