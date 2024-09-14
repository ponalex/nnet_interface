#include "layers.h"

//        Trainer(MethodOpts opt_method, std::vector<float>);


template <typename VSize>
Trainer<VSize>::Trainer(MethodOpts opt_method, std::vector<VSize>& coef){
    coefficients = coef;
    method = opt_method;   
};

template<typename VSize>
VSize Trainer<VSize>::change_weights( arma::Mat<VSize> &grad,
                                arma::Mat<VSize>& weights){
    auto alpha = coefficients[0];
    auto lambda = coefficients[1];
    switch (method){
        case MethodOpts::SGD:
            weights = weights - alpha*( grad + 2 * lambda *weights) ;
            break;
        case MethodOpts::Momentum:
            break;
        default:
            break;
    }
    return 0.0;
};
template class Trainer<float>;
template class Trainer<double>;
