#pragma once
/*
This doesn't do the actual parsing, this is more of a shared structure that multiple parts of the compiler
will share, mostly the syntax analyser and semantic analyser.
*/

#include "tree.h"

#include "token.h"

class parser
{
    public:
    /*
    Parser constructor
    */
    parser();

    /*
    */
   void setTokens(std::vector<token>);

    /*
    Returns the current token
    */
    token getToken();

    /*
    Advance the token
    */
    void nextToken();

    /*
    Returns the next token
    */
    token lookAhead();
    private:

    int tkn_pos;
    std::vector<token> tokens;
};