cmake_minimum_required(VERSION 3.10)
project(Project C)
set(CMAKE_C_STANDARD 11)

##debug
##set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")

file(GLOB VECTOR_RESOURSES Source/All/Vector/src/*.c)
file(GLOB TOKEN_RESOURSES Source/All/Token/src/*.c)
file(GLOB NODE_RESOURSES Source/All/Node/src/*.c)
file(GLOB VARIABLE_RESOURSES Source/All/Variable/src/*.c)
file(GLOB FUNCTION_RESOURSES Source/All/Function/src/*.c)
file(GLOB VARIABLELIST_RESOURSES Source/All/VariableList/src/*.c)
file(GLOB FUNCTIONLIST_RESOURSES Source/All/FunctionList/src/*.c)

file(GLOB ERROR_SOURCES Source/Safe/Error/src/*.c)
file(GLOB ASSERT_SOURCES Source/Safe/SafeAssert/src/*.c)

file(GLOB LEXER_SOURCES Source/Compiler/Lexer/src/*.c)
file(GLOB SYNTAXER_SOURCES Source/Compiler/Syntaxer/src/*.c)
file(GLOB CODE_GENERATOR_SOURCES Source/Compiler/CodeGenerator/src/*.c)

add_library(Vector ${VECTOR_RESOURSES})
add_library(Token ${TOKEN_RESOURSES})
add_library(Node ${NODE_RESOURSES})
add_library(Variable ${VARIABLE_RESOURSES})
add_library(Function ${FUNCTION_RESOURSES})

add_library(VariableList ${VARIABLELIST_RESOURSES})
add_library(FunctionList ${FUNCTIONLIST_RESOURSES})

add_library(Error ${ERROR_SOURCES})
add_library(Assert ${ASSERT_SOURCES})

add_library(Lexer ${LEXER_SOURCES})
add_library(Syntaxer ${SYNTAXER_SOURCES})
add_library(CodeGenerator ${CODE_GENERATOR_SOURCES})

add_executable(
        ccvc
        main.c
)

add_executable(
        lexer_tests
        Source/Compiler/Lexer/tests/lexerTests.c
)

add_executable(
        code_generator_tests
        Source/Compiler/CodeGenerator/tests/codeGeneratorTests.c
)


target_link_libraries(Token Vector)
target_link_libraries(Token Error)

target_link_libraries(Node Token)

target_link_libraries(VariableList Variable)
target_link_libraries(Function VariableList)

target_link_libraries(Node Token)
target_link_libraries(Node Function)

target_link_libraries(Assert Token)

target_link_libraries(Lexer Token)

target_link_libraries(FunctionList Function)

target_link_libraries(Syntaxer Node)
target_link_libraries(Syntaxer FunctionList)

target_link_libraries(CodeGenerator Node)
target_link_libraries(CodeGenerator FunctionList)

target_link_libraries(lexer_tests Lexer)
target_link_libraries(lexer_tests Assert)

target_link_libraries(code_generator_tests Lexer)
target_link_libraries(code_generator_tests Syntaxer)
target_link_libraries(code_generator_tests CodeGenerator)

target_link_libraries(ccvc Lexer)
target_link_libraries(ccvc Syntaxer)
target_link_libraries(ccvc CodeGenerator)

target_include_directories(ccvc PRIVATE Source/Compiler/Lexer)
target_include_directories(ccvc PRIVATE Source/Compiler/Syntaxer)
target_include_directories(ccvc PRIVATE Source/Compiler/CodeGenerator)

target_include_directories(code_generator_tests PRIVATE Source/Compiler/Lexer)
target_include_directories(code_generator_tests PRIVATE Source/Compiler/Syntaxer)
target_include_directories(code_generator_tests PRIVATE Source/Compiler/CodeGenerator)

target_include_directories(lexer_tests PRIVATE Source/Compiler/Lexer)
target_include_directories(lexer_tests PRIVATE Source/Safe/SafeAssert)

set_target_properties(lexer_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

set_target_properties(code_generator_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

