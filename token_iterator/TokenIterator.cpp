//
// Created by yassa on 20/12/2022.
//

#include "TokenIterator.h"


TokenIterator::TokenIterator(vector<Token> &__tokens) : tokens(__tokens) , lastToken(-1){

};


bool TokenIterator::hasNext() const {
    return (lastToken +1 < tokens.size());
}


Token TokenIterator::getNext() {
    if (!hasNext())
        throw TokenIteratorError("Calling get on an empty iterator");

    lastToken++;

    return tokens[lastToken];
}



