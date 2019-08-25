#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <QRandomGenerator>

class Perceptron
{
public:
    Perceptron();
    double w1;
    double w2;
    double wb;
    QRandomGenerator Gen;
    int functionZ(double,double);
};

#endif // PERCEPTRON_H
