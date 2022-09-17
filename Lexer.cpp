//
// Created by yassa on 15/09/2022.
//

#include "Lexer.h"


Lexer :: Lexer() : input_stream(nullptr), cur_char(' '){
    // empty initializer

}

Lexer::Lexer (std::ifstream *__input_stream) : input_stream(__input_stream), cur_char(' ') {
    nextChar();
}

void Lexer::nextChar() {

    if (input_stream->eof()) // reaches the end of the input code
        cur_char = '\0';
    else // takes one char at a time
        *(input_stream) >> noskipws >> cur_char;

}


char Lexer::getCurChar() {
    return cur_char;
}


char Lexer::peek() {
    if (input_stream->eof()) // reaches the end of the input code
        return '\0';

    return input_stream->peek();
}


void Lexer::abort() {
    throw "Invalid Token";
}
