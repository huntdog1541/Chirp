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
   void setTokens(const std::vector<token>&);

    /*
    Returns the current token
    */
    token getToken();

    /*
    Advance the token
    */
    void nextToken();

    /*
    Reverse the token
    */
    void backtrack();

    /*
    Returns the token, behind of the position
    */
    token lookBehind();

    /*
    Returns the next token
    */
    token lookAhead();
    private:

    int tkn_pos;
    std::vector<token> tokens;
};
