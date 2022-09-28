#include "./lexer/Lexer.h"
#include "./parser/Parser.h"
#include "./emitter/Emitter.h"



int main() {
    // inter point

    try {
        ifstream *input_file = new ifstream ("./input.toro");
        Lexer *lexer = new Lexer(input_file);
        Emitter *emitter = new Emitter();
        Parser *parser = new Parser(lexer, emitter);

        emitter->emit_file();
        delete input_file;
        delete lexer;
        delete emitter;
        delete parser;
    } catch (string msg) {
        cout << "ERROR ! " << msg << endl;
    }
    return 0;
}
