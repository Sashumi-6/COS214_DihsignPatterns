cmake_minimum_required(VERSION 4.0)
project(COS214_DihsignPatterns)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(project_lib
        cpp/inventory.cpp
        #ADD CPPS HERE !!!!!!!
        ##############
        ##############
)

target_include_directories(project_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

## WE WILL UNCOMMENT THIS ONCE WE HAVE A MAIN!!!
# add_executable(COS214_DihsignPatterns main.cpp)
# target_link_libraries(COS214_DihsignPatterns PRIVATE project_lib)

include(CTest)
enable_testing()

##TESTS GO IN THE TESTS FOLDER
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_executable(project_tests
        ${TEST_SOURCES}
        tests/inventory_test.cpp
)

target_link_libraries(project_tests
        PRIVATE
        project_lib
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
)

include(GoogleTest)
gtest_discover_tests(project_tests)



