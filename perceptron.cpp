#include "perceptron.h"
#include "point.h"
#include <QDebug>

Perceptron::Perceptron()
{
    w1 = Gen.bounded(20.0) - 10.0;
    w2 = Gen.bounded(20.0) - 10.0;
    wb = Gen.bounded(20.0) - 10.0;
}

int Perceptron::functionZ(double x1, double x2)
{
    double test = (w1*x1) + (w2*x2) - wb;
    if(test > 0.0){
        return 1;
    }
    return 0;

}

void Perceptron::rand(){
    w1 = Gen.bounded(20.0) - 10.0;
    w2 = Gen.bounded(20.0) - 10.0;
    wb = Gen.bounded(20.0) - 10.0;
}

void Perceptron::update(Point i,double factor,int error){
    w1 = w1 + (i.x * factor * error);
    w2 = w2 + (i.y * factor * error);
    wb = wb + (-1 * factor * error);
    qDebug() << w1  << " " << w2 << " " << wb;
}
