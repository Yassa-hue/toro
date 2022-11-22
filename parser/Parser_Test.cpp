//
// Created by yassa on 21/09/2022.
//

#include "Parser_Test.h"


Parser_Test::Parser_Test(int __tests_num) {
    for (int i = 0; i < __tests_num; ++i) {
        try {
            ifstream *input_file = new ifstream ("./test" + to_string(i) + ".txt");
            Lexer *l = new Lexer(input_file);

            sm = new ScopeManager();
            p = new Parser(l, sm);

            const vector<EmitQuery> &eq = p->getAST();

            e = new Emitter(&cout, eq);

            e->proccessAST();
            delete input_file;
            delete l;
            delete p;
            delete e;
            delete sm;
        } catch (string msg) {
            cout << msg << endl;
        }
    }
}