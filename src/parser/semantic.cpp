/*
Phase 4: Semantic analysis

This reads the parse tree, and checks for errors, it also 
*/
#include "semantic.h"
#include "../cli/log.h"

namespace semantic
{

// === Env class definition ===

// nothing here

// === Semantic analysis ===
env analyze(tree* t)
{
    cli::log(cli::log_level::debug, "--===-- SEMANTIC ANALYSIS --===--");

    env e;

    auto root = std::make_unique<node>("root");
    e.ast.setRoot(std::move(root));

    auto& rootptr = e.ast.getRoot();

    std::unique_ptr<node> block_node;

    std::vector<node*> path = t->traverse();

    block_node = std::make_unique<node>("entry");

    for(auto n : path)
    {
        // btw, the variable names are like this
        // p_... p for parser, node from parser
        // a_.. a for ast, node from ast
        if(n->value == "statement")
        {
            if(n->getChild(0).value == "declaration")
            {
                std::string v_type;
                std::string v_name;

                auto& p_dec = n->getChild(0);
                auto& p_spec = p_dec.getChild(0);
                auto& p_type = p_spec.getChild(0).getChild(0);
                auto& p_name = p_dec.getChild(1).getChild(0);

                v_type = p_type.value;
                v_name = p_name.value;
                
                cli::log(cli::log_level::debug,"Analysed variable declaration");
                cli::log(cli::log_level::debug,"type:" + v_type);
                cli::log(cli::log_level::debug,"name:" + v_name);

                // AST
                auto declaration = std::make_unique<node>("declaration");
                auto type = std::make_unique<node>(v_type);
                auto name = std::make_unique<node>(v_name);

                declaration->addChild(std::move(type));
                declaration->addChild(std::move(name));
                block_node->addChild(std::move(declaration));
            } 
        } 
    }

    rootptr.addChild(std::move(block_node));

    return e;
}

}
