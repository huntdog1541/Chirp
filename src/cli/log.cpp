#include "log.h"

namespace cli
{
    std::string writeColor(const int color, const std::string& text)
    {
        std::string result = "\u001b[";
        
        if(color == BLACK)
        {
            result += "30m";
        }
        else if(color == WHITE)
        {
            result += "37m";
        }
        else if(color == RED)
        {
            result += "31m";
        }
        else if(color == YELLOW)
        {
            result += "33m";
        }
        else if(color == GREEN)
        {
            result += "32m";
        }

        result += text;
        result += " \u001b[0m"; // Reset code

        return result;
    }
    
    void log(const int level, const std::string& message)
    {
        if(level == LOG)
        {
            std::cout<<"LOG: "<<message<<std::endl;
        }
        else if(level == WARNING)
        {
            std::cout<<writeColor(YELLOW,"WARNING: ")<<message<<std::endl;
        }
        else if(level == ERROR)
        {
            std::cout<<writeColor(RED,"ERROR: ")<<message<<std::endl;
        }
        else if(level == SUCCESS)
        {
            std::cout<<writeColor(GREEN,"SUCCESS: ")<<message<<std::endl;
        }
    }
}
