/*
Phase 5: Assembly code generation

This takes the intermediate code, and turns it into assembly.
*/
#include "gen_asm.h"

#include "../cli/log.h"

// === OBJECT MANAGEMENT ===

enum type_size {
    interger = 4,
    character = 1,
    boolean = 1 
}; // can't change if you want to add a class(that has a specific )

class object
{
    public:
    std::string name;
    std::string value;
    int position;
    int scope_height;
    type_size type;
};

int last_pos;

int height; // scope height, is weird
std::vector<object> scope; // avaible objects in scope

bool objectExist(std::string name)
{
    bool res = false;

    for(auto& obj : scope)
    {
        if(obj.name == name)
        {
            res = true;
        }
    }

    return res;
}

object* getObjectByName(std::string name)
{
    object* result;

    for(auto& obj : scope)
    {
        if(obj.name == name)
        {
            result = &obj;
        }
    }

    return result;
}

// === GENERATION CODE ===

namespace gen
{
    void make_declaration(ir::operation op)
    {
        cli::log(cli::log_level::debug,"Registering variable");

        object var;
        std::string typel; // type litteral

        var.name = op.getProperty("name")->value;

        if(typel == "int")
        {
            var.type = type_size::interger;
            last_pos += type_size::interger;
        }

        var.position = last_pos;
        var.scope_height = height;

        scope.push_back(var);
    }
    std::string make_asm(std::vector<ir::operation> code)
    {
        std::string res = "";
        last_pos = 0;
        height = 0;

        for(auto op : code)
        {
            if(op.type == ir::op::declaration)
            {
                make_declaration(op);
            }
        }

        return res;
    }
}