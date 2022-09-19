# Compile the test source code

# Object files dir
obj_files_path="."


# lexer file
g++ -c ./Lexer.cpp -o $obj_files_path/Lexer.o


# test files
g++ -c ./Lexer_Test.cpp -o $obj_files_path/Lexer_Test.o


# Main file
g++ -c main.cpp -o $obj_files_path/main.o

# Link the object files
g++ $obj_files_path/main.o $obj_files_path/Lexer_Test.o $obj_files_path/Lexer.o