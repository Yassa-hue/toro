//
// Created by yassa on 21/09/2022.
//

#include "Parser.h"

//#ifndef TESTING_LOG
//
//#define TESTING_LOG
//
//#endif


Parser::Parser(TokenIterator *__tokens_iterator, ScopeManager *__scope_manager) :
        tokens_iterator(__tokens_iterator), scope_manager(__scope_manager){

    test_log("starting parsing");

    // initialize the global scope
    scope_manager->create_inner_scope();

    // calling next_token() twice to fill the current and the peek token
    move_to_next_token();
    move_to_next_token();
}


void Parser::test_log(string __log_msg) {

#ifdef TESTING_LOG

    cout << __log_msg << endl;

#endif
}


void Parser::move_to_next_token() {
    // gets the next token form the lexer

    cur_token = peek_token;
    if (tokens_iterator->hasNext())
        peek_token = tokens_iterator->getNext();
}


bool Parser::is_cur_token(Token __token) const {
    // checks if the current token is equal to the given token

    return (__token.kind == cur_token.kind);
}


bool Parser::is_peek_token(Token __token) const {
    // checks if the peek token is equal to the given token

    return (__token.kind == peek_token.kind);
}


void Parser::abort(string __msg) const {
    // error handler

    throw ParserError("Parser Error : " + __msg);
}



void Parser::match(Token __should_be_token, int __ident_checker = DONT_CHECK_IDENT) {
    /*
     * if the parser know what the current token should be use match
     */

    if (__should_be_token != cur_token)
        abort("Expected " + __should_be_token.text + "(" + to_string(__should_be_token.kind) + ")" +  " Found " + cur_token.text + "(" +
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

}


void Parser::program() {

    // Our program contains more than one statement

    while (!is_cur_token(Token("EOF", EOF)))
        statement();
}


void Parser::statement() {
    // test_log("Calling statement on " + cur_token.text + " " + peek_token.text);

    ast.push_back({PRINT_IND_TABS, ""});
    // Output statement : print expression | string
    if (is_cur_token(Token("keyword", OUTPUT))) {
        move_to_next_token();

        if (is_cur_token(Token("", STRING))) {
            test_log("printing text");
            ast.push_back({OUTPUT_STATEMENT_STR, cur_token.text});
            move_to_next_token();
        } else {
            test_log("printing expression");
            ast.push_back({OUTPUT_STATEMENT_NUM, ""});
            expression();
            ast.push_back({END_PRINT_EXPRESSION, ""});
        }
    }

    // If statement : if comparison then
    else if (is_cur_token(Token("keyword", IF))) {

        test_log("starting if statement");

        ast.push_back({START_IF_EXP, ""});

        // comparison
        move_to_next_token();
        comparison();

        // then keyword
        ast.push_back({THEN_EXP, ""});
        match(Token("keyword", THEN));
        move_to_next_token();
        newline();


        // start new scope for if statement
        scope_manager->create_inner_scope();

        // zero or more statements till reaching endif
        while (!is_cur_token(Token("keyword", ENDIF)))
            statement();

        // endif
        ast.push_back({END_IF_EXP, ""});
        match(Token("keyword", ENDIF));
        move_to_next_token();

        // delete if statement inner scope
        scope_manager->pop_out_scope();

        test_log("end if statement");
    }

    // while loop
    else if (is_cur_token(Token("keyword", WHILE))) {
        test_log("starting while statement");

        ast.push_back({START_WHILE_EXP, ""});

        // comparison
        move_to_next_token();
        comparison();

        // repeat keyword
        match(Token("keyword", REPEAT));
        move_to_next_token();
        ast.push_back({REPEAT_EXP, ""});
        newline();


        // start new scope for while statement
        scope_manager->create_inner_scope();

        // zero or more statements till reaching endwhile
        while (!is_cur_token(Token("keyword", ENDWHILE)))
            statement();

        // endwhile
        ast.push_back({END_WHILE_EXP, ""});
        match(Token("keyword", ENDWHILE));
        move_to_next_token();


        // delete while statement inner scope
        scope_manager->pop_out_scope();

        test_log("end while statement");
    }


    // Let statement : let ident = expression
    else if (is_cur_token(Token("keyword", LET))) {
        test_log("let statement");

        move_to_next_token();

        match(Token("", IDENT), CHECK_IDENT_NOT_DECLARED);
        ast.push_back({CREATE_VAR, cur_token.text});
        move_to_next_token();

        match(Token("=", EQ));
        move_to_next_token();

        // add this var to the current scope
        scope_manager->add_ident_to_curr_scope(cur_token.text);

        expression();
    }


    // input statement : input keyword
    else if (is_cur_token(Token("keyword", INPUT))) {
        test_log("input statement");

        move_to_next_token();
        ast.push_back({INPUT_STATEMENT, cur_token.text});
        match(Token("", IDENT), CHECK_IDENT_DECLARED);
        move_to_next_token();

    }


    // assigning statement : ident = expression
    else if (is_cur_token(Token("", IDENT))) {
        test_log("assigning statement");

        // check id the identifier is declared
        if (!scope_manager->identifier_is_declared(cur_token.text))
            abort("Undeclared identifier " + cur_token.text);

        ast.push_back({ASSIGNING_EXP, cur_token.text});

        move_to_next_token();
        match(Token("=", EQ));
        move_to_next_token();

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
        ast.push_back({EXPRESSION_EXP, cur_token.text});
        move_to_next_token();
        term();
    }
}


// term is unary [(*|/)unary]*
void Parser::term () {
    test_log("calling term on " + cur_token.text);

    unary();

    while (is_cur_token(Token("*", AST))
           || is_cur_token(Token("/", SLASH))) {
        ast.push_back({EXPRESSION_EXP, cur_token.text});
        move_to_next_token();
        unary();
    }
}


// unary is ±primary
void Parser::unary() {
    test_log("calling unary on " + cur_token.text);

    // plus or minus
    if (is_cur_token(Token("+", PLUS))
        || is_cur_token(Token("-", MINUS))) {
        ast.push_back({EXPRESSION_EXP, cur_token.text});
        move_to_next_token();
    }

    primary();
}


// primary is num|ident
void Parser::primary() {
    test_log("calling primary on " + cur_token.text);


    if (is_cur_token(Token("", IDENT))) {
        if (scope_manager->identifier_is_declared(cur_token.text)) {
            ast.push_back({EXPRESSION_EXP, cur_token.text});
            move_to_next_token();
        } else
            abort("Undeclared identifier " + cur_token.text);
    } else if (is_cur_token(Token("", NUMBER))) {
        ast.push_back({EXPRESSION_EXP, cur_token.text});
        move_to_next_token();
    } else
        abort("Expected identifier or number found " + cur_token.text);
}


void Parser::newline() {
    // Expects one or more newlines
    test_log("new line on " + cur_token.text);

    if (!is_cur_token(Token("nl", NEWLINE))
        && !is_cur_token(Token("EOF", EOF)))
        abort("Expected new line found " + cur_token.text);

    ast.push_back({NEW_LINE_EXP, ""});

    move_to_next_token();
}


// comparison is expression comp_op expression
void Parser::comparison() {
    test_log("comparison on " + cur_token.text);

    expression();

    // comparison operators
    if (cur_token.kind > GTEQ || cur_token.kind < EQEQ)
        abort("Expected comparison operators found " + cur_token.text);

    ast.push_back({EXPRESSION_EXP, cur_token.text});
    move_to_next_token();

    expression();

}



void Parser::start_parsing() {
    program();
}

const vector<EmitQuery> &Parser::getAST() const {
    return ast;
}



