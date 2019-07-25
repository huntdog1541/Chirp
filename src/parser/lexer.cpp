/*
Phase 2: Lexing

This should take the ouput of the preprocessor, and assign tokens to each word & symbols.
*/
#include "lexer.h"

#include <iostream>

#define enumString(name) # name

bool isNumber(const std::string& word)
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
    std::vector<token> tokenize(const std::vector<std::string>& prep)
    {
        std::vector<token> tokens;

        token_name next = token_name::no_token;

        int pos = 0;

        for(std::string word : prep)
        {
            token tkn;
            tkn.value = word;

            if(next != token_name::no_token)
            {
                tkn.name = next;
                next = token_name::no_token;
            }
            else
            {
                if(word == "int" || word == "char" || word == "bool") // Just int for the moment
                {
                    tkn.name = token_name::data_type;
                }
                else if(word == ":")
                {
                    tkn.name = token_name::confirm;
                    next = token_name::identifier;
                }
                else if(word == "=")
                {
                    tkn.name = token_name::assign_op;

                    // Doesn't detect char or string or bool yet
                    if(isNumber(prep.at(pos + 1)) == true)
                    {
                        next = token_name::litteral;
                    }
                    else
                    {
                        next = token_name::identifier;
                    }
                }
            }

            tokens.push_back(tkn);
            pos++;
        }

        return tokens;
    }
}
