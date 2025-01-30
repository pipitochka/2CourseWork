cmake_minimum_required(VERSION 3.10)
project(Project C)
set(CMAKE_C_STANDARD 11)

file(GLOB VECTOR_RESOURSES Source/All/Vector/src/*.c)
file(GLOB TOKEN_RESOURSES Source/All/Token/src/*.c)
file(GLOB NODE_RESOURSES Source/All/Node/src/*.c)
file(GLOB LEXER_SOURCES Source/Compiler/Lexer/src/*.c)
file(GLOB SYNTAXER_SOURCES Source/All/Node/src/*.c)
file(GLOB ERROR_SOURCES Source/Safe/Error/src/*.c)
file(GLOB ASSERT_SOURCES Source/Safe/SafeAssert/src/*.c)

add_library(Vector ${VECTOR_RESOURSES})
add_library(Token ${TOKEN_RESOURSES})
add_library(Node ${NODE_RESOURSES})
add_library(Lexer ${LEXER_SOURCES})
add_library(Syntaxer ${SYNTAXER_SOURCES})
add_library(Error ${ERROR_SOURCES})
add_library(Assert ${ASSERT_SOURCES})

add_executable(
        ccvc
        main.c
)

add_executable(
        lexer_tests
        Source/Compiler/Lexer/tests/lexerTests.c
)

target_link_libraries(Token Vector)

target_link_libraries(Node Token)

target_link_libraries(Assert Token)

target_link_libraries(Lexer Token)
target_link_libraries(Lexer Error)

target_link_libraries(lexer_tests Token)
target_link_libraries(lexer_tests Lexer)
target_link_libraries(lexer_tests Assert)

target_link_libraries(ccvc Lexer)
target_link_libraries(ccvc Syntaxer)

target_include_directories(ccvc PRIVATE Source/Compiler/Lexer)
target_include_directories(ccvc PRIVATE Source/Compiler/Syntaxer)
target_include_directories(lexer_tests PRIVATE Source/Compiler/Lexer)

set_target_properties(lexer_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

