//
// Created by yassa on 21/09/2022.
//

#ifndef TOROPROJECT_PARSER_H
#define TOROPROJECT_PARSER_H


#include "../lexer/Lexer.h"
#include "../abstract_emitter/Emitter.h"
#include "../scope_manager/ScopeManager.h"



// identifier checker statuses
#define DONT_CHECK_IDENT 0
#define CHECK_IDENT_DECLARED 1 // check if ident is declared
#define CHECK_IDENT_NOT_DECLARED 2 // check if ident is not declared


class Parser {
private:
    Lexer *lexer;

    Emitter *emitter;

    ScopeManager *scope_manager;

    Token cur_token, peek_token;

    void test_log(string s);

    void next_token();

    bool is_cur_token(Token __token) const;

    bool is_peek_token(Token __token) const;

    void abort(string __msg) const;

    void match(Token __token, int __ident_checker);

    void program();

    void statement();

    void expression();

    void term();

    void unary();

    void primary();

    void comparison();

    void newline();

public:
    Parser(Lexer *__lexer, Emitter * __emitter, ScopeManager *__scope_manager);

};


#endif //TOROPROJECT_PARSER_H
