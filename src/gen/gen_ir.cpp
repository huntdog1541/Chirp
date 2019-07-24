/*
Phase 4: Intermediate code generation

This generates an intermediate code that will then be used to generate the real
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
            if(n->value == "declaration")
            {
                auto& a_type = n->getChild(0);
                auto& a_name = n->getChild(1);

                ir::operation dec(ir::op::declaration);
                dec.set("type",a_type.value);
                dec.set("name",a_name.value);
            }
        }

        return ir;
    }
}
