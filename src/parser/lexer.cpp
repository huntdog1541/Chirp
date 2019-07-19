/*
Phase 2: Lexing

This should take the ouput of the preprocessor, and assign tokens to each word & symbols.
*/
#include "lexer.h"

#include <iostream>

#define enumString(name) # name

bool isNumber(std::string word)
{
    bool result = false;

    for(char c : word)
    {
        if(isdigit(c))
        {
            result = true;
        }
    }
    
    return result;
}

namespace lexer
{
    std::vector<token> tokenize(std::vector<std::string> prep)
    {
        std::vector<token> tokens;

        token_name next = no_token;

        int pos = 0;

        for(std::string word : prep)
        {
            token tkn;
            tkn.value = word;

            if(next != no_token)
            {
                tkn.name = next;
                next = no_token;
            }
            else
            {
                if(word == "int") // Just int for the moment
                {
                    tkn.name = data_type;
                }
                else if(word == ":")
                {
                    tkn.name = confirm;
                    next = identifier;
                }
                else if(word == "=")
                {
                    tkn.name = assignment;

                    // Doesn't detect char or string or bool yet
                    if(isNumber(prep.at(pos + 1)) == true)
                    {
                        next = litteral;
                    }
                    else
                    {
                        next = identifier;
                    }
                }
            }

            tokens.push_back(tkn);
            pos++;
        }

        return tokens;
    }
}