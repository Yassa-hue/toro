cmake_minimum_required(VERSION 3.23)
project(toroProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(toro_compile main.cpp ./lexer/Lexer.cpp ./parser/Parser.cpp ./scope_manager/ScopeManager.cpp ./abstract_emitter/Emitter.cpp ./python_emitter/PythonEmitter.cpp ./cpp_emitter/CppEmitter.cpp ./compilation_error/CompilationError.cpp ./token_iterator/TokenIterator.cpp)
