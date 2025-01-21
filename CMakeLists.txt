cmake_minimum_required(VERSION 3.10)
project(Project C)

set(CMAKE_C_STANDARD 11)

file(GLOB LEXER_SOURCES Source/Lexer/*.c)
add_library(Lexer ${LEXER_SOURCES})

add_executable(ccvc main.c)
add_executable(
        lexer_tests
        Source/Lexer/tests/lexerTests.c
)

target_link_libraries(lexer_tests Lexer)
target_link_libraries(ccvc Lexer)

target_include_directories(ccvc PRIVATE Source/Lexer)
target_include_directories(lexer_tests PRIVATE Source/Lexer)

set_target_properties(lexer_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

