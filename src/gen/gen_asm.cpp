/*
Phase 5: Assembly code generation

This takes the intermediate reprensentation, and turns it into assembly. Also this is the most fun part of the code to work on.
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

// Removes the items that are out of scope from the scope vector
void updateScope()
{
    int count = 0;

    auto begin = scope.begin();
    auto end = scope.end();

    for(auto it = begin; it != end; ++it)
    {
        if(it->scope_height > height)
        {
            scope.erase(it);
            count++;
        }
    }

    cli::log(cli::log_level::debug,"Updated scope, " + std::to_string(count) + " items deleted.");
}

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
    bool found = false;

    for(auto& obj : scope)
    {
        if(obj.name == name)
        {
            result = &obj;
            found = true;
        }
    }

    if(!found)
    {
        cli::log(cli::log_level::error,"Unrecognized object " + name);
        //result->name = "unknown";
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
        else if(typel == "char")
        {
            var.type = type_size::character;
            last_pos += type_size::character;
        }
        else if(typel == "bool")
        {
            var.type = type_size::boolean;
            last_pos += type_size::boolean;
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

    //    if(target->name == "unknown") // yea this sure isn't a weird limitation right
    //    {
    //        cli::log(cli::log_level::error,"Tried to assign unrecognized object");
    //    }

        if(op->getProperty("source_type")->value == "static")
        {
            cli::log(cli::log_level::debug,"Litteral found");

            std::string source = op->getProperty("source")->value;
            std::string value;

            // This is basically doing what the code in the lexer did
            if(source.at(0) == '\'')
            {
                // Character
                value = std::to_string(int(source.at(1)));
                // std::cout<<value<<std::endl;
            }
            else if(source == "true" || source == "false")
            {
                // Boolean
                if(source == "true")
                {
                    value = "1";
                }
                else
                {
                    value = "0";
                }
            }
            else
            {
                // Number
                value = source;
            }

            result = assembly::mov(target->getRegister(),value);
        }
        else if(op->getProperty("source_type")->value == "identifier")
        {
            std::string id = op->getProperty("source")->value;

            if(objectExist(id))
            {
                object* source = getObjectByName(id);
                result = assembly::mov(target->getRegister(),source->getRegister());
            }
            else
            {
                cli::log(cli::log_level::error,"Cannot reach object " + id + "object is either non-existing or out of scope");
            }
            
        }
        else if(op->getProperty("source_type")->value == "math")
        {
            result = assembly::mov(target->getRegister(), assembly::getReg("ax"));
        }

        cli::log(cli::log_level::debug,"Result of variable assignement is:\n<===> \n" + result + "<===>");

        return result;
    }
    // add,sub,mul,div
    std::string make_math(ir::operation* op)
    {
        std::string res;

        std::string type = op->getProperty("type")->value;

        std::string first_type = op->getProperty("first_type")->value;
        std::string first_value = op->getProperty("first_value")->value;

        std::string second_type = op->getProperty("second_type")->value;
        std::string second_value = op->getProperty("second_value")->value;

        if(first_type == "identifier")
        {
            first_value = getObjectByName(first_value)->getRegister();
        }

        if(second_type == "identifier")
        {
            second_value = getObjectByName(second_value)->getRegister();
        }

        if(type == "add"){
            res += assembly::mov(assembly::getReg("ax"), first_value);
            res += assembly::add(assembly::getReg("ax"), second_value);
        }
        else if (type == "sub"){
            res += assembly::mov(assembly::getReg("ax"), first_value);
            res += assembly::sub(assembly::getReg("ax"), second_value);
        }
        else if (type == "mul"){
            res += assembly::mov(assembly::getReg("ax"), first_value);
            res += assembly::mul(assembly::getReg("ax"), second_value);
        }
        else if(type == "div"){
            res += assembly::mov(assembly::getReg("ax"), first_value);
            res += assembly::div(assembly::getReg("ax"), second_value);
        }

        return res;
    }
    std::string make_func(ir::operation* op)
    {
        std::string res;

        res += op->getProperty("name")->value += ":\n";
        res += assembly::push(assembly::getReg("sp"));
        res += assembly::mov(assembly::getReg("bp"),assembly::getReg("sp"));

        height++;

        return res;
    }
    std::string make_funcEnd(ir::operation* op)
    {
        height--;
        updateScope();

        std::string res;
        res += assembly::pop(assembly::getReg("bp"));
        res += assembly::ret();
        return res;
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
            if(op.type == ir::op::math_operation)
            {
                res += make_math(&op);
            }
            if(op.type == ir::op::function_begin)
            {
                cli::log(cli::log_level::debug,"Generating function");
                res += make_func(&op);
            }
            if(op.type == ir::op::function_end)
            {
                res += make_funcEnd(&op);
            }
        }

        return res;
    }
}