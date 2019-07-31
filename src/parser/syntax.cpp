 /*
Phase 3: Syntax analysis parser

This is the actual parser(but I didn't call it that). It reads the tokens generated by the lexer, and generates a parse tree.
This should use a bottom up parsing algorithm, but I'm not sure which.

P.S I could really make this file less long
*/
#include "syntax.h"
#include <memory>
#include "../cli/log.h"
#include <iostream>

// I have no idea if this is ok, but this seems to work
namespace syntax
{
    parser* local_env; // *munchii is triggered*
    tree* local_tree;
    std::unique_ptr<node>* current_node;
    std::unique_ptr<node> subtree_node;

    // Will advance the token stream if the current token is the one specified
    bool match(token_name t)
    {
        if(local_env->getToken().name == t)
        {
            local_env->nextToken();
            return true;
        }
        else
        {
            return false;
        }
        
    }

    // Will advance the token stream if hte current token is the one specified, it will throw an error if not
    bool expect(token_name t)
    {
        if(match(t))
        {
            return true;
        }
        else
        {
            // TO-DO: An error handler
            cli::log(cli::log_level::error,"Unexpected token");
            return false;
        }
    }

    // === Grammar ===
    /*
    The grammar something like this

    Statement -> Declaration
    Statement -> Assign

    Declaration -> data_type(token) Variable_Declaration
    Variable_Declaration -> confirm(token) identifier(token)

    Assign -> identifier(token) =(token) Expresssion

    Expression -> litteral
    Expression -> identifier
    Expression -> identifier operator(token) identifier
    Expression -> litteral operator(token) litteral

    For the moment I am using an handwritten grammar but I migt write a simple parser generator to make it easier.
    */

   // int 

   // Variable declaration
    void var_decl()
    {
       if(match(token_name::identifier))
       {
           cli::log(cli::log_level::debug, "Matched confirm token");
           // Doesn't match, because we don't want to lose it yet
            cli::log(cli::log_level::debug, "Matched identifier token");
            // btw when I write a variable with a name like namel, the l is for litteral
            auto name = std::make_unique<node>("identifier");
            auto namel = std::make_unique<node>(local_env->lookBehind().value);
            name->addChild(std::move(namel));
            current_node->get()->getChild(current_node->get()->getChildSize() - 1).addChild(std::move(name));
       }
    }
    // Declaration
    bool decl()
    {
        //if(local_env->getToken().name == token_name::data_type && local_env->lookAhead().name == token_name::confirm)
        if(match(token_name::data_type))
        {
            auto typel = std::make_unique<node>(local_env->lookBehind().value);

            if(match(token_name::confirm))
            {
            auto decl = std::make_unique<node>("declaration");
            auto spec = std::make_unique<node>("specifier");
            auto type = std::make_unique<node>("data_type");
            
            type->addChild(std::move(typel));
            spec->addChild(std::move(type));
            decl->addChild(std::move(spec));
            current_node->get()->addChild(std::move(decl));

            var_decl();
            return true;
            }
            local_env->backtrack(); // So function conditions can be met
            return false;
        }
        return false;
    }

    void math_op()
    {
        if(local_env->getToken().name == token_name::math_op)
        {
        
        std::string optype = "";
        std::string at;
        std::string bt;       
        at = tokenToString(local_env->lookBehind().name);
        bt = tokenToString(local_env->lookAhead().name);

        token op = local_env->getToken();

        if(op.value == "+")
        {
            optype = "addition";
        }
        else if (op.value == "-")
        {
        optype = "subtraction";
        }
        else if (op.value == "/")
        {
            optype = "division";
        }
        else if(op.value == "*")
        {
            optype = "multiplication";
        }

        auto operation = std::make_unique<node>(optype);
        auto atype = std::make_unique<node>(at);
        auto btype = std::make_unique<node>(bt);
        auto al = std::make_unique<node>(local_env->lookBehind().value);
        auto bl = std::make_unique<node>(local_env->lookAhead().value);

        atype->addChild(std::move(al));
        btype->addChild(std::move(bl));
        operation->addChild(std::move(atype));
        operation->addChild(std::move(btype));

        current_node->get()->getChild(0).getChild(1).getChild(0).addChild(std::move(operation));

        local_env->nextToken();
        local_env->nextToken();
        math_op();
        //current_node->addChild(std::move(expr));
        }
        else
        {
        }
    }

