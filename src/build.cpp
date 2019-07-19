#include "build.h"
#include "preprocessor.h"

#include <iostream>

void compile(std::string source)
{
    std::vector<std::string> prep = preprocess(source);

    for(auto w: prep)
    {
        std::cout<<w<<std::endl;
    }
}

void build()
{

}