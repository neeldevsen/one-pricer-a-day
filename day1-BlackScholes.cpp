#include <iostream>
#include <cmath>
#include <type_traits>


template <typename T>
auto normalCDF(T x) -> std::common_type_t <double , T>
{
    using commonType = std::common_type_t<double, T>;
    return static_cast<commonType>(0.5) * (static_cast<commonType>(1) + std::erf(x / std::sqrt(2.0)));
}


template <typename SType, typename KType, typename rType, typename sigmaType, typename tType>
auto blackScholesCall(SType S, KType K, rType r, sigmaType sigma, tType t) -> std::common_type_t<double, SType, KType, rType, sigmaType, tType>
{
    using commonType = std::common_type_t<double, SType, KType, rType, sigmaType, tType>;
    auto S_new {static_cast<commonType>(S)};
    auto K_new {static_cast<commonType>(K)};
    auto r_new {static_cast<commonType>(r)};
    auto sigma_new {static_cast<commonType>(sigma)};
    auto t_new {static_cast<commonType>(t)};


    auto d1 {(std::log(S_new / K_new) + (r_new + 0.5 * sigma_new * sigma_new) * t_new) / (sigma_new * std::sqrt(t_new))};
    auto d2 {d1 - sigma_new * std::sqrt(t_new)};


    auto C {S_new * normalCDF(d1) - K_new * std::exp(-r_new * t_new) * normalCDF(d2)};
    return C;
}


template <typename SType, typename KType, typename rType, typename sigmaType, typename tType>
auto blackScholesPut(SType S, KType K, rType r, sigmaType sigma, tType t) -> std::common_type_t<double, SType, KType, rType, sigmaType, tType>
{
    using commonType = std::common_type_t<double, SType, KType, rType, sigmaType, tType>;
    auto S_new {static_cast<commonType>(S)};
    auto K_new {static_cast<commonType>(K)};
    auto r_new {static_cast<commonType>(r)};
    auto sigma_new {static_cast<commonType>(sigma)};
    auto t_new {static_cast<commonType>(t)};


    auto d1 {(std::log(S_new / K_new) + (r_new + 0.5 * sigma_new * sigma_new) * t_new) / (sigma_new * std::sqrt(t_new))};
    auto d2 {d1 - sigma_new * std::sqrt(t_new)};


    auto P {K_new * std::exp(-r_new * t_new) * normalCDF(-d2) - S_new * normalCDF(-d1)};
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

    std::cout << "Input implied volatility (yearly): ";
    double sigma {};
    std::cin >> sigma;

    std::cout << "Input time to maturity (years): ";
    double t {};
    std::cin >> t;

    std::cout << "Call price: $" << blackScholesCall(S,K,r,sigma,t) << '\n';
    std::cout << "Put price: $" << blackScholesPut(S,K,r,sigma,t) << '\n';
   
    return 0;
}







