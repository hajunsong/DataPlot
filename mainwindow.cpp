#include "mainwindow.h"
#include "ui_mainwindow.h"

void load_data(QString file_name, QVector<double> *data, int *row, int *col) {
    FILE *fp_in;
    int buffer = 10000000;
    char *basic = new char[buffer];
    char *ptr;
    fp_in = fopen(file_name.toUtf8(), "r");
    int i = 0, j = 0;
    QVector<double> temp;
    while (fgets(basic, buffer, fp_in) != nullptr)
    {
        j = 0;
        ptr = strtok(basic, "\t");
        while (ptr != nullptr) {
            temp.push_back(atof(ptr));
            ptr = strtok(nullptr, "\t");
            j++;
        }
        i++;
    }
    fclose(fp_in);
    delete[] basic;

    *row = i;
    *col = j;
    for(int j = 0; j < *col; j++){
        for(int i = 0; i < *row; i++){
            data->push_back(temp[i*(*col) + j]);
        }
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sbNum->setValue(1);
    connect(ui->btnRun, SIGNAL(clicked()), this, SLOT(btnRunClicked()));

    Group *group = new Group();
    group->gb = new QGroupBox();
    group->gb->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    group->gb->setObjectName("gb_1");
    group->gb->setTitle(QApplication::translate("MainWindow", "Group 1", nullptr));
    gVector.push_back(group);
    addGroupBox(&gVector);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnSearchClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("텍스트 파일"),"","txt (*.txt)");
    int indx = sender()->objectName().split("_")[0].toInt();
    gVector[indx]->txt->setText(fileName);
    gVector[indx]->indx = gVector[indx]->spin->value();
    load_data(gVector[indx]->txt->text(), &gVector[indx]->data, &gVector[indx]->row, &gVector[indx]->col);
    gVector[indx]->spin->setRange(0, gVector[indx]->col);
}

void MainWindow::btnRunClicked()
{
    int size = gVector.length();
    for(int i = 0; i < size; i++){
        QVector<double> x, y;
        x = gVector[i]->data.mid(0, gVector[i]->row);
        y = gVector[i]->data.mid(gVector[i]->indx*gVector[i]->row, gVector[i]->row);
        gVector[i]->plot->graph(0)->setData(x,y);

        vector<double> x_temp, y_temp;
        x_temp = x.toStdVector();
        y_temp = y.toStdVector();
        sort(y_temp.begin(), y_temp.end());

        gVector[i]->plot->xAxis->setRange(x_temp.front(), x_temp.back());
        gVector[i]->plot->yAxis->setRange(y_temp.front(), y_temp.back());

        gVector[i]->plot->replot();
    }
}

void MainWindow::sbValueChanged(int arg1)
{
    int indx = sender()->objectName().split("_")[0].toInt();
    gVector[indx]->indx = arg1;

    QVector<double> x, y;
    x = gVector[indx]->data.mid(0, gVector[indx]->row);
    y = gVector[indx]->data.mid(gVector[indx]->indx*gVector[indx]->row, gVector[indx]->row);
    gVector[indx]->plot->graph(0)->setData(x,y);

    vector<double> x_temp, y_temp;
    x_temp = x.toStdVector();
    y_temp = y.toStdVector();
    sort(y_temp.begin(), y_temp.end());

    gVector[indx]->plot->xAxis->setRange(x_temp.front(), x_temp.back());
    gVector[indx]->plot->yAxis->setRange(y_temp.front(), y_temp.back());

    gVector[indx]->plot->replot();
}

void MainWindow::addGroupBox(QVector<Group*> *gVector)
{
    QString size = QString::number(gVector->length());
    QGridLayout *gridLayout = new QGridLayout(gVector->back()->gb);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gVector->back()->check = new QCheckBox(gVector->back()->gb);
    gVector->back()->check->setObjectName("cb_"+size);
    gridLayout->addWidget(gVector->back()->check, 0, 2, 1, 1);
    gVector->back()->btn = new QPushButton(gVector->back()->gb);
    gVector->back()->btn->setObjectName("btn_"+size);
    gVector->back()->btn->setText("...");
    gridLayout->addWidget(gVector->back()->btn, 0, 1, 1, 1);
    gVector->back()->txt = new QLineEdit(gVector->back()->gb);
    gVector->back()->txt->setObjectName("le_"+size);
    gridLayout->addWidget(gVector->back()->txt, 0, 0, 1, 1);
    gVector->back()->spin = new QSpinBox(gVector->back()->gb);
    gVector->back()->spin->setObjectName("sb_"+size);
    gVector->back()->spin->setValue(1);
    gridLayout->addWidget(gVector->back()->spin, 0, 3, 1, 1);
    gVector->back()->plot= new QCustomPlot(gVector->back()->gb);
    gVector->back()->plot->setObjectName("plot_"+size);
    gridLayout->addWidget(gVector->back()->plot, 1, 0, 1, 4);
    ui->gridLayout->addWidget(gVector->back()->gb);

    connect(gVector->back()->btn, SIGNAL(clicked()), this, SLOT(btnSearchClicked()));
    connect(gVector->back()->spin, SIGNAL(valueChanged(int)), this, SLOT(sbValueChanged(int)));

    gVector->back()->plot->addGraph();
    gVector->back()->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);
    gVector->back()->plot->graph(0)->setLineStyle(QCPGraph::lsLine);

    QPen blueDotPen;
    blueDotPen.setColor(QColor(30, 40, 255, 150));
    blueDotPen.setStyle(Qt::DotLine);
    blueDotPen.setWidthF(4);
    gVector->back()->plot->graph(0)->setPen(blueDotPen);
    gVector->back()->plot->graph(0)->setName("Sine envelope");
    gVector->back()->plot->xAxis->setRange(-1, 1);
    gVector->back()->plot->yAxis->setRange(-1, 1);
    gVector->back()->plot->replot();
    gVector->back()->plot->xAxis->setLabel("time [s]");
    gVector->back()->plot->yAxis->setLabel("position [deg]");
}
