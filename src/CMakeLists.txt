

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

##### CPPS GO HERE!!!!
add_library(project_lib
        cpp/inventory.cpp
        cpp/plant.cpp
        cpp/employee.cpp
        cpp/product.cpp
        cpp/command.cpp
        cpp/order.cpp

        # ADD CPPS HERE !!!!!!!
        ##############
        ##############
)
#### CPPS GO HERE!!!

target_include_directories(project_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

## KEEP THIS COMMENTED UNTIL WE ADD AN ACTUAL MAIN.CPP !!!
# add_executable(COS214_DihsignPatterns cpp/main.cpp)
# target_link_libraries(COS214_DihsignPatterns PRIVATE project_lib)


file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

add_executable(project_tests
        ${TEST_SOURCES}
        # (You don’t need to list tests/inventory_test.cpp again if it’s matched by the glob)
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
