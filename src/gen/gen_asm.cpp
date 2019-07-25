/*
Phase 5: Assembly code generation

This takes the intermediate code, and turns it into assembly. Also this is the most fun part of the code to work on.
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

    std::string getRegister()
    {
        std::string result;

        std::string bp = assembly::getReg("bp");
        result = "[" + bp + "-" + std::to_string(this->position) + "]";

        return result;
    }
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

// === CODE GENERATION ===

namespace gen
{
    void make_declaration(ir::operation* op)
    {
        cli::log(cli::log_level::debug,"Registering variable");

        object var;
        std::string typel; // type litteral

        typel = op->getProperty("type")->value;
        var.name = op->getProperty("name")->value;

        if(typel == "int")
        {
            var.type = type_size::interger;
            last_pos += type_size::interger;
        }
        else
        {
            cli::log(cli::log_level::error,"Couldn't register object " + var.name + ", type " + typel + "is unrecognized.");
        }
        

        var.position = last_pos;
        var.scope_height = height;

        scope.push_back(var);
    }
    std::string make_assignement(ir::operation* op)
    {
        std::string result;

        object* target;
        target = getObjectByName(op->getProperty("target")->value);

        if(op->getProperty("source_type")->value == "litteral")
        {
            cli::log(cli::log_level::debug,"Litteral found");
            result = assembly::mov(target->getRegister(),op->getProperty("source")->value);
        }

        cli::log(cli::log_level::debug,"Result of variable assignement is:\n<===> \n" + result + "<===>");

        return result;
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
                make_declaration(&op);
            }
            if(op.type == ir::op::assignment)
            {
                res += make_assignement(&op);
            }
        }

        return res;
    }
}