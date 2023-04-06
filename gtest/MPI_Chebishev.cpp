//
// Created by perseverance on 19.03.2023.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/Iteration_methods/ChebishevMPI.h"

TEST(task_4, task_test_twotwo) {
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
    std::vector<double> tau = Chebishev_solver<double>(16, 4, 1, 10);

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

/*    for (auto i: mpi) {
        std::cout << i << std::endl;
    }*/
    for(int i = 0; i < solve.size(); ++i){
        ASSERT_NEAR(mpi[i], solve[i], 0.001);
    }
}

/*
TEST(MPI_Chebishev, MPI_Cheb_first){
    std::vector<element<double>> matrix_CSR = {
            {0, 0, 12}, {0, 1, 17}, {0,2, 3}, {1,0,17}, {1,1, 15825}, {1,2,28}, {2,0,3}, {2,1, 28}, {2,2,238}
    };
    sort_me_plz(matrix_CSR);

    CompressedMatrix<double> CSR(matrix_CSR, 3, 3);

    std::vector<double> b = {1, 2, 3};
    std::vector<double> x0 = {1, 1, 1};

    std::vector<double> tau = {1, 2, 3};
    double tolerance1 = 1e-12;
    double tolerance2 = 1e-15;
    std::vector<double> mpi = MPI_chebishev(CSR, tolerance1, b, x0, tau);

    for (auto i : mpi)
    {
        std::cout << i << std::endl;
    }
}*/
