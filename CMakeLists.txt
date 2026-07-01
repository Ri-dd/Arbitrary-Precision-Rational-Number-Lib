cmake_minimum_required(VERSION 3.16)

project(
    BigRational
    VERSION 1.0
    DESCRIPTION "Arbitrary Precision Rational Arithmetic Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(BigRationalLib
    src/BigInteger.cpp
    src/BigRational.cpp
)

target_include_directories(BigRationalLib PUBLIC include)

target_compile_options(BigRationalLib PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(calculator
    examples/calculator.cpp
)

target_link_libraries(calculator PRIVATE BigRationalLib)

add_executable(test_runner
    tests/test.cpp
)

target_link_libraries(test_runner PRIVATE BigRationalLib)
