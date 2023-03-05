//
// Created by perseverance on 04.03.23.
//
#pragma once
#ifndef SLAE_COMPRESSEDCONVERTERMATRIXWITHZEROS_H
#define SLAE_COMPRESSEDCONVERTERMATRIXWITHZEROS_H
#include "CompressedMatrix.h"
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
CompressedMatrix<T> represent_with_zeros(const std::vector<element<T>> &matrix_, unsigned int n, unsigned int m) noexcept{
    std::vector<T> vector_of_values;
    std::vector<unsigned int> colomn_index_vector;
    std::vector<unsigned int> counts_vector;
    std::vector<element<T>> non_zero_triple;

    for(auto i = 0; i < n*m; ++i){
        if(matrix_[i].v != 0){
            vector_of_values.push_back(matrix_[i].v);         //Получаем строку с ненулевыми элементами матрицы
            colomn_index_vector.push_back(matrix_[i].j);      //Получаем строку с номерами столбцов
            non_zero_triple.push_back(matrix_[i]);
        }
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

#endif //SLAE_COMPRESSEDCONVERTERMATRIXWITHZEROS_H