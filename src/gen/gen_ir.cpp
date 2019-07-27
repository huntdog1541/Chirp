/*
Phase 4: Intermediate representation generation

This generates an intermediate reprensation that will then be used to generate the real
assembly target code.
*/
#include "gen_ir.h"

#include "../cli/log.h"

void make_exp(node* n,std::vector<ir::operation>* ir)
{
    //std::vector<ir::operation> result;
    // *n->getChild(1).getChild(0).getAllChilds()
    for(auto& a_op : *n->getAllChilds()) // assignment->source->expression->...
    {
        ir::operation op(ir::op::math_operation);

        cli::log(cli::log_level::debug,"First source is " + a_op->getChild(0).getChild(0).value);

        op.set("first_type",a_op->getChild(0).value);
        op.set("first_value", a_op->getChild(0).getChild(0).value);

        op.set("second_type",a_op->getChild(1).value);
        op.set("second_value", a_op->getChild(1).getChild(0).value);

        if(a_op->value == "addition")
        {
            op.set("type","add");
        }
        else if(a_op->value == "subtraction")
        {
            op.set("type","sub");
        }
        else if(a_op->value == "multiplication")
        {
            op.set("type","mul");
        }
        else if(a_op->value == "division")
        {
            op.set("type","div");
        }

        ir->push_back(op);
    }
    //return result;
}

namespace gen
{
    //bool inFunc = false;
    int scopeHeight = 0;
    std::vector<ir::operation> make_ir(tree* p_tree)
    {
        cli::log(cli::log_level::debug,"--===-- IR GENERATION --===--");
        std::vector<ir::operation> ir;
        std::vector<node*> path;

        path = p_tree->traverse();

        for(auto node : path)
        {
            if(node->value == "statement")
            { // rip identation
            auto& n = node->getChild(0);
            if(n.value == "declaration")
            {
                auto& p_type = n.getChild(0).getChild(0).getChild(0);
                auto& p_name = n.getChild(1).getChild(0);

                cli::log(cli::log_level::debug,"Variable declaration found");
                cli::log(cli::log_level::debug,"type: " + p_type.value);
                cli::log(cli::log_level::debug,"name: " + p_name.value);

                ir::operation dec(ir::op::declaration);
                dec.set("type",p_type.value);
                dec.set("name",p_name.value);
                ir.push_back(dec);
            }
            if(n.value == "assignment")
            {
                // You should really get a pen and paper to follow this (and gdb too look at the tree)
                std::string p_id = n.getChild(0).getChild(0).getChild(0).value; // n->target->identifier->a
                std::string p_vtype = n.getChild(1).getChild(0).getChild(0).value; //  n->source->expression->static
                std::string p_value = n.getChild(1).getChild(0).getChild(0).getChild(0).getChild(0).value; // n->source->expression->static->litteral->123

                if(p_vtype != "static")
                {
                    p_vtype = "math";
                    p_value = "";

                    make_exp(&n.getChild(1).getChild(0),&ir);
                    //ir.insert(ir.begin(),exp.begin(),exp.end());
                }

                // Godamn I love logging
                cli::log(cli::log_level::debug,"Analysed assignment parse tree");
                cli::log(cli::log_level::debug,"target:" + p_id);
                cli::log(cli::log_level::debug,"source type:" + p_vtype);
                cli::log(cli::log_level::debug,"source:" + p_value);

                ir::operation assign(ir::op::assignment);
                assign.set("target",p_id);
                assign.set("source_type",p_vtype);
                assign.set("source",p_value);
                ir.push_back(assign);
            }
            if(n.value == "entry")
            {
                scopeHeight++;

                ir::operation func(ir::op::function_begin);
                func.set("type","none");
                func.set("name","_start");
                ir.push_back(func);
            }
            if(n.value == "function")
            {
                //inFunc = true;
                scopeHeight++;

                auto& p_spec = n.getChild(0);
                auto& p_datatype = n.getChild(0).getChild(0);
                auto& p_id = n.getChild(0).getChild(1);
                auto& p_datatypel = n.getChild(0).getChild(0).getChild(0);
                auto& p_idl = n.getChild(0).getChild(1).getChild(0);

                cli::log(cli::log_level::debug,"Analyzed function parse tree");
                cli::log(cli::log_level::debug,"return type: " + p_datatypel.value);
                cli::log(cli::log_level::debug,"identifier: " + p_idl.value);

                ir::operation func(ir::op::function_begin);
                func.set("type",p_datatypel.value);
                func.set("name",p_idl.value);
                ir.push_back(func);

                // Must be after function start
                for(auto& p_param : *n.getChild(1).getAllChilds()) // declare a new variable for each declaration
                {
                    ir::operation var(ir::op::declaration);
                    var.set("type",p_param->getChild(0).getChild(0).getChild(0).value);
                    var.set("name",p_param->getChild(1).getChild(0).value);
                    ir.push_back(var);
                }
            }
            if(n.value == "function_call")
            {
                cli::log(cli::log_level::debug,"Generating IR for function call");

                ir::operation call(ir::op::function_call);
                std::string p_id = n.getChild(1).value;

                call.set("name",p_id);

                for(auto&p_arg : *n.getChild(0).getAllChilds())
                {
                    //std::cout<<p_arg->value<<std::endl;
                    ir::operation arg(ir::op::push_arg);
                    std::string p_vtype = p_arg->getChild(0).getChild(0).value;
                    std::string p_value = p_arg->getChild(0).getChild(0).getChild(0).getChild(0).value;

                    if(p_vtype != "static")
                    {
                        p_vtype = "math";
                        p_value = "";
                        make_exp(p_arg.get(),&ir);
                    }

                    arg.set("source_type", p_vtype);
                    arg.set("source",p_value);

                    ir.push_back(arg);
                }
                
                ir.push_back(call);
            }
            if(n.value == "closing_bracket")
            {
                scopeHeight--;
                if(scopeHeight == 0)
                {
                    ir::operation close(ir::op::function_end);
                    ir.push_back(close);
                }
            }
            }
        }

        return ir;
    }
}
