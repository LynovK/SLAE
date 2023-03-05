//
// Created by perseverance on 05.03.23.
//

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "../src/Compressed_spars_row/CompressedMatrix.h"
#include "../src/Compressed_spars_row/CompressedConverter.h"
#include "../src/Compressed_spars_row/MPI.h"


TEST(task_4, task_test)
{

    std::vector<element<float>> matrix_CSR = {
            {0, 0, 12}, {0, 1, 17}, {0,2, 3}, {1,0,17}, {1,1, 15825}, {1,2,28}, {2,0,3}, {2,1, 28}, {2,2,238}
    };
    sort_me_plz(matrix_CSR);
    CompressedMatrix<float> res = represent(matrix_CSR, 3, 3);

    std::vector<float> b = {1, 2, 3};
    std::vector<float> x0 = {1, 1, 1};

    float tau = 0.0001;
    float tolerance = 1e-5;
    std::vector<float> mpi = MPI(res, tolerance, b, x0, tau);

    for (auto i : mpi)
    {
        std::cout << i << std::endl;
    }
    std::vector<float> gz = G_Z(res, tolerance, b, x0);
    std::vector<float> jac = Jacoby(res, tolerance, b, x0);
    //
    for (long i = 0; i < 3; i ++)
    {
        ASSERT_NEAR(mpi[i], gz[i], 1e-13);
    }
    for (long i = 0; i < 3; i ++)
    {
        ASSERT_NEAR(mpi[i], jac[i], 1e-13);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}