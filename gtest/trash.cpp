//
// Created by perseverance on 08.04.2023.
//

#include <gtest/gtest.h>
#include "../src/Vector.h"

TEST(trash, first_Vector_test){
    Vector<double> a(std::vector<double> {1, 2, 3});
    Vector<double> b( std::vector<double> {0, 1, 2, 3});

    double scal = a.scal_dot(b);
}