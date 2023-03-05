//
// Created by perseverance on 05.03.23.
//
#pragma once
#ifndef SLAE_MPI_H
#define SLAE_MPI_H

#include "CompressedMatrixRepresent.h"
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

float get_r(CompressedMatrix &A, const std::vector<float> &x, const std::vector<float> &b) {
    float r = 0;
    for (size_t j = 0; j < b.size(); j++) {
        r += (b[j] - dot(x, A)[j]) * (b[j] - dot(x, A)[j]);
    }
    return r;
}


float r_inf(CompressedMatrix &CSR, const std::vector<float> &x, const std::vector<float> &b) {
    float r = 0;
    for (size_t j = 0; j < b.size(); j++) {
        if (fabs(b[j] - dot(x, CSR)[j]) > r)
            r = fabs(b[j] - dot(x, CSR)[j]);
    }
    return r;
}

std::vector<float> MPI(CompressedMatrix &CSR, const float tolerance, const std::vector<float> &b,
                       const std::vector<float> &x_0, const float tau) {
    unsigned int count = 0;
    std::vector<float> result = x_0, r = dot(result, CSR) - b;
    while (tolerance < get_r(CSR, result, b)) {
        count++;
        result = result - r * tau;
        r = dot(result, CSR) - b;
        std::cout << count << std::endl;
    }
    return result;
}

std::vector<float> Jacoby_meth(CompressedMatrix &CSR, const float tolerance, const std::vector<float> &b,
                               const std::vector<float> &x0) {
    std::vector<float> xk = x0, xt(x0.size(), 0);
    while (tolerance < r_inf(CSR, xk, b)) {
        for (size_t k = 0; k < x0.size(); k++) {
            xt[k] = (1 / CSR.element(k, k)) * (b[k] - dot(xk, CSR)[k] + CSR.element(k, k) * xk[k]);
        }
        xk = xt;
    }
    return xk;
}


std::vector<float> G_Z_meth(CompressedMatrix &CSR, const float tolerance, const std::vector<float> &b, const std::vector<float> &x0)
{
    std::vector<float> xk = x0;
    float sum_1 = 0, sum_2 = 0;
    while(tolerance < r_inf(CSR, xk, b)){
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