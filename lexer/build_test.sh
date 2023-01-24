# Compile the test source code

# Object files dir
obj_files_path="."

class_name="Lexer"


# lexer file
g++ -std=c++20 -c ./"$class_name".cpp -o $obj_files_path/"$class_name".o


# Main file
g++ -std=c++20 -c main.cpp -o $obj_files_path/main.o

# Link the object files
g++ -std=c++20 $obj_files_path/main.o  $obj_files_path/"$class_name".o