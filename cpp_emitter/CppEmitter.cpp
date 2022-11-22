//
// Created by yassa on 28/09/2022.
//

#include "CppEmitter.h"

CppEmitter::CppEmitter(ostream * __output_stream, const vector <EmitQuery> &__ast) : Emitter(__output_stream, __ast), no_semicolon(false) {
    // cpp code is in the main function so that the initial number of tabs is 1
    indentation_tabs = 1;

    (*output_stream) << "#include <iostream>\nusing namespace std;\nint main () {\n";
}



void CppEmitter::print_ind_tabs() {
    for (int i = 0; i < indentation_tabs; ++i) {
        (*output_stream) << '\t';
    }
}


void CppEmitter::emit_file() {
    (*output_stream) << "\treturn 0;\n}";
    ((ofstream*)output_stream)->close();
//    delete output_stream;
}

void CppEmitter::input_statement(const std::string &__var_name) {
    (*output_stream) << "cin >> " << __var_name;
}



void CppEmitter::output_statement_str(const std::string &__text) {
    (*output_stream) << "cout << \"" << __text << "\"" << " << endl";
}


void CppEmitter::output_statement_num() {
    (*output_stream) << "cout << ";
}


void CppEmitter::assigning(const std::string &_var_name) {
    (*output_stream) << _var_name << " = ";
}


void CppEmitter::new_line() {
    if (no_semicolon)
        no_semicolon = false;
    else
        (*output_stream) << ";";
    (*output_stream) << "\n";
}

void CppEmitter::start_if() {
    (*output_stream) << "if (";
}


void CppEmitter::then() {
    (*output_stream) << ") {";
    no_semicolon = true;
    indentation_tabs++;
}


void CppEmitter::end_if() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_stream) << "}";
    no_semicolon = true;
}


void CppEmitter::start_while() {
    (*output_stream) << "while (";
}

void CppEmitter::repeat() {
    (*output_stream) << ") {";
    indentation_tabs++;
    no_semicolon = true;
}

void CppEmitter::end_while() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_stream) << "}";
    no_semicolon = true;
}

void CppEmitter::create_var(const std::string &_var_name) {
    (*output_stream) << "double " << _var_name << " = ";
}

void CppEmitter::expression(const std::string &_ex) {
    (*output_stream) << _ex;
}


void CppEmitter::end_print_expression() {
    (*output_stream) << " << endl";
}







