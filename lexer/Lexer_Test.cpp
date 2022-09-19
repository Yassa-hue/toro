//
// Created by yassa on 15/09/2022.
//

#include "Lexer_Test.h"





Lexer_Test::Lexer_Test(int __num_of_tests) {
    for (int test_num = 0; test_num < __num_of_tests; ++test_num) {
        string test_file_path = LEXER_TESTS_PATH + "lexer_test" + to_string(test_num) + ".txt";
        ifstream *test_file = new ifstream (test_file_path);

        lexer = Lexer(test_file);

        test();

        delete test_file;
    }
}


void Lexer_Test::test() {
    while (lexer.peek() != '\0') {
        cout << lexer.getCurChar() << '\n';
        lexer.nextChar();
    }
    cout << endl;
}