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
        // a_... a for ast, node from ast
        // v_... v for variable
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
            else if(n->getChild(0).value == "assignment")
            {
                //cli::log(cli::log_level::debug,"Assignment found");
                std::string v_target;
                std::string v_source;

                auto& p_assign = n->getChild(0);
                auto& p_target = p_assign.getChild(0);
                auto& p_source = p_assign.getChild(1);
                auto& p_id = p_target.getChild(0).getChild(0);
                auto& p_src = p_source.getChild(0).getChild(0);

                v_source = p_src.getChild(0).value;
                v_target = p_id.value;

                cli::log(cli::log_level::debug,"Analysed variable assignement");
                cli::log(cli::log_level::debug,"target:" + v_target);
                cli::log(cli::log_level::debug,"source:" + v_source);

                // AST
                auto a_assign = std::make_unique<node>("assignement");
                auto a_target = std::make_unique<node>("target");
                auto a_source = std::make_unique<node>("source");
                std::unique_ptr<node> a_sourcetype;
                //auto a_sourcetype = std::make_unique<node>();

                if(p_src.value == "litteral")
                {
                    a_sourcetype = std::make_unique<node>("litteral");
                }
                else if(p_src.value == "identifier")
                {
                    a_sourcetype = std::make_unique<node>("identifier");
                }

                auto a_sourcel = std::make_unique<node>(v_source);
                auto a_targetl = std::make_unique<node>(v_target);

                a_target->addChild(std::move(a_targetl));
                a_assign->addChild(std::move(a_target));
                a_sourcetype->addChild(std::move(a_sourcel));
                a_source->addChild(std::move(a_sourcetype));
                a_assign->addChild(std::move(a_source));
            }
        } 
    }

    rootptr.addChild(std::move(block_node));

    return e;
}

}
