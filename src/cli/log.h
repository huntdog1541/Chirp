#include <iostream>
#include <string>

#define LOG 0
#define WARNING 1
#define ERROR 2
#define SUCCESS 3

#define BLACK 0
#define WHITE 1
#define RED 2
#define YELLOW 3
#define GREEN 4

namespace cli
{
    std::string writeColor(const int,const std::string&);
    /*
    Logs a message to the console. Uses 3 different level of status,
    
    LOG: Writes message in default color
    WARNING: Writes message in yellow
    ERROR: Writes message in red
    */
    void log(const int,const std::string&);
}
