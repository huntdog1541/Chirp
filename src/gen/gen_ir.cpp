/*
Phase 4: Intermediate representation generation

This generates an intermediate reprensation that will then be used to generate the real
assembly target code.
*/
#include "gen_ir.h"

#include "../cli/log.h"

namespace gen
{
    std::vector<ir::operation> make_ir(tree* ast)
    {
        cli::log(cli::log_level::debug,"--===-- IR GENERATION --===--");
        std::vector<ir::operation> ir;
        std::vector<node*> path;

        path = ast->traverse();

        for(auto n : path)
        {
            //std::cout<<n->value<<std::endl;
            if(n->value == "declaration")
            {
                auto& a_type = n->getChild(0);
                auto& a_name = n->getChild(1);

                ir::operation dec(ir::op::declaration);
                dec.set("type",a_type.value);
                dec.set("name",a_name.value);
                ir.push_back(dec);
            }
            if(n->value == "assignment")
            {
                std::string a_id = n->getChild(0).getChild(0).value;
                std::string a_vtype = n->getChild(1).getChild(0).value;
                std::string a_value = n->getChild(1).getChild(0).getChild(0).value;

                // Godamn I love logging
                cli::log(cli::log_level::debug,"Analysed assignment AST");
                cli::log(cli::log_level::debug,"target:" + a_id);
                cli::log(cli::log_level::debug,"source type:" + a_vtype);
                cli::log(cli::log_level::debug,"source:" + a_value);

                ir::operation assign(ir::op::assignment);
                assign.set("target",a_id);
                assign.set("source_type",a_vtype);
                assign.set("source",a_value);
                ir.push_back(assign);
            }
        }

        return ir;
    }
}
