//
// Created by yassa on 28/09/2022.
//

#include "Emitter.h"

Emitter::Emitter() : indentation_tabs(1), no_semicolon(false) {
    output_file = new ofstream("./output.cpp");
    (*output_file) << "#include <iostream>\nusing namespace std;\nint main () {\n";
}



void Emitter::print_ind_tabs() {
    for (int i = 0; i < indentation_tabs; ++i) {
        (*output_file) << '\t';
    }
}


void Emitter::emit_file() {
    (*output_file) << "\treturn 0;\n}";
    output_file->close();
    delete output_file;
}

void Emitter::input_statement(const std::string &__var_name) {
    (*output_file) << "cin >> " << __var_name;
}



void Emitter::output_statement_str(const std::string &__text) {
    (*output_file) << "cout << \"" << __text << "\"" << " << endl";
}


void Emitter::output_statement_num() {
    (*output_file) << "cout << ";
}


void Emitter::assigning(const std::string &_var_name) {
    (*output_file) << _var_name << " = ";
}


void Emitter::new_line() {
    if (no_semicolon)
        no_semicolon = false;
    else
        (*output_file) << ";";
    (*output_file) << "\n";
}

void Emitter::start_if() {
    (*output_file) << "if (";
}


void Emitter::then() {
    (*output_file) << ") {";
    no_semicolon = true;
    indentation_tabs++;
}


void Emitter::end_if() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_file) << "}";
    no_semicolon = true;
}


void Emitter::start_while() {
    (*output_file) << "while (";
}

void Emitter::repeat() {
    (*output_file) << ") {";
    indentation_tabs++;
    no_semicolon = true;
}

void Emitter::end_while() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_file) << "}";
    no_semicolon = true;
}

void Emitter::create_var(const std::string &_var_name) {
    (*output_file) << "double " << _var_name << " = ";
}

void Emitter::expression(const std::string &_ex) {
    (*output_file) << _ex;
}







