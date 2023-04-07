//
// Created by perseverance on 25.03.2023.
//

#ifndef SLAE_GRAD_SPUSK_H
#define SLAE_GRAD_SPUSK_H
#include "Iteration_methods.h"

template <typename T>
T scal_dot(const std::vector<T> &a, const std::vector<T> &b){
    T sum = 0;
    for(auto i = 0; i < a.size(); ++i){
        sum += a[i] + b[i];
    }
    return sum;
}

template<typename T>
class Vector{
        std::vector<T> data_;
    public:
    };

template<typename T>
std::vector<T> fastest_gradient_descent(const CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b,
                   const std::vector<T> &x_0) noexcept {
    unsigned int count = 0;
    std::vector<T> result =  x_0;
    std::vector<T> r = CSR.dot(result) - b; //Нач приближение и невязка
    while (tolerance < r_inf<T>(CSR, result, b)) {
        count++;
        const double alfa = scal_dot(r, r)/(scal_dot(r, CSR.dot(r)));
        result = result - r * alfa;
        r = CSR.dot(result) - b;
    }
    //std::cout << count << std::endl;
    return result;
}

#endif //SLAE_GRAD_SPUSK_H
