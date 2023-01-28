//
// Created by yassa on 28/1/2023.
//

#ifndef TOROPROJECT_COMPILATIONERROR_H
#define TOROPROJECT_COMPILATIONERROR_H

#include <iostream>
#include <string>

using namespace std;

class CompilationError : public exception{
private:
    string error_msg;

public:
    CompilationError(string __error_msg);

    string get_error_msg() const;
};


#endif //TOROPROJECT_COMPILATIONERROR_H
