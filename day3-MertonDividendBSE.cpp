#include <iostream>
#include <cmath>
#include <type_traits>
#include "functions.hpp"

template <typename SType, typename KType, typename rType, typename qType, typename sigmaType, typename tType>
auto bsDividendCall(SType S, KType K, rType r, qType q, sigmaType sigma, tType t) -> std::common_type_t<double, SType, KType, rType, qType, sigmaType, tType>
{
    using commonType = std::common_type_t<double, SType, KType, rType, qType, sigmaType, tType>;
    auto S_new {static_cast<commonType>(S)};
    auto K_new {static_cast<commonType>(K)};
    auto r_new {static_cast<commonType>(r)};
    auto q_new {static_cast<commonType>(q)};
    auto sigma_new {static_cast<commonType>(sigma)};
    auto t_new {static_cast<commonType>(t)};
    auto sqrt_t_new {std::sqrt(t_new)};

    auto d1 {(std::log(S_new / K_new) + (r_new - q_new + (static_cast<commonType>(0.5) * sigma_new * sigma_new) ) * t_new) / (sigma_new * sqrt_t_new)};
    auto d2 {d1 - sigma_new * sqrt_t_new};

    auto C {S_new * std::exp(-q_new * t_new) * normalCDF(d1) - K_new * std::exp(-r_new * t_new) * normalCDF(d2)};
    return C;
}

template <typename SType, typename KType, typename rType, typename qType, typename sigmaType, typename tType>
auto bsDividendPut(SType S, KType K, rType r, qType q, sigmaType sigma, tType t) -> std::common_type_t<double, SType, KType, rType, qType, sigmaType, tType>
{
    using commonType = std::common_type_t<double, SType, KType, rType, qType, sigmaType, tType>;
    auto S_new {static_cast<commonType>(S)};
    auto K_new {static_cast<commonType>(K)};
    auto r_new {static_cast<commonType>(r)};
    auto q_new {static_cast<commonType>(q)};
    auto sigma_new {static_cast<commonType>(sigma)};
    auto t_new {static_cast<commonType>(t)};
    auto sqrt_t_new {std::sqrt(t_new)};

    auto d1 {(std::log(S_new / K_new) + (r_new - q_new + (static_cast<commonType>(0.5) * sigma_new * sigma_new) ) * t_new) / (sigma_new * sqrt_t_new)};
    auto d2 {d1 - sigma_new * sqrt_t_new};

    auto P {K_new * std::exp(-r_new * t_new) * normalCDF(-d2) - S_new * std::exp(-q_new * t_new) * normalCDF(-d1)};
    return P;
}

int main()
{
    std::cout << "Input underlying stock price: ";
    double S {};
    std::cin >> S;

    std::cout << "Input strike price: ";
    double K {};
    std::cin >> K;

    std::cout << "Input the risk-free rate of interest (yearly): ";
    double r {};
    std::cin >> r;

    std::cout << "Input the dividend yield of the stock (yearly): ";
    double q {};
    std::cin >> q;


    std::cout << "Input implied volatility (yearly): ";
    double sigma {};
    std::cin >> sigma;

    std::cout << "Input time to maturity (years): ";
    double t {};
    std::cin >> t;

    std::cout << "Call price: $" << bsDividendCall(S,K,r,q,sigma,t) << '\n';
    std::cout << "Put price: $" << bsDividendPut(S,K,r,q,sigma,t) << '\n';
   
    return 0;
}







