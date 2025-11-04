add_library(project_lib_obj OBJECT
    cpp/command.cpp
    cpp/Customer.cpp
    cpp/employee.cpp
    cpp/frontDesk.cpp
    cpp/garden.cpp
    cpp/inventory.cpp
    cpp/iterator.cpp
    cpp/order.cpp
    cpp/plant.cpp
    cpp/plantDatabase.cpp
    cpp/product.cpp
    cpp/simulator.cpp
)

target_include_directories(project_lib_obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

add_library(project_lib STATIC $<TARGET_OBJECTS:project_lib_obj>)

add_executable(project_tests
    tests/testingmain.cpp
)

set_target_properties(project_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(project_tests PRIVATE project_lib)
