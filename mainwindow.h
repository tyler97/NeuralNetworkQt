#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "point.h"

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

private:

    Ui::MainWindow *ui;
    QVector<double> qv_x1, qv_y1;
    QVector<double> qv_x2, qv_y2;

};

#endif // MAINWINDOW_H
