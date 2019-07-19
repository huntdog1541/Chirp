#include "build.h"
#include "log.h"

#include "preprocessor.h"
#include "parser/parser.h"
#include "parser/lexer.h"

#include <iostream>

void compile(std::string source)
{
    std::vector<std::string> prep = preprocess(source);
    std::vector<token> tokens = lexer::tokenize(prep);

    // Should maybe make a parser init function
    parser.token_cluster = tokens;
    parser.token_pos = 0;

    cli::log(SUCCESS,"Nothing wen't wrong, and this is all it can do right now");
}

void build()
{

}