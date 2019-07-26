/*
Intermediate code
This declare the intermediate code, but doesn't generate it. This is like the relation between the parser and syntax files.
*/
//  
#pragma once

#include <vector>
#include <string>

namespace ir
{
    enum class op{declaration,assignment,math_operation,function_begin,function_end};

    class property
    {
        public:
        std::string name;
        std::string value;
    };

    class operation
    {
        public:
        // Basic constructor
        operation(op);

        // Sets property with specific name, to specific value. If it doesn't exist, will create one
        void set(std::string,std::string);

        // Returns true if property with given name exists 
        bool hasProperty(std::string);

        // Returns property with given name
        property* getProperty(std::string);
        op type;
        std::vector<property> arguments;
    };
}
