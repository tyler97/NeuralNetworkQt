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

    count = 0;
    Buttons.setExclusive(true);
    ui->customPlot->xAxis->setRange(-1,1);
    ui->customPlot->yAxis->setRange(-1,1);
    ui->inputA->setText("3,4");
    ui->inputC->setText("5");
    ui->inputE->setText("0.2");
    ui->inputF->setText("0.4");
    ui->inputG->setText("500");

    Network.setFunction(sigmoid);

    myColors = {QColor(255,0,0),QColor(255,128,0),QColor(255,255,0),
              QColor(128,255,0),QColor(0,255,255),QColor(0,128,255),
              QColor(0,0,255),QColor(127,0,255),QColor(255,0,255),
              QColor(255,0,127),QColor(128,128,128),QColor(204,255,229)};


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

void MainWindow::clearData()
{


}

void MainWindow::clearError(){

}

void MainWindow::plot()
{

}

void MainWindow::drawLine(){

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

    //initializing network
    std::vector<int> temp;
    ui->customPlot->clearGraphs();
    temp.push_back(2);
    QStringList nodeList = ui->inputA->text().split(",");
    for(const QString& i : nodeList){
        if(i.toInt() != 0){
              temp.push_back(i.toInt());
        }
    }
    temp.push_back(ui->inputC->text().toInt());

    Network.CreateRed(temp);

    //initializing class checkboxes
    QCheckBox* ch;
    QPen myPen;
    for(int i = 0; i < temp[temp.size() - 1]; i++){

        //Class checkbox
        ch = new QCheckBox(QString("Clase %1").arg(i),this);
        ui->gridLayout->addWidget(ch,i,0);
        CheckList.push_back(ch);


        //creating graphs for classes
        myPen.setColor(myColors[unsigned(i)]);
        ui->customPlot->addGraph();
        ui->customPlot->graph(i)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,2));
        ui->customPlot->graph(i)->setPen(myPen);

    }

    for(unsigned int i = 0; i < CheckList.size(); i++){
        Buttons.addButton(CheckList[i],int(i));
    }

    std::cout << ui->customPlot->graphCount() << std::endl;

    this->update();
}

void MainWindow::plotError(){


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

    for(int i = 0; i < N; i++){
        for(const Point& j : pointVector){

            Network.Delta(Network.FeedForward({j.x,j.y}),CreateVect(j.Class),f);

        }
    }
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
