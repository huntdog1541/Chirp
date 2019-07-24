/*
Intermediate code
This declare the intermediate code, but doesn't generate it. This is like the relation between the parser and syntax files.

The intermediate code doesn't exist as a string, but just as a vector of operation classes.
*/
#pragma once

#include <vector>
#include <string>

enum class op{declaration};

class operation
{
    op type;
    std::vector<std::string> args;
};