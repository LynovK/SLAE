cmake_minimum_required(VERSION 3.0.0)
project(slae)
#[[//add_compile_definitions(-Wall -Werror)]]
set(CMAKE_CXX_STANDART 17)

add_subdirectory(src)
add_subdirectory(gtest)

#[[
//target_link_libraries(cmake_demo fmt::fmt)]]
