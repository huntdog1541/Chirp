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
        else
        {
            result = false;
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

        bool inlineAsm = false;

        for(std::string word : prep)
        {
            token tkn;
            tkn.value = word;
            
            if(inlineAsm)
            {
                if(word == "@end")
                {
                    tkn.name = token_name::no_token;
                    inlineAsm = false;
                }
                else
                {
                    tkn.name = token_name::asm_code;
                    tkn.value += " ";
                }
            }
            else
            {
             if(next != token_name::no_token)
             {
                tkn.name = next;
                next = token_name::no_token;
             }
             else
             {
                if(word == "@asm")
                {
                    tkn.name = token_name::no_token;
                    inlineAsm = true;
                }
                else if(word == "\n")
                {
                    tkn.name = token_name::no_token;
                    tkn.value = '\n';
                }
                else if(word == "int" || word == "char" || word == "bool") // Just int for the moment
                {
                    tkn.name = token_name::data_type;
                }
                else if(word == "entry")
                {
                    tkn.name = token_name::entry;
                }
                else if(word == ":")
                {
                    tkn.name = token_name::confirm;
                    next = token_name::identifier;
                }
                else if(word == "=")
                {
                    tkn.name = token_name::assign_op;
                }
                else if(word == "+" || word == "-" || word == "*" || word == "/")
                {
                    tkn.name = token_name::math_op;
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
                    // tokens.at(pos - 1).name = token_name::identifier;
                }
                else if(word == ")")
                {
                    tkn.name = token_name::rparen;
                }
                else if(word == ",")
                {
                    tkn.name = token_name::comma;
                }
                // Theses should always be at the bottom
                else if(isNumber(word))
                {
                    tkn.name = token_name::litteral;
                }
                else if(word == "true" || word == "false")
                {
                    tkn.name = token_name::litteral;
                }
                else if(word.at(0) == '\'')
                {
                    tkn.name = token_name::litteral;
                }
                else
                {
                    tkn.name = token_name::identifier;                    
                }
             }
            }
            if(tkn.name != token_name::no_token)
            {
                tokens.push_back(tkn);
            }
            pos++;
        }

        token eos(token_name::end_of_string,"");
        tokens.push_back(eos);
        return tokens;
    }
}
