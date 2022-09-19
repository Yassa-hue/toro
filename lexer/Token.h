//
// Created by yassa on 17/09/2022.
//

#ifndef TOROPROJECT_TOKEN_H
#define TOROPROJECT_TOKEN_H

#include <iostream>
using namespace std;


#define INV -3
#define NEWLINE 0
#define NUMBER 1
#define IDENT 2
#define STRING 3


// Keywords
#define LABEL 4
#define GOTO 5
#define PRINT 6
#define INPUT 7
#define LET 8
#define IF 9
#define THEN 10
#define ENDIF 11
#define WHILE 12
#define REPEAT 13
#define ENDWHILE 14


// Operators
#define EQ 15
#define PLUS 16
#define MINUS 17
#define AST 18
#define SLASH 19
#define EQEQ 20
#define NOTEQ 21
#define LT 22
#define LTEQ 23
#define GT 24
#define GTEQ 25


struct Token {
    string text;
    int kind;
    Token() {
        text = "";
        kind = INV;
    }

    Token (string __text, int __kind) {
        text = __text;
        kind = __kind;
    }
};





#endif //TOROPROJECT_TOKEN_H
