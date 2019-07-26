/*
This does assembly related stuff
*/

#include <string>

namespace assembly
{
    std::string getReg(std::string);
    // Memory
    std::string push(std::string);
    std::string mov(std::string,std::string);
    std::string pop(std::string);
    std::string ret();
    // Math
    std::string add(std::string,std::string);
    std::string sub(std::string,std::string);
    std::string mul(std::string,std::string);
    std::string div(std::string,std::string);
}