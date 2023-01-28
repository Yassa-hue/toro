#include <iostream>
#include <vector>
#include "../Token.h"

using namespace std;

vector <Token> successful_test_0_output = {
    Token("keyword", LET),
    Token("x", IDENT),
    Token("=", EQ),
    Token("45", NUMBER),
    Token("/", SLASH),
    Token("0.56", NUMBER),
    Token("nl", NEWLINE),
    Token("keyword", LET),
    Token("y", IDENT),
    Token("=", EQ),
    Token("x", IDENT),
    Token("*", AST),
    Token("-", MINUS),
    Token("x", IDENT),
    Token("nl", NEWLINE),
    Token("keyword", OUTPUT),
    Token("-", MINUS),
    Token("2", NUMBER),
    Token("+", PLUS),
    Token("y", IDENT),
    Token("EOF", EOF)
};

vector <Token> successful_test_1_output = {
    Token("keyword", OUTPUT),
    Token("yassa", STRING),
    Token("nl", NEWLINE),
    Token("keyword", LET),
    Token("y", IDENT),
    Token("=", EQ),
    Token("-", MINUS),
    Token("45.09", NUMBER),
    Token("nl", NEWLINE),
    Token("keyword", IF),
    Token("y", IDENT),
    Token("!=", NOTEQ),
    Token("y", IDENT),
    Token("keyword", THEN),
    Token("nl", NEWLINE),
    Token("keyword", WHILE),
    Token("y", IDENT),
    Token("==", EQEQ),
    Token("iff", IDENT),
    Token("EOF", EOF)
};



class LexerTestError : public CompilationError {
public:
    LexerTestError(string __error_msg) : CompilationError(__error_msg) {

    }
};