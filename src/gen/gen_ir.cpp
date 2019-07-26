/*
Phase 4: Intermediate representation generation

This generates an intermediate reprensation that will then be used to generate the real
assembly target code.
*/
#include "gen_ir.h"

#include "../cli/log.h"

namespace gen
{
    std::vector<ir::operation> make_ir(tree* p_tree)
    {
        cli::log(cli::log_level::debug,"--===-- IR GENERATION --===--");
        std::vector<ir::operation> ir;
        std::vector<node*> path;

        path = p_tree->traverse();

        for(auto n : path)
        {
            //std::cout<<n->value<<std::endl;
            if(n->value == "declaration")
            {
                auto& p_type = n->getChild(0).getChild(0).getChild(0);
                auto& p_name = n->getChild(1).getChild(0);

                cli::log(cli::log_level::debug,"Variable declaration found");
                cli::log(cli::log_level::debug,"type: " + p_type.value);
                cli::log(cli::log_level::debug,"name: " + p_name.value);

                ir::operation dec(ir::op::declaration);
                dec.set("type",p_type.value);
                dec.set("name",p_name.value);
                ir.push_back(dec);
            }
            if(n->value == "assignment")
            {
                // You should really get a pen and paper to follow this (and gdb too look at the tree)
                std::string p_id = n->getChild(0).getChild(0).getChild(0).value; // n->target->identifier->a
                std::string p_vtype = n->getChild(1).getChild(0).getChild(0).value; //  n->source->expression->static
                std::string p_value = n->getChild(1).getChild(0).getChild(0).getChild(0).getChild(0).value; // n->source->expression->static->litteral->123

                if(p_vtype != "static")
                {
                    p_vtype = "math";
                    p_value = "";

                    for(auto& a_op : *n->getChild(1).getChild(0).getAllChilds()) // assignment->source->expression->...
                    {
                        ir::operation op(ir::op::math_operation);

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

                        ir.push_back(op);
                    }
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
        }

        return ir;
    }
}
