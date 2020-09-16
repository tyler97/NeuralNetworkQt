#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStringList>
#include <QThread>

double sigmoid(double x){
    double t = 1 / (1 + qPow(2.71828182,x * -1.0));
    return t;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent* )), SLOT(clickedGraph(QMouseEvent*)));

    myColors = {QColor(128,0,0),QColor(170,110,0),QColor(0,0,128),
              QColor(128,128,0),QColor(230, 25, 75),QColor(128, 128, 128),
              QColor(0, 0, 0),QColor(0, 128, 128),QColor(255,0,255),
              QColor(255,0,127),QColor(128,128,128),QColor(204,255,229)};

    Buttons.setExclusive(true);
    ui->customPlot->xAxis->setRange(-1,1);
    ui->customPlot->yAxis->setRange(-1,1);

    ui->errorPlot->addGraph();
    ui->errorPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->errorPlot->graph(0)->setPen(QPen(myColors[0]));

    ui->inputA->setText("8");
    ui->inputC->setText("3");
    ui->inputE->setText("0.01");
    ui->inputF->setText("0.1");
    ui->inputG->setText("1000");

    Network.setFunction(sigmoid);

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

    if(p.Class == -1){
        return;
    }
    ui->customPlot->graph(p.Class)->addData(p.x,p.y);
    pointVector.append(p);

}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event->pos();
    Point myPoint(ui->customPlot->xAxis->pixelToCoord(point.x()),
                  ui->customPlot->yAxis->pixelToCoord(point.y()),Buttons.checkedId());

    addPoint(myPoint);
    ui->customPlot->replot();
}

void MainWindow::on_btnInit_clicked()
{

    Clean();

    //Initializing network
    std::vector<int> temp;
    temp.push_back(2); //Input layer will always be 2-dimensional


    QStringList nodeList = ui->inputA->text().split(",");
    for(const QString& i : nodeList){
        if(i.toInt() != 0){
              temp.push_back(i.toInt());
        }
    }
    temp.push_back(ui->inputC->text().toInt());

    Network.CreateRed(temp);
    InitCheckBoxes(temp[temp.size() - 1]);

    this->update();
}

void MainWindow::InitCheckBoxes(const int& size)
{
    //initializing class checkboxes
    QCheckBox* ch;
    QPen myPen;
    for(int i = 0; i < size; i++){

        //Class checkbox
        ch = new QCheckBox(QString("Clase %1").arg(i),this);
        ui->gridLayout->addWidget(ch,i,0);
        CheckList.push_back(ch);


        //creating graphs for classes
        myPen.setColor(myColors[unsigned(i)]);
        ui->customPlot->addGraph();
        ui->customPlot->graph(i)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,4));
        ui->customPlot->graph(i)->setPen(myPen);

    }

    for(unsigned int i = 0; i < CheckList.size(); i++){
        Buttons.addButton(CheckList[i],int(i));
    }
}

void MainWindow::plotError(const int& N,const double& error){

    ui->errorPlot->graph()->addData(double(N),error);
    ui->errorPlot->replot();
    this->update();

}

std::vector<double> MainWindow::CreateVect(int cl){
    std::vector<double> temp(CheckList.size(),0);
    temp[unsigned(cl)] = 1.0;
    return temp;

}

void MainWindow::on_btnClean_clicked()
{
    Clean();
}

void MainWindow::Clean(){

    //Cleaning graph
    ui->errorPlot->graph()->setData({},{});
    ui->errorPlot->replot();

    ui->customPlot->clearGraphs();
    ui->customPlot->replot();

    //Cleaning buttons
    for(auto i : CheckList){
        Buttons.removeButton(i);
        ui->gridLayout->removeWidget(i);
        delete i;

    }

    CheckList.clear();

    pointVector.clear();

    this->update();

}

int MainWindow::getMax(const std::vector<double>& vect){
    double max = 0.0;
    int pos = 0;
    for(unsigned int i = 0; i < vect.size(); i++){
        if(vect[i] > max){
            max = vect[i];
            pos = int(i);
        }
    }
    return pos;
}

void MainWindow::on_btnTrain_clicked()
{
    int N = ui->inputG->text().toInt();
    double f = ui->inputF->text().toDouble();
    double error = 0.0;

    ui->errorPlot->xAxis->setRange(0,N);
    ui->errorPlot->yAxis->setRange(0,0.5);

    for(int i = 0; i < N; i++){
        for(const Point& j : pointVector){

            std::vector<double> temp = Network.FeedForward({j.x,j.y});
            error += qPow(1 - temp[unsigned(j.Class)],2);
            Network.Delta(temp,CreateVect(j.Class),f);

        }

        error /= double(pointVector.size());
        plotError(i,error);

        if(error <= ui->inputE->text().toDouble())
        {
            break;
        }

    }
        ui->errorPlot->replot();
}

void MainWindow::on_btnPrint_clicked()
{
    for(double i = -1.0; i < 1.0; i+=0.01){
        for(double j = -1.0; j < 1.0; j+=0.01){
            Point temp(i,j,getMax(Network.FeedForward({i,j})));
            addPoint(temp);
        }
    }
    ui->customPlot->replot();
}
