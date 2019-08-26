#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent* )), SLOT(clickedGraph(QMouseEvent*)));

    //Init errorX
    count = 0;

    // first set
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);

    //second set
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);

    //line
    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);

    //setting range
    ui->customPlot->xAxis->setRange(-10, 10);
    ui->customPlot->yAxis->setRange(-10, 10);

    // error graph
    ui->errorPlot->addGraph();
    ui->errorPlot->xAxis->setRange(0,200);
    ui->errorPlot->yAxis->setRange(0,10);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::addPoint(Point p)
{
    if(p.Class == 1){
        qv_x1.append(p.x);
        qv_y1.append(p.y);
    }else{
        qv_x2.append(p.x);
        qv_y2.append(p.y);
    }
    pointVector.append(p);

}

void MainWindow::clearData()
{
    ui->customPlot->graph(0)->data()->clear();
    ui->customPlot->graph(1)->data()->clear();
    ui->customPlot->graph(2)->data()->clear();

    ui->customPlot->replot();
    ui->customPlot->update();

    qv_x1.clear();
    qv_x2.clear();

    qv_y1.clear();
    qv_y2.clear();

    pointVector.clear();
    clearError();

}

void MainWindow::clearError(){
    ui->errorPlot->graph(0)->data()->clear();
    ui->errorPlot->replot();
    ui->errorPlot->update();

    errorX.clear();
    errorY.clear();
}

void MainWindow::plot()
{
    ui->customPlot->graph(0)->setData(qv_x1,qv_y1);
    ui->customPlot->graph(1)->setData(qv_x2,qv_y2);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void MainWindow::drawLine(){
    QVector<double> x,y;
    double y1,y2;

    y1 = ((10 * percept.w1) + (percept.wb)) / percept.w2;
    y2 = ((-10 * percept.w1) + (percept.wb)) / percept.w2;

    x.append(-10.0);
    x.append(10);

    y.append(y1);
    y.append(y2);

    ui->customPlot->graph(2)->setData(x,y);
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
    int Cl = -1;
    if(event->buttons() == Qt::RightButton){
        Cl = 0;
    }else if(event->buttons() == Qt::LeftButton){
        Cl = 1;
    }

    Point myPoint(ui->customPlot->xAxis->pixelToCoord(point.x()),ui->customPlot->yAxis->pixelToCoord(point.y()),Cl);
    addPoint(myPoint);
    plot();

}

void MainWindow::on_btnInit_clicked()
{
    percept.rand();
    drawLine();
    plot();
}

void MainWindow::plotError(){

    ui->errorPlot->graph(0)->setData(errorX,errorY);
    ui->errorPlot->replot();
    ui->errorPlot->update();
}

void MainWindow::on_btnCorrer_clicked()
{
    clearError();

    double factor = 0.5;
    bool done = false;
    int error;
    int cont;
    while(!done){
        done = true;
        cont = 0;

        for(int i=0; i < pointVector.size(); i++){
            error = pointVector[i].Class - percept.functionZ(pointVector[i].x,pointVector[i].y);
            if(error != 0){
                done = false;
                percept.update(pointVector[i],factor,error);
                cont += error * error;
            }
        }

        errorY.append(double(cont));
        errorX.append(count);
        count++;

        drawLine();
        plotError();
        plot();
        //QThread::sleep(1);

    }

}

void MainWindow::on_btnClean_clicked()
{
    clearData();
}
