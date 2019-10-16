#ifndef NN_H
#define NN_H
#include "neuron.h"

class NN
{
    public:
        NN();
        NN(const std::vector<int>& nodes);
        std::vector<double> FeedForward(std::vector<double> data);
        std::vector<std::vector<Neuron>> layers;
        void CreateRed(const std::vector<int>& nodes);
        void Delta(const std::vector<double>& data,const std::vector<double>& test,const double& factor);
        void trainNetwork(const std::vector<std::vector<double>>& data,std::vector<std::vector<double>>& test,const int& N, const double& factor);
        void setFunction(double(*point)(double i));
        void Clear();
        bool isEmpty();
        void Print();
        int DataInputSize();

    private:
        double (*functionZ)(double);
        unsigned int Size;
};

#endif // NN_H
