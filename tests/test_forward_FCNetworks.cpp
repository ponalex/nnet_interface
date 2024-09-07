#include "../src/layers.h"
#include <iostream>


int main(){
    arma::Mat<float>  W1 = {{0.5, 0.1},
                            {0.1, 0.5},
                            {0.2, 0.2},
                            {0.9, 0.3},
                            {0.7, 0.2}};
    FCNetwork<float> layer1(W1, ActivationFunc::Sigmoid);
    std::cout << layer1;
    std::cout << "*********************\n" ;

    arma::Mat<float> Inp = {{1, 0, 0.5, -1, 0.75, 0.25},
                            {0, 1, 0.5, 2 , 0.25, 0.75}};
    std::cout << "Input:\n" << Inp;
    std::cout << "###########################\n";
    layer1.forward(Inp);
    std::cout << layer1;
    std::cout << "*********************\n" ;
    return 0;
};
