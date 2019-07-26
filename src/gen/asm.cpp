#include "asm.h"

#include "../cli/log.h"

namespace assembly
{
    std::string getReg(std::string reg)
    {
        std::string res;

        if(reg == "bp")
        {
            res = "rbp";
        }
        else if(reg == "ax")
        {
            res = "rax";
        }
        else if(reg == "sp")
        {
            res = "rsp";
        }
        else
        {
            cli::log(cli::log_level::warning,"(ASM GEN) Unrecognized register " + reg);
            res = "unrecognized_register";
        }

        return res;
    }
    std::string push(std::string source)
    {
        return "push " + source  + "\n";
    }
    std::string mov(std::string target, std::string source)
    {
        return "mov " + target + ", " + source + "\n";
    }
    std::string pop(std::string reg)
    {
        return "pop " + reg + "\n";
    }
    std::string ret()
    {
        // wow this is so incredibly useless lmao
        return "ret \n";
    }
    std::string add(std::string a, std::string b)
    {
        return "add " + a + ", " + b + "\n";
    }
    std::string sub(std::string a, std::string b)
    {
        return "sub " + a + ", " + b + "\n";
    }
    std::string mul(std::string a, std::string b)
    {
        return "mul " + a + ", " + b + "\n";
    }
    std::string div(std::string a,std::string b)
    {
        return "div " + a + ", " + b + "\n";
    }
}