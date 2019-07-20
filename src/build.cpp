#include "build.h"
#include "log.h"

#include "preprocessor.h"
#include "parser/parser.h"
#include "parser/lexer.h"
#include "syntax.h"

#include <iostream>

void compile(std::string source)
{
    std::vector<std::string> prep = preprocess(source);
    std::vector<token> tokens = lexer::tokenize(prep);

    parser p_env;
    p_env.setTokens(tokens);

    tree parseTree = syntax::parse(&p_env);

    cli::log(SUCCESS,"Nothing wen't wrong, and this is all it can do right now");
}

void build()
{

}