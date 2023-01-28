# Compile the test source code


# Compilation error class
g++ -std=c++20 -c ../compilation_error/CompilationError.cpp -o compilation_error.o


# lexer file
g++ -std=c++20 -c ./Lexer.cpp -o lexer.o


# Main file
g++ -std=c++20 -c main.cpp -o main.o

# Link the object files
g++ -std=c++20 main.o  lexer.o  compilation_error.o

# clean the environment after compilation
rm *.o