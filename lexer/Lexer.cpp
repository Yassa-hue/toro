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


void Lexer::abort(string __msg) {
    throw __msg;
}


void Lexer::skip_white_spaces() {
    if (cur_char == ' ' || cur_char == '\n' || cur_char == '\t')
        nextChar();
}


void Lexer::skip_commit() {
    // imp
}


Token Lexer::get_token() {
    skip_white_spaces();

    // Arithmatic operators

    if (cur_char == '+')
        return Token("+", PLUS);
    else if (cur_char == '-')
        return Token("-", MINUS);
    else if (cur_char == '*')
        return Token("*", AST);
    else if (cur_char == '/')
        return Token("/", SLASH);

    // Logic operators

    else if (cur_char == '>') {
        if (peek() == '=')
            return Token(">=", GTEQ);
        else
            return Token(">", GT);
    } else if (cur_char == '<') {
        if (peek() == '=')
            return Token("<=", LTEQ);
        else
            return Token("<", LT);
    } else if (cur_char == '=') {
        if (peek() == '=')
            return Token("==", EQEQ);
        else
            return Token("=", EQ);
    }

    else if (cur_char == '!') {
        if (peek() == '=')
            return Token("!=", NOTEQ);
        else
            abort("Invalid token");
    }

    abort("Invalid token");
}