cmake_minimum_required(VERSION 3.16)
project(COS214_DihsignPatterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(project_lib STATIC
    src/cpp/command.cpp
    src/cpp/Customer.cpp
    src/cpp/employee.cpp
    src/cpp/frontDesk.cpp
    src/cpp/garden.cpp
    src/cpp/inventory.cpp
    src/cpp/iterator.cpp
    src/cpp/order.cpp
    src/cpp/plant.cpp
    src/cpp/plantDatabase.cpp
    src/cpp/product.cpp
    src/cpp/simulator.cpp
)

target_include_directories(project_lib PUBLIC src/headers)

add_executable(project_tests
    src/tests/testingmain.cpp
)

target_link_libraries(project_tests PRIVATE project_lib)
