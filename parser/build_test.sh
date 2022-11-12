# Compile the test source code

# compile lexer class
g++ -c ../lexer/Lexer.cpp -o lexer.o


# compile the abstract emitter class
g++ -c ../abstract_emitter/Emitter.cpp -o emitter.o


# compile the parser class
g++ -c ./Parser.cpp -o parser.o


# compile the parser test class
g++ -c ./Parser_Test.cpp -o parser_test.o


# compile the main test file
g++ -c ./main.cpp -o main.o




# link the object files
g++ main.o lexer.o emitter.o parser.o parser_test.o


