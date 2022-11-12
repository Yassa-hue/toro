//
// Created by yassa on 28/09/2022.
//

#ifndef TOROPROJECT_EMITTER_H
#define TOROPROJECT_EMITTER_H

#include <iostream>
#include <fstream>
using namespace std;


class Emitter {
private:

    ofstream *output_file;

    int indentation_tabs;

    bool no_semicolon;

public:
    Emitter();

    void print_ind_tabs();


    void emit_file();

    void input_statement(const string &_var_name);

    void output_statement_str(const string &_text);

    void output_statement_num();

    void assigning(const string &_var_name);

    void new_line();

    void start_if();

    void then();

    void end_if();

    void start_while();

    void repeat();

    void end_while();

    void create_var(const string &_var_name);

    void expression(const string &_ex);


};


#endif //TOROPROJECT_EMITTER_H
