/*
This file isn't the parser by itself, but the custom parser generator. The actual parsing is happening in syntax.cpp
*/
#include "parser.h"
#include "../cli/log.h"

parser::parser() {
    this->tkn_pos = 0;
    this->tokens.reserve(1);
}

void parser::setTokens(std::vector<token> newTokens)
{
    for(token t : newTokens)
    {
        this->tokens.push_back(t);
    }

    this->tokens.push_back(token(token_name::end_of_string,""));
    //std::cout<<newTokens.size()<<std::endl;
}

token parser::getToken()
{
    token t;
    t = this->tokens.at(this->tkn_pos);
    return t;
}

void parser::nextToken()
{
    if(this->tkn_pos + 1 <= this->tokens.size())
    {
        // good
        this->tkn_pos++;
    }
    else
    {
        // bad
        cli::log(WARNING, "Cannot go forward");
    }
}

token parser::lookAhead()
{
    token t;

    if(this->tkn_pos + 1 <= this->tokens.size())
    {
        t = this->tokens.at(this->tkn_pos + 1);
    }
    else
    {
        cli::log(WARNING, "Cannot look ahead");
    }

    return t;
}
