#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point.h"
#include "perceptron.h"

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

private slots:
    void makePlot();
    void clickedGraph(QMouseEvent *event);

    void on_btnInit_clicked();

    void on_btnCorrer_clicked();

    void on_btnClean_clicked();

    void on_btnCorrer2_clicked();

private:

    Ui::MainWindow *ui;
    QVector<double> qv_x1, qv_y1;
    QVector<double> qv_x2, qv_y2;
    QVector<double> errorY, errorX;
    int count;
    Perceptron percept;
    QVector<Point> pointVector;
    void drawLine();
    void delay();
    void plotError();
    void clearError();
};

#endif // MAINWINDOW_H
