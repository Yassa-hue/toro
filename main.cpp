#include "./lexer/Lexer.h"
#include "./parser/Parser.h"
#include "./cpp_emitter/CppEmitter.h"
#include "./python_emitter/PythonEmitter.h"



int main() {
    // inter point

    try {
        ifstream *input_file = new ifstream ("./input.toro");

        ofstream *output_cpp_file = new ofstream ("./output.cpp");
        ofstream *output_python_file = new ofstream ("./output.py");

        Lexer *lexer = new Lexer(input_file);

        CppEmitter *cpp_emitter = new CppEmitter(output_cpp_file);

        PyhtonEmitter *pyhton_emitter = new PyhtonEmitter(output_python_file);



//        Parser *parser = new Parser(lexer, pyhton_emitter);
//
//        pyhton_emitter->emit_file();

        Parser *parser = new Parser(lexer, cpp_emitter);

        cpp_emitter->emit_file();

        delete input_file;
        delete lexer;
        delete pyhton_emitter;
        delete cpp_emitter;
        delete parser;
        delete output_cpp_file;
        delete output_python_file;
    } catch (string msg) {
        cout << "ERROR ! " << msg << endl;
    }
    return 0;
}
