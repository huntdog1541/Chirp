#include "ir.h"
#include "../parser/tree.h"

namespace gen
{
    /*
    Uses AST as input, and outputs intermediate code
    */
    std::vector<operation> make_ir(tree*);
}