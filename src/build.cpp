#include "build.h"
#include "preprocessor.h"
#include "log.h"

#include <iostream>

void compile(std::string source)
{
    std::vector<std::string> prep = preprocess(source);
    cli::log(SUCCESS,"Nothing wen't wrong, and this is all it can do right now");
}

void build()
{

}