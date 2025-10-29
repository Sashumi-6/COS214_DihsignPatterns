cmake_minimum_required(VERSION 4.0)
project(COS214_DihsignPatterns)

set(CMAKE_CXX_STANDARD 11)

include_directories(headers)

add_executable(COS214_DihsignPatterns
        cpp/inventory.cpp
        headers/command.h
        headers/decorator.h
        headers/employee.h
        headers/frontDesk.h
        headers/garden.h
        headers/inventory.h
        headers/iterator.h
        headers/observer.h
        headers/order.h
        headers/plant.h
        headers/productBuilder.h)
