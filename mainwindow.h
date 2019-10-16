#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point.h"
#include "perceptron.h"
#include <nn.h>
#include <QButtonGroup>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Graph Functions
    void addPoint(Point);
    void clearData();
    void plot();

    std::vector<double> CreateVect(int cl);
    void Clean();
    int getMax(const std::vector<double> &vect);
private slots:
    void clickedGraph(QMouseEvent *event);

    void on_btnInit_clicked();

    void on_btnCorrer_clicked();

    void on_btnClean_clicked();

    void on_btnCorrer2_clicked();

    void on_btnTrain_clicked();

    void on_btnPrint_clicked();

private:

    Ui::MainWindow *ui;
    NN Network;
    std::vector<QColor> myColors;
    QButtonGroup Buttons;
    std::vector<QCheckBox*> CheckList;

    int count;
    Perceptron percept;
    QVector<Point> pointVector;
    void drawLine();
    void delay();
    void plotError();
    void clearError();
};

#endif // MAINWINDOW_H
