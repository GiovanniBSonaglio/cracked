cmake_minimum_required(VERSION 3.20)
project(cracked_compiler)

# Require C++17 for lexer (std::regex, inline member initializers, etc.)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(cracked_compiler ${SRC_DIR}/main.cpp ${SRC_DIR}/tokens.cpp ${SRC_DIR}/lexer.cpp)
target_include_directories(cracked_compiler PUBLIC ${INCLUDE_DIR})
