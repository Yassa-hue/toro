# Compile the source code

# Object files dir
obj_files_path="./object_files"

# Lexer files
g++ -c ./lexer/Lexer.cpp -o $obj_files_path/Lexer.o

# Main file
g++ -c main.cpp -o $obj_files_path/main.o

# Link the object files
g++ $obj_files_path/main.o $obj_files_path/Lexer.o

