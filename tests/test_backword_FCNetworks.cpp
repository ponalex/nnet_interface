#include "../src/layers.h"
#include <iostream>
#include <vector>


int main(){
// Trainer config
    std::vector<float> conf;
    conf.push_back(0.4);
    conf.push_back(0.0001);
    
    Trainer<float> trainer(MethodOpts::SGD, conf); 
// First layer weights
    arma::Mat<float>  W1 = {{ 0.5, 0.5},
                            { 0.2, 0.4},
                            { 0.4, 0.2}};
    FCNetwork<float> layer1(W1, ActivationFunc::Sigmoid);
//  Second layer weights
    arma::Mat<float>  W2 = {-0.1,
                             0.1,
                             0.2};
    FCNetwork<float> layer2(W2.t(), ActivationFunc::Sigmoid);
//  Input data with bias
    arma::Mat<float> Inp = {{ 1, 0.01, 0.01},
                            { 1, 0.01, 0.99},
                            { 1, 0.99, 0.01},
                            { 1, 0.99, 0.99},};
//  True value
    arma::Mat<float> Value ={ 0.01 ,
                               0.99 ,
                                0.99,
                                0.01};
//  Variable for storing output from layer1
    arma::Mat<float> Z1(Inp.n_rows,3, arma::fill::ones);
    Z1.submat(0,1, Z1.n_rows-1, Z1.n_cols-1) = layer1.forward(Inp);
    auto Y_tilda = layer2.forward(Z1);

    arma::Mat<float> Errors = -2 * (Value.t() - Y_tilda);
    std::cout << "Layer 1: \n";
    std::cout << layer1;
    std::cout << "*********************\n" ;
    std::cout << "Layer 2: \n";
    std::cout << layer2;
    std::cout << "*********************\n" ;
    std::cout << "Output layer1: \n";
    std::cout << Z1;
    std::cout << "*********************\n" ;
    std::cout << "Error on layer 2:\n" << Errors ;
    std::cout << "*********************\n";
//  Back propagation
    auto grad = layer2.backword(Errors);
    std::cout << "Error on layer 1:\n" << grad ;
    std::cout << "*********************\n";
    std::cout << "#####################\n";
//  Train layer 2:
    layer2.train(Z1, Errors, trainer);
//  Train layer 1:
    arma::Mat<float> r_grad = grad.submat(0,1,grad.n_rows-1, grad.n_cols-1);
    std::cout << "Gradient:\n" << grad;
    std::cout << "\n" << r_grad;
    layer1.train(Inp, r_grad, trainer);
//  Verifiaction
    Z1.submat(0,1, Z1.n_rows-1, Z1.n_cols-1) = layer1.forward(Inp);
    Y_tilda = layer2.forward(Z1); 
    std::cout << "Layer 1: \n";
    std::cout << layer1;
    std::cout << "*********************\n" ;
    std::cout << "Layer 2: \n";
    std::cout << layer2;
    std::cout << "*********************\n" ;
    for(int i = 0 ; i < 5000; ++i){
        Z1.submat(0,1, Z1.n_rows-1, Z1.n_cols-1) = layer1.forward(Inp);
        Y_tilda = layer2.forward(Z1);
        Errors = -2 * (Value.t() - Y_tilda);
        grad = layer2.backword(Errors);
        r_grad = grad.submat(0,1,grad.n_rows-1, grad.n_cols-1);
        layer2.train(Z1, Errors, trainer);
        layer1.train(Inp, r_grad, trainer);
        if(i%100==0){
            std::cout << "Error: " << Errors.t()*Errors;
        }
    }
    std::cout << "88888888888888888888888888\n";
    std::cout << "Layer 1: \n";
    std::cout << layer1;
    std::cout << "*********************\n" ;
    std::cout << "Layer 2: \n";
    std::cout << layer2;
    std::cout << "*********************\n" ;
    
    return 0;
};
