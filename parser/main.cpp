#include <iostream>
#include "Parser.h"
#include "parser_tests.h"


using namespace std;


class TestCase {
public:
    string name;
    int number;
    TokenIterator input;

    TestCase (string __name, int __number, TokenIterator __input)
        : name(__name), number(__number), input(__input) {

    }
};


class SuccessfulTestCase : public TestCase {
public:
    vector <EmitQuery> output;

    SuccessfulTestCase(string __name, int __number, TokenIterator __input, vector <EmitQuery> &__output)
        : TestCase(__name, __number, __input), output(__output) {

    }

};


class FailingTestCase : public TestCase {
public:
    FailingTestCase (string __name, int __number, TokenIterator __input)
        : TestCase(__name, __number, __input) {

    }
};







void successful_test(SuccessfulTestCase &test_case) {
    cout << "Running successful test " << test_case.name << endl;
    ScopeManager *scope_manager = new ScopeManager();
    Parser *parser = new Parser(&(test_case.input), scope_manager);

    try {
        parser->start_parsing();
        const vector <EmitQuery> &test_output = parser->getAST();
        if (test_output.size() != test_case.output.size()) {
            cout << to_string(test_output.size()) + " " + to_string (test_case.output.size()) << endl;
            for (const auto &emit_query : test_output)
                cout << emit_query.type << ' ' << emit_query.args << endl;
            throw ParserTestError("Test Error : the test generated different number of emit queries");
        }
        for (int i = 0; i < test_output.size(); ++i)
            if (test_case.output[i] != test_output[i])
                throw ParserTestError("Test Error : expected " + to_string(test_case.output[i].type) + " got " + to_string(test_output[i].type));

        cout << "[ Test Passed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number);

    } catch (ParserTestError err) {
        cout << "[ Test Failed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number) + "\n\t => " + err.get_error_msg();
    } catch (ParserError err) {
        cout << "[ Test Failed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number) + "\n\t => " + err.get_error_msg();
    }

    delete scope_manager;
    delete parser;
}


void failing_test(FailingTestCase &test_case) {
    cout << "Running failing test " << test_case.name << endl;
    ScopeManager *scope_manager = new ScopeManager();
    Parser *parser = new Parser(&(test_case.input), scope_manager);

    try  {
        parser->start_parsing();
        cout << "[ Test Failed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number) + "\n\t => " + "this test should fail";
    } catch (ParserError err) {
        cout << "[ Test Passed ] test name : " + test_case.name + " , test number : " + to_string(test_case.number) + "\n\t => " + err.get_error_msg();
    } 

    delete scope_manager;
    delete parser;
}



void run_successful_tests (vector<SuccessfulTestCase> &test_cases) {
    for (SuccessfulTestCase &test_case : test_cases) {
        successful_test(test_case);
        cout << "\n ------------------------------------ \n\n\n" << endl;
    }
}


void run_failing_tests (vector<FailingTestCase> &test_cases) {
    for (FailingTestCase &test_case : test_cases) {
        
        failing_test(test_case);
        cout << "\n ------------------------------------ \n\n\n" << endl;
    }
    
}

int main() {

    cout << "Start testing" << endl;


    vector<SuccessfulTestCase> successful_test_cases = {
            SuccessfulTestCase(
                    "Successful test 0",
                    0,
                    successful_test0_input,
                    successful_test0_output
            ),
            SuccessfulTestCase(
                    "Successful test 1",
                    1,
                    successful_test1_input,
                    successful_test1_output
            )
    };

    vector<FailingTestCase> failing_test_cases = {
            FailingTestCase (
                    "Failing test 0",
                    2,
                    failing_test0_input
            ),
            FailingTestCase (
                    "Failing test 1",
                    3,
                    failing_test1_input
            )
    };

    
    cout << "testing functions" << endl;
    run_successful_tests(successful_test_cases);
    run_failing_tests(failing_test_cases);

    return 0;
}


