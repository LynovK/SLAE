//
// Created by perseverance on 06.04.2023.
//

#ifndef SLAE_OPERATORS_H
#define SLAE_OPERATORS_H


#include <iostream>
#include <vector>

template<typename T>
struct basis {
    std::vector<T> I;// = {1, 0, 0};
    std::vector<T> J;// = {0, 1, 0};
    std::vector<T> K;// = {0, 0, 1};
};

template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> c(a.size());
    for (auto i = 0; i < a.size(); ++i) {
        c[i] = a[i] - b[i];
    }
    return c;
}

//Works
template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<T> c(a.size());
    for (auto i = 0; i < c.size(); ++i) {
        c[i] = a[i] + b[i];
    }
    return c;
}

//Works
template<typename T>
std::vector<T> operator*(const T &a, const std::vector<T> v) noexcept {
    std::vector<T> result(v.size());
    for (auto i = 0; i < v.size(); ++i) {
        result[i] = a * v[i];
    }
    return result;
}

//Works
template<typename T>
T scal_dot(const std::vector<T> &a, const std::vector<T> &b) noexcept {
    T scal = 0;
    if (a.size() == b.size()) {
        for (auto i = 0; i < a.size(); ++i) {
            scal += a[i] * b[i];
        }
    } else { std::cout << "Different size of vectors in scal dot" << std::endl; }
    return scal;
}

// Works
template<typename T>
std::vector<T> vect_dot(const std::vector<T> &a, const std::vector<T> &b, const basis<T> &basis) noexcept {
    std::vector<T> vect(a.size());
    vect = (a[1] * b[2] - a[2] * b[1]) * basis.I + (a[2] * b[0] - a[0] * b[2]) * basis.J +
           (a[0] * b[1] - b[0] * a[1]) * basis.K;
    return vect;
}

template<typename T>
std::vector<T> vect_dot(const std::vector<T> &a, const std::vector<T> &b) noexcept {
    std::vector<T> vect(a.size());
    vect[0] = (a[1] * b[2] - a[2] * b[1]);
    vect[1] = (a[2] * b[0] - a[0] * b[2]);
    vect[2] = (a[0] * b[1] - b[0] * a[1]);
    return vect;
}

//Works
template<typename T>
T norm(const std::vector<T> &a) {
    T norm = 0;
    for (auto i: a) {
        norm += pow(i, 2);
    }
    return pow(norm, 0.5);
}

#endif //SLAE_OPERATORS_H
