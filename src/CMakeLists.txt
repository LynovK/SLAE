#file(GLOB_RECURSE all *.cpp *.h)
#add_library(slae STATIC ${all} "Compressed_spars_row/CSR.cpp" Tridiagonal/ThreeDiagonalSolver.h ../gtest/ThreeDiagTest.cpp)
#
#add_library(slae STATIC ${all} Tridiagonal/ThreeDiagonalSolver.h)

file(GLOB_RECURSE source *.h *.cpp)
add_library(slae INTERFACE ${source} Iteration_methods/MPI.h Compressed_spars_row/CompressedSorting.h Iteration_methods/ChebishevMPI.h)
