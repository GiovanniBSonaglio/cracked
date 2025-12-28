cmake_minimum_required(VERSION 3.20)
project(cracked_compiler)

set(SRC_DIR src)
set(INCLUDE_DIR include)

add_executable(cracked_compiler ${SRC_DIR}/main.cpp)
target_include_directories(cracked_compiler PUBLIC ${INCLUDE_DIR})
