//
// Created by perseverance on 13.02.23.
//
#pragma once
#ifndef SLAE_COMPRESSEDMATRIX_H
#define SLAE_COMPRESSEDMATRIX_H
#include <iostream>
#include <vector>


struct Coords
{
    Coords(long x, long y)
    {
        col = x;
        row = y;
    }

    friend bool operator==(const Coords pair1, const Coords pair2) { return (pair1.col == pair2.col and pair1.row == pair2.row); }
    friend bool operator<(const Coords pair1, const Coords pair2)
    {
        if (pair1.col == pair2.col)
            return pair1.row < pair2.row;
        return pair1.col < pair2.col;
    }

    long col = 0, row = 0;
};

template <typename T>
struct element{
    unsigned int i;
    unsigned int j;
    T v;

    bool operator < (const element &elem) noexcept{ // Хочу в дальнейшем отсортировать элементы в матрицу по порядку
        if(i != elem.i) return i < elem.i;          // Юзну std::sort
        if(i = elem.i) return j < elem.j;
    }
};

template <typename T>
class CompressedMatrix{
private:
    std::vector<T> vector_of_values_;
    std::vector<unsigned int> colomn_index_vector_;
    std::vector<unsigned int> counts_vector_;
public:
    CompressedMatrix(std::vector<T> vector_of_values, const std::vector<unsigned int> &colomn_index_vector, const std::vector<unsigned int> &counts_vector) noexcept{
        vector_of_values_ = vector_of_values;
        colomn_index_vector_ = colomn_index_vector;
        counts_vector_ = counts_vector;
    }
    std::vector<T> getValue() const noexcept{
        return vector_of_values_;
    }
    std::vector<unsigned int> get_index() const noexcept{
        return colomn_index_vector_;
    }
    std::vector<unsigned int> get_count() const noexcept{
        return counts_vector_;
    }
    T element(const unsigned long row_coor, const unsigned long col_coor) const{ //взятие по индексу
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