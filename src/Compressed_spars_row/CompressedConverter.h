//
// Created by perseverance on 05.03.23.
//
#pragma once
#ifndef SLAE_COMPRESSEDCONVERTER_H
#define SLAE_COMPRESSEDCONVERTER_H
#include "CompressedMatrix.h"
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
void sort_me_plz(std::vector<element<T>> &matrix_){
    std::sort(matrix_.begin() + 2, matrix_.end());
}

template <typename T>
CompressedMatrix<T> represent(std::vector<element<T>> matrix_, unsigned int n, unsigned int m) noexcept{
    std::vector<T> vector_of_values;
    std::vector<unsigned int> colomn_index_vector;
    std::vector<unsigned int> counts_vector;
    std::vector<element<T>> non_zero_triple;

    for(auto i = 0; i < matrix_.size(); ++i){
        vector_of_values.push_back(matrix_[i].v);         //Получаем строку с ненулевыми элементами матрицы
        colomn_index_vector.push_back(matrix_[i].j);      //Получаем строку с номерами столбцов
        non_zero_triple.push_back(matrix_[i]);
    }

    unsigned int count = 0;
    counts_vector.push_back(0);
    for(auto k = 0; k < n; ++k){
        for(auto p = 0; p < non_zero_triple.size(); ++p){     // Вектор с количеством ненулевых элементов построчно
            if(non_zero_triple[p].i == k){
                count++;
            }
        }
        counts_vector.push_back(count);
    }

    CompressedMatrix result(vector_of_values, colomn_index_vector, counts_vector);
    return result;
}

template <typename T>
std::vector<T> dot(const std::vector<T> &X, const CompressedMatrix<T> &CSR) noexcept{
    std::vector<T> x;
    for(auto i = 0; i < CSR.get_count().size() - 1; ++i){
        unsigned int k = CSR.get_count()[i + 1] - CSR.get_count()[i];
        unsigned int b = CSR.get_count()[i];
        x.push_back(0);
        for(auto j = 0; j < k; ++j){
            x[i] += CSR.getValue()[b + j]*X[CSR.get_index()[b + j]];
        }
    }
    return x;
}

#endif //SLAE_COMPRESSEDCONVERTER_H