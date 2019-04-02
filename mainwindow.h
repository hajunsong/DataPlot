#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QtDebug>
#include <QGroupBox>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#include "qcustomplot.h"

class Group{
public:
    QGroupBox *gb;
    QPushButton *btn;
    QLineEdit *txt;
    QCheckBox *check;
    QSpinBox *spin;
    QCustomPlot *plot;
    QVector<double> data;
    int row, col, indx;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void btnSearchClicked();
    void btnRunClicked();
    void sbValueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QPushButton *btnRun;
    QPushButton *btnSearch;
    QVector<Group*> gVector;

    void addGroupBox(QVector<Group*> *gVector);
};

#endif // MAINWINDOW_H
