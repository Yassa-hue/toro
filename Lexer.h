//
// Created by yassa on 15/09/2022.
//

#ifndef TOROPROJECT_LEXER_H
#define TOROPROJECT_LEXER_H

#include <iostream>
#include <fstream>
#include <map>



using namespace std;


typedef map<string, string> token;



class Lexer {
private:

    ifstream *input_stream;

    char cur_char;


public:

    Lexer();

    Lexer(ifstream *__input_stream);


    void nextChar();

    char getCurChar();

    char peek();

    void abort();

    void skip_white_spaces();

    void skip_commit();

    token get_token();
};


#endif //TOROPROJECT_LEXER_H
