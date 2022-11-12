//
// Created by yassa on 10/11/2022.
//

#ifndef TOROPROJECT_EMITTER_H
#define TOROPROJECT_EMITTER_H

#include <iostream>
#include <map>

using namespace std;


class Emitter {
protected:
    ostream *output_stream;

    int indentation_tabs;

public:
    Emitter(ostream * __output_stream);

    virtual void print_ind_tabs();

    virtual void emit_file();

    virtual void input_statement(const string &_var_name);

    virtual void output_statement_str(const string &_text);

    virtual void output_statement_num();

    virtual void assigning(const string &_var_name);

    virtual void new_line();

    virtual void start_if();

    virtual void then();

    virtual void end_if();

    virtual void start_while();

    virtual void repeat();

    virtual void end_while();

    virtual void create_var(const string &_var_name);

    virtual void expression(const string &_ex);

    virtual void end_print_expression();
};


#endif //TOROPROJECT_EMITTER_H
