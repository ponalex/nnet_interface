#include "layers.h"
#include <armadillo>
#include <ostream>

template <class VSize>
FCNetwork<VSize>::FCNetwork(arma::Mat<VSize> initalized_weights,
                            ActivationFunc activation){
    weights = initalized_weights;
    func = activation;
}

template <class VSize> std::ostream& operator<<(std::ostream& stream, const FCNetwork<VSize>& layer){
    stream << "Neuron numbers: " << layer.weights.n_cols<< "\n";
    stream << "Input numbers: " << layer.weights.n_rows<< "\n";
    stream << "Weights:\n" << layer.weights;
    stream << "Dot product:\n" << layer.dot_prod;
    stream << "Output:\n" << layer.output;
    return stream;
}

template <class VSize> 
arma::Mat<VSize> FCNetwork<VSize>::forward(arma::Mat<VSize>& input){
    dot_prod = input * weights ;
    switch (func){
        case ActivationFunc::Linear:
            break;
        case ActivationFunc::Sigmoid:
                output = sigmoid(dot_prod);
            break;
        case ActivationFunc::Softplus:
                output = softplus(dot_prod);
            break;
        default:
                std::cout << "Wrong type of activation!" << std::endl;
                std::cout << "Add more activation function!" << std::endl;
            break;
    }
    return output;
}

template <class VSize>
arma::Mat<VSize> FCNetwork<VSize>::backword(arma::Mat<VSize>& error){
    arma::Mat<VSize> result = dot_prod;
    switch (func) {
        case ActivationFunc::Sigmoid: 
                result = diff_sigmoid(result);
            break;
        case ActivationFunc::Softplus:
                result = diff_softplus(result);
        case ActivationFunc::Linear:break;
        default:;
    }
    result %=  error;
    result =  result * weights.t() ;
    return result;
}

template <class VSize>
void FCNetwork<VSize>::train(
                             arma::Mat<VSize>& input,
                             arma::Mat<VSize>& error,
                             Trainer<VSize>& trainer){
    arma::Mat<VSize> grad;
    switch(func){
        case ActivationFunc::Sigmoid:
            grad = error % diff_sigmoid(dot_prod);
            break;
        case ActivationFunc::Softplus:
            grad = error % diff_sigmoid(dot_prod);
            break;
        case ActivationFunc::Linear:
            grad = error % dot_prod;
            break;
        default:break;
    }
    grad = -1.0 * input.t() * grad ;
    trainer.change_weights(grad, weights);
}

template <class VSize> FCNetwork<VSize>::~FCNetwork(){}

template class FCNetwork<float>;
template class FCNetwork<double>;

template std::ostream& operator<<(std::ostream& stream,const FCNetwork<float>& layer);
template std::ostream& operator<<(std::ostream& stream,const FCNetwork<double>& layer);