    // Expression
    void exp()
    {
        auto source = std::make_unique<node>("source"); 
        auto expr = std::make_unique<node>("expression");
       
       if(local_env->getToken().name == token_name::litteral || local_env->getToken().name == token_name::identifier)
       {
           local_env->nextToken();

           if(local_env->getToken().name == token_name::math_op)
           {
               source->addChild(std::move(expr));
               current_node->get()->getChild(0).addChild(std::move(source));
               math_op();
           }
           else
           {
                auto operation = std::make_unique<node>("static"); // static == no operation\

                std::string t = tokenToString(local_env->lookBehind().name);

                auto type = std::make_unique<node>(t);
                auto lit = std::make_unique<node>(local_env->lookBehind().value);

                type->addChild(std::move(lit));
                operation->addChild(std::move(type));
                expr->addChild(std::move(operation));
                source->addChild(std::move(expr));
                current_node->get()->getChild(0).addChild(std::move(source));

                //local_env->nextToken();
                //local_env->nextToken();
           }
       }
       else
       {
       }
    }

    // Assignment
    bool assign()
    {
        // cli::log(cli::log_level::debug,"-- Assign --");
        // Assignment -> identifier(token) =(token) Expression
        // Assignement -> (backtrack) identifier(token) =(token) Expression
        if(match(token_name::identifier) || local_env->lookBehind().name == token_name::identifier)
        {   
            // Declaration and definition
            cli::log(cli::log_level::debug, "Identifier matched here");
            if(local_env->getToken().name == token_name::assign_op)
            {
                // This is the part where you get a pen and paper, because this is some complicated tree stuff
                cli::log(cli::log_level::debug, "Assignement operator matched");
                auto assign = std::make_unique<node>("assignment");
                auto target = std::make_unique<node>("target");
                auto id = std::make_unique<node>("identifier");
                auto idl = std::make_unique<node>(local_env->lookBehind().value);

                id->addChild(std::move(idl));
                target->addChild(std::move(id));
                assign->addChild(std::move(target));
                current_node->get()->addChild(std::move(assign));
                
                local_env->nextToken();
                exp();

                return true;
            }
            // How did this get so far
            if(local_env->lookBehind().name != token_name::identifier || local_env->getToken().name == token_name::lparen)
            {
                local_env->backtrack();
            }
            return false;
        }
        return false;
    }

    // Parameters aren't arguments,
    // Parameters are in function definition
    // Arguments are in function calls 
    void param()
    {
        decl(); // Basically a parameter is just like a declaration, but we put thoses declaration inside Statement->Function->Params, instead of Statement->Declaration
        if(match(token_name::rparen))
        {
            cli::log(cli::log_level::debug,"Closing params");
            expect(token_name::lbracket);
        }
        else if(match(token_name::comma))
        {
            cli::log(cli::log_level::debug,"Found another parameter");
            param();
        }
    }

    bool function()
    {
        // func -> data_type(tkn) identifier(tkn) lparen(tkn) Param
        if(match(token_name::data_type))
        {
            cli::log(cli::log_level::debug,"Suspecting function");
            if(match(token_name::identifier))
            {
                cli::log(cli::log_level::debug,"Confirmed function");
                auto p_function = std::make_unique<node>("function");
                auto p_params = std::make_unique<node>("parameters");
                auto p_spec = std::make_unique<node>("specifier");
                auto p_datatype = std::make_unique<node>("data_type");
                auto p_identifier = std::make_unique<node>("identifier");

                local_env->backtrack();
                auto p_datatypel = std::make_unique<node>(local_env->lookBehind().value);
                auto p_identifierl = std::make_unique<node>(local_env->getToken().value);

                p_datatype->addChild(std::move(p_datatypel));
                p_identifier->addChild(std::move(p_identifierl));
                p_spec->addChild(std::move(p_datatype));
                p_spec->addChild(std::move(p_identifier));
                p_function->addChild(std::move(p_spec));
                local_env->nextToken(); // So it doesn't break the flow

                expect(token_name::lparen);
                cli::log(cli::log_level::debug,"Opening parenthesis found in function definition");
                current_node = &p_params;
                param();

                p_function->addChild(std::move(p_params));
                subtree_node->addChild(std::move(p_function));
                return true;
            }
            else
            {
                cli::log(cli::log_level::debug,"Not a function");
                local_env->backtrack();
                return false;
            }
        }
        return false;
    }

    // Args != Params
    void arg()
    {
        exp();

        if(match(token_name::rparen))
        {
            cli::log(cli::log_level::debug,"Closing args");
        }
        if(match(token_name::comma))
        {
            cli::log(cli::log_level::debug,"Found another argument");
            arg();
        }
    }

    bool function_call()
    {
        //cli::log(cli::log_level::debug,"-- Call --");
        if(match(token_name::identifier))
        {
            cli::log(cli::log_level::debug,"Matched identifier for function call");
            if(match(token_name::lparen)) 
            {
                cli::log(cli::log_level::debug,"Matched function call");

                auto fcall = std::make_unique<node>("function_call");
                auto args = std::make_unique<node>("arguments");
                auto id = std::make_unique<node>("identifier");

                local_env->backtrack();
                auto idl = std::make_unique<node>(local_env->lookBehind().value);
                local_env->nextToken();

                id->addChild(std::move(id));
                fcall->addChild(std::move(args));
                fcall->addChild(std::move(idl));

                current_node = &fcall;
                arg();
                subtree_node->addChild(std::move(fcall));
                return true;
            }
            local_env->backtrack();
            return false;
        }
        return false;
    }

