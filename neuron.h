#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <random>
#include <ostream>
#include <iostream>
#include <math.h>

class Neuron
{
public:
    Neuron(int size,std::random_device* gen);

    void rand();
    double activate(std::vector<double> x, double(*point)(double i) = nullptr);
    std::vector<double> delta(const double& i,const double& del,const double& factor);

    double Z;
    double FZ;
    double delt;

    std::vector<double> weights;
    std::vector<double> input;

    std::random_device* generator;

    friend std::ostream& operator<<(std::ostream& os, const Neuron& dt);

};

#endif // NEURON_H
