/*
This file is used for defining the token class, so it doesn't do much.
*/

#include "token.h"

std::string tokenToString(token_name name)
{
    switch(name)
    {
        case token_name::identifier:
        return "identifier";
            break;
        case token_name::data_type:
        return "data_type";
            break;
        case token_name::lparen:
        return "lparen";
            break;
        case token_name::rparen:
        return "rparem";
            break;
        case token_name::lbracket:
        return "lbracket";
            break;
        case token_name::rbracket:
        return "rbracket";
            break;
        case token_name::assign_op:
        return "assign_op";
            break;
        case token_name::math_op:
        return "math_op";
            break;
        case token_name::confirm:
        return "confirm";
            break;
        case token_name::litteral:
        return "litteral";
            break;
        case token_name::no_token:
        return "no_token";
            break;
        case token_name::end_of_string:
        return "end_of_string";
            break;
        default:
            return "no_token";
            break;
    }
}

// Does nothing
token::token () {}

token::token(token_name n,std::string v)
{
    this->name = n;
    this->value = v;
}
