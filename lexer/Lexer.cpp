//
// Created by yassa on 15/09/2022.
//

#include "Lexer.h"



bool Lexer::is_alpha(char __c) const {
    return ((__c >= 'a' & __c <= 'z') || (__c >= 'A' & __c <= 'Z'));
}


bool Lexer::is_num(char __c) const {
    return (__c >= '0' & __c <= '9');
}


int Lexer::keyword_val(const std::string &str) const {
    if (str == "label")
        return LABEL;
    if (str == "goto")
        return GOTO;
    if (str == "input")
        return INPUT;
    if (str == "output")
        return OUTPUT;

    if (str == "let")
        return LET;
    if (str == "if")
        return IF;
    if (str == "then")
        return THEN;
    if (str == "endif")
        return ENDIF;
    if (str == "while")
        return WHILE;
    if (str == "repeat")
        return REPEAT;
    if (str == "endwhile")
        return ENDWHILE;
    return INV;
}


Lexer::Lexer (std::ifstream *__input_stream) : input_stream(__input_stream), cur_char(' '), check_nl(true) {
    // next_char();
}

void Lexer::next_char() {
    //cout << "| " << input_stream->eof() << " | ";
    if (input_stream->peek() == EOF) {// reaches the end of the input code
        cur_char = EOF;
        //cout << "ch1";
    } else { // takes one char at a time
        *(input_stream) >> cur_char;
        //cout << "ch2";
    }
    //cout << endl;
}


char Lexer::get_cur_char() {
    return cur_char;
}


char Lexer::peek() {
    if (input_stream->eof()) // reaches the end of the input code
        return EOF;

    return input_stream->peek();
}


void Lexer::abort(string __msg) {
    throw "Lexer Error: " + __msg;
}




void Lexer::skip_commit() {
    while (cur_char == '#') {
        input_stream->ignore(100, '\n');
        next_char();
    }
}


bool Lexer::next_token_is_new_line() {
    if (check_nl && input_stream->peek() == '\n') {
        check_nl = false;
        output_tokens.push_back(Token("nl", NEWLINE));
        return true;
    }
    return false;
}


bool Lexer::next_token_is_EOF() {
    if (cur_char == EOF) {
        output_tokens.push_back(Token("EOF", EOF));
        return true;
    }
    return false;
}


bool Lexer::next_token_is_arithmatic_operator() {
    
    switch (cur_char) {
        case '+':
            output_tokens.push_back(Token("+", PLUS));
            break;
        case '-':
            output_tokens.push_back(Token("-", MINUS));
            break;
        case '*':
            output_tokens.push_back(Token("*", AST));
            break;
        case '/':
            output_tokens.push_back(Token("/", SLASH));
            break;
        default:
            return false;
    }
    
    return true;
}


bool Lexer::next_token_is_logic_operator() {
    if (cur_char == '>') {
        if (peek() == '=') {
            next_char();
            output_tokens.push_back(Token(">=", GTEQ));
        } else
            output_tokens.push_back(Token(">", GT));
        return true;
    } else if (cur_char == '<') {
        if (peek() == '=') {
            next_char();
            output_tokens.push_back(Token("<=", LTEQ));
        } else
            output_tokens.push_back(Token("<", LT));
        return true;
    } else if (cur_char == '=') {
        if (peek() == '=') {
            next_char();
            output_tokens.push_back(Token("==", EQEQ));
        } else
            output_tokens.push_back(Token("=", EQ));
        return true;
    } else if (cur_char == '!') {
        if (peek() == '=') {
            next_char();
            output_tokens.push_back(Token("!=", NOTEQ));
        } else
            abort("Expected = after !");
        
        return true;
    }
    return false;
}


bool Lexer::next_token_is_string() {
    if (cur_char == '\"') {
        next_char();
        string str;
        while (cur_char != '\"') {
            //cout << "string loop '" << cur_char << "'" << endl;
            str.push_back(cur_char);
            if (cur_char == EOF)
                abort("Expected \" at the end of the string");
            next_char();
        }
        //cout << "end string loop '" << cur_char << "'" << endl;
        output_tokens.push_back(Token(str, STRING));
        return true;
    }

    return false;
}


bool Lexer::next_token_is_number() {
    if (cur_char >= '0' && cur_char <= '9') {
        string num;

        while ((cur_char == '.' || is_num(cur_char)) // current char is a number
               && (peek() == '.' || is_num(peek()))) {  // it is not the end
            num.push_back(cur_char);
            if (cur_char == '.' && !is_num(peek()))  // if there is no nums after the decimal point (34.)
                abort("Inappropriate decimal point");
            next_char();
        }
        num.push_back(cur_char);
        output_tokens.push_back(Token(num, NUMBER));
        return true;
    }
    return false;
}


bool Lexer::next_token_is_identifier_or_keyword() {
    string identifier;

    if (!is_alpha(cur_char))
        abort("Invalid identifier");

    identifier.push_back(cur_char);

    while (is_alpha(peek()) || is_num(peek())) {
        next_char();
        identifier.push_back(cur_char);
    }

    if (keyword_val(identifier) != INV) {
        output_tokens.push_back(Token("keyword", keyword_val(identifier)));
        return true;
    }

    output_tokens.push_back(Token(identifier, IDENT));
    return true;
}



void Lexer::lex_next_token() {
    // cout << cur_char << endl;
    // handles newline
    // cout << "cl = " << check_nl << " Peek is of " << cur_char <<" (" << (int)(input_stream->peek()) << ')' << endl;

    if (next_token_is_new_line())
        return;

    next_char();
    skip_commit();

    check_nl = true;

    if (next_token_is_EOF())
        return;
    
    
    // Arithmatic operators
    
    if (next_token_is_arithmatic_operator())
        return;

    // Logic operators

    if (next_token_is_logic_operator())
        return;


    // String token
    if (next_token_is_string())
        return;

    // Number token
    if (next_token_is_number())
        return;


    // Identifier token
    next_token_is_identifier_or_keyword();
}


vector<Token> Lexer::generate_token_vector() {
    lex_next_token();
    while (output_tokens.back().kind != EOF)
        lex_next_token();

    return output_tokens;
}