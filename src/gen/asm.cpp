#include "asm.h"

namespace assembly
{
    std::string push(std::string source)
    {
        return "push " + source  + "\n";
    }
}