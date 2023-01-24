//
// Created by yassa on 15/09/2022.
//

#ifndef TOROPROJECT_LEXER_H
#define TOROPROJECT_LEXER_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "./Token.h"


using namespace std;





class Lexer {
private:

    ifstream *input_stream;

    char cur_char;

    bool check_nl;

    vector <Token> output_tokens;

    bool is_alpha(char __c) const;

    bool is_num(char __c) const;

    int keyword_val(const string &str) const;

    bool next_token_is_new_line();
    
    bool next_token_is_EOF();
    
    bool next_token_is_arithmatic_operator();
    
    bool next_token_is_logic_operator();

    bool next_token_is_string();

    bool next_token_is_number();

    bool next_token_is_identifier_or_keyword();


    void next_char();

    char get_cur_char();

    char peek();

    void abort(string __msg);

    void skip_commit();

    void lex_next_token();

public:

    Lexer(ifstream *__input_stream);

    vector <Token> generate_token_vector();
};


#endif //TOROPROJECT_LEXER_H
