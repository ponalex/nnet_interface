#include "../src/layers.h"
#include <iostream>
#include <vector>


int main(){
    float alpha = 0.4;
    float lambda= 0.01;
    std::vector<float> config={alpha, lambda};
    Trainer<float> trainer(MethodOpts::SGD, config);
    arma::Mat<float> grad = {{-0.5, 0.1},
                            {-0.1, 0.5},
                            {0.2, -0.2},
                            {0.9, -0.3},
                            {-0.7, 0.2}};
    std::cout << "Gradient:\n";
    std::cout << grad ;
    std::cout << "*********************\n" ;
    arma::Mat<float> weights = {{ 0.22,  0.33},
                                {-0.1 ,  0.51},
                                { 0.2 , -0.31},
                                {-0.75,  0.55},
                                {-0.01, -0.25}};
    std::cout << "Weights:\n";
    std::cout << weights;
    std::cout << "*********************\n" ;
    trainer.change_weights(grad, weights);
    std::cout << "Weights:\n";
    std::cout << weights;
    std::cout << "*********************\n" ;
    return 0;
};
