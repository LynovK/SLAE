//
// Created by perseverance on 16.03.23.
//

#ifndef SLAE_CHEBISHEVMPI_H
#define SLAE_CHEBISHEVMPI_H

#include <iostream>
#include "../Iteration_methods/MPI.h"

#define M_PI 3.14159265358979323846


template<typename T>
std::vector<T> Chebishev_solver(unsigned int n, unsigned int r, T lambda_min, T lambda_max) {
    std::vector<T> z;
    z.resize(n);
    std::vector<T> betta;
    betta.resize(n);
    const double pi = M_PI;

    //Корни полинома Чебышева
    betta[0] = sin(pi / (2 * n));
    T sin_alpha = sin(pi / n);
    T cos_alpha = cos(pi / n);
    z[0] = cos(pi / (2 * n));
    //z[1] = z[0] * cos_alpha - betta[0] * sin_alpha;

    for (auto i = 1; i < n; ++i) {
        betta[i] = (betta[i - 1] * cos_alpha + z[i - 1] * sin_alpha);
    }

    for (auto i = 1; i < n; ++i){
        z[i] = z[i - 1] * cos_alpha - betta[i - 1] * sin_alpha;

    }

    //Афинное преобразование
    for (auto i = 0; i < z.size(); ++i) {
        z[i] = (lambda_min + lambda_max) / 2 + (lambda_max - lambda_min) * z[i] / 2;
    }

    //Переупорядоченный массив индексов
    std::vector<unsigned int> indexes = {0, 1};
    std::vector<unsigned int> ind;
    ind.resize(n);
    indexes.resize(n);
    unsigned int point = 4;
    for (auto i = 1; i < r; ++i) {
        for (auto j = 0; j < point % 2; ++j) {
            ind[2 * j] = indexes[j];
            ind[2 * j + 1] = point - 1 - indexes[j];
            indexes = ind;
        }
        point *= 2;
    }

    //Вектор тау
    std::vector<T> tau;
    tau.resize(n);
    for (auto i = 0; i < z.size(); ++i) {
        tau[i] = z[indexes[i]];
    }
    return tau;
}

#endif //SLAE_CHEBISHEVMPI_H