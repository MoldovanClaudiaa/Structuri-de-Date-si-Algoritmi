cmake_minimum_required(VERSION 3.27)
project(PriorityQueueDSA)

set(CMAKE_CXX_STANDARD 17)

add_executable(PriorityQueueDSA main.cpp
        PriorityQueue.cpp
        PriorityQueue.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h)
