#include "log.h"

namespace cli
{
    #ifdef __WIN32
    void writeColor(int,std::string)
    {
        // To do
    }
    #else
    std::string writeColor(int color,std::string text)
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

        result += text;
        result += " \u001b[0m"; // Reset code

        return result;
    }
    #endif
    void log(int level,std::string messsage)
    {
        if(level == LOG)
        {
            std::cout<<"LOG: "<<messsage<<std::endl;
        }
        else if(level == WARNING)
        {
            std::cout<<writeColor(YELLOW,"WARNING: ")<<messsage<<std::endl;
        }
        else if(level == ERROR)
        {
            std::cout<<writeColor(RED,"ERROR: ")<<messsage<<std::endl;
        }
    }
}