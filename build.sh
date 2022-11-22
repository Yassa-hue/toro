# Compile the source code

# Object files dir
obj_files_path="./object_files"

# Lexer files
g++ -std=c++20 -c ./lexer/Lexer.cpp -o $obj_files_path/Lexer.o

# Parser files
g++ -std=c++20 -c ./parser/Parser.cpp -o $obj_files_path/Parser.o


# Scope manager files
g++ -std=c++20 -c ./scope_manager/ScopeManager.cpp -o $obj_files_path/scope_manager.o



# Abstract emitter files
g++ -std=c++20 -c ./abstract_emitter/Emitter.cpp -o $obj_files_path/Emitter.o


# Python emitter files
g++ -std=c++20 -c ./python_emitter/PythonEmitter.cpp -o $obj_files_path/PythonEmitter.o


# Cpp emitter files
g++ -std=c++20 -c ./cpp_emitter/CppEmitter.cpp -o $obj_files_path/CppEmitter.o


# Main file
g++ -std=c++20 -c main.cpp -o $obj_files_path/main.o

# Link the object files
g++ $obj_files_path/main.o $obj_files_path/Lexer.o $obj_files_path/Parser.o $obj_files_path/Emitter.o $obj_files_path/PythonEmitter.o $obj_files_path/CppEmitter.o $obj_files_path/scope_manager.o

