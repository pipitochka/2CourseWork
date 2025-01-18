cmake_minimum_required(VERSION 3.29)
project(Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Project
        main.c
)

add_executable(
        lexer_tests
        Sourse/Lexer/tests/lexerTests.c
)

set_target_properties(lexer_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)