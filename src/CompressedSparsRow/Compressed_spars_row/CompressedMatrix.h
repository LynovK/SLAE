//
// Created by perseverance on 13.02.23.
//
// #pragma once

#ifndef SLAE_COMPRESSEDMATRIX_H
#define SLAE_COMPRESSEDMATRIX_H
#include <iostream>
#include <vector>
//#include "CompressedMatrixCont.h"


/*template <typename T>   // Тройка матрицы: строка, столбец, значение
struct element{
    unsigned int i;
    unsigned int j;
    T v;

    bool operator < (const element<T> &elem) const noexcept{ // Хочу в дальнейшем отсортировать элементы в матрицу по порядку
        if(i != elem.i) return i < elem.i;                   // Юзну std::sort
        if(i = elem.i) return j < elem.j;
    }
};*/
 // Тройка матрицы: строка, столбец, значение
struct element{
    unsigned int i;
    unsigned int j;
    float v;

    bool operator < (const element &elem) noexcept{ // Хочу в дальнейшем отсортировать элементы в матрицу по порядку
        if(i != elem.i) return i < elem.i;          // Юзну std::sort
        if(i = elem.i) return j < elem.j;
    }
};
/*
template<typename T>
class CompressedMatrix{
private:
    std::vector<T> vector_of_values_;
    std::vector<unsigned int> colomn_index_vector_;
    std::vector<unsigned int> counts_vector_;
public:
    CompressedMatrix(std::vector<T> vector_of_values, const std::vector<unsigned int> &colomn_index_vector, const std::vector<unsigned int> &counts_vector;) noexcept{
        vector_of_values_ = vector_of_values;
        colomn_index_vector_ = colomn_index_vector;
        counts_vector_ = counts_vector;
    }
};*/


class CompressedMatrix{
private:
    std::vector<float> vector_of_values_;
    std::vector<unsigned int> colomn_index_vector_;
    std::vector<unsigned int> counts_vector_;
public:
    CompressedMatrix(std::vector<float> vector_of_values, const std::vector<unsigned int> &colomn_index_vector, const std::vector<unsigned int> &counts_vector) noexcept{
        vector_of_values_ = vector_of_values;
        colomn_index_vector_ = colomn_index_vector;
        counts_vector_ = counts_vector;
    }
    std::vector<float> getValue(){
        return vector_of_values_;
    }
    std::vector<unsigned int> get_index(){
        return colomn_index_vector_;
    }
    std::vector<unsigned int> get_count(){
        return counts_vector_;
    }

    float element(const unsigned long row_coor, const unsigned long col_coor) const{
        if(col_coor > *std::max_element(colomn_index_vector_.begin(), colomn_index_vector_.end()) or row_coor > counts_vector_.size() - 1){
            return 0;
        }
        else{
            unsigned long needed = counts_vector_[row_coor], in_row = counts_vector_[row_coor + 1] - counts_vector_[row_coor];
            for(unsigned long i = needed; i < needed + in_row; i++){
                if(colomn_index_vector_[i] == col_coor){
                    return vector_of_values_[i];
                }
            }
            return 0;
        }
    }
};
#endif //SLAE_COMPRESSEDMATRIX_H