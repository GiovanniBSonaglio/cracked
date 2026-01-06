# utest CMake - defines tests for the lexer using GoogleTest

include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(utest_lexer lexer_gtests.cpp)

target_include_directories(utest_lexer PRIVATE ${INCLUDE_DIR})
# Link the tested library plus gtest
target_link_libraries(utest_lexer PRIVATE cracked_lib gtest_main)
add_test(NAME lexer_gtests COMMAND utest_lexer)
