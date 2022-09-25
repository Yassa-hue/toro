//
// Created by yassa on 15/09/2022.
//

#include "Lexer_Test.h"





Lexer_Test::Lexer_Test(int __num_of_tests) {

    cout << "Testing the input" << endl;

    for (int test_num = 0; test_num < __num_of_tests; ++test_num) {
        string test_file_path = LEXER_TESTS_PATH + "lexer_test" + to_string(test_num) + ".txt";
        ifstream *test_file = new ifstream (test_file_path);

        lexer = Lexer(test_file);

        test_input();

        delete test_file;
    }
    cout << "Testing the token" << endl;

    for (int test_num = 0; test_num < __num_of_tests; ++test_num) {
        string test_file_path = LEXER_TESTS_PATH + "lexer_test" + to_string(test_num) + ".txt";
        ifstream *test_file = new ifstream (test_file_path);

        lexer = Lexer(test_file);

        test_token();

        delete test_file;
    }
}


void Lexer_Test::test_input() {
    while (lexer.peek() != EOF) {
        lexer.next_char();
        cout << '(' << lexer.get_cur_char() << ')' << '\n';
    }
    cout << endl;
}


void Lexer_Test::test_token() {
    Token tk;
    while (lexer.get_cur_char() != EOF) {
        try {
            tk = lexer.get_token();
            cout << tk.text << ' ' << tk.kind << '\n';
        } catch (string msg) {
            cout << "ERROR : " << msg << endl;
        }
    }

    cout << endl;
}