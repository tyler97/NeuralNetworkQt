#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <QRandomGenerator>
#include "point.h"

class Perceptron
{
public:
    Perceptron();
    double w1;
    double w2;
    double wb;
    QRandomGenerator Gen;
    int functionZ(double,double);
    void rand();
    void update(Point i, double factor, int error);
};

#endif // PERCEPTRON_H
