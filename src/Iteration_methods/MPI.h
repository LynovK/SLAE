//
// Created by perseverance on 05.03.23.
//

#pragma once
#ifndef SLAE_MPI_H
#define SLAE_MPI_H

#include <cmath>
#include <fstream>
#include "../Compressed_spars_row/CompressedMatrix.h"
#include "../Compressed_spars_row/CompressedSorting.h"

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

template<typename T>
T get_r(const CompressedMatrix<T> &CSR, const std::vector<T> &x, const std::vector<T> &b) noexcept {
    T r = 0;
    for (size_t j = 0; j < b.size(); ++j) {
        r += (b[j] - CSR.dot(x)[j]) * (b[j] - CSR.dot(x)[j]); //евклидова длина стобца невязки
    }
    return r;
}

template<typename T>
T r_inf(CompressedMatrix<double> CSR, const std::vector<T> &x, const std::vector<T> &b) noexcept {
    T r = 0;
    for (size_t j = 0; j < b.size(); ++j) { //size_t = unsigned int
        if (fabs(b[j] - CSR.dot(x)[j]) > r)
            r = fabs(b[j] - CSR.dot(x)[j]);
    }
    return r;
}

template<typename T>
std::vector<T> MPI(CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b,
                   const std::vector<T> &x_0, const T tau) noexcept {
    unsigned int count = 0;
    std::vector<T> result = (const std::vector<T> &) x_0, r = CSR.dot(result) - b; //Нач приближение и невязка
    while (tolerance < r_inf<T>(CSR, result, b)) {
        count++;
        result = result - r * tau;
        r = CSR.dot(result) - b;
    }
    std::cout << count << std::endl;
    return result;
}

template<typename T>
std::vector<T> MPI_chebishev(CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b,
                             const std::vector<T> &x_0, const std::vector<T> &tau) noexcept {
    unsigned int count = 0;
    std::vector<T> result = (const std::vector<T> &) x_0, r = CSR.dot(result) - b; //Нач приближение и невязка
    while (tolerance < r_inf<T>(CSR, result, b)) {
        count++;
        result = result - r * tau;
        r = CSR.dot(result) - b;
    }
    std::cout << count << std::endl;
    return result;
}

/*template <typename T>
std::vector<T> Jacoby(CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b,
                               const std::vector<T> &x0) {
    std::vector<T> xk = x0, xt(x0.size(), 0);
    unsigned long long count = 0;
    while (tolerance < r_inf<T>(CSR, xk, b)) {
        count++;
        for (size_t k = 0; k < x0.size(); k++) {
            xt[k] = (1 / CSR.element(k, k)) * (b[k] - CSR.dot(xk)[k] + CSR.element(k, k) * xk[k]);
        }
        xk = xt;
        *//*std::ofstream fout("/home/perseverance/jacoby_res.txt", std::ios::app);
        fout << r_inf<T>(CSR, xk, b) << " " << count << std::endl;
        fout.close();*//*
    }
    return xk;
}*/

/*template <typename T>
std::vector<T> G_Z(const CompressedMatrix<T> &CSR, const T tolerance, const std::vector<T> &b, const std::vector<T> &x0)
{
    std::vector<T> xk = x0;
    unsigned long long count = 0;
    T sum_1 = 0, sum_2 = 0;
    while(tolerance < r_inf<T>(CSR, xk, b)){
        count++;
        for(long long k = 0; k < x0.size(); k ++){
            for(long long i = 0; i < k; i ++)
                sum_1 += CSR.element(k, i) * xk[i];
            for(long long i = k + 1; i < x0.size(); i ++)
                sum_2 += CSR.element(k, i) * xk[i];
            xk[k] = (1 / CSR.element(k, k)) * (b[k] - sum_1 - sum_2);
            sum_1 = 0;
            sum_2 = 0;
        }
        *//*std::ofstream fout("/home/perseverance/gz_res.txt", std::ios::app);
        fout << r_inf<T>(CSR, xk, b) << " " << count << std::endl;
        fout.close();*//*
    }
    return xk;
}*/

#endif //SLAE_MPI_H