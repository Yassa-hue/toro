#include "Parser.h"

// Succesful Tests
vector <Token> successful_test0_input_tokens = {
    Token("keyword", LET), Token("x", IDENT), Token("=", EQ), Token("45", NUMBER), Token("/", SLASH), Token("0.56", NUMBER), Token("nl", NEWLINE),
    Token("keyword", LET), Token("y", IDENT), Token("=", EQ), Token("x", IDENT), Token("*", AST), Token("-", MINUS), Token("x", IDENT), Token("nl", NEWLINE),
    Token("keyword", OUTPUT), Token("-", MINUS), Token("2", NUMBER), Token("+", PLUS), Token("y", IDENT),
    Token("EOF", EOF)
};

TokenIterator successful_test0_input (successful_test0_input_tokens);


vector <EmitQuery> successful_test0_output = {
    {PRINT_IND_TABS, ""},
    {CREATE_VAR, "x"},
    {EXPRESSION_EXP, "45"},
    {EXPRESSION_EXP, "/"},
    {EXPRESSION_EXP, "0.56"},
    {NEW_LINE_EXP, ""},
    {PRINT_IND_TABS, ""},
    {CREATE_VAR, "y"},
    {EXPRESSION_EXP, "x"},
    {EXPRESSION_EXP, "*"},
    {EXPRESSION_EXP, "-"},
    {EXPRESSION_EXP, "x"},
    {NEW_LINE_EXP, ""},
    {PRINT_IND_TABS, ""},
    {OUTPUT_STATEMENT_NUM, ""},
    {EXPRESSION_EXP, "-"},
    {EXPRESSION_EXP, "2"},
    {EXPRESSION_EXP, "+"},
    {EXPRESSION_EXP, "y"},
    {END_PRINT_EXPRESSION, ""},
    {NEW_LINE_EXP, ""},
};

vector <Token> successful_test1_input_tokens = {
    Token("keyword", LET), Token("x", IDENT), Token("=", EQ), Token("3", NUMBER), Token("nl", NEWLINE),
    Token("keyword", IF), Token("x", IDENT), Token(">=", GTEQ), Token("2.5", NUMBER), Token("keyword", THEN), Token("nl", NEWLINE),
    Token("x", IDENT), Token("=", EQ), Token("x", IDENT), Token("+", PLUS), Token("2", NUMBER), Token("nl", NEWLINE),
    Token("keyword", WHILE), Token("x", IDENT), Token(">", GT), Token("3", NUMBER), Token("keyword", REPEAT), Token("nl", NEWLINE),
    Token("keyword", LET), Token("y", IDENT), Token("=", EQ), Token("x", IDENT), Token("nl", NEWLINE),
    Token("x", IDENT), Token("=", EQ), Token("x", IDENT), Token("-", MINUS), Token("1", NUMBER), Token("nl", NEWLINE),
    Token("keyword", ENDWHILE), Token("nl", NEWLINE),
    Token("keyword", ENDIF), Token("nl", NEWLINE),
    Token("EOF", EOF)
};

TokenIterator successful_test1_input (successful_test1_input_tokens);


vector <EmitQuery> successful_test1_output = {
    {PRINT_IND_TABS, ""},
    {CREATE_VAR, "x"},
    {EXPRESSION_EXP, "3"},
    {NEW_LINE_EXP, ""},
    {PRINT_IND_TABS, ""},
    {START_IF_EXP, ""},
    {EXPRESSION_EXP, "x"},
    {EXPRESSION_EXP, ">="},
    {EXPRESSION_EXP, "2.5"},
    {THEN_EXP, ""},
    {NEW_LINE_EXP, ""},
    {PRINT_IND_TABS, ""},
    {ASSIGNING_EXP, "x"},
    {EXPRESSION_EXP, "x"},
    {EXPRESSION_EXP, "+"},
    {EXPRESSION_EXP, "2"},
    {NEW_LINE_EXP, ""},
    {PRINT_IND_TABS, ""},
    {START_WHILE_EXP, ""},
    {EXPRESSION_EXP, "x"},
    {EXPRESSION_EXP, ">"},
    {EXPRESSION_EXP, "3"},
    {REPEAT_EXP, ""},
    {NEW_LINE_EXP, ""},
    {PRINT_IND_TABS, ""},
    {CREATE_VAR, "y"},
    {EXPRESSION_EXP, "x"},
    {NEW_LINE_EXP, ""},
    {PRINT_IND_TABS, ""},
    {ASSIGNING_EXP, "x"},
    {EXPRESSION_EXP, "x"},
    {EXPRESSION_EXP, "-"},
    {EXPRESSION_EXP, "1"},
    {NEW_LINE_EXP, ""},
    {END_WHILE_EXP, ""},
    {NEW_LINE_EXP, ""},
    {END_IF_EXP, ""},
    {NEW_LINE_EXP, ""},
};





// Failing tests
/*

// smaple 1
if 3 < -4.5 + 3 then
let x = 7
endif
output x

// smaple 2
let iff = 5+8
while 1 == iff/2 repeat
if iff != -2 then
output -3 + iff
endwhile
endif

*/
vector <Token> failing_test0_input = {
    Token("keyword", IF), Token("3", NUMBER), Token("<", GTEQ), Token("-", MINUS), Token("4.5", NUMBER), Token("+", MINUS), Token("3", NUMBER), Token("keyword", THEN), Token("nl", NEWLINE),
    Token("keyword", LET), Token("x", IDENT), Token("=", EQ), Token("45", NUMBER), Token("nl", NEWLINE),
    Token("keyword", ENDIF), Token("nl", NEWLINE),
    Token("keyword", OUTPUT), Token("x", IDENT), 
    Token("EOF", EOF)
};

vector <Token> failing_test1_input = {
    Token("keyword", LET), Token("iff", IDENT), Token("=", EQ), Token("5", NUMBER), Token("+", PLUS), Token("8", NUMBER), Token("nl", NEWLINE),
    Token("keyword", WHILE), Token("1", NUMBER), Token("==", EQEQ), Token("iff", IDENT), Token("/", SLASH), Token("2", NUMBER), Token("keyword", REPEAT), Token("nl", NEWLINE),
    Token("keyword", IF), Token("iff", IDENT), Token("!=", NOTEQ), Token("-", MINUS), Token("2", NUMBER), Token("keyword", THEN), Token("nl", NEWLINE),
    Token("keyword", OUTPUT), Token("-", MINUS), Token("3", NUMBER), Token("+", PLUS), Token("iff", IDENT), Token("nl", NEWLINE),
    Token("keyword", ENDWHILE), Token("nl", NEWLINE),
    Token("keyword", ENDIF),
    Token("EOF", EOF)
};


class ParserTestError : public CompilationError{


public:
    ParserTestError(string __error_msg) : CompilationError(__error_msg) {

    };
};



