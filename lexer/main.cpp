#include <iostream>
#include "Lexer.h"
#include "./tests/tests_output.h"


using namespace std;


class TestCase {
public:
    string name, file_path;
    int number;

    TestCase (string __name, int __number, string __file_path)
        : name(__name), number(__number), file_path(__file_path) {

    }
};


class SuccessfulTestCase : public TestCase {
public:
    vector<Token> output_tokens;

    SuccessfulTestCase(string __name, int __number, string __file_path, vector<Token> __output_tokens)
        : TestCase(__name, __number, __file_path), output_tokens(__output_tokens) {

    }

};


class FailingTestCase : public TestCase {
public:
    FailingTestCase(string __name, int __number, string __file_path)
        : TestCase(__name, __number, __file_path) {

    }
};




void successful_test(const SuccessfulTestCase &test_case) {
    ifstream *input_file = new ifstream (test_case.file_path);

    if (!input_file->is_open()) {
        cout << "error open the file : " << test_case.file_path << endl;
        return;
    }

    Lexer *lexer = new Lexer(input_file);

    try {
        vector<Token> test_output = lexer->generate_token_vector();

        if (test_output.size() != test_case.output_tokens.size()) {
            cout << to_string(test_output.size()) + " " + to_string (test_case.output_tokens.size()) << endl;
            for (const auto &token : test_output)
                cout << token.text << ' ' << token.kind << endl;
            throw LexerTestError("Test Error : the test generated different number of tokens");
        }
        for (int i = 0; i < test_output.size(); ++i)
            if (test_output[i] != test_case.output_tokens[i])
                throw LexerTestError("Test Error : expected " + test_case.output_tokens[i].text + " got " + test_output[i].text);

        cout << "[ Test Passed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number);

    } catch (CompilationError err) {
        cout << "[ Test Failed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number) + "\n\t => " + err.get_error_msg();
    }

    delete input_file;
    delete lexer;
}


void failing_test(const FailingTestCase &test_case) {
    ifstream *input_file = new ifstream (test_case.file_path);

    if (!input_file->is_open()) {
        cout << "error open the file : " << test_case.file_path << endl;
        return;
    }

    Lexer *lexer = new Lexer(input_file);

    try  {
        vector<Token> test_output = lexer->generate_token_vector();

        cout << "[ Test Failed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number) + "\n\t => " + "this test should fail";
    } catch (CompilationError err) {
        cout << "[ Test Passed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number) + "\n\t => " + err.get_error_msg();
    }

    delete input_file;
    delete lexer;
}



void run_successful_tests (const vector<SuccessfulTestCase> &test_cases) {
    for (const SuccessfulTestCase &test_case : test_cases) {
        successful_test(test_case);
        cout << endl;
    }
}


void run_failing_tests (const vector<FailingTestCase> &test_cases) {
    for (const FailingTestCase &test_case : test_cases) {
        failing_test(test_case);
        cout << endl;
    }
}

int main() {

    cout << "Start" << endl;
    string tests_dir_path = "./tests/",
            successful_tests_file_name = "successful_test",
            failing_tests_file_name = "failing_test",
            test_files_extension = ".txt";


    vector<SuccessfulTestCase> successful_test_cases = {
            SuccessfulTestCase(
                    "Successful test 0",
                    0,
                    tests_dir_path + successful_tests_file_name + "0" + test_files_extension,
                    successful_test_0_output
            ),
            SuccessfulTestCase(
                    "Successful test 1",
                    1,
                    tests_dir_path + successful_tests_file_name + "1" + test_files_extension,
                    successful_test_1_output
            )
    };

    vector<FailingTestCase> failing_test_cases = {
            FailingTestCase (
                    "Failing test 0",
                    2,
                    tests_dir_path + failing_tests_file_name + "0" + test_files_extension
            ),
            FailingTestCase (
                    "Failing test 1",
                    3,
                    tests_dir_path + failing_tests_file_name + "1" + test_files_extension
            )
    };

    
    cout << "testing functions" << endl;
    run_successful_tests(successful_test_cases);
    run_failing_tests(failing_test_cases);

    return 0;
}