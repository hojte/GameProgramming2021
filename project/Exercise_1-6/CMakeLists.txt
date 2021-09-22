cmake_minimum_required(VERSION 2.90)
project(Exercise_1_6)

set(CMAKE_CXX_STANDARD 14)

file(COPY test.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Exercise_1_6
        HelloSRE.cpp)

target_link_libraries(Exercise_1_6 ${all_libs})
