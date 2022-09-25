//
// Created by yassa on 21/09/2022.
//

#include "Parser.h"


Parser::Parser(Lexer *__lexer) : lexer(__lexer) {
    cout << "starting parsing" << endl;

    // calling next_token() twice to fill the current and the peek token
    next_token();
    next_token();

    program();
}


void Parser::next_token() {
    // gets the next token form the lexer

    cur_token = peek_token;
    peek_token = lexer->get_token();
}


bool Parser::is_cur_token(Token __token) const {
    // checks if the current token is equal to the given token

    return (__token.kind == cur_token.kind);
}


bool Parser::is_peek_token(Token __token) const {
    // checks if the peek token is equal to the given token

    return (__token.kind == peek_token.kind);
}


void Parser::abort(std::string __msg) const {
    // error handler

    throw __msg;
}


void Parser::match(Token __token) {
    /*
     * if the parser know what the current token should be use match
     */

    if (__token != cur_token)
        abort("Expected " + __token.text + " Found " + cur_token.text);

    next_token();
}


void Parser::program() {

    // Our program contains more than one statement

    while (!is_cur_token(Token("EOF", EOF)))
        statement();
}


void Parser::statement() {
    cout << "Calling statement on " << cur_token.text << ' ' << peek_token.text << endl;

    // Output statement : print expression | string
    if (is_cur_token(Token("keyword", OUTPUT))) {

        next_token();

        if (is_cur_token(Token("str", STRING))) {
            cout << "printing text" << endl;
            next_token();
        } else
            expression();
    }




}


void Parser::expression() {

}


void Parser::newline() {
    // Expects one or more newlines
    cout << "new line" << endl;
    match(Token("nl", NEWLINE));
}



