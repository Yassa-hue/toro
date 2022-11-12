//
// Created by yassa on 12/11/2022.
//

#ifndef TOROPROJECT_PYHTONEMITTER_H
#define TOROPROJECT_PYHTONEMITTER_H

#include "../abstract_emitter/Emitter.h"
#include <iostream>
#include <fstream>


class PyhtonEmitter : public Emitter {

public:

    PyhtonEmitter(ostream * __output_stream);

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

};


#endif //TOROPROJECT_PYHTONEMITTER_H
