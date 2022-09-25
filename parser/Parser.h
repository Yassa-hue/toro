//
// Created by yassa on 21/09/2022.
//

#ifndef TOROPROJECT_PARSER_H
#define TOROPROJECT_PARSER_H


#include "../lexer/Lexer.h"


class Parser {
private:
    Lexer *lexer;

    Token cur_token, peek_token;

    bool open_if;

    void next_token();

    bool is_cur_token(Token __token) const;

    bool is_peek_token(Token __token) const;

    void abort(string __msg) const;

    void match(Token __token);

    void program();

    void statement();

    void expression();

    void comparison();

    void newline();

public:
    Parser(Lexer *__lexer);

};


#endif //TOROPROJECT_PARSER_H
