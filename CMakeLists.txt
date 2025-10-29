cmake_minimum_required(VERSION 4.0)


project(COS214_DihsignPatterns LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(CTest)
enable_testing()

add_subdirectory(src)
