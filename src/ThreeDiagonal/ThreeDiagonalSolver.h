#ifndef SLAE_THREEDIAGONALSOLVER_H
#define SLAE_THREEDIAGONALSOLVER_H

#include "ThreeDiagonalMatrix.h"
#include <vector>

template<typename T>
std::vector<T> solver(const ThreeDiagonalMatrix<T> &TDM, const std::vector<T>  &d) {
    std::vector<T> p;
    p.resize(TDM.size());
    p[0] = -TDM.getString(0).c/TDM.getString(0).b; // нулевое p

    std::vector<T> q;
    q.resize(TDM.size());
    q[0] = d[0]/TDM.getString(0).b;                  // нулевое q

    std::vector<T> x; x.resize(TDM.size());

    for(auto i = 0; i < TDM.size(); ++i) {             // считаем p, q
        auto z = TDM.getString(i).a*p[i] + TDM.getString(i).b;
        p[i + 1] = -TDM.getString(i).c/z;
        q[i + 1] = (d[i] - TDM.getString(i).a*q[i])/z;
    }

    auto sd = d.size();
    x[TDM.size()] = (d[sd] - TDM.getString(sd).a*q[sd])/(TDM.getString(sd).a*p[sd] + TDM.getString(sd).b);

    for(auto i = TDM.size(); i > 0; --i){
        x[i - 1] = p[i]*x[i] + q[i];                   // находим х
    }
    return x;
}

#endif //SLAE_THREEDIAGONALSOLVER_H
