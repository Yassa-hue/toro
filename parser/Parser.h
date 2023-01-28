//
// Created by yassa on 21/09/2022.
//

#ifndef TOROPROJECT_PARSER_H
#define TOROPROJECT_PARSER_H


#include "../lexer/Lexer.h"
#include "../scope_manager/ScopeManager.h"
#include "./Emiter_Query.h"
#include "../token_iterator/TokenIterator.h"



class ParserError : public CompilationError {
public:
    ParserError(string __error_msg) : CompilationError(__error_msg) {

    };
};


// identifier checker statuses
#define DONT_CHECK_IDENT 0
#define CHECK_IDENT_DECLARED 1 // check if ident is declared
#define CHECK_IDENT_NOT_DECLARED 2 // check if ident is not declared


class Parser {
private:
    TokenIterator *tokens_iterator;

    ScopeManager *scope_manager;

    Token cur_token, peek_token;

    vector <EmitQuery> ast;

    void test_log(string s);

    void move_to_next_token();

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
    Parser(TokenIterator *__tokens_iterator, ScopeManager *__scope_manager);

    void start_parsing();

    const vector <EmitQuery> & getAST() const;

};


#endif //TOROPROJECT_PARSER_H
