#pragma once
/*
Header file for lexer
*/
#include <vector>
#include "token.h"

namespace lexer
{
    /*
    Takes preprocessed string as input and outputs a vector of tokens
    */
    std::vector<token> tokenize(const std::string&);
}
