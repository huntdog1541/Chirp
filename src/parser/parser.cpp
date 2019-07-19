/*
This file isn't the parser by itself, but the custom parser generator. The actual parsing is happening in syntax.cpp
*/
#include "parser.h"
#include "../cli/log.h"

token lookAhead()
{
    // This is probably a misuse of look ahead in recursive parsers, but ¯\_(ツ)_/¯
    if(parser.token_pos + 1 <= parser.token_cluster.size())
    {
        cli::log(LOG,"Looking ahead"); // Debug, should be removed
        parser.token_pos++;
        return parser.token_cluster.at(parser.token_pos);
    }
    else
    {
        token eof(end_of_string,"");
        return eof;
    }
}