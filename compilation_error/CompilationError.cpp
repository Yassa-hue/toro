//
// Created by yassa on 28/1/2023.
//

#include "./CompilationError.h"



CompilationError::CompilationError(string __error_msg) : exception(), error_msg(__error_msg) {

}



string CompilationError::get_error_msg() const {
    return error_msg;
}
