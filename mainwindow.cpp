#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent* )), SLOT(clickedGraph(QMouseEvent*)));

    // first set
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);

    //second set
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);

    //setting range
    ui->customPlot->xAxis->setRange(-10, 10);
    ui->customPlot->yAxis->setRange(-10, 10);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(Point p)
{
    if(p.Class == "1"){
        qv_x1.append(p.x);
        qv_y1.append(p.y);
    }else{
        qv_x2.append(p.x);
        qv_y2.append(p.y);
    }

}

void MainWindow::clearData()
{

}

void MainWindow::plot()
{
    ui->customPlot->graph(0)->setData(qv_x1,qv_y1);
    ui->customPlot->graph(1)->setData(qv_x2,qv_y2);
    ui->customPlot->replot();
    ui->customPlot->update();
}



void MainWindow::makePlot(){
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/5.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    //ui->customPlot->xAxis->setLabel("x");
    //ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(-10, 10);
    ui->customPlot->yAxis->setRange(-10, 10);
    ui->customPlot->replot();
}



void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event->pos();
    QString Cl = "";
    if(event->buttons() == Qt::RightButton){
        Cl = "1";
    }else if(event->buttons() == Qt::LeftButton){
        Cl = "2";
    }

    Point myPoint(ui->customPlot->xAxis->pixelToCoord(point.x()),ui->customPlot->yAxis->pixelToCoord(point.y()),Cl);
    //qDebug() << ui->customPlot->xAxis->pixelToCoord(point.x()) << ui->customPlot->yAxis->pixelToCoord(point.y());
    addPoint(myPoint);
    plot();
}
