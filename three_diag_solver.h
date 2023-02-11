/**
 * Решаем Ax = f, где A - трехдиагональная матрица.
 *
 * Метод прогонки:
 * x(i-1) = p(i)x(i) + q(i)
 * xn = [d(n) - a(n)q(n)]/[a(n)p(n)+b(n)]
 *
 * Для первого уравнения: p1 = -c0/b0, q1 = d0/b0
 *
 * Для i-го:
 * p(i+1) = -c(i)/[a(i)p(i)+b(i)]
 * q(i+1) = [d(i) - a(i)q(i)]/[a(i)p(i)+b(i)]
 * */
#pragma once
#ifndef CLION_MATRIX_CLASS_H
#define CLION_MATRIX_CLASS_H
#include <iostream>
#include <vector>
#include <array>


template<typename T>
struct elements {
    T a = 0;
    T b = 0;
    T c = 0;
};

template<typename T>
class TDM_Faradays_analizer {
private:
    int matrix_size = 0;
    std::vector<T> d; //Столбец свободных членов
    std::vector<elements<T>> triple; //Вектор троек
    std::vector<T> p; //вектор pi
    std::vector<T> q; //вектор
    std::vector<T> x; //столбец решений
public:
    TDM_Faradays_analizer(int matrix_size, std::vector<T> d,
                          std::vector<elements<T>> triple) { //я хз как объявить это по другому
        this->matrix_size = matrix_size;                              //поэтому просто буду объявлять через конструктор
        this->d = d;
        this->triple = triple;
    }

    void koef_counter() { // первый подсчет (подсчет коэффициентов p и q)
        p.push_back(1);
        q.push_back(1);
        p.push_back(-triple[0].c / triple[0].b);
        q.push_back(d[0] / triple[0].b);
        for (int i = 1; i < matrix_size - 1; i++) {
            p.push_back(-triple[i].c / (triple[i].a * p[i] + triple[i].b));
            q.push_back((d[i] - triple[i].a * q[i]) / (triple[i].a * p[i] + triple[i].b));
        }
    }

    void x_counter() { //второй подсчет (подсчет иксов)
        x.resize(matrix_size);
        x[d.size() - 1] = (d[matrix_size - 1] - triple[matrix_size - 1].a * q[matrix_size - 1]) /
                          (triple[matrix_size - 1].a * p[matrix_size - 1] + triple[matrix_size - 1].b);
        for (int i = d.size() - 2; i >= 0; i--) {
            x[i] = p[i + 1] * x[i + 1] + q[i + 1];
        }
    }

    void solution() { //вывод решения
        for (int i = 0; i < x.size(); i++) {
            std::cout << x[i] << std::endl;
        }
    }
};



#endif //CLION_MATRIX_CLASS_H

/*
template<typename T, int size>
class three_diag_solver {
private:
    const std::vector<T> matrA; // [a, b, c] размера 3n-2
    const std::vector<T> matrf; // Столбец свободных членов
    std::vector<T> x = NULL;
public:
    three_diag_solver(std::vector<T> a, std::vector<T> b, std::vector<T> c, std::vector<T> f) {
        if (a.size() != c.size() || b.size() - a.size() != 1) {
            throw(std::exception());
        }
    }



    void solve_system() {
        std::vector<T> salv;



        this->x = salv;
    }
};
*/

/*#endif //TEST_THREE_DIAG_SOLVER_H*/
