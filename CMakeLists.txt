cmake_minimum_required(VERSION 3.19)

project(simulator)

file(GLOB_RECURSE includes include/*.hpp)

add_executable(simulator ${includes} src/main.cpp)
target_include_directories(simulator PRIVATE include)
target_compile_features(simulator PRIVATE cxx_std_20)
target_compile_options(simulator PRIVATE -Wall -Wextra -pedantic -fno-strict-aliasing)

option(SIM_BUILD_TESTS "Build tests" OFF)
if (SIM_BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    file(GLOB_RECURSE test_sources tests/*.hpp tests/*.cpp)

    add_executable(sim_tests ${includes} ${test_sources})
    target_link_libraries(sim_tests PRIVATE GTest::GTest GTest::Main)
    target_include_directories(sim_tests PRIVATE include tests)
    target_compile_features(sim_tests PRIVATE cxx_std_20)
    target_compile_options(sim_tests PRIVATE -Wall -Wextra -pedantic -fno-strict-aliasing)
    target_compile_options(sim_tests PRIVATE -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined)
    target_link_libraries(sim_tests PRIVATE -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined)
endif ()
