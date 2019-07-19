/*
This file is used for defining the token class, so it doesn't do much.
*/

#include "token.h"

// Does nothing
token::token () {}

token::token(token_name n,std::string v)
{
    this->name = n;
    this->value = v;
}