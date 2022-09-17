cmake_minimum_required(VERSION 3.23)
project(toroProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(main.cpp Lexer.cpp Lexer.h Lexer_Test.cpp Lexer_Test.h)
