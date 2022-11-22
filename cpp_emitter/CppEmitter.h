//
// Created by yassa on 28/09/2022.
//

#ifndef TOROPROJECT_CPPEMITTER_H
#define TOROPROJECT_CPPEMITTER_H

#include <iostream>
#include <fstream>
#include "../abstract_emitter/Emitter.h"
using namespace std;


class CppEmitter : public Emitter {
private:

    bool no_semicolon;

    void print_ind_tabs() override;


    void emit_file() override;

    void input_statement(const string &_var_name) override;

    void output_statement_str(const string &_text) override;

    void output_statement_num() override;

    void assigning(const string &_var_name) override;

    void new_line() override;

    void start_if() override;

    void then() override;

    void end_if() override;

    void start_while() override;

    void repeat() override;

    void end_while() override;

    void create_var(const string &_var_name) override;

    void expression(const string &_ex) override;


    void end_print_expression() override;


public:
    CppEmitter(ostream * __output_stream, const vector <EmitQuery> &__ast);



};


#endif //TOROPROJECT_CPPEMITTER_H
