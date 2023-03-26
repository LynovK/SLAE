//
// Created by perseverance on 05.03.23.
//

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "../src/Compressed_spars_row/CompressedMatrix.h"
#include "../src/Compressed_spars_row/CompressedSorting.h"
#include "../src/Iteration_methods/MPI.h"
#include "../src/Iteration_methods/ChebishevMPI.h"


TEST(task_4, task_test) {
    std::vector<element<double>> matrix_CSR = {
            {0, 0, 12},
            {0, 1, 17},
            {0, 2, 3},
            {1, 0, 17},
            {1, 1, 15825},
            {1, 2, 28},
            {2, 0, 3},
            {2, 1, 28},
            {2, 2, 238}
    };
    sort_me_plz(matrix_CSR);
    CompressedMatrix<double> res(matrix_CSR, 3, 3);

    std::vector<double> b = {1, 2, 3};
    std::vector<double> x0 = {1, 1, 1};
    double tau = 0.0001;
    double tolerance1 = 1e-12;
    double tolerance2 = 1e-15;
    std::vector<double> mpi = MPI(res, tolerance1, b, x0, tau);

    for (auto i: mpi) {
        std::cout << i << std::endl;
    }
/*    std::vector<double> gz = G_Z(res, tolerance2, b, x0);
    std::vector<double> jac = Jacoby(res, tolerance2, b, x0);
    //
    for (long i = 0; i < 3; i ++)
    {
        ASSERT_NEAR(mpi[i], gz[i], 1e-13);
    }
    for (long i = 0; i < 3; i ++)
    {
        ASSERT_NEAR(mpi[i], jac[i], 1e-13);
    }*/
}

TEST(task_4, task_test_two) {
    std::vector<element<double>> matrix_CSR = {
            {0, 0, 1},
            {1, 1, 2},
            {2, 2, 3},
            {3, 3, 4},
            {4, 4, 5},
            {5, 5, 6},
            {6, 6, 7},
            {7, 7, 8},
            {8, 8, 9},
            {9, 9, 10}
    };
    sort_me_plz(matrix_CSR);
    CompressedMatrix<double> res(matrix_CSR, 10, 10);
    std::vector<double> tau = Chebishev_solver<double>(16448, 14, 1, 10);

    std::vector<double> solve = {5,
                                 1,
                                 0.667,
                                 1.75,
                                 1.6,
                                 7.16667,
                                 0.2857,
                                 0.125,
                                 0.556,
                                 0.6};

    std::vector<double> b = {5, 2, 2, 7, 8, 43, 2, 1, 5, 6};
    std::vector<double> x0 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    double tolerance1 = 1e-12;
    double tolerance2 = 1e-15;
    std::vector<double> mpi = MPI_chebishev(res, tolerance1, b, x0, tau);

    for (auto i: mpi) {
        std::cout << i << std::endl;
    }
}