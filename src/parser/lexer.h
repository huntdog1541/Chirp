#pragma once
/*
Header file for lexer
*/
#include <vector>
#include "token.h"

namespace lexer
{
    /*
    Takes preprocessed vector of string as input and outputs a vector of tokens
    */
    std::vector<token> tokenize(std::vector<std::string>);
}