#include <armadillo>

#define DIMENSION 0

enum ActivationFunc {
    Sigmoid,
    Softplus,
    Linear,
    Maximum,
    Average,
};

enum MethodOpts{
    SGD,
    AdaGrad,
    Adam,
    RMSprop,
    Momentum
};

template<typename VSize> arma::Mat<VSize> sigmoid(arma::Mat<VSize>& input);
template<typename VSize> arma::Mat<VSize> diff_sigmoid(arma::Mat<VSize>& input);
template<typename VSize> arma::Mat<VSize> softplus(arma::Mat<VSize>& input);
template<typename VSize> arma::Mat<VSize> diff_softplus(arma::Mat<VSize>& input);
template<typename VSize> arma::Mat<VSize> average(arma::Mat<VSize> &input);
template<typename VSize> arma::Mat<VSize> diff_average(arma::Mat<VSize> &input);
template<typename VSize> arma::Mat<VSize> get_max(arma::Mat<VSize> &input);
template<typename VSize> arma::Mat<VSize> diff_max(arma::Mat<VSize> &input);

