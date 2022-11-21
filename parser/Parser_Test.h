//
// Created by yassa on 21/09/2022.
//

#ifndef TOROPROJECT_PARSER_TEST_H
#define TOROPROJECT_PARSER_TEST_H

#include "./Parser.h"

class Parser_Test {
private:
    Parser *p;
    Emitter *e;
    ScopeManager *sm;
public:
    Parser_Test(int __tests_num);
};


#endif //TOROPROJECT_PARSER_TEST_H
