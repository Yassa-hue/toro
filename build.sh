# Compile the source code

# Lexer files
g++ -std=c++20 -c ./lexer/Lexer.cpp -o Lexer.o

# Parser files
g++ -std=c++20 -c ./parser/Parser.cpp -o Parser.o


# Scope manager files
g++ -std=c++20 -c ./scope_manager/ScopeManager.cpp -o scope_manager.o


# Abstract emitter files
g++ -std=c++20 -c ./abstract_emitter/Emitter.cpp -o Emitter.o


# Python emitter files
g++ -std=c++20 -c ./python_emitter/PythonEmitter.cpp -o PythonEmitter.o


# Cpp emitter files
g++ -std=c++20 -c ./cpp_emitter/CppEmitter.cpp -o CppEmitter.o


# Compilation error files
g++ -std=c++20 -c ./compilation_error/CompilationError.cpp -o compilation_error.o


# Token iterator files
g++ -std=c++20 -c ./token_iterator/TokenIterator.cpp -o token_iterator.o


# Main file
g++ -std=c++20 -c main.cpp -o main.o

# Link the object files
g++ main.o Lexer.o Parser.o Emitter.o PythonEmitter.o CppEmitter.o scope_manager.o compilation_error.o token_iterator.o


# clean the environment after compiling
rm *.o
