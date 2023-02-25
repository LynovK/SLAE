//
// Created by perseverance on 13.02.23.
//
// #pragma once

#ifndef SLAE_COMPRESSEDSPARSROW_H
#define SLAE_COMPRESSEDSPARSROW_H
#include <iostream>
#include <vector>


template <typename T>   // Тройка векторов, хранящая матрицу
struct Representation{
    std::vector<T> values;
    std::vector<unsigned int> colomn_number;
    std::vector<unsigned int> not_zero_amount;
};

template <typename T>   // Тройка матрицы: строка, столбец, значение
struct element{
    T i;
    T j;
    T v;

    bool operator < (const element<T> &elem) const noexcept{ // Хочу в дальнейшем отсортировать элементы в матрицу по порядку
        if(i != elem.i) return i < elem.i;                   // Юзну std::sort
        if(i = elem.i) return j < elem.j;
    }
};


template <typename T>   // Сам контейнер матрицы
class CompressedSparsRow {
private:
    unsigned int m_, n_; // Кол-во строк, столбцов
    std::vector<element<T>> matrix_;
public:
    CompressedSparsRow(const std::vector<element<T>> & matrix,const int m, const int n) noexcept:m_(m), n_(n), matrix_(matrix){}

    unsigned int get_colomn_amount(){
        return m_;
    }
    unsigned int get_row_amount(){
        return n_;
    }
    const element<T>& getString() const  noexcept {
        return matrix_;
    }
    const element<T>& getString(unsigned int i) const  noexcept {
        return matrix_[i];
    }
};

#endif //SLAE_COMPRESSEDSPARSROW_H