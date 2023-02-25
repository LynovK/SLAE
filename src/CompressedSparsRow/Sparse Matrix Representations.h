//
// Created by perseverance on 23.02.23.
//

#ifndef SLAE_COMPRESSEDSPARSROWMAKER_H
#define SLAE_COMPRESSEDSPARSROWMAKER_H
#include <algorithm>
#include <vector>
#include "CompressedSparsRow.h"



template<typename T>
Representation<T> represent(const CompressedSparsRow<T> &CSR){
    std::vector<T> vector_of_values;
    std::vector<unsigned int> colomn_index_vector;
    std::vector<unsigned int> counts_vector;
    std::vector<element<T>> non_zero_triple;

    std::sort(CSR.getString().begin(), CSR.getString().end());
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
}


#endif //SLAE_COMPRESSEDSPARSROWMAKER_H