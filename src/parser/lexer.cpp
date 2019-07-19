/*
Phase 2: Lexing

This should take the ouput of the preprocessor, and assign tokens to each word & symbols.
*/
#include "lexer.h"

#include <iostream>

namespace lexer
{
    std::vector<token> tokenize(std::vector<std::string> prep)
    {
        std::vector<token> tokens;

        for(std::string word : prep)
        {
        //    std::cout<< word << std::endl;
        }

        return tokens;
    }
}