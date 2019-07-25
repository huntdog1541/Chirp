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
}