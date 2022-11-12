//
// Created by yassa on 21/09/2022.
//

#include "Parser_Test.h"


Parser_Test::Parser_Test(int __tests_num) {
    for (int i = 0; i < __tests_num; ++i) {
        try {
            ifstream *input_file = new ifstream ("./test" + to_string(i) + ".txt");
            Lexer *l = new Lexer(input_file);
            e = new Emitter(&cout);
            p = new Parser(l, e);
            delete input_file;
            delete l;
            delete p;
            delete e;
        } catch (string msg) {
            cout << msg << endl;
        }
    }
}