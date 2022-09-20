//
// Created by yassa on 15/09/2022.
//

#include "Lexer.h"



bool Lexer::is_alpha(char __c) const {
    return ((__c >= 'a' & __c <= 'z') || (__c >= 'A' & __c <= 'Z'));
}


bool Lexer::is_num(char __c) const {
    return (__c >= '1' & __c <= '9');
}


int Lexer::keyword_val(const std::string &str) const {
    if (str == "label")
        return LABEL;
    if (str == "goto")
        return GOTO;
    if (str == "input")
        return INPUT;
    if (str == "output")
        return OUTPUT;

    if (str == "let")
        return LET;
    if (str == "if")
        return IF;
    if (str == "then")
        return THEN;
    if (str == "endif")
        return ENDIF;
    if (str == "while")
        return WHILE;
    if (str == "repeat")
        return REPEAT;
    if (str == "endwhile")
        return ENDWHILE;
    return INV;
}

Lexer :: Lexer() : input_stream(nullptr), cur_char(' '){
    // empty initializer

}

Lexer::Lexer (std::ifstream *__input_stream) : input_stream(__input_stream), cur_char(' ') {
    // nextChar();
}

void Lexer::next_char() {

    if (input_stream->eof()) // reaches the end of the input code
        cur_char = '\0';
    else // takes one char at a time
        *(input_stream) >> noskipws >> cur_char;

}


char Lexer::get_cur_char() {
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
        next_char();
}


void Lexer::skip_commit() {
    if (cur_char == '#')
        while (cur_char != '\n')
            next_char();
}


Token Lexer::get_token() {
    next_char();
    skip_white_spaces();
    skip_commit();

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
        if (peek() == '=') {
            next_char();
            return Token(">=", GTEQ);
        } else
            return Token(">", GT);
    } else if (cur_char == '<') {
        if (peek() == '=') {
            next_char();
            return Token("<=", LTEQ);
        } else
            return Token("<", LT);
    } else if (cur_char == '=') {
        if (peek() == '=') {
            next_char();
            return Token("==", EQEQ);
        } else
            return Token("=", EQ);
    } else if (cur_char == '!') {
        if (peek() == '=') {
            next_char();
            return Token("!=", NOTEQ);
        } else
            abort("Expected = after !");
    }


    // String token
    else if (cur_char == '\"') {
        next_char();
        while (cur_char != '\"') {
            if (cur_char == '\0')
                abort("Expected \" at the end of the string");
            next_char();
        }
        return Token("str", STRING);
    }

    // Number token
    if (cur_char >= '0' && cur_char <= '9') {
        while (cur_char == '.' || (cur_char >= '0' && cur_char <= '9')) {
            if (cur_char == '.' && peek() < '0' || peek() > '9')
                abort("Inappropriate decimal point");
            next_char();
        }

        return Token("num", NUMBER);
    }


    // Identifier token
    string identifier, var_name;
    while (is_alpha(cur_char)) {
        identifier.push_back(cur_char);
        next_char();
    }

    if (keyword_val(identifier) != INV)
        return Token("keyword", keyword_val(identifier));

    if (cur_char != ' ')
        abort("Invalid identifier");

    next_char();
    if (!is_alpha(cur_char))
        abort("Invalid variable name");

    while (is_alpha(cur_char) || is_num(cur_char)) {
        var_name.push_back(cur_char);
        next_char();
    }

    if (keyword_val(var_name) != INV)
        abort("Invalid variable name");

    return Token("ident", IDENT);
}