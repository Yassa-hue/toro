//
// Created by yassa on 21/09/2022.
//

#include "Parser.h"

#ifndef TESTING_LOG

//#define TESTING_LOG

#endif


Parser::Parser(Lexer *__lexer) : lexer(__lexer), open_if(false) {

    test_log("starting parsing");

    // calling next_token() twice to fill the current and the peek token
    next_token();
    next_token();

    program();
}


void Parser::test_log(string __log_msg) {

#ifdef TESTING_LOG

    cout << __log_msg << endl;

#endif
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
        abort("Expected " + __token.text + "(" + to_string(__token.kind) + ")" +  " Found " + cur_token.text + "(" +
                      to_string(cur_token.kind) + ")");

    next_token();
}


void Parser::program() {

    // Our program contains more than one statement

    while (!is_cur_token(Token("EOF", EOF)))
        statement();
}


void Parser::statement() {
    test_log("Calling statement on " + cur_token.text + " " + peek_token.text);

    // Output statement : print expression | string
    if (is_cur_token(Token("keyword", OUTPUT))) {
        next_token();

        if (is_cur_token(Token("str", STRING))) {
            cout << "printing text" << endl;
            next_token();
        } else
            expression();
    }

    // If statement : if comparison then
    else if (is_cur_token(Token("keyword", IF))) {

        cout << "starting if statement" << endl;

        // comparison
        next_token();
        comparison();

        // then keyword
        match(Token("keyword", THEN));
        newline();

        // zero or more statements till reaching endif
        while (!is_cur_token(Token("keyword", ENDIF)))
            statement();

        // endif
        match(Token("keyword", ENDIF));
        cout << "end if statement" << endl;
    }

    // while loop
    else if (is_cur_token(Token("keyword", WHILE))) {
        cout << "starting while statement" << endl;

        // comparison
        next_token();
        comparison();

        // repeat keyword
        match(Token("keyword", REPEAT));
        newline();

        // zero or more statements till reaching endwhile
        while (!is_cur_token(Token("keyword", ENDWHILE)))
            statement();

        // endwhile
        match(Token("keyword", ENDWHILE));
        cout << "end while statement" << endl;
    }


    // Let statement : let ident = expression
    else if (is_cur_token(Token("keyword", LET))) {
        cout << "let statement" << endl;

        next_token();

        match(Token("ident", IDENT));
        match(Token("=", EQ));

        expression();
    }


    // input statement : input keyword
    else if (is_cur_token(Token("keyword", INPUT))) {
        cout << "input statement" << endl;

        next_token();
        match(Token("ident", IDENT));
    }


    // assigning statement : ident = expression
    else if (is_cur_token(Token("keyword", INPUT))) {
        cout << "assigning statement" << endl;

        next_token();
        match(Token("=", EQ));

        next_token();
        expression();
    }

    // invalid statement
    else
        abort("Invalid statement");


    newline();


}



// exp is term [(+|-)term]*
void Parser::expression() {

    test_log("calling expression on " + cur_token.text);

    term();

    // zero or more terms
    while (is_cur_token(Token("+", PLUS))
           || is_cur_token(Token("-", MINUS))) {

        next_token();
        term();
    }
}


// term is unary [(*|/)unary]*
void Parser::term () {
    test_log("calling term on " + cur_token.text);

    unary();

    while (is_cur_token(Token("*", AST))
           || is_cur_token(Token("/", SLASH))) {

        next_token();
        unary();
    }
}


// unary is ±primary
void Parser::unary() {
    test_log("calling unary on " + cur_token.text);

    // plus or minus
    if (is_cur_token(Token("+", PLUS))
        || is_cur_token(Token("-", MINUS)))
        next_token();

    primary();
}


// primary is num|ident
void Parser::primary() {
    test_log("calling primary on " + cur_token.text);

    if (!is_cur_token(Token("ident", IDENT))
        && !is_cur_token(Token("num", NUMBER)))
        abort("Expected identifier or number found " + cur_token.text);
    next_token();
}


void Parser::newline() {
    // Expects one or more newlines
    test_log("new line on " + cur_token.text);

    if (!is_cur_token(Token("nl", NEWLINE))
        && !is_cur_token(Token("EOF", EOF)))
        abort("Expected new line found " + cur_token.text);

    next_token();
}


// comparison is expression comp_op expression
void Parser::comparison() {
    test_log("comparison on " + cur_token.text);

    expression();

    // comparison operators
    if (cur_token.kind > GTEQ || cur_token.kind < EQEQ)
        abort("Expected comparison operators found " + cur_token.text);
    next_token();

    expression();

}



