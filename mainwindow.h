#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <stdio.h>
#include <QPushButton>
#include <QFileDialog>
#include <QtDebug>
#include <QGroupBox>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:
    void btnSearchClicked();
    void on_sbNum_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QVector<QCustomPlot> *plot;
    QPushButton *btnRun;
    QPushButton *btnSearch;
    QVector<QGroupBox> *gb;
};

#endif // MAINWINDOW_H
