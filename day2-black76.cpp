#include <iostream>
#include <cmath>
#include <type_traits>
#include "functions.hpp"

template <typename FType, typename KType, typename rType, typename sigmaType, typename tType>
auto black76Call(FType F, KType K, rType r, sigmaType sigma, tType t) -> std::common_type_t<double, FType, KType, rType, sigmaType, tType>
{
    using commonType = std::common_type_t<double, FType, KType, rType, sigmaType, tType>;
    auto F_new {static_cast<commonType>(F)};
    auto K_new {static_cast<commonType>(K)};
    auto r_new {static_cast<commonType>(r)};
    auto sigma_new {static_cast<commonType>(sigma)};
    auto t_new {static_cast<commonType>(t)};
    auto sqrt_t_new {std::sqrt(t_new)};

    auto d1 {(std::log(F_new / K_new) + (static_cast<commonType>(0.5) * sigma_new * sigma_new) * t_new ) / (sigma_new * sqrt_t_new)};
    auto d2 {d1 - sigma_new * sqrt_t_new};

    auto C {(std::exp(-r_new * t_new)) * (F_new * normalCDF(d1) - K_new * normalCDF(d2))};
    return C;
}

template <typename FType, typename KType, typename rType, typename sigmaType, typename tType>
auto black76Put(FType F, KType K, rType r, sigmaType sigma, tType t) -> std::common_type_t<double, FType, KType, rType, sigmaType, tType>
{
    using commonType = std::common_type_t<double, FType, KType, rType, sigmaType, tType>;
    auto F_new {static_cast<commonType>(F)};
    auto K_new {static_cast<commonType>(K)};
    auto r_new {static_cast<commonType>(r)};
    auto sigma_new {static_cast<commonType>(sigma)};
    auto t_new {static_cast<commonType>(t)};
    auto sqrt_t_new {std::sqrt(t_new)};

    auto d1 {(std::log(F_new / K_new) + (static_cast<commonType>(0.5) * sigma_new * sigma_new) * t_new ) / (sigma_new * sqrt_t_new)};
    auto d2 {d1 - sigma_new * sqrt_t_new};

    auto P {std::exp(-r_new * t_new) * (K_new * normalCDF(-d2) - (F_new * normalCDF(-d1)))};
    return P;
}

int main()
{
    std::cout << "Input underlying future price: ";
    double F {};
    std::cin >> F;

    std::cout << "Input strike price: ";
    double K {};
    std::cin >> K;

    std::cout << "Input the risk-free rate of interest (yearly): ";
    double r {};
    std::cin >> r;

    std::cout << "Input implied volatility (yearly): ";
    double sigma {};
    std::cin >> sigma;

    std::cout << "Input time to maturity (years): ";
    double t {};
    std::cin >> t;

    std::cout << "Call price: $" << black76Call(F,K,r,sigma,t) << '\n';
    std::cout << "Put price: $" << black76Put(F,K,r,sigma,t) << '\n';
   
    return 0;
}
