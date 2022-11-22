# Compile the test source code

# compile lexer class
g++ -std=c++20 -c ../lexer/Lexer.cpp -o lexer.o


# compile the abstract emitter class
g++ -std=c++20 -c ../abstract_emitter/Emitter.cpp -o emitter.o


# compile the scope manager class
g++ -std=c++20 -c ../scope_manager/ScopeManager.cpp -o scope_manager.o


# compile the parser class
g++ -std=c++20 -c ./Parser.cpp -o parser.o


# compile the parser test class
g++ -std=c++20 -c ./Parser_Test.cpp -o parser_test.o


# compile the main test file
g++ -std=c++20 -c ./main.cpp -o main.o




# link the object files
g++ main.o lexer.o emitter.o parser.o parser_test.o scope_manager.o


