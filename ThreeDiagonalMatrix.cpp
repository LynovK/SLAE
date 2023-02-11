//
// Created by Пользователь on 10.02.2023.
//


#include <iostream>
#include <vector>
#include <array>
#include <three_diag_solver.h>

int main() { //Еще не тестил гтестами, добавлю
    std::vector<float> d = {3, 7, 9, 7, 9};
    elements<float> f = {0, 2, 1};
    elements<float> s = {1, 4, 2};
    elements<float> t = {1, 6, 2};
    elements<float> fo = {1, 4, 2};
    elements<float> fi = {4, 5, 0};
    std::vector<elements<float>> triple = {f, s, t, fo, fi};


    TDM_Faradays_analizer<float> SLAE(4, d, triple);
    SLAE.koef_counter();
    SLAE.x_counter();
    SLAE.solution();
    return 0;
}