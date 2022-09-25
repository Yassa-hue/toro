//
// Created by yassa on 21/09/2022.
//

#include "Parser.h"


Parser::Parser(Lexer *__lexer) : lexer(__lexer), open_if(false) {
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
    // cout << "Calling statement on " << cur_token.text << ' ' << peek_token.text << endl;

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


    newline();


}


void Parser::expression() {

}


void Parser::newline() {
    // Expects one or more newlines
    // cout << "new line on " << cur_token.text << endl;

    if (!is_cur_token(Token("nl", NEWLINE))
        && !is_cur_token(Token("EOF", EOF)))
        abort("Expected new line found " + cur_token.text);

    next_token();
}


void Parser::comparison() {
    // (ident | num) COMP_OP (ident | num)

    // cout << "comparison on " << cur_token.text << endl;

    if (!is_cur_token(Token("ident", IDENT)) && !is_cur_token(Token("NUM", NUMBER)))
        abort("Expected identifier or number found " + cur_token.text);

    next_token();

    // comparison operators
    if (cur_token.kind > GTEQ || cur_token.kind < EQEQ)
        abort("Expected comparison operators found " + cur_token.text);

    next_token();

    if (!is_cur_token(Token("ident", IDENT)) && !is_cur_token(Token("NUM", NUMBER)))
        abort("Expected identifier or number found " + cur_token.text);

    next_token();

}



