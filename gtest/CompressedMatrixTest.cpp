//
// Created by perseverance on 05.03.23.
//
#include <gtest/gtest.h>
#include "../src/Compressed_spars_row/CompressedMatrixRepresent.h"


TEST(CompressedTest, firstTest){
    std::vector<element> matrix = {{0,0,1}, {0,1,2}, {0,2,0},
                                        {1,0,0}, {1,1,1}, {1,2,3},
                                        {2,0,4}, {2,1,0}, {2,2,2}};

    CompressedMatrix res = represent(matrix, 3, 3);


    std::vector<float> vector_of_values = {1, 2, 1, 3, 4, 2};
    std::vector<unsigned int> colomn_index_vector = {0, 1, 1, 2, 0, 2};
    std::vector<unsigned int> counts_vector = {0, 2, 4, 6};
    CompressedMatrix testMatr(vector_of_values, colomn_index_vector, counts_vector);

    for (int i = 0; i < vector_of_values.size(); i++){
        ASSERT_NEAR(vector_of_values[i], res.getValue()[i], 0.001);
        ASSERT_NEAR(colomn_index_vector[i], res.get_index()[i], 0.001);
    }
    for(int i = 0; i < counts_vector.size(); ++i){
        ASSERT_NEAR(counts_vector[i], res.get_count()[i], 0.001);
    }
}

TEST(CompressedTest, SecondTest){
    std::vector<element> matrix = {{0,0,5}, {0,1,0}, {0,2,6},
                                   {1,0,1}, {1,1,2}, {1,2,0},
                                   {2,0,0}, {2,1,0}, {2,2,1}};

    CompressedMatrix res = represent(matrix, 3, 3);


    std::vector<float> vector_of_values = {5, 6, 1, 2, 1};
    std::vector<unsigned int> colomn_index_vector = {0, 2, 0, 1, 2};
    std::vector<unsigned int> counts_vector = {0, 2, 4, 5};
    CompressedMatrix testMatr(vector_of_values, colomn_index_vector, counts_vector);

    for (int i = 0; i < vector_of_values.size(); i++){
        ASSERT_NEAR(vector_of_values[i], res.getValue()[i], 0.001);
        ASSERT_NEAR(colomn_index_vector[i], res.get_index()[i], 0.001);
    }
    for(int i = 0; i < counts_vector.size(); ++i){
        ASSERT_NEAR(counts_vector[i], res.get_count()[i], 0.001);
    }
}



TEST(CompressedTest, ThirdTest){
    std::vector<element> matrix = {{0,0,15}, {0,1,1.2}, {0,2,0}, {0,3,0}, {0,4,1},
                                   {1,0,0}, {1,1,0}, {1,2,0}, {1,3,1}, {1,4,2},
                                   {2,0,0}, {2,1,3}, {2,2,4}, {2, 3, 0}, {2,4,7},
                                   {3,0,1}, {3,1,2}, {3,2,0}, {3,3,1}, {3,4,0},
                                   {4,0,5.8}, {4,1,3}, {4,2,0}, {4,3,0}, {4,4,9}
    };

    CompressedMatrix res = represent(matrix, 5, 5);


    std::vector<float> vector_of_values = {15, 1.2, 1, 1, 2, 3, 4, 7, 1, 2, 1, 5.8, 3, 9};
    std::vector<unsigned int> colomn_index_vector = {0, 1, 4, 3, 4, 1, 2, 4, 0, 1, 3, 0, 1, 4};
    std::vector<unsigned int> counts_vector = {0, 3, 5, 8, 11, 14};
    CompressedMatrix testMatr(vector_of_values, colomn_index_vector, counts_vector);

    for (int i = 0; i < vector_of_values.size(); i++){
        ASSERT_NEAR(vector_of_values[i], res.getValue()[i], 0.001);
        ASSERT_NEAR(colomn_index_vector[i], res.get_index()[i], 0.001);
    }
    for(int i = 0; i < counts_vector.size(); ++i){
        ASSERT_NEAR(counts_vector[i], res.get_count()[i], 0.001);
    }
}


TEST(CompressedTest, FirstSolveTest){
    std::vector<element> matrix = {{0,0,1}, {0,1,2}, {0,2,0},
                                   {1,0,0}, {1,1,4}, {1,2,0},
                                   {2,0,0}, {2,1,2}, {2,2,6}};

    CompressedMatrix res = represent(matrix, 3, 3);


    std::vector<float> vector_of_values = {1, 2, 1, 3, 4, 2};
    std::vector<unsigned int> colomn_index_vector = {0, 1, 1, 2, 0, 2};
    std::vector<unsigned int> counts_vector = {0, 2, 4, 6};
    CompressedMatrix testMatr(vector_of_values, colomn_index_vector, counts_vector);

    std::vector<float> x = {1, 3, 5};
    std::vector<float> d = {7, 12, 36};
    std::vector<float> solve;
    solve = dot(x, res);
    for(auto i = 0; i < solve.size(); ++i){
        ASSERT_NEAR(d[i], solve[i], 0.001);
    }
}