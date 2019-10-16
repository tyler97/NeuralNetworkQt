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

    Neuron();
    Neuron(int size,int& count);
    Neuron(int size,std::random_device* gen);
    std::vector<double> weights;
    void rand();
    void update(std::vector<double> x, double factor, int error);
    void updateA(std::vector<double> x, double factor, double error,double(*point)(double i) = nullptr);
    double activate(std::vector<double> x, double(*point)(double i) = nullptr);
    std::vector<double> delta(const double& i,const double& del,const double& factor);


    double Z;
    double FZ;
    double delt;
    std::vector<double> input;

    friend std::ostream& operator<<(std::ostream& os, const Neuron& dt);
    std::random_device* generator;

};

#endif // NEURON_H
