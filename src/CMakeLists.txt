cmake_minimum_required(VERSION 3.16)
project(COS214_DihsignPatterns)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ===============================
#        PROJECT LIBRARY
# ===============================
add_library(project_lib
    cpp/command.cpp
    cpp/product.cpp
    cpp/employee.cpp
    cpp/inventory.cpp
    cpp/order.cpp
    cpp/plant.cpp
)

target_include_directories(project_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# ===============================
#        MAIN EXECUTABLE
# ===============================
# Uncomment or add this section to build your program executable
# add_executable(COS214_DihsignPatterns
#   cpp/main.cpp       # Replace with your actual main file
# )
# target_link_libraries(COS214_DihsignPatterns
#     PRIVATE
#     project_lib
# )

# ===============================
#        UNIT TESTS
# ===============================
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_executable(project_tests
    ${TEST_SOURCES}
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

