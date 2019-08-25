#include "perceptron.h"

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
