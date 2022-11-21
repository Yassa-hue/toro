//
// Created by yassa on 21/09/2022.
//

#include "Parser.h"

//#ifndef TESTING_LOG
//
//#define TESTING_LOG
//
//#endif


Parser::Parser(Lexer *__lexer, Emitter *__emitter, ScopeManager *__scope_manager) :
        lexer(__lexer), emitter(__emitter) ,scope_manager(__scope_manager){

    test_log("starting parsing");

    // initialize the global scope
    scope_manager->create_inner_scope();

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

    throw "Parser Error : " + __msg;
}



void Parser::match(Token __token, int __ident_checker = DONT_CHECK_IDENT) {
    /*
     * if the parser know what the current token should be use match
     */

    if (__token != cur_token)
        abort("Expected " + __token.text + "(" + to_string(__token.kind) + ")" +  " Found " + cur_token.text + "(" +
                      to_string(cur_token.kind) + ")");

    // check if this identifier is already declared
    if (cur_token.kind == IDENT && __ident_checker == CHECK_IDENT_DECLARED) {
        if (!scope_manager->identifier_is_declared(cur_token.text)) // error
            abort("Undeclared identifier " + cur_token.text);
    }

    // check if this identifier is not declared
    if (cur_token.kind == IDENT && __ident_checker == CHECK_IDENT_NOT_DECLARED) {
        if (scope_manager->identifier_is_declared(cur_token.text)) // error
            abort("Declaring declared identifier");
        scope_manager->add_ident_to_curr_scope(cur_token.text);
    }

    next_token();
}


void Parser::program() {

    // Our program contains more than one statement

    while (!is_cur_token(Token("EOF", EOF)))
        statement();
}


void Parser::statement() {
    test_log("Calling statement on " + cur_token.text + " " + peek_token.text);

    emitter->print_ind_tabs();
    // Output statement : print expression | string
    if (is_cur_token(Token("keyword", OUTPUT))) {
        next_token();

        if (is_cur_token(Token("", STRING))) {
            test_log("printing text");
            emitter->output_statement_str(cur_token.text);
            next_token();
        } else {
            test_log("printing expression");
            emitter->output_statement_num();
            expression();
            emitter->end_print_expression();
        }
    }

    // If statement : if comparison then
    else if (is_cur_token(Token("keyword", IF))) {

        test_log("starting if statement");

        emitter->start_if();

        // comparison
        next_token();
        comparison();

        // then keyword
        emitter->then();
        match(Token("keyword", THEN));
        newline();


        // start new scope for if statement
        scope_manager->create_inner_scope();

        // zero or more statements till reaching endif
        while (!is_cur_token(Token("keyword", ENDIF)))
            statement();

        // endif
        emitter->end_if();
        match(Token("keyword", ENDIF));

        // delete if statement inner scope
        scope_manager->pop_out_scope();

        test_log("end if statement");
    }

    // while loop
    else if (is_cur_token(Token("keyword", WHILE))) {
        test_log("starting while statement");

        emitter->start_while();

        // comparison
        next_token();
        comparison();

        // repeat keyword
        match(Token("keyword", REPEAT));
        emitter->repeat();
        newline();


        // start new scope for while statement
        scope_manager->create_inner_scope();

        // zero or more statements till reaching endwhile
        while (!is_cur_token(Token("keyword", ENDWHILE)))
            statement();

        // endwhile
        emitter->end_while();
        match(Token("keyword", ENDWHILE));


        // delete while statement inner scope
        scope_manager->pop_out_scope();

        test_log("end while statement");
    }


    // Let statement : let ident = expression
    else if (is_cur_token(Token("keyword", LET))) {
        test_log("let statement");

        next_token();

        emitter->create_var(cur_token.text);


        match(Token("", IDENT), CHECK_IDENT_NOT_DECLARED);
        match(Token("=", EQ));

        // add this var to the current scope
        scope_manager->add_ident_to_curr_scope(cur_token.text);

        expression();
    }


    // input statement : input keyword
    else if (is_cur_token(Token("keyword", INPUT))) {
        test_log("input statement");

        next_token();
        emitter->input_statement(cur_token.text);
        match(Token("", IDENT), CHECK_IDENT_DECLARED);

    }


    // assigning statement : ident = expression
    else if (is_cur_token(Token("", IDENT))) {
        test_log("assigning statement");

        // check id the identifier is declared
        if (!scope_manager->identifier_is_declared(cur_token.text))
            abort("Undeclared identifier " + cur_token.text);

        emitter->assigning(cur_token.text);

        next_token();
        match(Token("=", EQ));

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
        emitter->expression(cur_token.text);
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
        emitter->expression(cur_token.text);
        next_token();
        unary();
    }
}


// unary is ±primary
void Parser::unary() {
    test_log("calling unary on " + cur_token.text);

    // plus or minus
    if (is_cur_token(Token("+", PLUS))
        || is_cur_token(Token("-", MINUS))) {
        emitter->expression(cur_token.text);
        next_token();
    }

    primary();
}


// primary is num|ident
void Parser::primary() {
    test_log("calling primary on " + cur_token.text);


    if (is_cur_token(Token("", IDENT))) {
        if (scope_manager->identifier_is_declared(cur_token.text)) {
            emitter->expression(cur_token.text);
            next_token();
        } else
            abort("Undeclared identifier " + cur_token.text);
    } else if (is_cur_token(Token("", NUMBER))) {
        emitter->expression(cur_token.text);
        next_token();
    } else
        abort("Expected identifier or number found " + cur_token.text);
}


void Parser::newline() {
    // Expects one or more newlines
    test_log("new line on " + cur_token.text);

    if (!is_cur_token(Token("nl", NEWLINE))
        && !is_cur_token(Token("EOF", EOF)))
        abort("Expected new line found " + cur_token.text);

    emitter->new_line();

    next_token();
}


// comparison is expression comp_op expression
void Parser::comparison() {
    test_log("comparison on " + cur_token.text);

    expression();

    // comparison operators
    if (cur_token.kind > GTEQ || cur_token.kind < EQEQ)
        abort("Expected comparison operators found " + cur_token.text);

    emitter->expression(cur_token.text);
    next_token();

    expression();

}



