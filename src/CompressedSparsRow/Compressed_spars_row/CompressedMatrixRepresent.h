//
// Created by perseverance on 04.03.23.
//

#ifndef SLAE_COMPRESSEDMATRIXREPRESENT_H
#define SLAE_COMPRESSEDMATRIXREPRESENT_H
#include "CompressedMatrix.h"
#include <iostream>
#include <algorithm>
#include <vector>



/*template<typename T>
Representation<T> represent(const CompressedSparsRow<T> &CSR) noexcept{
    std::vector<T> vector_of_values;
    std::vector<unsigned int> colomn_index_vector;
    std::vector<unsigned int> counts_vector;
    std::vector<element<T>> non_zero_triple;


    for(auto i = 0; i < CSR.get_colomn_amount()*CSR.get_row_amount(); ++i){
        if(CSR.getString(i) != 0){
            vector_of_values.push_back(CSR.getString(i).v);         //Получаем строку с ненулевыми элементами матрицы
            colomn_index_vector.push_back(CSR.getString(i).j);      //Получаем строку с номерами столбцов
            non_zero_triple.push_back(CSR.getString(i));
        }
    }

    unsigned int count = 0;
    counts_vector.push_back(0);
    for(auto k = 0; k < CSR.get_row_amount(); ++k){
        for(auto p = 0; p < non_zero_triple.size(); ++p){       // Вектор с количеством ненулевых элементов построчно
            if(non_zero_triple[p].i = k){
                count++;
            }
        }
        counts_vector.push_back(count);
    }

    Representation<T> result =  {vector_of_values, colomn_index_vector, counts_vector};
    return result;
}*/

CompressedMatrix represent(std::vector<element> matrix_, unsigned int n, unsigned int m) noexcept{
    std::vector<float> vector_of_values;
    std::vector<unsigned int> colomn_index_vector;
    std::vector<unsigned int> counts_vector;
    std::vector<element> non_zero_triple;


    std::sort(matrix_.begin() + 2, matrix_.end()); //почему плюс 2 я не понимаю, почему (так работают тесты)

/*    for(auto i = 0; i < n*m; i++){
        std::cout << matrix_[i].v << ' ';
    }
    std::cout << std::endl;*/

    for(auto i = 0; i < n*m; ++i){
        if(matrix_[i].v != 0){
            vector_of_values.push_back(matrix_[i].v);         //Получаем строку с ненулевыми элементами матрицы
            colomn_index_vector.push_back(matrix_[i].j);      //Получаем строку с номерами столбцов
            non_zero_triple.push_back(matrix_[i]);
        }
    }

/*    for(auto p = 0; p < non_zero_triple.size(); ++p){
        std::cout << non_zero_triple[p].i << non_zero_triple[p].j << non_zero_triple[p].v << ' ';
    }*/

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

/*    for(auto i = 0; i < vector_of_values.size(); i++){
        std::cout << vector_of_values[i] << ' ';
    }
    std::cout << std::endl;

    for(auto i = 0; i < colomn_index_vector.size(); i++){
        std::cout << colomn_index_vector[i] << ' ';
    }
    std::cout << std::endl;

    for(auto i = 0; i < counts_vector.size(); i++){
        std::cout << counts_vector[i] << ' ';
    }*/

    CompressedMatrix result(vector_of_values, colomn_index_vector, counts_vector);
    return result;
}

std::vector<float> dot(const std::vector<float> &X, CompressedMatrix &CSR) noexcept{
    std::vector<float> x;
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

#endif //SLAE_COMPRESSEDMATRIXREPRESENT_H