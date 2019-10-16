#include "neuron.h"

const double euler = 2.71828182845;

Neuron::Neuron()
{
    //w1 =Gen.bounded(10.0) - 5.0;
    //w2 =Gen.bounded(10.0) - 5.0;
    //wb =Gen.bounded(10.0) - 5.0;

}

Neuron::Neuron(int size,int& count)
{

    for(int i = 0; i < size; i++){
        weights.push_back(count);
        count++;
    }
    weights.push_back(1);
    Z = 0;
    FZ = 0;
    delt = 0;

}

std::vector<double> Neuron::delta(const double& err,const double& del,const double& factor){

    double z = FZ;
    std::vector<double> temp;
    z = z * (1 - z); //derivative


    if(err != 0){ // if error != 0 aka output layer...

        delt = z * err;

        for(unsigned int i = 0; i < weights.size() - 1; i++){
            temp.push_back(weights[i] * delt);
        }

        for(unsigned int i = 0; i < weights.size(); i++){
            weights[i] += input[i] * delt * factor;
        }

    } else if(del != 0.0){ // if delta != 0 aka hidden layer...



        delt = z * del;

        for(unsigned int i = 0; i < weights.size() - 1; i++){
            temp.push_back(weights[i] * delt);
        }

        for(unsigned int i = 0; i < weights.size(); i++){
            weights[i] += input[i] * delt * factor;
        }

    }

    return temp;

}

double Neuron::activate(std::vector<double> x, double(*point)(double i))
{
    double sumz = 0.0;

    if(point == nullptr){
        throw "Neuron: Error function pointer not valid - activate()";
    }

    if(x.size() != weights.size()){
        throw "Neuron: Error weights and data not the same size - activate()";
    }

    for(unsigned int i = 0; i < x.size(); i++){
        sumz += x[i] * weights[i];
    }

    Z = sumz;
    FZ = point(sumz);
    input = x;

    return FZ;

}

void Neuron::rand(){
    std::uniform_real_distribution<double> dist(-1.0,1.0);
    for(unsigned int i = 0; i < weights.size(); i++){
        weights[i] = dist(*generator);
    }
}

Neuron::Neuron(int size, std::random_device* gen)
{
    generator = gen;
    std::uniform_real_distribution<double> dist(-1.0,1.0);
    for(int i = 0; i < size+1; i++){
        weights.push_back(dist(*generator));
    }

    Z = 0;
    FZ = 0;
    delt = 0;

}


std::ostream& operator<<(std::ostream& os, const Neuron& dt)
{
    if(dt.weights.size() < 1){
        throw "Neuron: Error Neuron is empty operator<<";
    }
    for(unsigned int i = 0; i < dt.weights.size(); i++){
        os << " " << i << ": " << dt.weights[i];
        os << " -";
    }
    os << " Z: " << dt.Z;
    os << " FZ: " << dt.FZ;
    os << " Delta: " << dt.delt;
    os << std::endl;
    return os;
}

void Neuron::update(std::vector<double> x,double factor,int error){

    if(x.size() != weights.size()){
        throw "Neuron: Error weights and data not the same size - update()";
    }

    for(unsigned int i = 0; i < x.size(); i++){
        weights[i] += x[i] * factor * error;
    }

}

void Neuron::updateA(std::vector<double> x, double factor, double error, double(*point)(double i))
{

    if(point == nullptr){
        throw "Error";
    }

    double z = activate(x,point);
    z = z * (1 - z);

    for(unsigned int i = 0; i < x.size(); i++){
        weights[i] += x[i] * factor * error * z;
    }

}
