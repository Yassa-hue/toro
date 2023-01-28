//
// Created by yassa on 10/11/2022.
//

#include "Emitter.h"




Emitter::Emitter(ostream * __output_stream, const vector <EmitQuery> &__ast) : indentation_tabs(0), output_stream(__output_stream), ast(__ast) {
    cout << "starting emitter" << endl;
}







void Emitter::proccessAST() {


    for (const EmitQuery &query : ast) {

        const int &type = query.type;

        switch (type) {

            case PRINT_IND_TABS: {
                print_ind_tabs();
                break;
            }

            case OUTPUT_STATEMENT_STR: {
                output_statement_str(query.args);
                break;
            }

            case OUTPUT_STATEMENT_NUM: {
                output_statement_num();
                break;
            }

            case END_PRINT_EXPRESSION: {
                end_print_expression();
                break;
            }

            case START_IF_EXP: {
                start_if();
                break;
            }

            case THEN_EXP: {
                then();
                break;
            }

            case END_IF_EXP: {
                end_if();
                break;
            }

            case START_WHILE_EXP: {
                start_while();
                break;
            }

            case REPEAT_EXP: {
                repeat();
                break;
            }

            case END_WHILE_EXP: {
                end_while();
                break;
            }

            case CREATE_VAR: {
                create_var(query.args);
                break;
            }

            case INPUT_STATEMENT: {
                input_statement(query.args);
                break;
            }

            case ASSIGNING_EXP: {
                assigning(query.args);
                break;
            }

            case EXPRESSION_EXP: {
                expression(query.args);
                break;
            }

            case NEW_LINE_EXP: {
                new_line();
                break;
            }

            default:
                throw "Invalid Emit Query";
        }

    }

    (*output_stream) << "}";

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
