/*
Phase 2: Lexing

This should take the ouput of the preprocessor, and assign tokens to each word & symbols.
*/
#include "lexer.h"
#include "../cli/log.h"

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

                    try
                    {
                        tokens.at(pos - 1).name = token_name::identifier;
                        cli::log(cli::log_level::debug,"Setting back token");
                    }
                    catch(std::out_of_range)
                    {
                        // Not very important
                        cli::log(cli::log_level::debug,"(LEXER) Out of range behind = symbol");
                    }

                    // Doesn't detect char or string or bool yet
                    if(isNumber(prep.at(pos + 1)) == true)
                    {
                        next = token_name::litteral;
                    }
                    else if(prep.at(pos + 1) == "true" || prep.at(pos + 1) == "false")
                    {
                        next = token_name::litteral;
                    }
                    else if(prep.at(pos+1).at(0) == '\'')
                    {
                        next = token_name::litteral;
                    }
                    else
                    {
                        next = token_name::identifier;
                    }
                }
                else if(word == "+" || word == "-" || word == "*" || word == "/")
                {
                    tkn.name = token_name::math_op;

                    if(isNumber(prep.at(pos - 1)) == true)
                    {
                        tokens.at(pos - 1).name = token_name::litteral;
                    }
                    else
                    {
                        // we don't care if it's true or false or even a char because it's not supposed to be there anywhere
                        tokens.at(pos - 1).name = token_name::identifier;
                    }

                    if(isNumber(prep.at(pos + 1)) == true)
                    {
                        next = token_name::litteral;
                    }
                    else 
                    {
                        next = token_name::identifier;
                    }
                }
                else if(word == "{")
                {
                    tkn.name = token_name::lbracket;
                }
                else if(word == "}")
                {
                    tkn.name = token_name::rbracket;
                }
                else if(word == "(")
                {
                    tkn.name = token_name::lparen;
                    tokens.at(pos - 1).name = token_name::identifier;
                }
                else if(word == ")")
                {
                    tkn.name = token_name::rparen;
                }
            }

            tokens.push_back(tkn);
            pos++;
        }

        token eos(token_name::end_of_string,"");
        tokens.push_back(eos);
        return tokens;
    }
}
