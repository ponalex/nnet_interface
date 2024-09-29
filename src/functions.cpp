#include "functions.h"
#include <armadillo>

template<typename VSize> arma::Mat<VSize> sigmoid(arma::Mat<VSize>& input){
    arma::Mat<VSize> result = 1.0 / (1.0 + arma::exp(-1*input));
    return result;
}
template<typename VSize> arma::Mat<VSize> diff_sigmoid(arma::Mat<VSize>& input){
    arma::Mat<VSize> result = arma::exp(-1*input)/(1.0+arma::exp(-1*input));
    return result/(1.0 + arma::exp(-1*input));
}
//  ********************************************************
template<typename VSize> arma::Mat<VSize> tanh(arma::Mat<VSize>& input){
    arma::Mat<VSize> result = (arma::exp(input) - arma::exp(-1*input)) / (arma::exp(input) + arma::exp(-1*input));
    return result;
}
template<typename VSize> arma::Mat<VSize> diff_tanh(arma::Mat<VSize>& input){
    arma::Mat<VSize> result = ( arma::exp(input) + arma::exp(-1*input)) * ( arma::exp(input) + arma::exp(-1*input));
    return 4 * result * arma::exp(input) * arma::exp(-1*input);
}
//  ********************************************************
template<typename VSize> arma::Mat<VSize> softplus(arma::Mat<VSize>& input){
    arma::Mat<VSize> result =arma::log( 1.0 + arma::exp(input));
    return result;
}
template<typename VSize> arma::Mat<VSize> diff_softplus(arma::Mat<VSize>& input){
    arma::Mat<VSize> result = 1.0/ ( 1.0 + arma::exp(-1.0*input));
    return result;
}
//  ********************************************************
template<typename VSize> arma::Mat<VSize> average(arma::Mat<VSize> &input){
    return arma::sum(input, DIMENSION)/input.n_rows;
}
template<typename VSize> arma::Mat<VSize> diff_average(arma::Mat<VSize> &input){
    arma::Mat<VSize> result(input.n_rows, input.n_cols, arma::fill::ones);
    return result;
}
//  ********************************************************
template<typename VSize> arma::Mat<VSize> get_max(arma::Mat<VSize> &input){
    arma::Mat<VSize> result = arma::max(input, 0);
    return result;
}
template<typename VSize> arma::Mat<VSize> diff_max(arma::Mat<VSize> &input){
    arma::Mat<VSize> result(input.n_rows, input.n_cols, arma::fill::zeros);
    arma::uword pointer = input.index_max();
    result(pointer) = 1;
    return result;
}
//  ********************************************************
template arma::Mat<float> sigmoid(arma::Mat<float>& input);
template arma::Mat<double> sigmoid(arma::Mat<double>& input);
template arma::Mat<float> diff_sigmoid(arma::Mat<float>& input);
template arma::Mat<double> diff_sigmoid(arma::Mat<double>& input);
template arma::Mat<float> softplus(arma::Mat<float>& input);
template arma::Mat<double> softplus(arma::Mat<double>& input);
template arma::Mat<float> diff_softplus(arma::Mat<float>& input);
template arma::Mat<double> diff_softplus(arma::Mat<double>& input);
template arma::Mat<float> average(arma::Mat<float> &input);
template arma::Mat<double> average(arma::Mat<double> &input);
template arma::Mat<float> diff_average(arma::Mat<float> &input);
template arma::Mat<double> diff_average(arma::Mat<double> &input);
template arma::Mat<float> get_max(arma::Mat<float> &input);
template arma::Mat<double> get_max(arma::Mat<double> &input);
template arma::Mat<float> diff_max(arma::Mat<float> &input);
template arma::Mat<double> diff_max(arma::Mat<double> &input);
