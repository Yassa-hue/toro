//
// Created by yassa on 22/11/2022.
//

#ifndef TOROPROJECT_EMITER_QUERY_H
#define TOROPROJECT_EMITER_QUERY_H

#include <istream>




#define PRINT_IND_TABS 1
#define OUTPUT_STATEMENT_STR 2
#define OUTPUT_STATEMENT_NUM 3
#define END_PRINT_EXPRESSION 4
#define START_IF_EXP 5
#define THEN_EXP 6
#define END_IF_EXP 7
#define START_WHILE_EXP 8
#define REPEAT_EXP 9
#define END_WHILE_EXP 10
#define CREATE_VAR 11
#define INPUT_STATEMENT 12
#define ASSIGNING_EXP 13
#define EXPRESSION_EXP 14
#define NEW_LINE_EXP 15





using namespace std;

struct EmitQuery {
public:
    int type;
    string args;
};


#endif //TOROPROJECT_EMITER_QUERY_H
