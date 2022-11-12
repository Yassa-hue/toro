//
// Created by yassa on 10/11/2022.
//

#include "Emitter.h"




Emitter::Emitter(ostream * __output_stream) : indentation_tabs(0), output_stream(__output_stream) {
    cout << "starting emitter" << endl;
}

void Emitter::print_ind_tabs() {
    for (int i = 0; i < indentation_tabs; ++i) {
        (*output_stream) << '\t';
    }
}


void Emitter::emit_file() {
    (*output_stream) << "\treturn 0;\n}";
}

void Emitter::input_statement(const std::string &__var_name) {
    (*output_stream) << "cin >> " << __var_name;
}



void Emitter::output_statement_str(const std::string &__text) {
    (*output_stream) << "cout << \"" << __text << "\"" << " << endl";
}


void Emitter::output_statement_num() {
    (*output_stream) << "cout << ";
}


void Emitter::assigning(const std::string &_var_name) {
    (*output_stream) << _var_name << " = ";
}


void Emitter::new_line() {
    (*output_stream) << "\n";
}

void Emitter::start_if() {
    (*output_stream) << "if (";
}


void Emitter::then() {
    (*output_stream) << ") {";
    indentation_tabs++;
}


void Emitter::end_if() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_stream) << "}";
}


void Emitter::start_while() {
    (*output_stream) << "while (";
}

void Emitter::repeat() {
    (*output_stream) << ") {";
    indentation_tabs++;
}

void Emitter::end_while() {
    indentation_tabs--;
    print_ind_tabs();
    (*output_stream) << "}";
}

void Emitter::create_var(const std::string &_var_name) {
    (*output_stream) << "double " << _var_name << " = ";
}

void Emitter::expression(const std::string &_ex) {
    (*output_stream) << _ex;
}


void Emitter::end_print_expression() {
    (*output_stream) << " << endl";
}
