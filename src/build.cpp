#include "build.h"
#include "cli/log.h"

#include "preprocessor.h"
#include "parser.h"
#include "parser/lexer.h"
#include "parser/syntax.h"

#include <iostream>

void compile(std::string source)
{
    std::vector<std::string> prep = preprocess(source);
    std::vector<token> tokens = lexer::tokenize(prep);

    parser p_env;
    p_env.setTokens(tokens);

    tree parseTree;
    node root("root");
    parseTree.setRoot(&root);

    syntax::parse(&p_env,&parseTree);

    std::vector<std::string> path = parseTree.traverse();
    
    for(auto v : path)
    {
        std::cout<<v<<std::endl;
    }

    cli::log(SUCCESS,"Nothing wen't wrong, and this is all it can do right now");
}

void build()
{

}
