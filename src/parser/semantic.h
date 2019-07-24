#pragma once

#include "tree.h"

namespace semantic
{
    // Any object in the environement
    class object
    {
        std::string identifier;
        std::string value;
        int size;
        int position;
    };
    /*
    Environement for semantic analysis
    */
    class env
    {
    public:
    tree ast; // abstract syntax tree
    std::vector<object> objects;
    };
    
    env analyze(tree*);
}