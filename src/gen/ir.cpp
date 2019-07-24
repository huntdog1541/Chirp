<<<<<<< Updated upstream
#include "ir.h"
=======
#include "ir.h"

#include <stdarg.h>

namespace ir
{

// === Operation class definition ===

operation::operation(op t)
{
    this->type = t;
}

void operation::set(std::string name, std::string value)
{
    if(hasProperty(name))
    {
        getProperty(name)->value = value;
    }
    else 
    {
        property p;
        p.name = name;
        p.value = value;
        this->arguments.push_back(p);
    }
}

bool operation::hasProperty(std::string name)
{
    bool res = false;

    for(auto prop : this->arguments)
    {
        if(prop.name == name)
        {
            res = true;
        }
    }

    return res;
}

property* operation::getProperty(std::string name)
{
    property* res;

    for(auto& prop : this->arguments)
    {
        if(prop.name == name)
        {
            res = &prop;
        }
    }

    return res;
}

}
>>>>>>> Stashed changes
