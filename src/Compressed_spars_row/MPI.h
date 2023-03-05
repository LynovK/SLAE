//
// Created by perseverance on 05.03.23.
//
#pragma once
#ifndef SLAE_MPI_H
#define SLAE_MPI_H

#include "CompressedConverterMatrixWithZEROS.h"
#include "CompressedMatrix.h"
#include <cmath>

template<typename Type>
std::vector<Type> operator-(const std::vector<Type> &a, const std::vector<Type> &b) {
    std::vector<Type> result(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

template<typename Type>
std::vector<Type> operator*(const std::vector<Type> &a, const Type &c) {
    std::vector<Type> result(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] * c;
    }
    return result;
}
template <typename T>
T get_r(const CompressedMatrix<T> &CSR, const std::vector<T> &x, const std::vector<T> &b) {
    T r = 0;
    for (size_t j = 0; j < b.size(); j++) {
        r += (b[j] - dot(x, CSR)[j]) * (b[j] - dot(x, CSR)[j]);
    }
    return r;
}

template<typename T>
T r_inf(const CompressedMatrix<T> &CSR, const std::vector<T> &x, const std::vector<T> &b) {
    T r = 0;
    for (size_t j = 0; j < b.size(); j++) {
        if (fabs(b[j] - dot(x, CSR)[j]) > r)
            r = fabs(b[j] - dot(x, CSR)[j]);
    }
    return r;
}

template <typename T>
std::vector<T> MPI(CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b,
                       const std::vector<T> &x_0, const T tau) {
    unsigned int count = 0;
    std::vector<T> result = (const std::vector<T> &) x_0, r = dot(result, CSR) - b;
    while (tolerance < r_inf<T>(CSR, result, b)) {
        count++;
        result = result - r * tau;
        r = dot(result, CSR) - b;
        std::cout << r_inf<T>(CSR, result, b) << std::endl;
    }
    return result;
}

template <typename T>
std::vector<T> Jacoby(CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b,
                               const std::vector<T> &x0) {
    std::vector<T> xk = x0, xt(x0.size(), 0);
    while (tolerance < r_inf<T>(CSR, xk, b)) {
        for (size_t k = 0; k < x0.size(); k++) {
            xt[k] = (1 / CSR.element(k, k)) * (b[k] - dot(xk, CSR)[k] + CSR.element(k, k) * xk[k]);
        }
        xk = xt;
    }
    return xk;
}

template <typename T>
std::vector<T> G_Z(const CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0)
{
    std::vector<T> xk = x0;
    T sum_1 = 0, sum_2 = 0;
    while(tolerance < r_inf<T>(CSR, xk, b)){
        for(long long k = 0; k < x0.size(); k ++){
            for(long long i = 0; i < k; i ++)
                sum_1 += CSR.element(k, i) * xk[i];
            for(long long i = k + 1; i < x0.size(); i ++)
                sum_2 += CSR.element(k, i) * xk[i];
            xk[k] = (1 / CSR.element(k, k)) * (b[k] - sum_1 - sum_2);
            sum_1 = 0;
            sum_2 = 0;
        }
    }
    return xk;
}

#endif //SLAE_MPI_H