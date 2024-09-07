#include "functions.h"
#include <random>

template<typename VSize> class Trainer{
    private:
        std::vector<VSize> coefficients;
        MethodOpts method;
    public:
        Trainer(MethodOpts opt_method, std::vector<VSize>& coef);
        VSize change_weights(arma::Mat<VSize> &grad, arma::Mat<VSize>& weights);
};

template<class VSize> class FCNetwork{
    protected:
        arma::Mat<VSize> weights;
        arma::Mat<VSize> dot_prod;
        arma::Mat<VSize> output;
        ActivationFunc func;
    public:
        FCNetwork(arma::Mat<VSize> initalized_weights, ActivationFunc activation);
        ~FCNetwork();
        arma::Mat<VSize> forward(arma::Mat<VSize> &input);
        arma::Mat<VSize> backword(arma::Mat<VSize>& error);     //  DOT_PROD * DIFF(DOT) %= ERROR
        template<typename V> 
        friend std::ostream& operator<<(std::ostream& stream,const FCNetwork<V>& layer);
        void train( arma::Mat<VSize> &input,
                    arma::Mat<VSize> &error,
                    Trainer<VSize>& trainer);
};

