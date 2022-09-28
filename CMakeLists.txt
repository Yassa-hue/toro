cmake_minimum_required(VERSION 3.23)
project(toroProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(main.cpp ./lexer/Lexer_Test.cpp ./lexer/Lexer_Test.h ./emitter/Emitter.cpp ./emitter/Emitter.h)
