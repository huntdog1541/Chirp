#include "build.h"
#include "cli/log.h"

#include "preprocessor.h"
#include "parser.h"
#include "parser/lexer.h"
#include "parser/syntax.h"
#include "parser/semantic.h"
#include "gen/gen_ir.h"
#include "gen/gen_asm.h"

#include <iostream>

std::string compile(std::string source)
{
    cli::log(cli::log_level::debug, "Debug messages are now visible");
    std::vector<std::string> prep = preprocess(source);
    std::vector<token> tokens = lexer::tokenize(prep);

    parser p_env;
    p_env.setTokens(tokens);

    tree parseTree;
    auto root = std::make_unique<node>("root");
    parseTree.setRoot(std::move(root));

    syntax::parse(&p_env,&parseTree);

    semantic::env sema;
    sema = semantic::analyze(&parseTree);

    std::vector<ir::operation> intermediate;
    intermediate = gen::make_ir(&sema.ast);

    std::string output;
    output = gen::make_asm(intermediate);

    cli::log(cli::log_level::success, "Nothing went wrong, and this is all it can do right now");

    return output;
}

void build()
{

}
