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

Lexer :: Lexer() : input_stream(nullptr), cur_char(' '), check_nl(true){
    // empty initializer

}

Lexer::Lexer (std::ifstream *__input_stream) : input_stream(__input_stream), cur_char(' '), check_nl(true) {
    // nextChar();
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
    throw __msg;
}




void Lexer::skip_commit() {
    while (cur_char == '#') {
        input_stream->ignore(100, '\n');
        next_char();
    }
}


Token Lexer::get_token() {

    // handles newline
    // cout << "cl = " << check_nl << " Peek is of " << cur_char <<" (" << (int)(input_stream->peek()) << ')' << endl;
    if (check_nl && input_stream->peek() == '\n') {
        check_nl = false;
        return Token("nl", NEWLINE);
    }
    next_char();
    skip_commit();

    check_nl = true;

//    cout << "get token '" << cur_char << "'" << endl;
    // Arithmatic operators

    if (cur_char == EOF)
        return Token("EOF", EOF);


//    cout << '(' << (cur_char == '\n' ? '~' : cur_char) << ')' << ' ';

    if (cur_char == '+')
        return Token("+", PLUS);
    else if (cur_char == '-')
        return Token("-", MINUS);
    else if (cur_char == '*')
        return Token("*", AST);
    else if (cur_char == '/')
        return Token("/", SLASH);

    // Logic operators

    else if (cur_char == '>') {
        if (peek() == '=') {
            next_char();
            return Token(">=", GTEQ);
        } else
            return Token(">", GT);
    } else if (cur_char == '<') {
        if (peek() == '=') {
            next_char();
            return Token("<=", LTEQ);
        } else
            return Token("<", LT);
    } else if (cur_char == '=') {
        if (peek() == '=') {
            next_char();
            return Token("==", EQEQ);
        } else
            return Token("=", EQ);
    } else if (cur_char == '!') {
        if (peek() == '=') {
            next_char();
            return Token("!=", NOTEQ);
        } else
            abort("Expected = after !");
    }


    // String token
    else if (cur_char == '\"') {
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
        return Token(str, STRING);
    }

    // Number token
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
        return Token(num, NUMBER);
    }


    // Identifier token

    string identifier;

    if (!is_alpha(cur_char))
        abort("Invalid identifier");

    identifier.push_back(cur_char);

    while (is_alpha(peek()) || is_num(peek())) {
        next_char();
        identifier.push_back(cur_char);
    }

    if (keyword_val(identifier) != INV)
        return Token("keyword", keyword_val(identifier));


    return Token(identifier, IDENT);
}