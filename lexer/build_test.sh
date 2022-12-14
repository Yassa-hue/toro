# Compile the test source code

# Object files dir
obj_files_path="."

class_name="Lexer"


# lexer file
g++ -c ./"$class_name".cpp -o $obj_files_path/"$class_name".o


# test files
g++ -c ./"$class_name"_Test.cpp -o $obj_files_path/"$class_name"_Test.o


# Main file
g++ -c main.cpp -o $obj_files_path/main.o

# Link the object files
g++ $obj_files_path/main.o $obj_files_path/"$class_name"_Test.o $obj_files_path/"$class_name".o