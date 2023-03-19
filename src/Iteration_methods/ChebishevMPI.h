//
// Created by perseverance on 16.03.23.
//

#ifndef SLAE_CHEBISHEVMPI_H
#define SLAE_CHEBISHEVMPI_H

#define M_PI 3.14159265358979323846

#include <iostream>
#include "../Iteration_methods/MPI.h"

#define _USE_MATH_DEFINES

template<typename T>
std::vector<T> Chebishev_solver(unsigned int n, T lambda_min, T lambda_max) {
    std::vector<T> z;
    z.resize(n);
    std::vector<T> betta;
    betta.resize(n);
    double pi = M_PI;

    //Корни полинома Чебышева
    betta[0] = sin(pi / (2 * n));
    T sin_alpha = sin(pi / n);
    T cos_alpha = cos(pi / n);
    z[0] = cos(pi / (2 * n));
    z[1] = z[0] * cos_alpha - betta[0] * sin_alpha;

    for (auto i = 1; i < n; ++i) {
        betta[i] = betta[i - 1] * cos_alpha + z[i - 1] * sin_alpha;
        z[i + 1] = z[i] * cos_alpha - betta[i] * sin_alpha;
    }

    //Афинное преобразование
    for (auto i = 0; i < z.size(); ++i) {
        z[i] = (lambda_min + lambda_max) / 2 + (lambda_max - lambda_min) * z[i] / 2;
    }

    //Переупорядоченный массив индексов
    std::vector<unsigned int> indexes = {0, 1};
    std::vector<unsigned int> ind;
    ind.resize(n);
    unsigned int r = std::log(n) / std::log(2);

    for (auto i = 1; i < r + 1; ++i) {
        indexes.resize(2 ^ (i + 1));
        for (auto j = 0; j < indexes.size(); ++i) {
            ind[2 * j] = indexes[j];
            ind[2 * j + 1] = 2 ^ (i + 1) - 1 - indexes[j];
            indexes = ind;
        }
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