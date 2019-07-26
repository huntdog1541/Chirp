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
                // Parse tree
                auto& p_target = n->getChild(0).getChild(0);
                auto& p_source = n->getChild(0).getChild(1);
                auto& p_expr = p_source.getChild(0);
                auto& p_identifier = p_target.getChild(0);
                
                std::string p_id = p_identifier.getChild(0).value;

                // std::cout<<p_expr.getChildSize()<<std::endl;

                // Creating the AST nodes
                auto a_assign = std::make_unique<node>("assignment");
                auto a_source = std::make_unique<node>("source");
                auto a_target = std::make_unique<node>("target");

                auto a_targetid = std::make_unique<node>(p_id);
                a_target->addChild(std::move(a_targetid));

                if(p_expr.getChild(0).value == "static")
                {
                    cli::log(cli::log_level::debug,"Value is static expression");
                    auto a_srctype = std::make_unique<node>(p_expr.getChild(0).getChild(0).value);
                    auto a_src = std::make_unique<node>(p_expr.getChild(0).getChild(0).getChild(0).value);
                    //std::cout<<a_srctype->value<<std::endl;
                    //std::cout<<a_src->value<<std::endl;

                    a_srctype->addChild(std::move(a_src));
                    a_source->addChild(std::move(a_srctype));

                    a_assign->addChild(std::move(a_target));
                    a_assign->addChild(std::move(a_source));
                    block_node->addChild(std::move(a_assign));
                }
                else
                {
                    cli::log(cli::log_level::debug,"Value is an complete expression");
                    for(auto& p_op : *p_expr.getAllChilds())
                    {
                        cli::log(cli::log_level::debug,"Added operation to AST");

                        auto op = std::make_unique<node>("");
                        auto a_type = std::make_unique<node>(p_op->getChild(0).value);
                        auto a = std::make_unique<node>(p_op->getChild(0).getChild(0).value);
                        auto b_type = std::make_unique<node>(p_op->getChild(1).value);
                        auto b = std::make_unique<node>(p_op->getChild(1).getChild(0).value);

                        if(p_op->value == "addition")
                        {
                            op->value = "add";
                        }
                        else if (p_op->value == "subtraction")
                        {
                            op->value = "sub";
                        }
                        else if (p_op->value == "multiplication")
                        {
                            op->value = "mul";
                        }
                        else if(p_op->value == "division")
                        {
                            op->value = "div";
                        }
                        
                        a_type->addChild(std::move(a));
                        b_type->addChild(std::move(b));
                        op->addChild(std::move(a_type));
                        op->addChild(std::move(b_type));
                        a_source->addChild(std::move(op));

                        a_assign->addChild(std::move(a_target));
                        a_assign->addChild(std::move(a_source));
                        block_node->addChild(std::move(a_assign));
                    }
                }
            }
        } 
    }

    rootptr.addChild(std::move(block_node));

    return e;
}

}
