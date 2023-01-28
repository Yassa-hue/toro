//
// Created by yassa on 20/12/2022.
//

#ifndef TOROPROJECT_TOKENITERATOR_H
#define TOROPROJECT_TOKENITERATOR_H

#include "../lexer/Token.h"
#include "../compilation_error/CompilationError.h"
#include "vector"




class TokenIteratorError : public CompilationError {
public:
    TokenIteratorError(string __error_msg) : CompilationError(__error_msg) {

    }
};






class TokenIterator {
private:
    vector <Token> tokens;
    int lastToken;
public:
    TokenIterator(vector<Token> & __tokens);
    bool hasNext() const;
    Token getNext();
};


#endif //TOROPROJECT_TOKENITERATOR_H
