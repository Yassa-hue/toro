# Compile the test source code



# compile the scope manager class
g++ -std=c++20 -c ../compilation_error/CompilationError.cpp -o compilation_error.o


# compile the scope manager class
g++ -std=c++20 -c ../scope_manager/ScopeManager.cpp -o scope_manager.o


# compile the token iterator class
g++ -std=c++20 -c ../token_iterator/TokenIterator.cpp -o token_iterator.o


# compile the parser class
g++ -std=c++20 -c ./Parser.cpp -o parser.o


# compile the main test file
g++ -std=c++20 -c ./main.cpp -o main.o



# link the object files
g++ main.o parser.o scope_manager.o token_iterator.o compilation_error.o

rm *.o


