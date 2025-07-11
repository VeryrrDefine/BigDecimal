cmake_minimum_required(VERSION 3.27.0)
project(bigdecimal VERSION 0.1.1 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set output executable file directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(bigdecimal SHARED src/bigdecimal.cpp)

add_executable(bigdecimal_tests tests/test_1.cpp)

target_include_directories(bigdecimal
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(bigdecimal_tests PRIVATE bigdecimal gtest_main)
enable_testing()
add_test(NAME bigdecimal_tests COMMAND bigdecimal_tests)
