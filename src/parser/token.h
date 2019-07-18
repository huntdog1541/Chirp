/*
This file is used to declare the token class
*/

#include <string>

class token
{
    public:
    token();
    token(std::string,std::string);
    std::string name;
    std::string value;
};