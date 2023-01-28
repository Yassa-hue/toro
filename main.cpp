#include "./lexer/Lexer.h"
#include "./parser/Parser.h"
#include "./cpp_emitter/CppEmitter.h"
#include "./python_emitter/PythonEmitter.h"



int main() {
    // inter point

    try {
        
        
        /*

            The input gourney throw the logic:
                1 - Open the input file (input.toro)
                2 - Lexing the input code generating a vector of tokens
                3 - Creating an iterator to loop over this vector of tokens
                4 - Parsing the tokens generating the AST
                5 - The emitter proccesses the AST and emittes the compiled code into the output files

        */
        
        // input file
        ifstream *input_file = new ifstream ("./input.toro");
        
        // output files
        ofstream *output_cpp_file = new ofstream ("./output.cpp");
        ofstream *output_python_file = new ofstream ("./output.py");

        // lexing
        Lexer *lexer = new Lexer(input_file);
        vector <Token> tokens = lexer->generate_token_vector();


        // generating the token iterator
        TokenIterator *token_iterator = new TokenIterator(tokens);

        ScopeManager *scope_manager = new ScopeManager();

        
        // parsing
        Parser *parser = new Parser(token_iterator, scope_manager);
        parser->start_parsing();
        const vector<EmitQuery> &ast = parser->getAST();


        // emitting
        CppEmitter *cpp_emitter = new CppEmitter(output_cpp_file, ast);
        cpp_emitter->proccessAST();

        PyhtonEmitter *pyhton_emitter = new PyhtonEmitter(output_python_file, ast);
        pyhton_emitter->proccessAST();

        output_cpp_file->close();
        output_python_file->close();



        // free the used memory
        delete input_file;
        delete lexer;
        delete pyhton_emitter;
        delete cpp_emitter;
        delete parser;
        delete scope_manager;
        delete output_cpp_file;
        delete output_python_file;
        delete token_iterator;
    } catch (CompilationError err) {
        cout << "ERROR ! " << err.get_error_msg() << endl;
    }
    return 0;
}
