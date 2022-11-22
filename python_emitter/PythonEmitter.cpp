//
// Created by yassa on 12/11/2022.
//

#include "PythonEmitter.h"


PyhtonEmitter::PyhtonEmitter (ostream * __output_stream, const vector <EmitQuery> &__ast) : Emitter(__output_stream, __ast) {
    (*output_stream) << "# Compiled toro code\n";
}



void PyhtonEmitter::print_ind_tabs() {
    for (int i = 0; i < indentation_tabs; ++i) {
        (*output_stream) << '\t';
    }
}


void PyhtonEmitter::emit_file() {
    (*output_stream) << "\n";
    ((ofstream*)output_stream)->close();
//    delete output_stream;
}

void PyhtonEmitter::input_statement(const std::string &__var_name) {
    (*output_stream) << __var_name << " = int(input())";
}



void PyhtonEmitter::output_statement_str(const std::string &__text) {
    (*output_stream) << "print(\"" << __text << "\"" << ")";
}


void PyhtonEmitter::output_statement_num() {
    (*output_stream) << "print(";
}


void PyhtonEmitter::assigning(const std::string &_var_name) {
    (*output_stream) << _var_name << " = ";
}


void PyhtonEmitter::new_line() {
    (*output_stream) << "\n";
}

void PyhtonEmitter::start_if() {
    (*output_stream) << "if ";
}


void PyhtonEmitter::then() {
    (*output_stream) << " :";
    indentation_tabs++;
}


void PyhtonEmitter::end_if() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_stream) << "\n";
}


void PyhtonEmitter::start_while() {
    (*output_stream) << "while ";
}

void PyhtonEmitter::repeat() {
    (*output_stream) << " :";
    indentation_tabs++;
}

void PyhtonEmitter::end_while() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_stream) << "\n";
}

void PyhtonEmitter::create_var(const std::string &_var_name) {
    (*output_stream) << _var_name << " = ";
}

void PyhtonEmitter::expression(const std::string &_ex) {
    (*output_stream) << _ex;
}


void PyhtonEmitter::end_print_expression() {
    (*output_stream) << ")";
}
