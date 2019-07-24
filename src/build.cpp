#include "build.h"
#include "cli/log.h"

#include "preprocessor.h"
#include "parser.h"
#include "parser/lexer.h"
#include "parser/syntax.h"
#include "parser/semantic.h"

#include <iostream>

void compile(std::string source)
{
    cli::log(DEBUG,"Debug messages are now visible");
    std::vector<std::string> prep = preprocess(source);
    std::vector<token> tokens = lexer::tokenize(prep);

    parser p_env;
    p_env.setTokens(tokens);

    tree parseTree;
    auto root = std::make_unique<node>("root");
    parseTree.setRoot(std::move(root));

    syntax::parse(&p_env,&parseTree);
    semantic::analyze(&parseTree);

    cli::log(SUCCESS,"Nothing wen't wrong, and this is all it can do right now");
}

void build()
{

}
