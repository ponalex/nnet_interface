#include "../src/layers.h"
#include <iostream>


int main(){
    arma::Mat<float> W1(3, 5, arma::fill::randu);
    FCNetwork<float> layer1(W1, ActivationFunc::Linear);
    std::cout << layer1;
    std::cout << "*********************\n" ;
    arma::Mat<float>  W2 = {{0.5, 0.1},
                            {0.1, 0.5},
                            {0.2, 0.2},
                            {0.9, 0.3},
                            {0.7, 0.2}};
    FCNetwork<float> layer2(W2, ActivationFunc::Sigmoid);
    std::cout << layer2;
    std::cout << "*********************\n" ;

    arma::Mat<float>  W3{1,1, arma::fill::ones};
    FCNetwork<float> layer3 (W3,ActivationFunc::Softplus);
    std::cout << layer3;
    std::cout << "*********************\n" ;
    return 0;
};
