#include <armadillo>
#include <iostream>
#include <ostream>
#include "src/layers.h"


using std::cout, std::endl;

int main(){
    uint Inp_l1 = 3;
    uint Neur_l1 = 2;
    uint Inp_l2 = 3;
    uint Neur_l2 = 2;
    uint Inp_l3 = 3;
    uint Neur_l3 = 1;
    arma::Mat<float> points = {{0, 0},{0, 1},{1, 0},{1, 1},    {0, 0}, {1,0} ,{1,1}, {0,1} };
    arma::Mat<float> result(8, 1);
    result(0, 0) = 0;
    result(1, 0) = 1;
    result(2, 0) = 1;  
    result(3, 0) = 0;
    result(4, 0) = 0;
    result(5, 0) = 1;
    result(6, 0) = 0;
    result(7, 0) = 1;
    float alpha = .9;
    float lambda = 0.00;
    std::vector<float> configs{alpha, lambda};
    
    arma::Mat<float> weight(Inp_l1, Neur_l1, arma::fill::randu);
    FCNetwork<float> layer1(0.008 * weight-0.004, ActivationFunc::Sigmoid);
    weight = arma::Mat<float>(Inp_l2, Neur_l2, arma::fill::randu);
    FCNetwork<float> layer2(weight-0.5, ActivationFunc::Sigmoid);
    weight = arma::Mat<float>(Inp_l3, Neur_l3, arma::fill::randu);
    FCNetwork<float> layer3(weight * 5, ActivationFunc::Sigmoid);
    Trainer<float> sgd_trainer(MethodOpts::SGD, configs);
    
    arma::Mat<float> input_1 = arma::Mat<float>(points.n_rows, points.n_cols+1, arma::fill::ones);
    arma::Mat<float> error_1 = arma::Mat<float>(points.n_rows, points.n_cols+1, arma::fill::zeros);
    arma::Mat<float> error_1_r = arma::Mat<float>(points.n_rows, points.n_cols, arma::fill::zeros);
    input_1.submat(0, 1, input_1.n_rows-1, input_1.n_cols-1) = points;

    arma::Mat<float> input_2 = arma::Mat<float>(points.n_rows, Neur_l1+1, arma::fill::ones);
    arma::Mat<float> error_2 = arma::Mat<float>(points.n_rows, Neur_l1+1, arma::fill::zeros);
    auto error_2_r = arma::Mat<float>(points.n_rows, Neur_l1, arma::fill::zeros);
    arma::Mat<float> input_3 = arma::Mat<float>(points.n_rows, 1 + Neur_l2, arma::fill::ones);
    arma::Mat<float> output(Neur_l3, points.n_rows);
    arma::Mat<float> error_3(Neur_l3, points.n_rows);
//
//
    for(int i = 0; i < 10000 ; ++i){
        input_2.submat(0, 1, input_2.n_rows-1, input_2.n_cols-1) = layer1.forward(input_1);
        input_3.submat(0, 1, input_3.n_rows-1, input_3.n_cols-1) = layer2.forward(input_2);
        output = layer3.forward(input_3);
        error_3 = -2 * (result - output );
        error_2 = layer3.backword(error_3);
        error_2_r = error_2.submat( 0, 1, input_2.n_rows-1, input_2.n_cols-1);
        error_1 = layer2.backword(error_2_r);
        error_1_r = error_1.submat( 0, 1, input_1.n_rows-1, input_1.n_cols-1);
        layer3.train(input_3, error_3, sgd_trainer);
        layer2.train(input_2, error_2_r, sgd_trainer);
        layer1.train(input_1, error_1_r, sgd_trainer);
//        cout << arma::sum(error_1_r);
        if(i%200 == 0){
            cout << "---------------------\n";
            cout << arma::sum(error_1_r);
     //       cout << i << ": " <<error_3.t()*error_3 ;
        }
    }
//    
    input_2.submat(0, 1, input_2.n_rows-1, input_2.n_cols-1) = layer1.forward(input_1);
    input_3.submat(0, 1, input_3.n_rows-1, input_3.n_cols-1) = layer2.forward(input_2);
    output = layer3.forward(input_3);
    cout << "---------------------\n";
    cout << output;
    cout << "---------------------\n";
    cout << layer3;
    cout << "---------------------\n";
    cout << layer2;
    cout << "---------------------\n";
    cout << layer1;
    return 0;
}
