cmake_minimum_required(VERSION 3.27)
project(SparseMatrixDSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(SparseMatrixDSA main.cpp
        Matrix.h
        Matrix.cpp
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h
)