    bool entry()
    {
        if(match(token_name::entry))
        {
            cli::log(cli::log_level::debug,"Entry point detected");
            auto entry = std::make_unique<node>("entry");
            auto params = std::make_unique<node>("parameters");
            cli::log(cli::log_level::debug,"Entry point detected");

            expect(token_name::lparen);
            current_node = &params;
            param();

            entry->addChild(std::move(params));
            subtree_node->addChild(std::move(entry));
            return true;
        }
        return false;
    }

    void inAsm()
    {
        if(match(token_name::asm_code))
        {
            current_node->get()->value += local_env->lookBehind().value;
            inAsm();
        }
    }

    bool assembly()
    {
        if(local_env->getToken().name == token_name::asm_code)
        {
            auto assembly = std::make_unique<node>("assembly");
            auto code = std::make_unique<node>(" ");
            current_node = &code;
            inAsm();
            assembly->addChild(std::move(code));
            subtree_node->addChild(std::move(assembly));
            return true;
        }
        return false;
    }

    // Condition
    void Cond()
    {
        auto condition = std::make_unique<node>("");

        exp();

        // Advances to know the type of comparaison
        // then goes back so it can parse the expressions
        if(match(token_name::equal_op))
        {
            if(match(token_name::equal_op))
            {
                condition->value = "equal";

                local_env->backtrack();
                local_env->backtrack();

                exp();

                local_env->nextToken();
                local_env->nextToken();

                if(match(token_name::rparen))
                {
                    expect(token_name::lbracket);
                }
            }
        }
    }

    // If statement
    bool If()
    {
        if(match(token_name::if_keyword))
        {
            expect(token_name::lparen);
            auto If = std::make_unique<node>("if_statement");

            return false;
        }
        return false;
    }

    // Statement
    void stat()
    {
        cli::log(cli::log_level::debug,"-- Statement --");
        // Statement -> Declaration
        // Statement -> Assignment
        auto& rootptr = local_tree->getRoot();
        subtree_node = std::make_unique<node>("statement");
        current_node = &subtree_node;

        if(decl())
        {
            rootptr.addChild(std::move(*current_node));

            if(local_env->lookAhead().name == token_name::end_of_string)
            {
                local_env->nextToken();
            }
            cli::log(cli::log_level::debug,"-- declaration --");
        }
        else if(assign())
        {
            rootptr.addChild(std::move(*current_node));
            cli::log(cli::log_level::debug,"-- assign --");
        }
        else if(entry())
        {
            rootptr.addChild(std::move(subtree_node));
            cli::log(cli::log_level::debug,"-- entry --");
        }
        else if(assembly())
        {
            rootptr.addChild(std::move(subtree_node));
            cli::log(cli::log_level::debug,"-- assembly --");
        }
        else if(function())
        {
            rootptr.addChild(std::move(subtree_node));
            //subtree_node = std::make_unique<node>("statement");
            //std::unique_ptr<node>* test;
            cli::log(cli::log_level::debug,"-- function --");
        }
        else if(function_call())
        {
            rootptr.addChild(std::move(subtree_node));
            cli::log(cli::log_level::debug,"-- call --");
        }
        else if(If())
        {
            rootptr.addChild(std::move(subtree_node));
            cli::log(cli::log_level::debug,"-- if --");
        }
        else if(match(token_name::rbracket))
        {
            auto close = std::make_unique<node>("closing_bracket");
            subtree_node->addChild(std::move(close));
            rootptr.addChild(std::move(subtree_node));
            cli::log(cli::log_level::debug,"-- rbracket --");
        }
        else
        {
            if(match(token_name::end_of_string))
            {
                cli::log(cli::log_level::debug, "Reached end");
            }
            else
            {
                cli::log(cli::log_level::error, "Unrecognized statement, with token value:" + local_env->getToken().value); 
                local_env->nextToken(); // Not to get stuck
            }
        }
    }

    void parse(parser* p,tree* t)
    {
        cli::log(cli::log_level::debug,"--===-- SYNTAX ANALYSIS --===--");
        auto root = std::make_unique<node>("root");
        t->setRoot(std::move(root));

        local_tree = t;
        local_env = p;

        std::string last = "";
        int stuck = 0;

        // For the moment can only parse one statement
        while(local_env->getToken().name != token_name::end_of_string)
        {
            stat();
        }
        // rootptr.addChild(std::move(statement));
    }
}
